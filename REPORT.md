# 编译原理实验

## 一、词法分析

### 方法介绍：

由于这个任务没有很难，我使用了C++实现。

词法分析的主要任务就是将代码分本分割成一个一个的词，然后在对此进行词法分析，

函数结构如下
```cpp
class Lex:
  private sign_char,    //  存储单字符运算符号
          sign_name,    //  允许的运算及其名称
          keywords,     //  关键字 (if/else/while...)
          types,        //  类型 (int,float,double)
          issign,       //  inline函数，判断字符是否在sign_char中

          show,         //  打印常量值、标识符
                /*
                  整型常数 直接读入输出	->	判断识别内容要素是否为合法 
              首元素非数字则判别为标识符、关键字、数据类型	->	判断是否 
                  
                  每行输出格式：
              [line_num(行数计数),  'const_int'|'const_double', value]
              or [line_num(行数计数), keyword] 
                */
          work          //  词法分析判断标识符、常量值等，之后根据代码块具体解释
          

  public  solve         //  读入文件送给private类操作

```
(然后string/char这些类型一开始忘记做了，昨天想加进去结果出了点bug，然后就先不加了)


大致思路概括如下：

1、首先我们构造出合法词表，我设置了
```cpp
string sign_char="+-*/&^%|=?<>!~:,;{}()[]";
```
作为基本符号，不在这个范围内的字符串判为非法字符

以及关键词表
```cpp
set<string>keywords={"if","else","while","for","return","break","continue"};
```
类型词表
```cpp
set<string>types={"int","float","double"};
```
允许的运算符及其名称，识别到不在这个范围内的运算符会引起错误，传给cout流
```cpp
map<string,string>sign_name = {
  {"+","add"},{"-","minus"},{"*","multiply"},{"/","divide"},{"%","module"},{"{","left{"},{"}","right}"},{"(","left("},{")","right)"},{"&","bit_and"},{"|","bit_or"},{"=","assign"},{";","semicolon"},{"&&","ans"},{"||","or"},{"<","less"},{">","greater"},{"<=","leq"},{">=","beq"},{"==","equals"},{"!=","ineq"},{"!","not"},{",","comma"},{"[","left["},{"]","right]"}
		};
```
如果要定义新运算的话，直接在这里加入运算符号就可以，具体计算方式之后添加到语法制导里就可以

2、work处理，穿插非法符号错误处理

3、show打印，穿插常量定义错误处理

下面结合具体代码做一些解释

#### work函数

以字符为单位读入：空字符自动跳过；识别合法运算符（单个），然后看第二位，看加上以后是否合法；其他情况引起错误处理。

每个work传入读入文件中的一行数据（getline），然后按照空格区分（在第一种情况），对每个词逐个判断

```cpp
if(isblank(s[i])){
				// 空格/'\0'... -> 词法单元结束 -> 打印当前词法单元 
				show(t,line_cnt,os);
				t="";		// 清空 -> 下一词法单元 
			}
			else if(issign(s[i])){
				// 符号 
				show(t,line_cnt,os);
				t="";
				string temp(1,s[i]);		//  char -> string (len -> 1) 
				if(s[i]=='|'||s[i]=='&'||s[i]=='<'||s[i]=='>'||s[i]=='!'||s[i]=='='||s[i]=='.'&&i+1<s.length()){
					//   当前读取到的符号为运算符且其后还有字符 
					string temp1=temp;temp1+=s[i+1];
					if(sign_name.find(temp1)!=sign_name.end()) temp+=s[++i];	
					// 判断为合法符号，然后将下一个字符拼接进temp中成为合法符号 
				}
	//			os<<sign_name[temp]<<" : "<<s[i]<<endl;
				string uu = ".";
				if(sign_name.find(temp)==sign_name.end() && !(temp==uu)){
						cout<<"ERROR sign \""<<temp<<"\" in line "<<line_cnt<<endl;cout<<121<<endl;
						throw "ERROR";
				}
				os<<line_cnt<<" ";
				os<<"\'"<<temp<<"\' "<<endl;
			}
			else t+=s[i];
```


然后将通过词法判断的string传入show函数，判断是关键字还是常数类型

#### show函数
对传入的常数（id/整数/浮点数），首字符非数字则判断为关键词（int,else..., '{'这样的符号也是关键词，作为id输出），若为字符，先做十六进制、八进制判断，都不是则为十进制，再做double类型判断

```cpp
void show(const string &s,int line_cnt,ostream &os){
		if(s.empty())return;				// 空字符直接返回 
		os<<line_cnt<<" ";
		if(!isdigit(s[0])){			// 若字符串首字符不是数字，表示它是一个标识符、关键字或类型
			if(types.find(s)!=types.end()) os << "\'" << s << "\' " <<endl;				// 判断为变量类型 
			else if(keywords.find(s)!=keywords.end()) os << "\'" << s << "\' " <<endl;		// 判断为关键字 
			else os << "id " << s << endl;												// 判断为标识符 
		}
		else{
			//  经过上面判断，这里对应首字符为数字的情况，表明其值为常量 
			int x=0, flag = 0, i = 0;
			if(s.length()>1&&(s[1]=='x'||s[1]=='X')&&s[0]=='0') {
				// 长度大于1，x开头，十六进制数，换算成正常十进制数 
				for(i=2;i<s.length();++i){
					if(isdigit(s[i]))x=x*16+s[i]-'0';
					else if(s[i]>='a'&&s[i]<='f') x = x*16 + (s[i]-'a');
					else if(s[i]>='A'&&s[i]<='F') x = x*16 + (s[i]-'A');
					else {
						cout << "Error type A at line " << line_cnt << " : Illegal hexadecimal number -> " << s[i] << endl;cout<<46<<endl;
						throw "ERROR";
						//		十六进制常量读入的错误处理 
					}
				}
	//			os<<"const int(hexadecimal) : "<<s<<" (="<<x<<"d)"<<endl;
			}
			else {
				if(s[0]=='0'&&s.length()>1&&s[1]!='.') {
					// 八进制数 
					for(i=1;i<s.length();++i){
						if(s[i]>='0'&&s[i]<='7') x = x*8 + (s[i] - '0');
						else {
							cout << "Error type A at line " << line_cnt << " : Illegal octal number -> " << s[i] << endl;cout<<59<<endl;
							throw "ERROR";
							// 非法八进制数读入错误处理 
						}
					}
				}
				else{
					// 正常十进制数 
					for(i=0;i<s.size();++i) {
						if(s[i]>='0'&&s[i]<='9') x = x*10 + (s[i] - '0');
						else if(s[i]=='.') {flag = 1;break;}
						else {
							cout << s[i] << endl;
							cout << "Error type A at line " << line_cnt << " : Illegal decimal number -> " << s[i] << endl;cout<<72<<endl;
							throw "ERROR";
						}
					}
				}
			}
			
			if(flag) {
//				cout << "flag!" << endl;
				int tt = 0;
				for(i=i+1;i<s.size();++i) {
					if(s[i]>='0'&&s[i]<='9') tt = 10*tt + (s[i] - '0');
					else {
						cout << "Error sign " << "\"" << s[i] << "\" in line" << line_cnt << endl;cout<<84<<endl;
						throw "ERROR";
					}
				}
				os << "const_double " << x << "." << tt << endl;		//	读入小数都存为double类型 
			}
			else
				os << "const_int " << x << endl;						//	整数常数类型	
		}
	} 
```



### 程序运行方法：

在dev-C++环境下，按F11键直接运行即可，测试样例放在in1.txtx,in2.txt,in3.txt,in4.txt中

#### in1.txt -> out1.txt

```c
int a[2][2]={{1,2},{3,4}};
int b[2][2]={{a[0][0],a[0][1]},{a[1][0],a[1][1]}};
float c = 1.123;
double pi = 3.1415926535;
```

```
1 'int' 
1 id a
1 '[' 
1 const_int 2
1 ']' 
1 '[' 
1 const_int 2
1 ']' 
1 '=' 
1 '{' 
1 '{' 
1 const_int 1
1 ',' 
1 const_int 2
1 '}' 
1 ',' 
1 '{' 
1 const_int 3
1 ',' 
1 const_int 4
1 '}' 
1 '}' 
1 ';' 
2 'int' 
2 id b
2 '[' 
2 const_int 2
2 ']' 
2 '[' 
2 const_int 2
2 ']' 
2 '=' 
2 '{' 
2 '{' 
2 id a
2 '[' 
2 const_int 0
2 ']' 
2 '[' 
2 const_int 0
2 ']' 
2 ',' 
2 id a
2 '[' 
2 const_int 0
2 ']' 
2 '[' 
2 const_int 1
2 ']' 
2 '}' 
2 ',' 
2 '{' 
2 id a
2 '[' 
2 const_int 1
2 ']' 
2 '[' 
2 const_int 0
2 ']' 
2 ',' 
2 id a
2 '[' 
2 const_int 1
2 ']' 
2 '[' 
2 const_int 1
2 ']' 
2 '}' 
2 '}' 
2 ';' 
3 'float' 
3 id c
3 '=' 
3 const_double 1.123
3 ';' 
4 'double' 
4 id pi
4 '=' 
4 const_double 3.1415926535
4 ';' 
```



#### in2.txt -> out2.txt

```c
int main(){
      int i = 1;
      int j = ~1;
      return 0;
}
```

```
ERROR sign "~" in line 3
```

由于在合法符号string中没有`~`，因此被识别出一个词法错误。



#### in3.txt -> out3.txt

```c
int main(){
 int c;
 c= getint();
 printf("%d",c);
 return c;
}
```

```
1 'int' 
1 id main
1 '(' 
1 ')' 
1 '{' 
2 'int' 
2 id c
2 ';' 
3 id c
3 '=' 
3 id getint
3 '(' 
3 ')' 
3 ';' 
4 id printf
4 '(' 
4 id "
4 '%' 
4 id d"
4 ',' 
4 id c
4 ')' 
4 ';' 
5 'return' 
5 id c
5 ';' 
6 '}' 

```



#### in4.txt -> out4.txt
这个来自北大github的一个sysY魔法代码库
```c
const int WIDTH = 100, HEIGHT = 100;

const int VISITED = 0;
const int NO_LEFT_WALL = 1;
const int NO_TOP_WALL = 2;


const int LEFT = 0;
const int RIGHT = 1;
const int TOP = 2;
const int DOWN = 3;

int map[HEIGHT][WIDTH][3];
int image[HEIGHT * 2 + 1][WIDTH * 2 + 1];

int seed;


int rand() {
  seed = (seed * 214013 + 2531011) % 0x40000000;
  if (seed < 0) seed = -seed;
  return seed / 65536 % 0x8000;
}


int get_neighbor(int x[], int y[], int dir) {
  if (dir == LEFT) {
    if (x[0] == 0) return 0;
    x[0] = x[0] - 1;
  } else if (dir == RIGHT) {
    if (x[0] == WIDTH - 1) return 0;
    x[0] = x[0] + 1;
  } else if (dir == TOP) {
    if (y[0] == 0) return 0;
    y[0] = y[0] - 1;
  } else if (dir == DOWN) {
    if (y[0] == HEIGHT - 1) return 0;
    y[0] = y[0] + 1;
  }
  return 1;
}

void remove_wall(int x, int y, int dir) {
  if (dir == LEFT) {
    map[y][x][NO_LEFT_WALL] = 1;
  } else if (dir == RIGHT) {
    map[y][x + 1][NO_LEFT_WALL] = 1;
  } else if (dir == TOP) {
    map[y][x][NO_TOP_WALL] = 1;
  } else if (dir == DOWN) {
    map[y + 1][x][NO_TOP_WALL] = 1;
  }
}

void gen_maze(int x, int y) {
  map[y][x][VISITED] = 1;
  int dirs[4] = {LEFT, RIGHT, TOP, DOWN}, i;
  i = 0;
  while (i < 4) {
    int r = rand() % 4;
    int temp = dirs[i];
    dirs[i] = dirs[r];
    dirs[r] = temp;
    i = i + 1;
  }
  i = 0;
  while (i < 4) {
    int xx[1] = {x}, yy[1] = {y};
    if (get_neighbor(xx, yy, dirs[i]) && !map[yy[0]][xx[0]][VISITED]) {
      remove_wall(x, y, dirs[i]);
      gen_maze(xx[0], yy[0]);
    }
    i = i + 1;
  }
}

void render() {
  int x, y;
  y = 0;
  while (y < HEIGHT) {
    x = 0;
    while (x < WIDTH) {
      if (!map[y][x][NO_LEFT_WALL]) image[y * 2 + 1][x * 2] = 1;
      if (!map[y][x][NO_TOP_WALL]) image[y * 2][x * 2 + 1] = 1;
      image[y * 2][x * 2] = 1;
      x = x + 1;
    }
    y = y + 1;
  }
  y = 0;
  while (y < HEIGHT * 2 + 1) {
    image[y][WIDTH * 2] = 1;
    y = y + 1;
  }
  x = 0;
  while (x < WIDTH * 2 + 1) {
    image[HEIGHT * 2][x] = 1;
    x = x + 1;
  }
}

int main() {
  seed = getint();
  int zoom = getint();
  starttime();
  gen_maze(rand() % WIDTH, rand() % HEIGHT);
  render();
  stoptime();
  starttime();
  putch(80); putch(51); putch(10);
  putint((WIDTH * 2 + 1) * zoom); putch(32);
  putint((HEIGHT * 2 + 1) * zoom); putch(10);
  putint(255); putch(10);
  int y = 0;
  while (y < (HEIGHT * 2 + 1) * zoom) {
    int x = 0;
    while (x < (WIDTH * 2 + 1) * zoom) {
      int xx = x / zoom, yy = y / zoom;
      int r = image[yy][xx] * 255 * x / ((WIDTH * 2 + 1) * zoom);
      int g = image[yy][xx] * 255 * y / ((HEIGHT * 2 + 1) * zoom);
      int b = image[yy][xx] * 255;
      putint(r); putch(32); putint(g); putch(32); putint(b); putch(32);
      x = x + 1;
    }
    putch(10);
    y = y + 1;
  }
  stoptime();
  return 0;
}
```

```
1 id const
1 'int' 
1 id WIDTH
1 '=' 
1 const_int 100
1 ',' 
1 id HEIGHT
1 '=' 
1 const_int 100
1 ';' 
3 id const
3 'int' 
3 id VISITED
3 '=' 
3 const_int 0
3 ';' 
4 id const
4 'int' 
4 id NO_LEFT_WALL
4 '=' 
4 const_int 1
4 ';' 
5 id const
5 'int' 
5 id NO_TOP_WALL
5 '=' 
5 const_int 2
5 ';' 
8 id const
8 'int' 
8 id LEFT
8 '=' 
8 const_int 0
8 ';' 
9 id const
9 'int' 
9 id RIGHT
9 '=' 
9 const_int 1
9 ';' 
10 id const
10 'int' 
10 id TOP
10 '=' 
10 const_int 2
10 ';' 
11 id const
11 'int' 
11 id DOWN
11 '=' 
11 const_int 3
11 ';' 
13 'int' 
13 id map
13 '[' 
13 id HEIGHT
13 ']' 
13 '[' 
13 id WIDTH
13 ']' 
13 '[' 
13 const_int 3
13 ']' 
13 ';' 
14 'int' 
14 id image
14 '[' 
14 id HEIGHT
14 '*' 
14 const_int 2
14 '+' 
14 const_int 1
14 ']' 
14 '[' 
14 id WIDTH
14 '*' 
14 const_int 2
14 '+' 
14 const_int 1
14 ']' 
14 ';' 
16 'int' 
16 id seed
16 ';' 
19 'int' 
19 id rand
19 '(' 
19 ')' 
19 '{' 
20 id seed
20 '=' 
20 '(' 
20 id seed
20 '*' 
20 const_int 214013
20 '+' 
20 const_int 2531011
20 ')' 
20 '%' 
20 const_int 1073741824
20 ';' 
21 'if' 
21 '(' 
21 id seed
21 '<' 
21 const_int 0
21 ')' 
21 id seed
21 '=' 
21 '-' 
21 id seed
21 ';' 
22 'return' 
22 id seed
22 '/' 
22 const_int 65536
22 '%' 
22 const_int 32768
22 ';' 
23 '}' 
26 'int' 
26 id get_neighbor
26 '(' 
26 'int' 
26 id x
26 '[' 
26 ']' 
26 ',' 
26 'int' 
26 id y
26 '[' 
26 ']' 
26 ',' 
26 'int' 
26 id dir
26 ')' 
26 '{' 
27 'if' 
27 '(' 
27 id dir
27 '==' 
27 id LEFT
27 ')' 
27 '{' 
28 'if' 
28 '(' 
28 id x
28 '[' 
28 const_int 0
28 ']' 
28 '==' 
28 const_int 0
28 ')' 
28 'return' 
28 const_int 0
28 ';' 
29 id x
29 '[' 
29 const_int 0
29 ']' 
29 '=' 
29 id x
29 '[' 
29 const_int 0
29 ']' 
29 '-' 
29 const_int 1
29 ';' 
30 '}' 
30 'else' 
30 'if' 
30 '(' 
30 id dir
30 '==' 
30 id RIGHT
30 ')' 
30 '{' 
31 'if' 
31 '(' 
31 id x
31 '[' 
31 const_int 0
31 ']' 
31 '==' 
31 id WIDTH
31 '-' 
31 const_int 1
31 ')' 
31 'return' 
31 const_int 0
31 ';' 
32 id x
32 '[' 
32 const_int 0
32 ']' 
32 '=' 
32 id x
32 '[' 
32 const_int 0
32 ']' 
32 '+' 
32 const_int 1
32 ';' 
33 '}' 
33 'else' 
33 'if' 
33 '(' 
33 id dir
33 '==' 
33 id TOP
33 ')' 
33 '{' 
34 'if' 
34 '(' 
34 id y
34 '[' 
34 const_int 0
34 ']' 
34 '==' 
34 const_int 0
34 ')' 
34 'return' 
34 const_int 0
34 ';' 
35 id y
35 '[' 
35 const_int 0
35 ']' 
35 '=' 
35 id y
35 '[' 
35 const_int 0
35 ']' 
35 '-' 
35 const_int 1
35 ';' 
36 '}' 
36 'else' 
36 'if' 
36 '(' 
36 id dir
36 '==' 
36 id DOWN
36 ')' 
36 '{' 
37 'if' 
37 '(' 
37 id y
37 '[' 
37 const_int 0
37 ']' 
37 '==' 
37 id HEIGHT
37 '-' 
37 const_int 1
37 ')' 
37 'return' 
37 const_int 0
37 ';' 
38 id y
38 '[' 
38 const_int 0
38 ']' 
38 '=' 
38 id y
38 '[' 
38 const_int 0
38 ']' 
38 '+' 
38 const_int 1
38 ';' 
39 '}' 
40 'return' 
40 const_int 1
40 ';' 
41 '}' 
43 id void
43 id remove_wall
43 '(' 
43 'int' 
43 id x
43 ',' 
43 'int' 
43 id y
43 ',' 
43 'int' 
43 id dir
43 ')' 
43 '{' 
44 'if' 
44 '(' 
44 id dir
44 '==' 
44 id LEFT
44 ')' 
44 '{' 
45 id map
45 '[' 
45 id y
45 ']' 
45 '[' 
45 id x
45 ']' 
45 '[' 
45 id NO_LEFT_WALL
45 ']' 
45 '=' 
45 const_int 1
45 ';' 
46 '}' 
46 'else' 
46 'if' 
46 '(' 
46 id dir
46 '==' 
46 id RIGHT
46 ')' 
46 '{' 
47 id map
47 '[' 
47 id y
47 ']' 
47 '[' 
47 id x
47 '+' 
47 const_int 1
47 ']' 
47 '[' 
47 id NO_LEFT_WALL
47 ']' 
47 '=' 
47 const_int 1
47 ';' 
48 '}' 
48 'else' 
48 'if' 
48 '(' 
48 id dir
48 '==' 
48 id TOP
48 ')' 
48 '{' 
49 id map
49 '[' 
49 id y
49 ']' 
49 '[' 
49 id x
49 ']' 
49 '[' 
49 id NO_TOP_WALL
49 ']' 
49 '=' 
49 const_int 1
49 ';' 
50 '}' 
50 'else' 
50 'if' 
50 '(' 
50 id dir
50 '==' 
50 id DOWN
50 ')' 
50 '{' 
51 id map
51 '[' 
51 id y
51 '+' 
51 const_int 1
51 ']' 
51 '[' 
51 id x
51 ']' 
51 '[' 
51 id NO_TOP_WALL
51 ']' 
51 '=' 
51 const_int 1
51 ';' 
52 '}' 
53 '}' 
55 id void
55 id gen_maze
55 '(' 
55 'int' 
55 id x
55 ',' 
55 'int' 
55 id y
55 ')' 
55 '{' 
56 id map
56 '[' 
56 id y
56 ']' 
56 '[' 
56 id x
56 ']' 
56 '[' 
56 id VISITED
56 ']' 
56 '=' 
56 const_int 1
56 ';' 
57 'int' 
57 id dirs
57 '[' 
57 const_int 4
57 ']' 
57 '=' 
57 '{' 
57 id LEFT
57 ',' 
57 id RIGHT
57 ',' 
57 id TOP
57 ',' 
57 id DOWN
57 '}' 
57 ',' 
57 id i
57 ';' 
58 id i
58 '=' 
58 const_int 0
58 ';' 
59 'while' 
59 '(' 
59 id i
59 '<' 
59 const_int 4
59 ')' 
59 '{' 
60 'int' 
60 id r
60 '=' 
60 id rand
60 '(' 
60 ')' 
60 '%' 
60 const_int 4
60 ';' 
61 'int' 
61 id temp
61 '=' 
61 id dirs
61 '[' 
61 id i
61 ']' 
61 ';' 
62 id dirs
62 '[' 
62 id i
62 ']' 
62 '=' 
62 id dirs
62 '[' 
62 id r
62 ']' 
62 ';' 
63 id dirs
63 '[' 
63 id r
63 ']' 
63 '=' 
63 id temp
63 ';' 
64 id i
64 '=' 
64 id i
64 '+' 
64 const_int 1
64 ';' 
65 '}' 
66 id i
66 '=' 
66 const_int 0
66 ';' 
67 'while' 
67 '(' 
67 id i
67 '<' 
67 const_int 4
67 ')' 
67 '{' 
68 'int' 
68 id xx
68 '[' 
68 const_int 1
68 ']' 
68 '=' 
68 '{' 
68 id x
68 '}' 
68 ',' 
68 id yy
68 '[' 
68 const_int 1
68 ']' 
68 '=' 
68 '{' 
68 id y
68 '}' 
68 ';' 
69 'if' 
69 '(' 
69 id get_neighbor
69 '(' 
69 id xx
69 ',' 
69 id yy
69 ',' 
69 id dirs
69 '[' 
69 id i
69 ']' 
69 ')' 
69 '&&' 
69 '!' 
69 id map
69 '[' 
69 id yy
69 '[' 
69 const_int 0
69 ']' 
69 ']' 
69 '[' 
69 id xx
69 '[' 
69 const_int 0
69 ']' 
69 ']' 
69 '[' 
69 id VISITED
69 ']' 
69 ')' 
69 '{' 
70 id remove_wall
70 '(' 
70 id x
70 ',' 
70 id y
70 ',' 
70 id dirs
70 '[' 
70 id i
70 ']' 
70 ')' 
70 ';' 
71 id gen_maze
71 '(' 
71 id xx
71 '[' 
71 const_int 0
71 ']' 
71 ',' 
71 id yy
71 '[' 
71 const_int 0
71 ']' 
71 ')' 
71 ';' 
72 '}' 
73 id i
73 '=' 
73 id i
73 '+' 
73 const_int 1
73 ';' 
74 '}' 
75 '}' 
77 id void
77 id render
77 '(' 
77 ')' 
77 '{' 
78 'int' 
78 id x
78 ',' 
78 id y
78 ';' 
79 id y
79 '=' 
79 const_int 0
79 ';' 
80 'while' 
80 '(' 
80 id y
80 '<' 
80 id HEIGHT
80 ')' 
80 '{' 
81 id x
81 '=' 
81 const_int 0
81 ';' 
82 'while' 
82 '(' 
82 id x
82 '<' 
82 id WIDTH
82 ')' 
82 '{' 
83 'if' 
83 '(' 
83 '!' 
83 id map
83 '[' 
83 id y
83 ']' 
83 '[' 
83 id x
83 ']' 
83 '[' 
83 id NO_LEFT_WALL
83 ']' 
83 ')' 
83 id image
83 '[' 
83 id y
83 '*' 
83 const_int 2
83 '+' 
83 const_int 1
83 ']' 
83 '[' 
83 id x
83 '*' 
83 const_int 2
83 ']' 
83 '=' 
83 const_int 1
83 ';' 
84 'if' 
84 '(' 
84 '!' 
84 id map
84 '[' 
84 id y
84 ']' 
84 '[' 
84 id x
84 ']' 
84 '[' 
84 id NO_TOP_WALL
84 ']' 
84 ')' 
84 id image
84 '[' 
84 id y
84 '*' 
84 const_int 2
84 ']' 
84 '[' 
84 id x
84 '*' 
84 const_int 2
84 '+' 
84 const_int 1
84 ']' 
84 '=' 
84 const_int 1
84 ';' 
85 id image
85 '[' 
85 id y
85 '*' 
85 const_int 2
85 ']' 
85 '[' 
85 id x
85 '*' 
85 const_int 2
85 ']' 
85 '=' 
85 const_int 1
85 ';' 
86 id x
86 '=' 
86 id x
86 '+' 
86 const_int 1
86 ';' 
87 '}' 
88 id y
88 '=' 
88 id y
88 '+' 
88 const_int 1
88 ';' 
89 '}' 
90 id y
90 '=' 
90 const_int 0
90 ';' 
91 'while' 
91 '(' 
91 id y
91 '<' 
91 id HEIGHT
91 '*' 
91 const_int 2
91 '+' 
91 const_int 1
91 ')' 
91 '{' 
92 id image
92 '[' 
92 id y
92 ']' 
92 '[' 
92 id WIDTH
92 '*' 
92 const_int 2
92 ']' 
92 '=' 
92 const_int 1
92 ';' 
93 id y
93 '=' 
93 id y
93 '+' 
93 const_int 1
93 ';' 
94 '}' 
95 id x
95 '=' 
95 const_int 0
95 ';' 
96 'while' 
96 '(' 
96 id x
96 '<' 
96 id WIDTH
96 '*' 
96 const_int 2
96 '+' 
96 const_int 1
96 ')' 
96 '{' 
97 id image
97 '[' 
97 id HEIGHT
97 '*' 
97 const_int 2
97 ']' 
97 '[' 
97 id x
97 ']' 
97 '=' 
97 const_int 1
97 ';' 
98 id x
98 '=' 
98 id x
98 '+' 
98 const_int 1
98 ';' 
99 '}' 
100 '}' 
102 'int' 
102 id main
102 '(' 
102 ')' 
102 '{' 
103 id seed
103 '=' 
103 id getint
103 '(' 
103 ')' 
103 ';' 
104 'int' 
104 id zoom
104 '=' 
104 id getint
104 '(' 
104 ')' 
104 ';' 
105 id starttime
105 '(' 
105 ')' 
105 ';' 
106 id gen_maze
106 '(' 
106 id rand
106 '(' 
106 ')' 
106 '%' 
106 id WIDTH
106 ',' 
106 id rand
106 '(' 
106 ')' 
106 '%' 
106 id HEIGHT
106 ')' 
106 ';' 
107 id render
107 '(' 
107 ')' 
107 ';' 
108 id stoptime
108 '(' 
108 ')' 
108 ';' 
109 id starttime
109 '(' 
109 ')' 
109 ';' 
110 id putch
110 '(' 
110 const_int 80
110 ')' 
110 ';' 
110 id putch
110 '(' 
110 const_int 51
110 ')' 
110 ';' 
110 id putch
110 '(' 
110 const_int 10
110 ')' 
110 ';' 
111 id putint
111 '(' 
111 '(' 
111 id WIDTH
111 '*' 
111 const_int 2
111 '+' 
111 const_int 1
111 ')' 
111 '*' 
111 id zoom
111 ')' 
111 ';' 
111 id putch
111 '(' 
111 const_int 32
111 ')' 
111 ';' 
112 id putint
112 '(' 
112 '(' 
112 id HEIGHT
112 '*' 
112 const_int 2
112 '+' 
112 const_int 1
112 ')' 
112 '*' 
112 id zoom
112 ')' 
112 ';' 
112 id putch
112 '(' 
112 const_int 10
112 ')' 
112 ';' 
113 id putint
113 '(' 
113 const_int 255
113 ')' 
113 ';' 
113 id putch
113 '(' 
113 const_int 10
113 ')' 
113 ';' 
114 'int' 
114 id y
114 '=' 
114 const_int 0
114 ';' 
115 'while' 
115 '(' 
115 id y
115 '<' 
115 '(' 
115 id HEIGHT
115 '*' 
115 const_int 2
115 '+' 
115 const_int 1
115 ')' 
115 '*' 
115 id zoom
115 ')' 
115 '{' 
116 'int' 
116 id x
116 '=' 
116 const_int 0
116 ';' 
117 'while' 
117 '(' 
117 id x
117 '<' 
117 '(' 
117 id WIDTH
117 '*' 
117 const_int 2
117 '+' 
117 const_int 1
117 ')' 
117 '*' 
117 id zoom
117 ')' 
117 '{' 
118 'int' 
118 id xx
118 '=' 
118 id x
118 '/' 
118 id zoom
118 ',' 
118 id yy
118 '=' 
118 id y
118 '/' 
118 id zoom
118 ';' 
119 'int' 
119 id r
119 '=' 
119 id image
119 '[' 
119 id yy
119 ']' 
119 '[' 
119 id xx
119 ']' 
119 '*' 
119 const_int 255
119 '*' 
119 id x
119 '/' 
119 '(' 
119 '(' 
119 id WIDTH
119 '*' 
119 const_int 2
119 '+' 
119 const_int 1
119 ')' 
119 '*' 
119 id zoom
119 ')' 
119 ';' 
120 'int' 
120 id g
120 '=' 
120 id image
120 '[' 
120 id yy
120 ']' 
120 '[' 
120 id xx
120 ']' 
120 '*' 
120 const_int 255
120 '*' 
120 id y
120 '/' 
120 '(' 
120 '(' 
120 id HEIGHT
120 '*' 
120 const_int 2
120 '+' 
120 const_int 1
120 ')' 
120 '*' 
120 id zoom
120 ')' 
120 ';' 
121 'int' 
121 id b
121 '=' 
121 id image
121 '[' 
121 id yy
121 ']' 
121 '[' 
121 id xx
121 ']' 
121 '*' 
121 const_int 255
121 ';' 
122 id putint
122 '(' 
122 id r
122 ')' 
122 ';' 
122 id putch
122 '(' 
122 const_int 32
122 ')' 
122 ';' 
122 id putint
122 '(' 
122 id g
122 ')' 
122 ';' 
122 id putch
122 '(' 
122 const_int 32
122 ')' 
122 ';' 
122 id putint
122 '(' 
122 id b
122 ')' 
122 ';' 
122 id putch
122 '(' 
122 const_int 32
122 ')' 
122 ';' 
123 id x
123 '=' 
123 id x
123 '+' 
123 const_int 1
123 ';' 
124 '}' 
125 id putch
125 '(' 
125 const_int 10
125 ')' 
125 ';' 
126 id y
126 '=' 
126 id y
126 '+' 
126 const_int 1
126 ';' 
127 '}' 
128 id stoptime
128 '(' 
128 ')' 
128 ';' 
129 'return' 
129 const_int 0
129 ';' 
130 '}' 
```


然后这个实验还算不那么难



### 二、语法分析

#### 方法介绍：

由于语法分析用C/CPP实现起来代码较复杂，因此我们使用$bison$和$flex$等语法分析器和词法分析器来实现任务。

我们首先需要建立要用到的词法和文法：

1、对于常数，十进制、二进制、八进制、十六进制通过正则表达式判断，并定义相应的错误处理。

2、关键词、操作符等字符的定义并对于每种情况，在主程序里面建立相对应的节点。



下面是数值常量的正则表达式`flex`分析器会根据正则识别错误：

```c++
INT_DEC [-+]?0|[1-9][0-9]*    // 十进制
INT_HEX 0[xX][a-fA-F0-9]+     // 十六进制
INT_OCT 0[1-7][0-7]*          // 八进制
INT_BIN 0[bB][01]+            // 二进制
INT {INT_HEX}|{INT_DEC}|{INT_OCT}|{INT_BIN}|{INT_HEX_ERROR}|{INT_OCT_ERROR}|{INT_BIN_ERROR}       // 正确的整数在某种正则进制下
FLOAT [-+]?((([0-9]+\.[0-9]*)|([0-9]*\.[0-9]+)|INT)[Ee][-+]?[0-9]+)|({INT}\.[0-9])            //  浮点变量
INT_HEX_ERROR 0[xX][a-fA-F0-9]*[g-zG-Z]+[a-fA-F0-9]*
INT_OCT_ERROR 0[0-7]*[89]+[0-7]*
INT_BIN_ERROR 0[bB][01]*[2-9]+[01]*
ID [a-z_A-Z][a-z_A-Z0-9]*
```



<!-- 
```
INT_DEC: 匹配十进制整数，同时也可以是零、正整数或负整数。

例子: 0, 42, -123
INT_HEX: 匹配十六进制整数。它以 "0x" 或 "0X" 开头，后面跟着一串十六进制数字（包括字母 A-F 或 a-f）。

例子: 0x2A, 0xFF, -0x1B
INT_OCT: 匹配八进制整数。它以零开头，后面跟着一串八进制数字。

例子: 0123, -075
INT_BIN: 匹配二进制整数。它以 "0b" 或 "0B" 开头，后面跟着一串二进制数字（0 或 1）。

例子: 0b1010, -0b1101
INT: 匹配整数。它可以是十进制、十六进制、八进制或二进制整数。

例子: 42, 0xFF, 0123, 0b1010
FLOAT: 匹配浮点数。它可以是常规的浮点数表示形式，包括小数点、指数符号和指数部分。也可以是整数加上小数部分。

例子: 3.14, -0.5, 1.23E+10, 42.0
INT_HEX_ERROR: 匹配错误的十六进制整数。它以 "0x" 或 "0X" 开头，后面跟着一串可能包含非法十六进制数字的字符。

例子: 0x2G, 0xZZ, -0x1X
INT_OCT_ERROR: 匹配错误的八进制整数。它以零开头，后面跟着一串可能包含非法八进制数字的字符。

例子: 0189, -07X
INT_BIN_ERROR: 匹配错误的二进制整数。它以 "0b" 或 "0B" 开头，后面跟着一串可能包含非法二进制数字的字符。

例子: 0b102, -0b21
ID: 匹配标识符。它以字母，后面可以跟字母、数字或下划线。

例子: variable, myVariable123
``` -->

然后定出，相应识别出的终结符号的语法制导 / 语义动作：

```
{SPACE} {}
{COMMENT} {}
{EOL} {}
{TYPE} {yylval.type_tnode=newAst("TYPE",0,yylineno);return TYPE;}
{STRUCT} {yylval.type_tnode=newAst("STRUCT",0,yylineno);return STRUCT;}
{RETURN} {yylval.type_tnode=newAst("RETURN",0,yylineno); return RETURN;}
{IF} {yylval.type_tnode=newAst("IF",0,yylineno);return IF;}
{ELSE} {yylval.type_tnode=newAst("ELSE",0,yylineno); return ELSE;}
{WHILE} {yylval.type_tnode=newAst("WHILE",0,yylineno); return WHILE;}
{INT_HEX_ERROR} {printf("INT_HEX_ERROR at line %d: charachters \"%s\"\n",yylineno,yytext);}
{INT_OCT_ERROR} {printf("INT_OCT_ERROR at line %d: charachters \"%s\"\n",yylineno,yytext);}
{INT_BIN_ERROR} {printf("INT_BIN_ERROR at line %d: charachters \"%s\"\n",yylineno,yytext);}
{INT} {yylval.type_tnode=newAst("INT",0,yylineno); return INT;}
{FLOAT} {yylval.type_tnode=newAst("FLOAT",0,yylineno); return FLOAT;}
{SEMI} {yylval.type_tnode=newAst("SEMI",0,yylineno); return SEMI;}
{COMMA} {yylval.type_tnode=newAst("COMMA",0,yylineno); return COMMA;}
{ASSIGNOP} {yylval.type_tnode=newAst("ASSIGNOP",0,yylineno); return ASSIGNOP;}
{PLUS} {yylval.type_tnode=newAst("PLUS",0,yylineno); return PLUS;}
{MINUS} {yylval.type_tnode=newAst("MINUS",0,yylineno); return MINUS;}
{STAR} {yylval.type_tnode=newAst("STAR",0,yylineno); return STAR;}
{DIV} {yylval.type_tnode=newAst("DIV",0,yylineno); return DIV;}
{AND} {yylval.type_tnode=newAst("AND",0,yylineno); return AND;}
{OR} {yylval.type_tnode=newAst("OR",0,yylineno); return OR;}
{DOT} {yylval.type_tnode=newAst("DOT",0,yylineno); return DOT;}
{NOT} {yylval.type_tnode=newAst("NOT",0,yylineno); return NOT;}
{LPARENT} {yylval.type_tnode=newAst("LPARENT",0,yylineno); return LPARENT;}
{RPARENT} {yylval.type_tnode=newAst("RPARENT",0,yylineno); return RPARENT;}
{LBRACKET} {yylval.type_tnode=newAst("LBRACKET",0,yylineno); return LBRACKET;}
{RBRACKET} {yylval.type_tnode=newAst("RBRACKET",0,yylineno); return RBRACKET;}
{LBRACE} {yylval.type_tnode=newAst("LBRACE",0,yylineno); return LBRACE;}
{RBRACE} {yylval.type_tnode=newAst("RBRACE",0,yylineno); return RBRACE;}
{RELOP} {yylval.type_tnode=newAst("RELOP",0,yylineno); return RELOP;}
{ID} {yylval.type_tnode=newAst("ID",0,yylineno); return ID;}
%%
```




下面是对每个终结符号和相应的语义动作的解释：

- `{SPACE}`: 匹配空格。在语义动作中没有定义具体操作。
- `{COMMENT}`: 匹配注释。在语义动作中没有定义具体操作。
- `{EOL}`: 匹配行结束符（换行符）。在语义动作中没有定义具体操作。
- `{TYPE}`: 匹配类型关键字（如int、float等）。在语义动作中创建一个类型节点，并返回类型标记。
- `{STRUCT}`: 匹配结构关键字。在语义动作中创建一个结构节点，并返回结构标记。
- `{RETURN}`: 匹配返回关键字。在语义动作中创建一个返回节点，并返回返回标记。
- `{IF}`: 匹配if关键字。在语义动作中创建一个if节点，并返回if标记。
- `{ELSE}`: 匹配else关键字。在语义动作中创建一个else节点，并返回else标记。
- `{WHILE}`: 匹配while关键字。在语义动作中创建一个while节点，并返回while标记。
- `{INT_HEX_ERROR}`: 匹配错误的十六进制整数。在语义动作中打印错误信息，指示行号和出错的字符。
- `{INT_OCT_ERROR}`: 匹配错误的八进制整数。在语义动作中打印错误信息，指示行号和出错的字符。
- `{INT_BIN_ERROR}`: 匹配错误的二进制整数。在语义动作中打印错误信息，指示行号和出错的字符。
- `{INT}`: 匹配整数。在语义动作中创建一个整数节点，并返回整数标记。
- `{FLOAT}`: 匹配浮点数。在语义动作中创建一个浮点数节点，并返回浮点数标记。
- `{SEMI}`: 匹配分号。在语义动作中创建一个分号节点，并返回分号标记。
- `{COMMA}`: 匹配逗号。在语义动作中创建一个逗号节点，并返回逗号标记。
- `{ASSIGNOP}`: 匹配赋值操作符。在语义动作中创建一个赋值操作符节点，并返回赋值操作符标记。
- `{PLUS}`: 匹配加号。在语义动作中创建一个加号节点，并返回加号标记。
- `{MINUS}`: 匹配减号。在语义动作中创建一个减号节点，并返回减号标记。
- `{STAR}`: 匹配乘号。在语义动作中创建一个乘号节点，并返回乘号标记。
- `{DIV}`: 匹配除号。在语义动作中创建一个除号节点，并返回除号标记。
- `{AND}`: 匹配逻辑与运算符。在语义动作中创建一个逻辑与运算符节点，并返回逻辑与运算符标记。
- `{OR}`: 匹配逻辑或运算符。在语义动作中创建一个逻辑或运算符节点，并返回逻辑或运算符标记。
- `{DOT}`: 匹配点号。在语义动作中创建一个点号节点，并返回点号标记。
- `{NOT}`: 匹配逻辑非运算符。在语义动作中创建一个逻辑非运算符节点，并返回逻辑非运算符标记。
- `{LPARENT}`: 匹配左括号。在语义动作中创建一个左括号节点，并返回左括号标记。
- `{RPARENT}`: 匹配右括号。在语义动作中创建一个右括号节点，并返回右括号标记。
- `{LBRACKET}`: 匹配左方括号。在语义动作中创建一个左方括号节点，并返回左方括号标记。
- `{RBRACKET}`: 匹配右方括号。在语义动作中创建一个右方括号节点，并返回右方括号标记。
- `{LBRACE}`: 匹配左花括号。在语义动作中创建一个左花括号节点，并返回左花括号标记。
- `{RBRACE}`: 匹配右花括号。在语义动作中创建一个右花括号节点，并返回右花括号标记。
- `{RELOP}`: 匹配关系运算符。在语义动作中创建一个关系运算符节点，并返回关系运算符标记。
- `{ID}`: 匹配标识符。在语义动作中创建一个标识符节点，并返回标识符标记。

这些语义动作的具体操作可以根据需要进行定义和实现，例如创建语法树节点、记录错误信息、设置标记等。





对于识别不了的词法，我们需要报错，这里也需要定义相应的错误表达方式：

```
{AERROR} {
	fault=1;
	printf("Error type A at line %d: Mystirious charachter '%s'\n",yylineno,yytext);
}
```

该词法可以用`flex`工具进行分析生成对应的c语言代码。

除此之外，我们还需要建立相关的文法，文法对函数、函数参数、表达式等规则都进行了定义，但有些地方可能与`SYsy`语言存在一定的差异：

```c
/*程序开头*/
CompUnit:FuncDef {$$=newAst("CompUnit",1,$1);}
	;
/*函数定义*/
FuncDef:ExtDef FuncDef {$$=newAst("FuncDef",2,$1,$2);}
	| {$$=newAst("FuncDef",0,-1);}
	;
/*类型定义*/	
ExtDef:Specifire ExtDecList SEMI    {$$=newAst("ExtDef",3,$1,$2,$3);}    
	|Specifire SEMI	{$$=newAst("ExtDef",2,$1,$2);}
	|Specifire FunDec Block	{$$=newAst("ExtDef",3,$1,$2,$3);}
	;
ExtDecList:VarDec {$$=newAst("ExtDecList",1,$1);}
	|VarDec COMMA ExtDecList {$$=newAst("ExtDecList",3,$1,$2,$3);}
	;
/*定义变量*/
VarDec:ID {$$=newAst("VarDec",1,$1);}
	|VarDec LBRACKET INT RBRACKET {$$=newAst("VarDec",4,$1,$2,$3,$4);}
	;
FunDec:ID LPARENT VarList RPARENT {$$=newAst("FunDec",4,$1,$2,$3,$4);}
	|ID LPARENT RPARENT {$$=newAst("FunDec",3,$1,$2,$3);}
	;
VarList:ParamDec COMMA VarList {$$=newAst("VarList",3,$1,$2,$3);}
	|ParamDec {$$=newAst("VarList",1,$1);}
	;
ParamDec:Specifire VarDec {$$=newAst("ParamDec",2,$1,$2);}
    ;
Specifire:TYPE {$$=newAst("Specifire",1,$1);}
	;
/*Statement*/
Block:LBRACE DefList StmtList RBRACE {$$=newAst("Block",4,$1,$2,$3,$4);}
	;
StmtList:Stmt StmtList{$$=newAst("StmtList",2,$1,$2);}
	| {$$=newAst("StmtList",0,-1);}
	;
Stmt:Exp SEMI {$$=newAst("Stmt",2,$1,$2);}
	|Block {$$=newAst("Stmt",1,$1);}
	|RETURN Exp SEMI {$$=newAst("Stmt",3,$1,$2,$3);}
    |IF LPARENT Exp RPARENT Stmt ELSE Stmt {$$=newAst("Stmt",7,$1,$2,$3,$4,$5,$6,$7);}
	|WHILE LPARENT Exp RPARENT Stmt {$$=newAst("Stmt",5,$1,$2,$3,$4,$5);}
	|error {yyclearin;}
	;
/*很多赋值表达式*/
DefList:Def DefList{$$=newAst("DefList",2,$1,$2);}
	| {$$=newAst("DefList",0,-1);}
	;
/*带声明的赋值表达式*/
Def:Specifire DecList SEMI {$$=newAst("Def",3,$1,$2,$3);}
	;
/*用逗号隔开的定义表达式*/
DecList:Dec {$$=newAst("DecList",1,$1);}
	|Dec COMMA DecList {$$=newAst("DecList",3,$1,$2,$3);}
	;
/*定义语句*/
Dec:VarDec {$$=newAst("Dec",1,$1);}
	|VarDec ASSIGNOP Exp {$$=newAst("Dec",3,$1,$2,$3);}
	;
/*表达式*/
Exp:Exp ASSIGNOP Exp{$$=newAst("Exp",3,$1,$2,$3);}
        |Exp AND Exp{$$=newAst("Exp",3,$1,$2,$3);}
        |Exp OR Exp{$$=newAst("Exp",3,$1,$2,$3);}
        |Exp RELOP Exp{$$=newAst("Exp",3,$1,$2,$3);}
        |Exp PLUS Exp{$$=newAst("Exp",3,$1,$2,$3);}
        |Exp MINUS Exp{$$=newAst("Exp",3,$1,$2,$3);}
        |Exp STAR Exp{$$=newAst("Exp",3,$1,$2,$3);}
        |Exp DIV Exp{$$=newAst("Exp",3,$1,$2,$3);}
        |LPARENT Exp RPARENT{$$=newAst("Exp",3,$1,$2,$3);}
        |MINUS Exp {$$=newAst("Exp",2,$1,$2);}
        |NOT Exp {$$=newAst("Exp",2,$1,$2);}
        |ID LPARENT Args RPARENT {$$=newAst("Exp",4,$1,$2,$3,$4);}
        |ID LPARENT RPARENT {$$=newAst("Exp",3,$1,$2,$3);}
        |Exp LBRACKET Exp RBRACKET {$$=newAst("Exp",4,$1,$2,$3,$4);}
        |Exp DOT ID {$$=newAst("Exp",3,$1,$2,$3);}
        |ID {$$=newAst("Exp",1,$1);}
        |INT {$$=newAst("Exp",1,$1);}
        |FLOAT{$$=newAst("Exp",1,$1);}
        ;
/*多个表达式参数*/
Args:Exp COMMA Args {$$=newAst("Args",3,$1,$2,$3);}
        |Exp {$$=newAst("Args",1,$1);}
        ;
```

```


具体解释如下：

- `CompUnit`: 程序的开头，表示整个程序的起始符号。
- `FuncDef`: 函数定义，包括函数声明和函数体。
- `ExtDef`: 扩展定义，用于定义全局变量或函数。
- `ExtDecList`: 全局变量定义列表，用于定义多个全局变量。
- `VarDec`: 变量声明，包括变量名和数组维度。
- `FunDec`: 函数声明，包括函数名和参数列表。
- `VarList`: 参数列表，用于定义多个函数参数。
- `ParamDec`: 函数参数声明，包括参数类型和参数名。
- `Specifier`: 类型限定符，指定变量或函数的类型。
- `Block`: 代码块，用于定义变量和语句的作用域。
- `StmtList`: 语句列表，用于存储多个语句。
- `Stmt`: 语句，包括表达式语句、代码块、返回语句等。
- `DefList`: 定义列表，用于存储多个定义。
- `Def`: 定义，包括类型限定符和声明列表。
- `DecList`: 声明列表，用于存储多个声明。
- `Dec`: 声明，包括变量声明和带初始化的变量声明。
- `Exp`: 表达式，用于表示各种运算和操作。
- `Args`: 参数列表，用于表示函数调用时的参数。

这些产生式规则定义了语言的语法结构，可以用于构建语法分析器来解析和分析相应的源代码。
```

特别的，为了在规约表达式的时候出错时不退出程序，我们可以在规约出错误的时候添加动作，利用工具自带的`yyclearin`语句进行清楚痕迹：

```
Stmt:Exp SEMI {$$=newAst("Stmt",2,$1,$2);}
	|Block {$$=newAst("Stmt",1,$1);}
	|RETURN Exp SEMI {$$=newAst("Stmt",3,$1,$2,$3);}
    |IF LPARENT Exp RPARENT Stmt %prec LOWER_THAN_ELSE {$$=newAst("Stmt",5,$1,$2,$3,$4,$5);}
    |IF LPARENT Exp RPARENT Stmt ELSE Stmt {$$=newAst("Stmt",7,$1,$2,$3,$4,$5,$6,$7);}
	|WHILE LPARENT Exp RPARENT Stmt {$$=newAst("Stmt",5,$1,$2,$3,$4,$5);}
	|error {yyclearin;}
	;
```

将以上两个文件编译后即可生成词法分析器和语法分析器。

上述代码片段是在语法规则`Stmt`中添加了错误处理的动作，即在规约出错时调用`yyclearin`函数清除分析器中的输入缓冲区。这样可以避免在出错时直接退出程序，而是继续分析后面的输入。

要生成词法分析器和语法分析器，您需要使用相应的工具来处理这些语法规则文件。例如，对于词法分析器，您可以使用Flex工具来生成，而对于语法分析器，可以使用Bison工具。

对于Flex，您可以将词法规则保存在一个独立的文件中（例如`lexer.l`），然后使用以下命令进行编译和生成词法分析器：

```shell
flex lexer.l
gcc lex.yy.c -o lexer
```

对于Bison，您可以将语法规则保存在一个独立的文件中（例如`parser.y`），然后使用以下命令进行编译和生成语法分析器：

```shell
bison -d parser.y
gcc parser.tab.c -o parser
```

在上述命令中，`lexer.l`和`parser.y`分别是词法规则文件和语法规则文件的文件名。`lex.yy.c`和`parser.tab.c`是由Flex和Bison生成的C源代码文件。最后，将生成的C源代码文件编译为可执行文件（例如`lexer`和`parser`）。





在词法分析的代码中，我们每次识别到一个终结符号，就建立关于该终结符号的叶子节点，同样的，我们在语法分析中每次规约出一个非终结符号，我们也去建立对应的非叶子节点。

在具体地建立节点的实现中，我们建立一个结构体来储存节点，对每个节点开一个数组储存儿子节点，如果是终结符号的话，判断其是不是一个数字，如果是的话就用x进制转十进制的方法计算具体的数字。

在具体实现的过程中，我们利用了`c`语言的多参数功能，以便降低代码实现的难度。

在代码中我们判断该符号是一个终结符号还是非终结符号，并进行相应处理。

```c
Ast newAst(char *name, int num, ...){
    tnode now=(tnode)malloc(sizeof(struct treeNode));
    tnode temp=(tnode)malloc(sizeof(struct treeNode));
    now->name=name;
    va_list list;
    va_start(list,num);
    if (num>0){
        now->ncld=num;
        temp=va_arg(list,tnode);
        now->cld[0]=temp;
        addtag(temp);
        now->line=temp->line;
        if (num>1){
            for(i=1;i<num;i++){
                temp=va_arg(list,tnode);
                (now->cld)[i]=temp;
                addtag(temp);
            }
        }
    }
    else{
        now->ncld=0;
        now->line=va_arg(list, int);
        if (!strcmp(name,"INT")){
            now->type="int";
            now->value=_atoi(yytext);
        }
        else if (!strcmp(name, "FLOAT")){
            now->type="float";
            now->value=atof(yytext);
        }
        else{
            char *str;
            str=(char *)malloc(sizeof(char)*40);
            strcpy(str,yytext);
            now->type = str;
        }
    }
    nodeList[nodeNum]=now;
    nodeNum++;
    return now;
}
```

```
上述代码是一个用于创建语法树节点的函数`newAst`的实现。该函数接受节点的名称、子节点的数量以及子节点列表作为参数，并返回创建的节点。

函数首先创建了一个新的节点 `now`，并设置节点的名称为传入的名称。然后，使用可变参数列表 `va_list` 来处理子节点。

如果子节点数量大于0，表示当前节点是一个非终结符号，函数会将子节点逐个添加到当前节点的子节点数组中，并调用 `addtag` 函数来标记子节点。

如果子节点数量为0，表示当前节点是一个终结符号。函数会根据终结符号的类型进行判断，并将其转换为相应的数据类型。对于整数类型的终结符号，使用 `_atoi` 函数将其转换为十进制整数；对于浮点数类型的终结符号，使用 `atof` 函数将其转换为浮点数；对于其他类型的终结符号，将其存储为字符串类型。

最后，函数将创建的节点添加到全局的节点列表 `nodeList` 中，并返回该节点。

需要注意的是，上述代码中使用了全局变量 `nodeList` 来存储所有创建的节点，并使用 `nodeNum` 来记录节点数量。此外，代码中的 `addtag` 函数用于标记子节点，具体实现未提供

```

在构建完语法分析树之后，我们根据树的结构输出语法分析树，在来到一个终结符号的时候，先判断它是不是一个数字，再根据其是`float`还是`int`进行判断输出，或者是一个普通的变量或符号，直接进行输出即可。

```c
void Preorder(Ast now, int dep){
    if (now!=NULL){
    	int i;
        for(i=0;i<dep;++i)
        	printf(" ");//输出前面的空格 
        if(~now->line){
            printf("%s", now->name);
            if ((!strcmp(now->name, "ID"))||(!strcmp(now->name, "TYPE")))
                printf(": %s", now->type);
            else if (!strcmp(now->name, "INT"))
                printf(": %d", (int)now->value);
            else if (!strcmp(now->name, "FLOAT"))
                printf(": %f", now->value);
            else printf("(%d)", now->line);
        }
        printf("\n");
        for(i=0;i<now->ncld;++i){
            Preorder((now->cld)[i],dep+1);
        }
    }
}
```

上述代码是用于输出语法分析树的函数`Preorder`的实现。该函数使用先序遍历的方式遍历语法树，并在每个节点处输出相应的信息。

函数首先检查当前节点 `now` 是否为空，如果为空，则直接返回。然后，根据节点的深度 `dep` 输出相应的缩进空格。

接下来，根据节点的类型进行判断并输出相应的信息。如果节点是标识符（ID）或类型（TYPE），则输出节点名称以及对应的值。如果节点是整数（INT），则输出节点名称以及整数值。如果节点是浮点数（FLOAT），则输出节点名称以及浮点数值。否则，输出节点名称以及行号。

然后，递归遍历当前节点的子节点，并将深度增加1，以进行下一层的遍历。

请注意，上述代码中的输出部分根据具体需求进行了简化，并未考虑到所有可能的情况。您可以根据实际需求进行相应的调整和补充。

使用该函数，您可以调用`Preorder`函数来输出语法分析树。例如：

```c
Preorder(root, 0);
```

其中，`root`是语法分析树的根节点，0是初始的深度。该调用将从根节点开始遍历语法树，并输出每个节点的信息。

输出的结果将按照先序遍历的顺序进行展示，并根据节点的深度进行缩进，形成一棵层次清晰的语法分析树。







#### 程序运行方法

由于使用了词法分析和语法分析工具，故编译指令如下：

```
flex syntax.l
bison -d syntax.y
gcc syntax.tab.c syntax.c lex.yy.c -o parser
parser datax.c
```



#### 测试用例1

```c
int func(){
	int x=0;
} 

int main(){
  int i=1;
  int j=~1;
  return 0;
}
```

```
Error type A at line 7: Mystirious charachter '~'
```

和上一个实验的例子一样。



#### 测试用例2

```c
int main()
{
 int a[10][12];
 int i;
 a[5,3]=5;
 if(a[1][2]==0)
     i=1
     else i=0;
 return 0;
}
```

```
Error type B at Line 5, syntax error ,before ,
Error type B at Line 8, syntax error ,before else
```

这里有两处语法错误，程序都在对应的位置识别了出来并且分别输出。



#### 测试用例3

```c
int inc(){
	int i;
	i=i+1;
}
```

```
CompUnit(1)
 FuncDef(1)
  ExtDef(1)
   Specifire(1)
    TYPE: int
   FunDec(1)
    ID: inc
    LPARENT(1)
    RPARENT(1)
   Block(1)
    LBRACE(1)
    DefList(2)
     Def(2)
      Specifire(2)
       TYPE: int
      DecList(2)
       Dec(2)
        VarDec(2)
         ID: i
      SEMI(2)

    StmtList(3)
     Stmt(3)
      Exp(3)
       Exp(3)
        ID: i
       ASSIGNOP(3)
       Exp(3)
        Exp(3)
         ID: i
        PLUS(3)
        Exp(3)
         INT: 1
      SEMI(3)

    RBRACE(4)
```

```
根据给定的测试用例，经过词法分析和语法分析后，生成了一个抽象语法树（Abstract Syntax Tree，AST）。下面是对该AST的解释：

- CompUnit(1): 整个程序的顶层节点。
  - FuncDef(1): 函数定义节点。
    - ExtDef(1): 扩展定义节点。
      - Specifier(1): 类型限定符节点。
        - TYPE: int，表示类型为整数。
      - FunDec(1): 函数声明节点。
        - ID: inc，表示函数名为"inc"。
        - LPARENT(1): 左括号，表示函数参数的开始。
        - RPARENT(1): 右括号，表示函数参数的结束。
      - Block(1): 函数体节点。
        - LBRACE(1): 左花括号，表示函数体的开始。
        - DefList(2): 定义列表节点。
          - Def(2): 定义节点。
            - Specifier(2): 类型限定符节点。
              - TYPE: int，表示类型为整数。
            - DecList(2): 声明列表节点。
              - Dec(2): 声明节点。
                - VarDec(2): 变量声明节点。
                  - ID: i，表示变量名为"i"。
        - SEMI(2): 分号，表示语句结束。
        - StmtList(3): 语句列表节点。
          - Stmt(3): 语句节点。
            - Exp(3): 表达式节点。
              - Exp(3): 表达式节点。
                - ID: i，表示变量名为"i"。
              - ASSIGNOP(3): 赋值操作符，表示赋值操作。
              - Exp(3): 表达式节点。
                - Exp(3): 表达式节点。
                  - ID: i，表示变量名为"i"。
                - PLUS(3): 加号，表示加法操作。
                - Exp(3): 表达式节点。
                  - INT: 1，表示整数值为1。
          - SEMI(3): 分号，表示语句结束。
        - RBRACE(4): 右花括号，表示函数体的结束。

这个AST表示了一个名为"inc"的函数定义，函数的返回类型为整数。函数体中声明了一个整数类型的变量"i"，并对变量"i"进行了自增操作。
```



#### 测试用例4

```c
int inc(int x){
	return x-x+x*x/x;
}
int main(){
	int y=1;
	int x=inc(444); 
    int a[5][5];
    y=x+a[0][0]*a[3][3];
	return 0;
}
```

```
CompUnit(1)
 FuncDef(1)
  ExtDef(1)
   Specifire(1)
    TYPE: int
   FunDec(1)
    ID: inc
    LPARENT(1)
    VarList(1)
     ParamDec(1)
      Specifire(1)
       TYPE: int
      VarDec(1)
       ID: x
    RPARENT(1)
   Block(1)
    LBRACE(1)

    StmtList(2)
     Stmt(2)
      RETURN(2)
      Exp(2)
       Exp(2)
        Exp(2)
         ID: x
        MINUS(2)
        Exp(2)
         ID: x
       PLUS(2)
       Exp(2)
        Exp(2)
         Exp(2)
          ID: x
         STAR(2)
         Exp(2)
          ID: x
        DIV(2)
        Exp(2)
         ID: x
      SEMI(2)

    RBRACE(3)
  FuncDef(4)
   ExtDef(4)
    Specifire(4)
     TYPE: int
    FunDec(4)
     ID: main
     LPARENT(4)
     RPARENT(4)
    Block(4)
     LBRACE(4)
     DefList(5)
      Def(5)
       Specifire(5)
        TYPE: int
       DecList(5)
        Dec(5)
         VarDec(5)
          ID: y
         ASSIGNOP(5)
         Exp(5)
          INT: 1
       SEMI(5)
      DefList(6)
       Def(6)
        Specifire(6)
         TYPE: int
        DecList(6)
         Dec(6)
          VarDec(6)
           ID: x
          ASSIGNOP(6)
          Exp(6)
           ID: inc
           LPARENT(6)
           Args(6)
            Exp(6)
             INT: 444
           RPARENT(6)
        SEMI(6)
       DefList(7)
        Def(7)
         Specifire(7)
          TYPE: int
         DecList(7)
          Dec(7)
           VarDec(7)
            VarDec(7)
             VarDec(7)
              ID: a
             LBRACKET(7)
             INT: 5
             RBRACKET(7)
            LBRACKET(7)
            INT: 5
            RBRACKET(7)
         SEMI(7)

     StmtList(8)
      Stmt(8)
       Exp(8)
        Exp(8)
         ID: y
        ASSIGNOP(8)
        Exp(8)
         Exp(8)
          ID: x
         PLUS(8)
         Exp(8)
          Exp(8)
           Exp(8)
            Exp(8)
             ID: a
            LBRACKET(8)
            Exp(8)
             INT: 0
            RBRACKET(8)
           LBRACKET(8)
           Exp(8)
            INT: 0
           RBRACKET(8)
          STAR(8)
          Exp(8)
           Exp(8)
            Exp(8)
             ID: a
            LBRACKET(8)
            Exp(8)
             INT: 3
            RBRACKET(8)
           LBRACKET(8)
           Exp(8)
            INT: 3
           RBRACKET(8)
       SEMI(8)
      StmtList(9)
       Stmt(9)
        RETURN(9)
        Exp(9)
         INT: 0
        SEMI(9)

     RBRACE(10)
```

```
根据给定的测试用例，经过词法分析和语法分析后，生成了一个抽象语法树（Abstract Syntax Tree，AST）。下面是对该AST的解释：

- CompUnit(1): 整个程序的顶层节点。
  - FuncDef(1): 函数定义节点。
    - ExtDef(1): 扩展定义节点。
      - Specifier(1): 类型限定符节点。
        - TYPE: int，表示类型为整数。
      - FunDec(1): 函数声明节点。
        - ID: inc，表示函数名为"inc"。
        - LPARENT(1): 左括号，表示函数参数的开始。
        - VarList(1): 参数列表节点。
          - ParamDec(1): 参数声明节点。
            - Specifier(1): 类型限定符节点。
              - TYPE: int，表示类型为整数。
            - VarDec(1): 变量声明节点。
              - ID: x，表示参数名为"x"。
        - RPARENT(1): 右括号，表示函数参数的结束。
      - Block(1): 函数体节点。
        - LBRACE(1): 左花括号，表示函数体的开始。
        - StmtList(2): 语句列表节点。
          - Stmt(2): 语句节点。
            - RETURN(2): 返回语句关键字。
            - Exp(2): 表达式节点。
              - Exp(2): 表达式节点。
                - Exp(2): 表达式节点。
                  - ID: x，表示变量名为"x"。
                - MINUS(2): 减号，表示减法操作。
                - Exp(2): 表达式节点。
                  - ID: x，表示变量名为"x"。
              - PLUS(2): 加号，表示加法操作。
              - Exp(2): 表达式节点。
                - Exp(2): 表达式节点。
                  - Exp(2): 表达式节点。
                    - ID: x，表示变量名为"x"。
                  - STAR(2): 乘号，表示乘法操作。
                  - Exp(2): 表达式节点。
                    - ID: x，表示变量名为"x"。
                - DIV(2): 除号，表示除法操作。
                - Exp(2): 表达式节点。
                  - ID: x，表示变量名为"x"。
            - SEMI(2): 分号，表示语句结束。
        - RBRACE(3): 右花括号，表示函数体的结束。
  - FuncDef(4): 函数定义节点。
    - ExtDef(4): 扩展定义节点。
      - Specifier(4): 类型限定符节点。
        - TYPE: int，表示类型为整数。
      - FunDec(4): 函数声明节点。
        - ID: main，表示函数名为"main"。
        - LPARENT(4): 左括号，表示函数参数的开始。
        - RPARENT(4): 右括号，表示函数参数的结束。
      - Block(4): 函数体节点。
        - LBRACE(4): 左花括号，表示函数体的开始。
        - DefList(5): 定义

列表节点。
          - Def(5): 定义节点。
            - Specifier(5): 类型限定符节点。
              - TYPE: int，表示类型为整数。
            - DecList(5): 声明列表节点。
              - Dec(5): 声明节点。
                - VarDec(5): 变量声明节点。
                  - ID: y，表示变量名为"y"。
                - ASSIGNOP(5): 赋值操作符，表示赋值操作。
                - Exp(5): 表达式节点。
                  - INT: 1，表示整数值为1。
            - SEMI(5): 分号，表示语句结束。
          - DefList(6): 定义列表节点。
            - Def(6): 定义节点。
              - Specifier(6): 类型限定符节点。
                - TYPE: int，表示类型为整数。
              - DecList(6): 声明列表节点。
                - Dec(6): 声明节点。
                  - VarDec(6): 变量声明节点。
                    - ID: x，表示变量名为"x"。
                  - ASSIGNOP(6): 赋值操作符，表示赋值操作。
                  - Exp(6): 表达式节点。
                    - ID: inc，表示函数调用表达式。
                    - LPARENT(6): 左括号，表示函数调用参数的开始。
                    - Args(6): 参数列表节点。
                      - Exp(6): 表达式节点。
                        - INT: 444，表示整数值为444。
                    - RPARENT(6): 右括号，表示函数调用参数的结束。
              - SEMI(6): 分号，表示语句结束。
            - DefList(7): 定义列表节点。
              - Def(7): 定义节点。
                - Specifier(7): 类型限定符节点。
                  - TYPE: int，表示类型为整数。
                - DecList(7): 声明列表节点。
                  - Dec(7): 声明节点。
                    - VarDec(7): 变量声明节点。
                      - VarDec(7): 变量声明节点。
                        - VarDec(7): 变量声明节点。
                          - ID: a，表示变量名为"a"。
                        - LBRACKET(7): 左方括号，表示数组维度的开始。
                        - INT: 5，表示数组维度为5。
                        - RBRACKET(7): 右方括号，表示数组维度的结束。
                      - LBRACKET(7): 左方括号，表示数组维度的开始。
                      - INT: 5，表示数组维度为5。
                      - RBRACKET(7): 右方括号，表示数组维度的结束。
                - SEMI(7): 分号，表示语句结束。
        - StmtList(8): 语句列表节点。
          - Stmt(8): 语句节点。
            - Exp(8): 表达式节点。
              - Exp(8): 表达式节点。
                - ID: y，表示变量名为"y"。
              - ASSIGNOP(8): 赋值操作符，表示赋值操作。
              - Exp(8): 表达式节点。
                - Exp(8

): 表达式节点。
                  - Exp(8): 表达式节点。
                    - ID: x，表示变量名为"x"。
                  - PLUS(8): 加号，表示加法操作。
                  - Exp(8): 表达式节点。
                    - Exp(8): 表达式节点。
                      - Exp(8): 表达式节点。
                        - Exp(8): 表达式节点。
                          - ID: a，表示变量名为"a"。
                        - LBRACKET(8): 左方括号，表示数组维度的开始。
                        - Exp(8): 表达式节点。
                          - INT: 0，表示整数值为0。
                        - RBRACKET(8): 右方括号，表示数组维度的结束。
                      - LBRACKET(8): 左方括号，表示数组维度的开始。
                      - Exp(8): 表达式节点。
                        - INT: 0，表示整数值为0。
                      - RBRACKET(8): 右方括号，表示数组维度的结束。
                    - STAR(8): 乘号，表示乘法操作。
                    - Exp(8): 表达式节点。
                      - Exp(8): 表达式节点。
                        - Exp(8): 表达式节点。
                          - ID: a，表示变量名为"a"。
                        - LBRACKET(8): 左方括号，表示数组维度的开始。
                        - Exp(8): 表达式节点。
                          - INT: 3，表示整数值为3。
                        - RBRACKET(8): 右方括号，表示数组维度的结束。
                      - LBRACKET(8): 左方括号，表示数组维度的开始。
                      - Exp(8): 表达式节点。
                        - INT: 3，表示整数值为3。
                      - RBRACKET(8): 右方括号，表示数组维度的结束。
                - PLUS(8): 加号，表示加法操作。
                - Exp(8): 表达式节点。
                  - Exp(8): 表达式节点。
                    - Exp(8): 表达式节点。
                      - ID: x，表示变量名为"x"。
                  - PLUS(8): 加号，表示加法操作。
                  - Exp(8): 表达式节点。
                    - Exp(8): 表达式节点。
                      - Exp(8): 表达式节点。
                        - ID: a，表示变量名为"a"。
                      - LBRACKET(8): 左方括号，表示数组维度的开始。
                      - Exp(8): 表达式节点。
                        - INT: 0，表示整数值为0。
                      - RBRACKET(8): 右方括号，表示数组维度的结束。
                    - LBRACKET(8): 左方括号，表示数组维度的开始。
                    - Exp(8): 表达式节点。
                      - INT: 0，表示整数值为0。
                    - RBRACKET(8): 右方括号，表示数组维度的结束。
              - SEMI(8): 分号，表示语句结束。
          - StmtList(9): 语句列表节点。
            -

 Stmt(9): 语句节点。
              - RETURN(9): 返回语句关键字。
              - Exp(9): 表达式节点。
                - INT: 0，表示整数值为0。
              - SEMI(9): 分号，表示语句结束。
        - RBRACE(10): 右花括号，表示函数体的结束。

这个AST表示了一个包含两个函数定义的程序。第一个函数是名为"inc"的函数，它有一个整型参数"x"，并返回一个表达式结果。第二个函数是名为"main"的函数，它没有参数，返回类型为整数。"main"函数体中包含了变量的定义和赋值语句，以及一系列的表达式操作。
```



### 三、语义分析

#### 方法介绍：

有了上面的语法分析部分，语义分析就可以在语法分析的基础上进行了。

在这个实现中，我们实现了几种常见的语法错误：

```
1、变量未定义 
2、赋值两边未匹配
3、赋值左边错误
4、变量重复定义
5、操作数类型不匹配 
6、函数未定义 
7、函数实参和形参类型不一致
8、函数重复定义
```

在该实验中我们主要实现的是对于变量、数组、常量、函数的语义检查。

为了能够充分利用语法分析器的功能，我们的语义分析和语法分析同时进行。



实现的大致思路为：

1、规约到一个需要进行语义分析的非终结符号时，需要对所有已经定义过的东西进行查询

2、由于`c`语言很多数据结构不支持，所以我们将使用链表。对变量、数组、函数分别开一个链表，存放已经声明或者定义过的。

为了体现变量的作用域，在判断的时候不同函数之间的变量不会相互影响，在每规约出一个函数之后，我们调用`flush`函数对变量和数组的链表进行刷新。

```
	|Specifire FunDec Compst	{
	        _flush();
			$$=newAst("ExtDef",3,$1,$2,$3); 
		}
	;
```

```c
void _flush(){
	varhead =(var *)malloc(sizeof(var));
    vartail =varhead;
    varhead->next=NULL; 
    arrayhead = (array *)malloc(sizeof(array));
    arraytail = arrayhead;
    arrayhead->next=NULL;
}
```



在对变量操作的时候，如果发现变量未定义，则返回错误：

```
	|ID {
		$$=newAst("Exp",1,$1); 
		// 1:变量未定义
		if(!findvar($1)&&!findarray($1))
			printf("Error type 1 at Line %d:undefined variable %s\n",yylineno,$1->content);
		else 
			$$->type=typevar($1);
	}
```



当规约出赋值表达式的时候，如果赋值号两边的类型不匹配，则返回错误：

```
Exp:Exp ASSIGNOP Exp{
		$$=newAst("Exp",3,$1,$2,$3); 
		if($1->type==NULL || $3->type==NULL){
			return;
		}
		//2:赋值号两边的表达式类型不匹配
		if(strcmp($1->type,$3->type))
			printf("Error type 2 at Line %d:Type mismatched for assignment.\n",yylineno);
```



于此同时，表达式左边也是有要求的，只能是变量或数组引用：

```
if(!checkleft($1))
	printf("Error type 3 at Line %d:The left-hand side of an assignment must be a variable.\n",yylineno);
```



具体判断代码如下，分普通变量和数组变量两种情况：

```c
int checkleft(tnode val){
    if (val->ncld==1&&!strcmp((val->cld)[0]->name,"ID"))  //变量形式 
        return 1;
    else if(val->ncld==4&&!strcmp((val->cld)[0]->name,"Exp")&&!strcmp((val->cld)[1]->name,"LB")&&!strcmp((val->cld)[2]->name, "Exp")&&!strcmp((val->cld)[3]->name, "RB"))
        //数组形式 
        return 1;
    else
        return 0;
}
```



在加减乘除运算时，如果两边类型不匹配，则返回错误。

```
	|Exp PLUS Exp{
		$$=newAst("Exp",3,$1,$2,$3); 
		//5:操作数类型不匹配或操作数类型与操作符不匹配
		if(strcmp($1->type,$3->type))
			printf("Error type 5 at Line %d:Type mismatched for operands.\n",yylineno);
	}
	|Exp MINUS Exp{
		$$=newAst("Exp",3,$1,$2,$3); 
		//5:操作数类型不匹配或操作数类型与操作符不匹配
		if(strcmp($1->type,$3->type))
			printf("Error type 5 at Line %d:Type mismatched for operands.\n",yylineno);
	}
	|Exp STAR Exp{
		$$=newAst("Exp",3,$1,$2,$3); 
		//5:操作数类型不匹配或操作数类型与操作符不匹配
		if(strcmp($1->type,$3->type))
			printf("Error type 5 at Line %d:Type mismatched for operands.\n",yylineno);
	}
	|Exp DIV Exp{
		$$=newAst("Exp",3,$1,$2,$3); 
		//5:操作数类型不匹配或操作数类型与操作符不匹配
		if(strcmp($1->type,$3->type))
			printf("Error type 5 at Line %d:Type mismatched for operands.\n",yylineno);
	}
```



在调用函数的时候，如果函数没有被定义或者已经被定义，但参数列表不能匹配，则返回错误。

```
|ID LPARENT Args RPARENT {
		$$=newAst("Exp",4,$1,$2,$3,$4); 
		//6、函数未定义 
		if(!findfunc($1))
			printf("Error type 6 at Line %d:Undefined function %s\n ",yylineno,$1->content);
		//7、函数实参和形参类型不一致
		else if(checkrtype($1,$3))
			printf("Error type 7 at Line %d:Function parameter type error.\n ",yylineno);
	}
```



在声明函数的时候，如果该函数已经被定义过了，则返回错误。

```
FunDec:ID LPARENT VarList RPARENT {
		$$=newAst("FunDec",4,$1,$2,$3,$4); $$->content=$1->content;
		//8:函数出现重复定义
		if(findfunc($1)) 
			printf("Error type 8 at Line %d:Redefined Function '%s'\n",yylineno,$1->content);
        else newfunc(2,$1,$3);
	}
	|ID LPARENT RPARENT {
	    $$=newAst("FunDec",3,$1,$2,$3); $$->content=$1->content;
	    //8:函数出现重复定义
		if(findfunc($1)) 
			printf("Error type 8 at Line %d:Redefined Function '%s'\n",yylineno,$1->content);
        else newfunc(2,$1,$3);
	}
	;
```



#### 程序运行方法

由于使用了词法分析和语法分析工具，故编译指令如下：

```
flex syntax.l
bison -d syntax.y
gcc syntax.tab.c syntax.c lex.yy.c -o parser
parser datax.c
```



#### 测试用例1

```c
int main()
{
  int i;
  float j;
  int i;
  i=1+1+1*2+j;
  10=i;
  i=1.5;
  z=i;
}
```

```
Error type 4 at Line 5:Redefined Variable 'i'
Error type 5 at Line 6:Type mismatched for operands.
Error type 3 at Line 7:The left-hand side of an assignment must be a variable.
Error type 2 at Line 8:Type mismatched for assignment.
Error type 1 at Line 9:undefined variable z
```

这个例子展示了代码可以判断出来的5中变量错误：重复定义、未定义、左右不匹配、赋值号左边非变量、操作符两边类型不匹配。



#### 测试用例2

```c
int myfunc(int x){
	return x*x;
}
int main()
{
   int x=0x2f;
   myfunc(x);
   return 0;
}
```

```
CompUnit(1)
 FuncDef(1)
  ExtDef(1)
   Specifire(1)
    TYPE: int
   FunDec(1)
    ID: myfunc
    LPARENT(1)
    VarList(1)
     ParamDec(1)
      Specifire(1)
       TYPE: int
      VarDec(1)
       ID: x
    RPARENT(1)
   Compst(1)
    LBRACE(1)

    StmtList(2)
     Stmt(2)
      RETURN(2)
      Exp(2)
       Exp(2)
        ID: x
       STAR(2)
       Exp(2)
        ID: x
      SEMI(2)

    RBRACE(3)
  FuncDef(4)
   ExtDef(4)
    Specifire(4)
     TYPE: int
    FunDec(4)
     ID: main
     LPARENT(4)
     RPARENT(4)
    Compst(5)
     LBRACE(5)
     DefList(6)
      Def(6)
       Specifire(6)
        TYPE: int
       DecList(6)
        Dec(6)
         VarDec(6)
          ID: x
         ASSIGNOP(6)
         Exp(6)
          INT: 47
       SEMI(6)

     StmtList(7)
      Stmt(7)
       Exp(7)
        ID: myfunc
        LPARENT(7)
        Args(7)
         Exp(7)
          ID: x
        RPARENT(7)
       SEMI(7)
      StmtList(8)
       Stmt(8)
        RETURN(8)
        Exp(8)
         INT: 0
        SEMI(8)

     RBRACE(9)
```

这个例子体现了每个函数都有自己的作用域，不同函数定义同一个变量名不影响。

可以看到每个函数都有自己的作用域，不同函数中可以定义同名的变量而不会相互影响。

在生成的语法分析树中，可以观察到以下关键点：

1. 函数`myfunc`的定义中，参数列表中有一个参数`x`，并在函数体中使用了参数`x`进行计算。

2. 函数`main`的定义中，定义了一个整型变量`x`并赋值为`0x2f`（十六进制数值）。然后调用了函数`myfunc`，并传递了参数`x`。

3. 在整个语法分析树中，可以看到`myfunc`函数和`main`函数的变量`x`是不同的变量，它们位于不同的作用域内。

这样的效果体现了函数作用域的特性：在不同的函数中可以定义同名的变量，而它们彼此独立，不会相互影响。

在进行语义分析时，可以使用符号表（Symbol Table）来维护变量和函数的定义信息，以实现作用域的划分。每当进入一个函数定义时，可以创建一个新的作用域，并将变量和函数的定义信息添加到相应的作用域中。这样，在进行变量引用和作用域检查时，可以根据符号表来判断变量的合法性和作用域的范围。



#### 测试用例3

```c
int myfunc(int x){
	return x*x;
}
int myfunc(){
	return 033;
}
int main()
{
   int x=0x2f;
   myfunc(x,x,x);
   func(x);
   return 0;
}
```

```
Error type 8 at Line 4:Redefined Function 'myfunc'
Error type 7 at Line 10:Function parameter type error.
Error type 6 at Line 11:Undefined function func
```

这个例子体现出了三个关于函数的错误：重复定义、参数错误、未定义。



### 四、中间代码生成

#### 方法介绍：

在本实验中，我们实现了简单的中间代码生成器。

因为在前面已经建立过分析树了，所以我们的大致方法为建出对分析树进行遍历，并逐步进行分析。

前面的函数开头、定义的翻译部分比较繁琐，这里不过多赘述；我们将用一个链表存储当前代码的操作语句。

```c
InterCode get_Tail(InterCode codes){
    InterCode temp=codes;
    while (temp->next)temp=temp->next;
    return temp;
}
//增加一些语句 
InterCode add_Codes(int num, ...){
    int i;
    //多参数列表 一条一条插进去 
    va_list list;
    va_start(list, num);
    InterCode code=va_arg(list, InterCode);
    InterCode temp=new_Code();
    InterCode tail=new_Code();
    for (i=1;i<num;++i){
        temp=va_arg(list,InterCode);
        tail=get_Tail(code);
        tail->next=temp;
        temp->prev=tail;
    }
    return code;
}
```

上述代码中的函数：

- `get_Tail(InterCode codes)`：用于获取代码链表的尾部节点，即链表中最后一个代码语句的节点。
- `add_Codes(int num, ...)`：用于向代码链表中添加多条代码语句。它接受一个整数参数 `num`，表示待添加的代码语句的数量，后面跟着 `num` 个参数，每个参数是一个 `InterCode` 类型的代码语句。函数会将这些代码语句按顺序添加到链表中，并返回添加后的链表。

接下来，我们将根据分析树的节点类型进行遍历，并逐步生成中间代码。

```c
InterCode translate_Exp(Node* node, Operand place){
    if (node->child_num==1){
        if (strcmp(node->children[0]->name,"ID")==0){//Exp->ID
            Operand var=new_Variable();
            strcpy(var->name,node->children[0]->value.str_value);
            InterCode code=new_Code();
            code->kind=ASSIGN;
            code->u.assign.left=place;
            code->u.assign.right=var;
            return code;
        }else if (strcmp(node->children[0]->name,"INT")==0){//Exp->INT
            Operand var=new_Variable();
            var->kind=CONSTANT;
            var->u.value=atoi(node->children[0]->value.str_value);
            InterCode code=new_Code();
            code->kind=ASSIGN;
            code->u.assign.left=place;
            code->u.assign.right=var;
            return code;
        }
    }
    ...
}
```

上述代码中的函数 `translate_Exp(Node* node, Operand place)` 用于生成表达式的中间代码。它接受一个分析树节点 `node` 和一个 `Operand` 类型的目标变量 `place`，表示将生成的表达式结果存放在 `place` 中。

在函数中，首先判断节点类型。如果节点的子节点只有一个，并且该子节点是标识符（ID）或整数（INT），则说明是一个简单的表达式，可以直接生成相应的中间代码。对于标识符，我们创建一个新的变量 `var`，并将其赋值为对应的标识符。对于整数，我们同样创建一个新的变量 `var`，并将其赋值为整数的值。然后，我们创建一条赋值语句的中间代码，将 `place` 作为左操作数，`var` 作为右操作数，最后返回该中间代码。

接下来的部分根据具体的语法规则和生成中间代码的需求，可以继续编写其他节点类型的处理逻辑。根据实际情况，可能需要处理变量声明、赋值语句、运算符表达式、条件语句等等。

这是一个简单的中间代码生成器的示例，可以根据具体的语法规则和需求进行扩展和优化。

#### 定义参数表存储寄存器：

```c
void init_tempvar_lable(){
    int i;
    for (i=0;i<100;i++){
        tempvar[i]=-1;
        lables[i]=-1;
    }
}
Operand new_tempvar(){
    int i;
    for (i=0;i<100;++i){
        if (tempvar[i]==-1){
            tempvar[i]=1;
            break;
        }
    }
    Operand result=new_Operand();
    result->kind=TEMPVAR;
    result->operand.tempvar=i+1;
    temp_Operands[i]=result;
    return result;
}
```

上述代码中的函数 `init_tempvar_lable()` 用于初始化寄存器相关的参数表。在这里，我们使用两个数组 `tempvar` 和 `labels` 来分别存储寄存器的使用情况和标签的使用情况。

- `tempvar` 数组：用于记录寄存器的使用情况。初始时，所有寄存器都设置为 `-1`，表示未被使用。当需要获取一个新的寄存器时，会在数组中找到第一个未被使用的寄存器，并将其标记为已使用。
- `lables` 数组：用于记录标签的使用情况。初始时，所有标签都设置为 `-1`，表示未被使用。当需要获取一个新的标签时，会在数组中找到第一个未被使用的标签，并将其标记为已使用。

函数 `new_tempvar()` 用于获取一个新的临时变量（寄存器）。它会遍历 `tempvar` 数组，找到第一个未被使用的寄存器，并将其标记为已使用。然后，创建一个新的 `Operand` 结构体，将其类型设置为 `TEMPVAR`，并将对应的寄存器编号存储在 `operand.tempvar` 字段中。最后，将新创建的 `Operand` 结构体存储在 `temp_Operands` 数组中，并返回该结构体作为结果。

这样，我们可以通过调用 `new_tempvar()` 函数来获取新的临时变量（寄存器），并在生成中间代码时使用这些临时变量来存储计算结果。









在分析表达式的时候，根据当前是什么类型的操作进行讨论处理：

1、如果是一个单一变量，直接赋值之后归约上去即可。

2、如果中间有操作，那么就需要多条三地址代码，最后归约上去即可。

```c
InterCode translate_Exp(tnode Exp, Operand place){
	//只有一个数字 建立赋值表达式后传递上去 
    if (Exp->ncld == 1 && !strcmp((Exp->cld)[0]->name, "INT")){
        Operand value = new_Const((Exp->cld)[0]->value);
        InterCode code = new_assign_Code(place, value);
        return code;
    }
    //只有一个变量 同样的建立赋值表达式后传递上去 
    else if (Exp->ncld == 1 && !strcmp((Exp->cld)[0]->name, "ID")){
        Operand variable = new_Variable((Exp->cld)[0]->content);
        InterCode code = new_assign_Code(place, variable);
        return code;
    }
    //一条赋值语句 如果父节点为空 那么就单纯赋值，否则要向上传递 a=b=c; 
    else if (Exp->ncld == 3 && !strcmp((Exp->cld)[1]->name, "ASSIGNOP")){
        Operand variable = new_Variable(((Exp->cld)[0]->cld)[0]->content);
        Operand t1 = new_tempvar();
        InterCode code1 = translate_Exp((Exp->cld)[2], t1);
        InterCode code2 = new_assign_Code(variable, t1);
        if (place==NULL)return add_Codes(2, code1, code2);
        else{
            InterCode code3 = new_assign_Code(place, variable);
            return add_Codes(3, code1, code2, code3);
        }
    }
    //加减法 
    else if (Exp->ncld==3&&(!strcmp((Exp->cld)[1]->name, "MINUS")||!strcmp((Exp->cld)[1]->name, "PLUS"))){
        Operand t1 = new_tempvar();
        Operand t2 = new_tempvar();
        InterCode code1 = translate_Exp((Exp->cld)[0], t1);
        InterCode code2 = translate_Exp((Exp->cld)[2], t2);
        InterCode code3 = new_Code();
        if(!strcmp((Exp->cld)[1]->name, "PLUS"))
           code3->kind=_ADD;
        else 
           code3->kind=_SUB;
        code3->operands.binop.result = place;
        code3->operands.binop.op1 = t1;
        code3->operands.binop.op2 = t2;
        return add_Codes(3, code1, code2, code3);
    }
    return new_Code();
}
```

在上述代码中，`translate_Exp` 函数用于分析表达式并生成相应的中间代码。根据表达式的类型和操作符进行不同的处理。

1. 如果表达式只包含一个数字（整数），则创建一个新的常量 `Operand`，将其值设置为该数字，并生成一条赋值语句的中间代码，将常量赋值给目标变量 `place`。
2. 如果表达式只包含一个变量（标识符），则创建一个新的变量 `Operand`，将其名称设置为该变量名，并生成一条赋值语句的中间代码，将变量赋值给目标变量 `place`。
3. 如果表达式是一条赋值语句（如 `a = b = c`），则首先分析右侧表达式 `(Exp->cld)[2]`，将其结果存储在临时变量 `t1` 中。然后，创建一条赋值语句的中间代码，将 `t1` 的值赋给左侧变量 `(Exp->cld)[0]`。如果目标变量 `place` 不为空，则再生成一条赋值语句的中间代码，将左侧变量的值赋给 `place`。
4. 如果表达式是加法或减法操作（如 `a + b` 或 `a - b`），则首先分析左右两个操作数的表达式，分别将其结果存储在临时变量 `t1` 和 `t2` 中。然后，创建一条加法或减法的中间代码，将 `t1` 和 `t2` 相加或相减，并将结果存储在目标变量 `place` 中。

需要注意的是，上述代码只处理了加法和减法的情况，并没有涵盖其他的操作符和语法规则。



由于这个任务只完成了一小部分，只能识别普通加减法语句，并且没有代码优化部分。



#### 程序运行方法

由于使用了词法分析和语法分析工具，故编译指令如下：

```
flex syntax.l
bison -d syntax.y
gcc syntax.tab.c syntax.c lex.yy.c -o parser
parser datax.c
```



#### 测试用例1

```c
int main()
{
  int i=1;
  int j=2;
  j=j+i;
  j=j+3;
}
```

```
FUNCTION main
t1 := #1
i := t1
t2 := #2
j := t2
t4 := j
t5 := i
t3 := t4 + t5
j := t3
t7 := j
t8 := #3
t6 := t7 + t8
j := t6
```



#### 测试用例2

```c
int main()
{
   int i=1;
   int j=1;
   int k=1;
   i=i+j-k;
   j=j-k+i; 
}
```

```
FUNCTION main
t1 := #1
i := t1
t2 := #1
j := t2
t3 := #1
k := t3
t7 := i
t8 := j
t5 := t7 + t8
t6 := k
t4 := t5 - t6
i := t4
t12 := j
t13 := k
t10 := t12 - t13
t11 := i
t9 := t10 + t11
j := t9
```





### 完成内容：

词法分析器部分的全部代码实现和中间代码生成中的寄存器查找部分代码编写。

语法分析中正则表达式的编写和对所有规约符号的语法动作编写，所有任务中文件读入模块的编写。

语法分析中文法的编写，语法分析中`AST`结构体以及其新建节点、先序遍历等代码的编写。

语义分析中链表等数据结构的实现、语义检查代码的编写，中间代码生成中简单翻译模式的编写。

实验收获：

​		这次的实验任务相对而言比较复杂，由于这个实验内容和上课所学内容有所区别，所以在刚开始做实验的时候也是遇到了许多困难；完成词法分析器的过程相对比较顺利，但是语法分析过程中走了许多弯路。在经过一下尝试后，我们决定使用`flex+bison`完成语法分析功能，为此我们也在网上查找了很多资料学习工具的使用，最后编写代码完成了语法分析任务满足了实验文件的要求(能够输出多行错误信息、能够判断进制错误)。

​		在后面的实验中我们完成了几种常见的语义错误的检查，尝试去实现了简单的中间代码生成。由于中间代码生成部分不能依靠语法分析器的功能，只能通过语法分析树手动实现，因此我们只实现了总任务的一部分，因此我们在这个过程中也明白了要真正实现一个完整的编译器是一件十分困难的事情。

​		总而言之，经过以上实验，我们对于编译原理课程中知识点的理解更加深入了，对于编译器的开发也有了浅层的认识与了解，对于编译原理课程在实际生活中的应用也有了大致的认识。

​		在这里，也感谢黄老师本学期的辛勤付出，让我们组收获了很多编译原理相关的知识。
