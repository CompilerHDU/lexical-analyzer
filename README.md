# lexical-analyzer

## TASK

⼩组任务是完成SysY语⾔编译器模块开发，主要任务包括

1. 词法分析器
2. 语法分析器
3. 语义分析与中间代码⽣成器
4. 代码⽣成

⼩组⼈员最多3⼈，要求⾄少完成第1-2任务，⿎励完成任务3（时间来不及的话，可以实现语义分析或中间代码的 ⼀个部分，或者是语⾔的⼀个⼦集的语义翻译，⽐如表达式部分）

⼩组任务：完成2个实验，可获得70分左右（根据完成程度、团队协作、验收情况），每多完成1个实验加15 分，⼩组的实验报告和汇报材料（占10分）
小组人数权重：
     1人1组：基础分*1.05
     2人1组： 基础分*1.0
     3人1组： 基础分*0.95

分组信息本周完成（5月14日之前）
小组作业验收（6月12日，如果课程内容提前讲完，也可以提前验收）

ZJHgiegie is too handsome!  
DingGieGie is handsome & TQL, orz, %%%%%

## 环境

* C++11
* Flex 2.5.4
* Bison 2.4.1
* Windows(cmd)

## 使用

Flex与Bison的安装在此略过。

在项目根目录下编译：

```[cmd]
make run
```

编译成功后会得到`main.exe`与若干新文件。此时运行：

```[cmd]
./main
```

输入测试用程序：

```[c++]
int main(){
    printf("test\n");
    return 0;
}
```

可以看到输入了编译后的汇编代码。

此外，也可以对文件进行输入/输出：

```[cmd]
./main [path-to-code-file] [> output-file]
```
