/*所有输入输出的txt文件都在Debug文件夹中，请将输入文件放在Debug中即可。*/
#pragma once
#include<string>
using namespace std;
#define _CRT_SECURE_NO_WARNINGS
enum TokenType
{
	TK_IF,        // if      1
	TK_THEN,      // then    2
	TK_ELSE,      // else    3
	TK_END,       // end     4 
	TK_REPEAT,    // repeat  5
	TK_UNTIL,     // until   6
	TK_READ,      // read    7
	TK_WRITE,     // write   8
	TK_WHILE,     // while   9
	TK_DO,        // do     10
	TK_TRUE,      // true   11
	TK_FALSE,     // false  12 
	TK_OR,        // or     13 
	TK_AND,       // and    14
	TK_NOT,       // not    15
	TK_INT,       // int    16
	TK_BOOL,      // bool   17
	TK_STRING,    // string 18
	TK_ID,        // 标识符 19
	TK_LSS,       // <      20
	TK_EQU,       // =      21
	TK_GTR,       // >      22
	TK_LEQ,       // <=     23 
	TK_GEQ,       // >=     24
	TK_ADD,       // +      25 
	TK_SUB,       // -      26
	TK_MUL,       // *      27
	TK_DIV,       // /      28
	TK_COMMA,     // ,      29
	TK_SEMICOLON, // ;      30 
	TK_ASSIGN,    // :=     31
	TK_LP,        // (      32 
	TK_RP,        // )      33
	TK_NUM,       // 整型数 34
	STRING        // 字符串 35
};
enum NodeType
{
	PROGRAM,       // 程序（开始符号）节点
	STMT_SEQUENCE, // 语句列表节点
	IF_STMT,	   // 条件语句节点
	REPEAT_STMT,   // repeat语句节点
	ASSIGN_STMT,   // 赋值语句节点
	READ_STMT,     // read语句节点
	WRITE_STMT,	   // write语句节点
	WHILE_STMT,	   // while语句节点
	GTR_EXP,       // 大于表达式节点
	GEQ_EXP,       // 大于等于表达式节点
	LSS_EXP,       // 小于表达式节点
	LEQ_EXP,       // 小于等于表达式节点
	EQU_EXP,       // 等于表达式节点
	COMP_EXP,      // 比较表达式结点
	LOG_OR_EXP,    // 逻辑或表达式节点
	LOG_AND_EXP,   // 逻辑与表达式节点
	LOG_NOT_EXP,   // 逻辑非表达式节点
	ADD_EXP,       // 加法表达式节点
	SUB_EXP,       // 减法表达式节点
	MUL_EXP,       // 乘法表达式节点
	DIV_EXP,       // 除法表达式节点
	FACTOR,        // 原子节点
};
enum ValType
{

	INT_TYPE,    // 整型数类型
	BOOL_TYPE,   // 布尔类型
	STRING_TYPE, // 字符串类型
	NULL_TYPE    // 中间节点类型
};
struct Token
{
	int kind;    //符号的Kind值，如TK_IF
	int ival;    //若符号是整型常量，则ival记录该常量的值
	string sval; //若符号是标识符或字符串常量，则sval记录标识符的名字或字符串
};
struct TreeNode
{
	NodeType nodetype;          //节点类型
	TreeNode* child[3];         //子节点的指针
	string id;                  //节点名字
	Token token;                //对应节点（当节点是FACTOR类型时该成员才有效）
	int intValue;                  //变量值（当节点是整型节点时该成员才有效）
	ValType valtype = NULL_TYPE;//节点属性（中间节点为NULL_TYPE）
};
void LexicalExecute(ifstream& infile, ofstream& outfile);
TreeNode* GrammaticalExecute(ifstream& infile, ofstream& outfile);
void PrintTree(TreeNode* root, ofstream& outfile);