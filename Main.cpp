/*�������������txt�ļ�����Debug�ļ����У��뽫�����ļ�����Debug�м��ɡ�*/
#include"MainHeader.h"
#include <Windows.h>
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<list>
#include"CodeGen.h"

using namespace std;
string GetExeDir()//��ȡexe�ļ����ڵ�ַ��txt�ļ���Ҫ�ʹ˳���exe�ļ���ͬһ�ļ����ڣ�
{
	char exeFullPath[MAX_PATH];
	string strPath = "";
	GetModuleFileNameA(NULL, exeFullPath, MAX_PATH);
	strPath = (string)exeFullPath;
	int pos = strPath.find_last_of('\\', strPath.length());
	return strPath.substr(0, pos);
}
int main()
{
	string path = GetExeDir() + "/experiment2_test";
	ifstream infile1(path + "1_in.txt", ios::in);
	ofstream outfile1(path + "2_LexicalOut.txt", ios::out);
	LexicalExecute(infile1, outfile1);

	ifstream infile3(path + "2_LexicalOut.txt", ios::in);
	ofstream outfile3(path + "2_GrammaticalOut.txt", ios::in);
	TreeNode* syntaxTree1 = GrammaticalExecute(infile3, outfile3);
//	PrintTree(syntaxTree1, outfile3);


	CodeGen(syntaxTree1);

	system("pause");
}