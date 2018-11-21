/*所有输入输出的txt文件都在Debug文件夹中，请将输入文件放在Debug中即可。*/
#include"MainHeader.h"
#include <Windows.h>
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<list>
#include"CodeGen.h"

using namespace std;
string GetExeDir()//获取exe文件所在地址（txt文件需要和此程序exe文件在同一文件夹内）
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