/*所有输入输出的txt文件都在Debug文件夹中，请将输入文件放在Debug中即可。*/
#pragma once
#include<iostream>
#include<fstream>
#include<sstream>
#include<list>
#include"MainHeader.h"
TreeNode* Program(ofstream& outfile);
TreeNode* StmtSequence(ofstream& outfile);
TreeNode* LogOrExp(ofstream& outfile);