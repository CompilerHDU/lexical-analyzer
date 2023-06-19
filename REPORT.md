# 编译原理实验


## 总述
我们使用C++语言和flex以及bison工具完成了SysY语言的编译工作，整个项目运行环境如下
```bash
C++11
Flex 2.5.4
Bison 2.4.1
Windows(cmd)
```
特别的，如不在Windows系统下运行本编译脚本，则需要安装Linux对应的Flex和Bison工具，然后再Linux中断操作即可

另外，我们将SysY编译到了ARM-v7(非最新版ARM指令，最新版ARM-v8)的指令集上


不同于实验平台上的平时作业，我们的编译器大作业使用C++和flex以及bison的联合使用

**使用方法**
先使用预置的Makefile使用flex和bison工具对我们书写text类型文件进行编译，输出词法分析和语法分析器，然后按照我们制定的标准（词法规范和关键词表、ARM-v7的语法定义等等）对手写文件进行编译测试

Makefile中内容如下
```cmake
CC := g++
CFLAGS := -Wall -Wextra -std=c++11 -g
TARGET := ./main.exe
.PHONY: all clean main run lex yacc test debug link testscope asm asmc nasm example-code out mytest
all: complier
src/pch.h.gch: src/pch.h
	g++ -x c++-header -o src/pch.h.gch -c src/pch.h
lex:
	flex -o"src\lexer.cpp" src\lexer.l
yacc:
	bison -o"src\parser.cpp" --defines=src\parser.h src\parser.y
main: src/pch.h.gch
	$(CC) $(CFLAGS) src\\*.cpp -o $(TARGET)
complier: lex yacc main
run: complier
clean:
	del /s "src\lexer.cpp" "src\parser.cpp" "src\parser.h" "src\pch.h.gch" "$(TARGET)" "*.o"
	del /s "src\*.output"
	del /s *.exe
```
运行方式是
```bash
make run
```
在编写完测试用例代码后，运行
```bash
./main [path-to-code-file] [> output-file]
```
从而可以看到汇编完成后的代码


## 词法分析
我们直接使用flex / bison中的正则表达式定义，非关键词类型的正则表达式如下
```lex
LOCKCOMMENT_BEGIN "/*"
BLOCKCOMMENT_ELE .
BLOCKCOMMENT_LINE \n
BLOCKCOMMENT_END "*/"
%x BLOCKCOMMENT
LINECOMMENT \/\/[^\n]*
EOL	(\r\n|\r|\n)
WHILTESPACE [[:blank:]]

OCTINT 0[0-7]+
DECINT [0-9]+
HEXINT 0[Xx][0-9a-fA-F]+

BOOL (true)|(false)
STRING \"[^(\")]*\"
CHAR \'\\?.\'

IDENTIFIER [[:alpha:]_][[:alpha:][:digit:]_]*
```
分别代表了前多行注释、点号、换行符、后多行注释以及数字常量的识别模式等等。另外，我们再给出将代码识别为关键字的部分
```lex
"int" return T_INT;
"bool" return T_BOOL;
"char" return T_CHAR;
"void" return T_VOID;

"&" return ADDR;

"(" return LPAREN;
")" return RPAREN;
"[" return LBRACKET;
"]" return RBRACKET;
"{" return LBRACE;
"}" return RBRACE;
"," return COMMA;
";" return SEMICOLON;

"==" return EQ;
">=" return GRAEQ;
"<=" return LESEQ;
"!=" return NEQ;
"=" return ASSIGN;
"+=" return PLUSASSIGN;
"-=" return MINUSASSIGN;
"*=" return MULASSIGN;
"/=" return DIVASSIGN;
"++" return INC;
"--" return DEC;
">" return GRA;
"<" return LES;
"+" return PLUS;
"-" return MINUS;
"*" return MUL;
"/" return DIV;
"%" return MOD;
"&&" return AND;
"||" return OR;
"!" return NOT;

"const" return CONST;
"if" return IF_;
"else" return ELSE;
"while" return WHILE_;
"for" return FOR_;
"break" return BREAK;
"continue" return CONTINUE;
"return" return RETURN;
```
在识别词法的自动机中，如果没有和正则表达式中的非关键词等匹配上的话，将通过这里获得返回值，分别是关键字、运算符号等等；另外，对应"return"类型的名称都已经在cpp源文件中定义

通过这一步可以识别出原始代码中的变量值以及运算符、关键词、id等元素的位置。整步可以概括为：源程序输入词法分析器，通过正则表达、NFA到DFA转换等获取到符号表中的关键词类型，然后将类型和值汇聚成词法单元输送各后续的语法分析器。

## 语法分析
词法分析后得到一系列语法单元，单元存入队列(queue)结构，在此基础进行语法分析；这一步也从符号表中获取基本类型，然后根据词法单元构建语法树，同时进行错误处理。

这里进行语法分析的时候，直接定义语法制导（语义动作），并做DAG分析，直接计算出每个节点上的属性值。

具体的**移入-规约**是在flex / bison工具中完成的，我们只手动定义了语法制导（语义动作）实现属性值的产生和赋值计算，然后直接进行代码的生成。

语法树中各个节点类型定义写在tree.h文件中，如下
```cpp
enum NodeType
{
	NODE_OP,
	NODE_CONST, 
	NODE_VAR,
	NODE_FUNCALL,

	NODE_PROG,
	NODE_STMT,
	NODE_EXPR,
	NODE_TYPE,
	NODE_VARLIST,
	NODE_PARAM,
};

enum OperatorType
{
	OP_EQ,  	// ==
	OP_NEQ, 	// !=
	OP_GRAEQ,	// >=
	OP_LESEQ,	// <=
	OP_ADDASSIGN,	// +=
	OP_SUBASSIGN,	// -=
	OP_MULASSIGN,	// *=
	OP_DIVASSIGN,	// /=
	OP_DECLASSIGN,	// = (仅在常变量声明赋值时使用)
	OP_ASSIGN,	// =
	OP_GRA,		// >
	OP_LES,		// <
	OP_INC,		// ++
	OP_DEC,		// --
	OP_ADD,		// +
	OP_SUB,		// -
	OP_POS,		// + (一元运算符)
	OP_NAG,		// - (一元运算符)
	OP_MUL,		// *
	OP_DIV,		// /
	OP_MOD,		// %
	OP_NOT,		// !
	OP_AND, 	// &&
	OP_OR,		// ||
	OP_INDEX,	// [] 下标运算符
};

enum StmtType {
	STMT_SKIP,
	STMT_BLOCK,
	STMT_DECL,
	STMT_CONSTDECL,
	STMT_FUNCDECL,
	STMT_IFELSE,
	STMT_IF,
	STMT_WHILE,
	STMT_FOR,
	STMT_RETURN,
	STMT_CONTINUE,
	STMT_BREAK,
};

struct Label {
	string true_label;
	string false_label;
	string begin_label;
	string next_label;
};
```
各个关键词以及ID对应的语法制导如下
```lex
"printf" {
    nodePrintf->var_name = "printf";
    nodePrintf->var_scope = "1";
    yylval = nodePrintf;
    return IDENTIFIER;
};
"scanf" {
    nodeScanf->var_name = "scanf";
    nodeScanf->var_scope = "1";
    yylval = nodeScanf;
    return IDENTIFIER;
};

{BOOL} {
    TreeNode* node = new TreeNode(lineno, NODE_CONST);
    node->type = TYPE_BOOL;
    node->b_val = strcmp("false", yytext);
    yylval = node;
    return BOOL;
}

{OCTINT} {
    TreeNode* node = new TreeNode(lineno, NODE_CONST);
    node->type = TYPE_INT;
    node->int_val = strtol(yytext, NULL, 8);
    yylval = node;
    return INTEGER;
}

{DECINT} {
    TreeNode* node = new TreeNode(lineno, NODE_CONST);
    node->type = TYPE_INT;
    node->int_val = atoi(yytext);
    yylval = node;
    return INTEGER;
}

{HEXINT} {
    TreeNode* node = new TreeNode(lineno, NODE_CONST);
    node->type = TYPE_INT;
    node->int_val = strtol(yytext, NULL, 16);
    yylval = node;
    return INTEGER;
}

{CHAR} {
    TreeNode* node = new TreeNode(lineno, NODE_CONST);
    node->type = TYPE_CHAR;
    // 支持转义字符
    if (yytext[1] == '\\') {
        switch (yytext[2]) {
        case 'a':
            node->ch_val = 7;
            break;
        case 'b':
            node->ch_val = 8;
            break;
        case 'f':
            node->ch_val = 12;
            break;
        case 'n':
            node->ch_val = 10;
            break;
        case 'r':
            node->ch_val = 13;
            break;
        case 't':
            node->ch_val = 9;
            break;
        case 'v':
            node->ch_val = 11;
            break;
        case '\\':
            node->ch_val = 92;
            break;
        case '\'':
            node->ch_val = 39;
            break;
        case '"':
            node->ch_val = 34;
            break;
        case '?':
            node->ch_val = 63;
            break;
        default:
            node->ch_val = 0;
            break;
        }
    }
    else {
        node->ch_val = yytext[1];
    }
    yylval = node;
    return CHAR;
}

{STRING} {
    TreeNode* node = new TreeNode(lineno, NODE_CONST);
    node->type = TYPE_STRING;
    string text = yytext;
    node->str_val = text.substr(1, text.length()-2);
    yylval = node;
    return STRING;
}

{IDENTIFIER} {
    TreeNode* node = new TreeNode(lineno, NODE_VAR);
    node->var_name = string(yytext);
    yylval = node;
#ifdef ID_TOKEN_DEBUG
    cout << "% get IDENTIFIER :" << yytext <<endl;
#endif
    return IDENTIFIER;
}

{WHILTESPACE} {}

{EOL} {lineno++;}

. {
    cerr << "[line "<< lineno <<" ] unknown character:" << yytext << endl;
}
```

其中，最后一行 ‘.’对应的是错误处理

## 测试样例

### 例1

#### 输入

```[c++]
int main(){
    printf("test\n");
    return 0;
}
```

#### 输出

```[arm]
# SysY compiler.
	.section	.rodata
.LC0:
	.string	"test\n"
	.text
	.globl	main
	.type	main, @function
main:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$12, %esp
	movl	$.LC0, %eax
	pushl	%eax
	call	printf
	addl	$4, %esp
	movl	$0, %eax
	jmp		.LRET_main
.LRET_main:
	addl	$12, %esp
	popl	%ebp
	ret
```

### 例2

#### 输入

```[c++]
int main(){
    int a=0xffffffff;
    if(a==-1){
        printf("True!\n");
    }else{
        printf("False!\n");
    }
    return 0;
}
```

#### 输出

```[arm]
# SysY compiler.
	.section	.rodata
.LC0:
	.string	"True!\n"
.LC1:
	.string	"False!\n"
	.text
	.globl	main
	.type	main, @function
main:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	movl	$2147483647, %eax
	movl	%eax, -12(%ebp)
.L0:
	movl	-12(%ebp), %eax
	pushl	%eax
	movl	$1, %eax
	negl	%eax
	popl	%ebx
	cmpl	%eax, %ebx
	sete	%al
	je		.L1
	jmp		.L2
.L1:
	movl	$.LC0, %eax
	pushl	%eax
	call	printf
	addl	$4, %esp
	jmp		.L3
.L2:
	movl	$.LC1, %eax
	pushl	%eax
	call	printf
	addl	$4, %esp
.L3:
	movl	$0, %eax
	jmp		.LRET_main
.LRET_main:
	addl	$16, %esp
	popl	%ebp
	ret

```

### 例3

#### 输入

```[c++]
int a;

int myFunc(int a, int b, int c) {
	a = 2;
	{
		int c;
		c = 0;
		if (c != 0) {
			return 0;
		}
	}
	while (b > 0) {
		b = b - 1;
	}
	return (a)+(b);
}

int main() {
	a = (3);
	int b;
	b = myFunc(1, 2, 1);
    printf("%d\n",a+b);
	return 0;
}
```

#### 输出

```[arm]
# SysY compiler.
	.text
	.data
	.align	4
	.globl	a
	.type	a, @object
	.size	a, 4
a:
	.long	0
	.section	.rodata
.LC0:
	.string	"%d\n"
	.text
	.globl	myFunc
	.type	myFunc, @function
myFunc:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	movl	$2, %eax
	movl	%eax, 8(%ebp)
	movl	$0, %eax
	movl	%eax, -12(%ebp)
.L0:
	movl	-12(%ebp), %eax
	pushl	%eax
	movl	$0, %eax
	popl	%ebx
	cmpl	%eax, %ebx
	setne	%al
	jne		.L1
	jmp		.L2
.L1:
	movl	$0, %eax
	jmp		.LRET_myFunc
.L2:
.L3:
	movl	12(%ebp), %eax
	pushl	%eax
	movl	$0, %eax
	popl	%ebx
	cmpl	%eax, %ebx
	setg	%al
	jg		.L4
	jmp		.L5
.L4:
	movl	12(%ebp), %eax
	pushl	%eax
	movl	$1, %eax
	movl	%eax, %ebx
	popl	%eax
	subl	%ebx, %eax
	movl	%eax, 12(%ebp)
	jmp		.L3
.L5:
	movl	8(%ebp), %eax
	pushl	%eax
	movl	12(%ebp), %eax
	popl	%ebx
	addl	%ebx, %eax
	jmp		.LRET_myFunc
.LRET_myFunc:
	addl	$16, %esp
	popl	%ebp
	ret
	.globl	main
	.type	main, @function
main:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	movl	$3, %eax
	movl	%eax, a
	movl	$1, %eax
	pushl	%eax
	movl	$2, %eax
	pushl	%eax
	movl	$1, %eax
	pushl	%eax
	call	myFunc
	addl	$12, %esp
	movl	%eax, -12(%ebp)
	movl	a, %eax
	pushl	%eax
	movl	-12(%ebp), %eax
	popl	%ebx
	addl	%ebx, %eax
	pushl	%eax
	movl	$.LC0, %eax
	pushl	%eax
	call	printf
	addl	$8, %esp
	movl	$0, %eax
	jmp		.LRET_main
.LRET_main:
	addl	$16, %esp
	popl	%ebp
	ret
```

### 例4

#### 输入

```[c++]
int n;
int Merge(int *array, int low, int middle, int high)
{
    int n1;
    n1 = middle - low + 1;
    int n2;
    n2 = high - middle;
    int L[10];
    int R[10];
    int i;
    i = 0;
    int j;
    j = 0;
 
    while(i < n1){
        L[i] = array[i + low];
        i = i + 1;        
    }
    while(j < n2){
        R[j] = array[j + middle  +1];
        j = j + 1;        
    }
    i = 0;
    j = 0;
    int k;
    k = low;
    while(i!=n1 && j!= n2)
    {   
        if(L[i] < R[j] + 1){
            array[k] = L[i];
            k = k + 1;
            i = i + 1;
        }
        else{
            array[k] = R[j];
            k = k + 1;
            j = j + 1;
        }
    }
    while(i < n1){
        array[k] = L[i];
        k = k + 1;
        i = i + 1;
        
    }
    while(j < n2){
        array[k] = R[j];
        k = k + 1;
        j = j + 1;
    }
    return 0;
}
 
int MergeSort(int *array, int p, int q)
{
    if(p < q)
    {
        int mid;
        mid = (p+q)/2;
        int tmp;
        tmp = MergeSort(array, p, mid);
        tmp = mid + 1;
        tmp = MergeSort(array, tmp, q);
        tmp = Merge(array,p, mid, q);
    }
    return 0;
}

int main(){
    n = 10;
    int a[10];
    a[0]=4;a[1]=3;a[2]=9;a[3]=2;a[4]=0;
    a[5]=1;a[6]=6;a[7]=5;a[8]=7;a[9]=8;
    int i;
    i = 0;
    int tmp;
    tmp = n - 1;
    i = MergeSort(a, i, tmp);
    while (i < n) {
        tmp = a[i];
        printf("%d",tmp);
        tmp = 10;
        printf("%c",tmp);
        i = i + 1;
    }
    return 0;
}
```

#### 输出

```[arm]
# SysY compiler.
	.text
	.data
	.align	4
	.globl	n
	.type	n, @object
	.size	n, 4
n:
	.long	0
	.section	.rodata
.LC0:
	.string	"%d"
.LC1:
	.string	"%c"
	.text
	.globl	Merge
	.type	Merge, @function
Merge:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$112, %esp
	movl	16(%ebp), %eax
	pushl	%eax
	movl	12(%ebp), %eax
	movl	%eax, %ebx
	popl	%eax
	subl	%ebx, %eax
	pushl	%eax
	movl	$1, %eax
	popl	%ebx
	addl	%ebx, %eax
	movl	%eax, -12(%ebp)
	movl	20(%ebp), %eax
	pushl	%eax
	movl	16(%ebp), %eax
	movl	%eax, %ebx
	popl	%eax
	subl	%ebx, %eax
	movl	%eax, -16(%ebp)
	movl	$0, %eax
	movl	%eax, -100(%ebp)
	movl	$0, %eax
	movl	%eax, -104(%ebp)
.L0:
	movl	-100(%ebp), %eax
	pushl	%eax
	movl	-12(%ebp), %eax
	popl	%ebx
	cmpl	%eax, %ebx
	setl	%al
	jl		.L1
	jmp		.L2
.L1:
	movl	-100(%ebp), %eax
	pushl	%eax
	movl	12(%ebp), %eax
	popl	%ebx
	addl	%ebx, %eax
	movl	8(%ebp,%eax,4), %eax
	pushl	%eax
	movl	-100(%ebp), %eax
	popl	%ebx
	movl	%ebx, -20(%ebp,%eax,4)
	movl	-100(%ebp), %eax
	pushl	%eax
	movl	$1, %eax
	popl	%ebx
	addl	%ebx, %eax
	movl	%eax, -100(%ebp)
	jmp		.L0
.L2:
.L3:
	movl	-104(%ebp), %eax
	pushl	%eax
	movl	-16(%ebp), %eax
	popl	%ebx
	cmpl	%eax, %ebx
	setl	%al
	jl		.L4
	jmp		.L5
.L4:
	movl	-104(%ebp), %eax
	pushl	%eax
	movl	16(%ebp), %eax
	popl	%ebx
	addl	%ebx, %eax
	pushl	%eax
	movl	$1, %eax
	popl	%ebx
	addl	%ebx, %eax
	movl	8(%ebp,%eax,4), %eax
	pushl	%eax
	movl	-104(%ebp), %eax
	popl	%ebx
	movl	%ebx, -60(%ebp,%eax,4)
	movl	-104(%ebp), %eax
	pushl	%eax
	movl	$1, %eax
	popl	%ebx
	addl	%ebx, %eax
	movl	%eax, -104(%ebp)
	jmp		.L3
.L5:
	movl	$0, %eax
	movl	%eax, -100(%ebp)
	movl	$0, %eax
	movl	%eax, -104(%ebp)
	movl	12(%ebp), %eax
	movl	%eax, -108(%ebp)
.L6:
	movl	-100(%ebp), %eax
	pushl	%eax
	movl	-12(%ebp), %eax
	popl	%ebx
	cmpl	%eax, %ebx
	setne	%al
	jne		.L9
	jmp		.L8
	pushl	%eax
.L9:
	movl	-104(%ebp), %eax
	pushl	%eax
	movl	-16(%ebp), %eax
	popl	%ebx
	cmpl	%eax, %ebx
	setne	%al
	jne		.L7
	jmp		.L8
	popl	%ebx
	andl	%eax, %ebx
	setne	%al
.L7:
.L10:
	movl	-100(%ebp), %eax
	movl	-20(%ebp,%eax,4), %eax
	pushl	%eax
	movl	-104(%ebp), %eax
	movl	-60(%ebp,%eax,4), %eax
	pushl	%eax
	movl	$1, %eax
	popl	%ebx
	addl	%ebx, %eax
	popl	%ebx
	cmpl	%eax, %ebx
	setl	%al
	jl		.L11
	jmp		.L12
.L11:
	movl	-100(%ebp), %eax
	movl	-20(%ebp,%eax,4), %eax
	pushl	%eax
	movl	-108(%ebp), %eax
	popl	%ebx
	movl	%ebx, 8(%ebp,%eax,4)
	movl	-108(%ebp), %eax
	pushl	%eax
	movl	$1, %eax
	popl	%ebx
	addl	%ebx, %eax
	movl	%eax, -108(%ebp)
	movl	-100(%ebp), %eax
	pushl	%eax
	movl	$1, %eax
	popl	%ebx
	addl	%ebx, %eax
	movl	%eax, -100(%ebp)
	jmp		.L13
.L12:
	movl	-104(%ebp), %eax
	movl	-60(%ebp,%eax,4), %eax
	pushl	%eax
	movl	-108(%ebp), %eax
	popl	%ebx
	movl	%ebx, 8(%ebp,%eax,4)
	movl	-108(%ebp), %eax
	pushl	%eax
	movl	$1, %eax
	popl	%ebx
	addl	%ebx, %eax
	movl	%eax, -108(%ebp)
	movl	-104(%ebp), %eax
	pushl	%eax
	movl	$1, %eax
	popl	%ebx
	addl	%ebx, %eax
	movl	%eax, -104(%ebp)
.L13:
	jmp		.L6
.L8:
.L14:
	movl	-100(%ebp), %eax
	pushl	%eax
	movl	-12(%ebp), %eax
	popl	%ebx
	cmpl	%eax, %ebx
	setl	%al
	jl		.L15
	jmp		.L16
.L15:
	movl	-100(%ebp), %eax
	movl	-20(%ebp,%eax,4), %eax
	pushl	%eax
	movl	-108(%ebp), %eax
	popl	%ebx
	movl	%ebx, 8(%ebp,%eax,4)
	movl	-108(%ebp), %eax
	pushl	%eax
	movl	$1, %eax
	popl	%ebx
	addl	%ebx, %eax
	movl	%eax, -108(%ebp)
	movl	-100(%ebp), %eax
	pushl	%eax
	movl	$1, %eax
	popl	%ebx
	addl	%ebx, %eax
	movl	%eax, -100(%ebp)
	jmp		.L14
.L16:
.L17:
	movl	-104(%ebp), %eax
	pushl	%eax
	movl	-16(%ebp), %eax
	popl	%ebx
	cmpl	%eax, %ebx
	setl	%al
	jl		.L18
	jmp		.L19
.L18:
	movl	-104(%ebp), %eax
	movl	-60(%ebp,%eax,4), %eax
	pushl	%eax
	movl	-108(%ebp), %eax
	popl	%ebx
	movl	%ebx, 8(%ebp,%eax,4)
	movl	-108(%ebp), %eax
	pushl	%eax
	movl	$1, %eax
	popl	%ebx
	addl	%ebx, %eax
	movl	%eax, -108(%ebp)
	movl	-104(%ebp), %eax
	pushl	%eax
	movl	$1, %eax
	popl	%ebx
	addl	%ebx, %eax
	movl	%eax, -104(%ebp)
	jmp		.L17
.L19:
	movl	$0, %eax
	jmp		.LRET_Merge
.LRET_Merge:
	addl	$112, %esp
	popl	%ebp
	ret
	.globl	MergeSort
	.type	MergeSort, @function
MergeSort:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$20, %esp
.L20:
	movl	12(%ebp), %eax
	pushl	%eax
	movl	16(%ebp), %eax
	popl	%ebx
	cmpl	%eax, %ebx
	setl	%al
	jl		.L21
	jmp		.L22
.L21:
	movl	12(%ebp), %eax
	pushl	%eax
	movl	16(%ebp), %eax
	popl	%ebx
	addl	%ebx, %eax
	pushl	%eax
	movl	$2, %eax
	movl	%eax, %ebx
	popl	%eax
	cltd
	idivl	%ebx
	movl	%eax, -12(%ebp)
	movl	-12(%ebp), %eax
	pushl	%eax
	movl	12(%ebp), %eax
	pushl	%eax
	movl	8(%ebp), %eax
	pushl	%eax
	call	MergeSort
	addl	$12, %esp
	movl	%eax, -16(%ebp)
	movl	-12(%ebp), %eax
	pushl	%eax
	movl	$1, %eax
	popl	%ebx
	addl	%ebx, %eax
	movl	%eax, -16(%ebp)
	movl	16(%ebp), %eax
	pushl	%eax
	movl	-16(%ebp), %eax
	pushl	%eax
	movl	8(%ebp), %eax
	pushl	%eax
	call	MergeSort
	addl	$12, %esp
	movl	%eax, -16(%ebp)
	movl	16(%ebp), %eax
	pushl	%eax
	movl	-12(%ebp), %eax
	pushl	%eax
	movl	12(%ebp), %eax
	pushl	%eax
	movl	8(%ebp), %eax
	pushl	%eax
	call	Merge
	addl	$16, %esp
	movl	%eax, -16(%ebp)
.L22:
	movl	$0, %eax
	jmp		.LRET_MergeSort
.LRET_MergeSort:
	addl	$20, %esp
	popl	%ebp
	ret
	.globl	main
	.type	main, @function
main:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$60, %esp
	movl	$10, %eax
	movl	%eax, n
	movl	$4, %eax
	pushl	%eax
	movl	$0, %eax
	popl	%ebx
	movl	%ebx, -12(%ebp,%eax,4)
	movl	$3, %eax
	pushl	%eax
	movl	$1, %eax
	popl	%ebx
	movl	%ebx, -12(%ebp,%eax,4)
	movl	$9, %eax
	pushl	%eax
	movl	$2, %eax
	popl	%ebx
	movl	%ebx, -12(%ebp,%eax,4)
	movl	$2, %eax
	pushl	%eax
	movl	$3, %eax
	popl	%ebx
	movl	%ebx, -12(%ebp,%eax,4)
	movl	$0, %eax
	pushl	%eax
	movl	$4, %eax
	popl	%ebx
	movl	%ebx, -12(%ebp,%eax,4)
	movl	$1, %eax
	pushl	%eax
	movl	$5, %eax
	popl	%ebx
	movl	%ebx, -12(%ebp,%eax,4)
	movl	$6, %eax
	pushl	%eax
	movl	$6, %eax
	popl	%ebx
	movl	%ebx, -12(%ebp,%eax,4)
	movl	$5, %eax
	pushl	%eax
	movl	$7, %eax
	popl	%ebx
	movl	%ebx, -12(%ebp,%eax,4)
	movl	$7, %eax
	pushl	%eax
	movl	$8, %eax
	popl	%ebx
	movl	%ebx, -12(%ebp,%eax,4)
	movl	$8, %eax
	pushl	%eax
	movl	$9, %eax
	popl	%ebx
	movl	%ebx, -12(%ebp,%eax,4)
	movl	$0, %eax
	movl	%eax, -52(%ebp)
	movl	n, %eax
	pushl	%eax
	movl	$1, %eax
	movl	%eax, %ebx
	popl	%eax
	subl	%ebx, %eax
	movl	%eax, -56(%ebp)
	movl	-56(%ebp), %eax
	pushl	%eax
	movl	-52(%ebp), %eax
	pushl	%eax
	movl	-12(%ebp), %eax
	pushl	%eax
	call	MergeSort
	addl	$12, %esp
	movl	%eax, -52(%ebp)
.L23:
	movl	-52(%ebp), %eax
	pushl	%eax
	movl	n, %eax
	popl	%ebx
	cmpl	%eax, %ebx
	setl	%al
	jl		.L24
	jmp		.L25
.L24:
	movl	-52(%ebp), %eax
	movl	-12(%ebp,%eax,4), %eax
	movl	%eax, -56(%ebp)
	movl	-56(%ebp), %eax
	pushl	%eax
	movl	$.LC0, %eax
	pushl	%eax
	call	printf
	addl	$8, %esp
	movl	$10, %eax
	movl	%eax, -56(%ebp)
	movl	-56(%ebp), %eax
	pushl	%eax
	movl	$.LC1, %eax
	pushl	%eax
	call	printf
	addl	$8, %esp
	movl	-52(%ebp), %eax
	pushl	%eax
	movl	$1, %eax
	popl	%ebx
	addl	%ebx, %eax
	movl	%eax, -52(%ebp)
	jmp		.L23
.L25:
	movl	$0, %eax
	jmp		.LRET_main
.LRET_main:
	addl	$60, %esp
	popl	%ebp
	ret
```
