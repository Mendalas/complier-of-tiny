/*�������������txt�ļ�����Debug�ļ����У��뽫�����ļ�����Debug�м��ɡ�*/
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
	TK_ID,        // ��ʶ�� 19
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
	TK_NUM,       // ������ 34
	STRING        // �ַ��� 35
};
enum NodeType
{
	PROGRAM,       // ���򣨿�ʼ���ţ��ڵ�
	STMT_SEQUENCE, // ����б�ڵ�
	IF_STMT,	   // �������ڵ�
	REPEAT_STMT,   // repeat���ڵ�
	ASSIGN_STMT,   // ��ֵ���ڵ�
	READ_STMT,     // read���ڵ�
	WRITE_STMT,	   // write���ڵ�
	WHILE_STMT,	   // while���ڵ�
	GTR_EXP,       // ���ڱ��ʽ�ڵ�
	GEQ_EXP,       // ���ڵ��ڱ��ʽ�ڵ�
	LSS_EXP,       // С�ڱ��ʽ�ڵ�
	LEQ_EXP,       // С�ڵ��ڱ��ʽ�ڵ�
	EQU_EXP,       // ���ڱ��ʽ�ڵ�
	COMP_EXP,      // �Ƚϱ��ʽ���
	LOG_OR_EXP,    // �߼�����ʽ�ڵ�
	LOG_AND_EXP,   // �߼�����ʽ�ڵ�
	LOG_NOT_EXP,   // �߼��Ǳ��ʽ�ڵ�
	ADD_EXP,       // �ӷ����ʽ�ڵ�
	SUB_EXP,       // �������ʽ�ڵ�
	MUL_EXP,       // �˷����ʽ�ڵ�
	DIV_EXP,       // �������ʽ�ڵ�
	FACTOR,        // ԭ�ӽڵ�
};
enum ValType
{

	INT_TYPE,    // ����������
	BOOL_TYPE,   // ��������
	STRING_TYPE, // �ַ�������
	NULL_TYPE    // �м�ڵ�����
};
struct Token
{
	int kind;    //���ŵ�Kindֵ����TK_IF
	int ival;    //�����������ͳ�������ival��¼�ó�����ֵ
	string sval; //�������Ǳ�ʶ�����ַ�����������sval��¼��ʶ�������ֻ��ַ���
};
struct TreeNode
{
	NodeType nodetype;          //�ڵ�����
	TreeNode* child[3];         //�ӽڵ��ָ��
	string id;                  //�ڵ�����
	Token token;                //��Ӧ�ڵ㣨���ڵ���FACTOR����ʱ�ó�Ա����Ч��
	int intValue;                  //����ֵ�����ڵ������ͽڵ�ʱ�ó�Ա����Ч��
	ValType valtype = NULL_TYPE;//�ڵ����ԣ��м�ڵ�ΪNULL_TYPE��
};
void LexicalExecute(ifstream& infile, ofstream& outfile);
TreeNode* GrammaticalExecute(ifstream& infile, ofstream& outfile);
void PrintTree(TreeNode* root, ofstream& outfile);