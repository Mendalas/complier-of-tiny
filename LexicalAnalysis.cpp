/*所有输入输出的txt文件都在Debug文件夹中，请将输入文件放在Debug中即可。*/
#include<iostream>
#include<fstream>
#include"MainHeader.h"
void OutputID(bool& previousIsID, bool& haveSpace, bool& haveT, string& spaceOrT, ostream& outfile, int j, string* token, int& colNum)
//判断是否应该输出ID标识
{
	if (j == 0)
		return;
	if (previousIsID)//前一个Token被确定为ID而非字符串中的字符（为输出错误所需）
	{
		previousIsID = false;
		spaceOrT = "";
		outfile << "(TK_ID," << token[j - 1] << ")\t";
		colNum++;
		if (colNum % 5 == 0)
			outfile << endl;
		haveSpace = false;
		haveT = false;
	}
}
void OutputEndl(int& colNum, ostream& outfile)//判断是否需要换行
{
	colNum++;
	if (colNum % 5 == 0)
		outfile << endl;
}
bool IsDigit(char c)//判断字符是否是数字
{
	if (c >= '0'&&c <= '9')
		return true;
	return false;
}
bool IsLetter(char c)//判断字符是否是字母
{
	if (c >= 'a'&&c <= 'z' || c >= 'A'&&c <= 'Z')
		return true;
	return false;
}
void LexicalExecute(ifstream& infile, ofstream& outfile)//词法分析执行程序
{
	char ch[10000];
	string token[10000], spaceOrT;//spaceOrT：存放空格和制表符的字符串（输出错误时使用）
	int j = 0, codeLen = 0, colNum = 0, codeRow = 1;
	//codeLen：txt的字符总数；colNum：输出是否需要换行（仅为输出能够美观）；codeRow：当前txt的行数
	bool previousIsID = false, haveSpace = false, haveT = false;
	//previousIsID：判断前一Token是否为标识符；haveSpace：判断字符串字符间是否有空格；haveT：判断字符串字符间是否有制表符
	for (int i = 0; !infile.eof(); i++)
	{
		ch[i] = infile.get();//一个字符一个字符地读取txt到数组ch[]中
		codeLen++;
	}
	codeLen--;
	for (int i = 0; i < codeLen; i++)//开始进行数组ch[]内字符识别 
	{
		if (IsLetter(ch[i]))//识别保留字或标识符或字符串
		{
			token[j] += ch[i];
			if (i < codeLen && !(IsLetter(ch[i + 1]) || IsDigit(ch[i + 1])))//后一个字符既不是字母也不是数字
			{
				//识别保留字
				if (token[j] == "true")
				{
					OutputID(previousIsID, haveSpace, haveT, spaceOrT, outfile, j, token, colNum);
					outfile << "(TK_TRUE," << token[j++] << ")\t";
					OutputEndl(colNum, outfile);
				}
				else if (token[j] == "false")
				{
					OutputID(previousIsID, haveSpace, haveT, spaceOrT, outfile, j, token, colNum);
					outfile << "(TK_FALSE," << token[j++] << ")\t";
					OutputEndl(colNum, outfile);
				}

				else if (token[j] == "or")
				{
					OutputID(previousIsID, haveSpace, haveT, spaceOrT, outfile, j, token, colNum);
					outfile << "(TK_OR," << token[j++] << ")\t";
					OutputEndl(colNum, outfile);
				}
				else if (token[j] == "and")
				{
					OutputID(previousIsID, haveSpace, haveT, spaceOrT, outfile, j, token, colNum);
					outfile << "(TK_AND," << token[j++] << ")\t";
					OutputEndl(colNum, outfile);
				}
				else if (token[j] == "not")
				{
					OutputID(previousIsID, haveSpace, haveT, spaceOrT, outfile, j, token, colNum);
					outfile << "(TK_NOT," << token[j++] << ")\t";
					OutputEndl(colNum, outfile);
				}
				else if (token[j] == "int")
				{
					OutputID(previousIsID, haveSpace, haveT, spaceOrT, outfile, j, token, colNum);
					outfile << "(TK_INT," << token[j++] << ")\t";
					OutputEndl(colNum, outfile);
				}
				else if (token[j] == "bool")
				{
					OutputID(previousIsID, haveSpace, haveT, spaceOrT, outfile, j, token, colNum);
					outfile << "(TK_BOOL," << token[j++] << ")\t";
					OutputEndl(colNum, outfile);
				}
				else if (token[j] == "string")
				{
					OutputID(previousIsID, haveSpace, haveT, spaceOrT, outfile, j, token, colNum);
					outfile << "(TK_STRING," << token[j++] << ")\t";
					OutputEndl(colNum, outfile);
				}
				else if (token[j] == "while")
				{
					OutputID(previousIsID, haveSpace, haveT, spaceOrT, outfile, j, token, colNum);
					outfile << "(TK_WHILE," << token[j++] << ")\t";
					OutputEndl(colNum, outfile);
				}
				else if (token[j] == "do")
				{
					OutputID(previousIsID, haveSpace, haveT, spaceOrT, outfile, j, token, colNum);
					outfile << "(TK_DO," << token[j++] << ")\t";
					OutputEndl(colNum, outfile);
				}
				else if (token[j] == "if")
				{
					OutputID(previousIsID, haveSpace, haveT, spaceOrT, outfile, j, token, colNum);
					outfile << "(TK_IF," << token[j++] << ")\t";
					OutputEndl(colNum, outfile);
				}
				else if (token[j] == "then")
				{
					OutputID(previousIsID, haveSpace, haveT, spaceOrT, outfile, j, token, colNum);
					outfile << "(TK_THEN," << token[j++] << ")\t";
					OutputEndl(colNum, outfile);
				}
				else if (token[j] == "else")
				{
					OutputID(previousIsID, haveSpace, haveT, spaceOrT, outfile, j, token, colNum);
					outfile << "(TK_ELSE," << token[j++] << ")\t";
					OutputEndl(colNum, outfile);
				}
				else if (token[j] == "end")
				{
					OutputID(previousIsID, haveSpace, haveT, spaceOrT, outfile, j, token, colNum);
					outfile << "(TK_END," << token[j++] << ")\t";
					OutputEndl(colNum, outfile);
				}
				else if (token[j] == "repeat")
				{
					OutputID(previousIsID, haveSpace, haveT, spaceOrT, outfile, j, token, colNum);
					outfile << "(TK_REPEAT," << token[j++] << ")\t";
					OutputEndl(colNum, outfile);
				}
				else if (token[j] == "until")
				{
					OutputID(previousIsID, haveSpace, haveT, spaceOrT, outfile, j, token, colNum);
					outfile << "(TK_UNTIL," << token[j++] << ")\t";
					OutputEndl(colNum, outfile);
				}
				else if (token[j] == "read")
				{
					OutputID(previousIsID, haveSpace, haveT, spaceOrT, outfile, j, token, colNum);
					outfile << "(TK_READ," << token[j++] << ")\t";
					OutputEndl(colNum, outfile);
				}
				else if (token[j] == "write")
				{
					OutputID(previousIsID, haveSpace, haveT, spaceOrT, outfile, j, token, colNum);
					outfile << "(TK_WRITE," << token[j++] << ")\t";
					OutputEndl(colNum, outfile);
				}
				else//Token都不是上述保留字，则确定是标识符还是缺失左引号或左大括号
				{
					if (previousIsID)//前一个token串也为标识符那这一个肯定不是标识符（两个标识符不能紧连）
					{
						if (haveSpace || haveT)
						{
							token[j - 1] += spaceOrT;
							spaceOrT = "";
							haveSpace = false;
							haveT = false;
						}
						token[j - 1] += token[j];
						token[j] = "";
						j--;
						i++;
						while (i < codeLen&&ch[i] != '\n'&&ch[i] != '\''&&ch[i] != '{'&&ch[i] != '}')
							//一直囊括后面的字符直到必要的中断
						{
							token[j] += ch[i++];
						}
						if (i == codeLen)//到了txt末尾（本质同下）
							outfile << endl << "第" << codeRow << "行错误：“" << token[j++] << "”为非法字符串。" << endl;
						else if (ch[i] == '\n' || ch[i] == '{')//没有大小括号或引号包含的字符串
						{
							outfile << endl << "第" << codeRow << "行错误：“" << token[j++] << "”为非法字符串。" << endl;
							colNum = 0;
							previousIsID = false;
							if (ch[i] == '\n')
								codeRow++;
						}
						else if (ch[i] == '}')
						{
							token[j] += ch[i];
							outfile << endl << "第" << codeRow << "行错误：“" << token[j++] << "”没有匹配的左大括号“{”。" << endl;
							colNum = 0;
							previousIsID = false;
						}
						else if (ch[i] == '\'')
						{
							token[j] += ch[i];//囊括引号再做后续判断
							if (i < codeLen&&ch[i + 1] == '\n')//该引号为右引号
							{
								outfile << endl << "第" << codeRow << "行错误：“" << token[j++] << "”没有匹配左引号。" << endl;
								colNum = 0;
								previousIsID = false;
							}
							else
							{
								if (i < codeLen)
								{
									i++;
									while (i < codeLen&&ch[i] != '\n'&&ch[i] != '}')
										token[j] += ch[i++];
								}
								if (i == codeLen)//到了txt末尾（本质同下）
									outfile << endl << "第" << codeRow << "行错误：“" << token[j] << "”为非法字符串。" << endl;
								else if (ch[i] == '\n')//没有大小括号或引号包含的字符串
								{
									outfile << endl << "第" << codeRow << "行错误：“" << token[j++] << "”为非法字符串。" << endl;
									colNum = 0;
									previousIsID = false;
									codeRow++;
								}
								else if (ch[i] == '}')
								{
									token[j] += ch[i];
									outfile << endl << "第" << codeRow << "行错误：“" << token[j++] << "”没有匹配的左大括号“{”。" << endl;
									colNum = 0;
									previousIsID = false;
								}
							}
						}
					}
					else//若前一个Token不是标识符，那这一个Token只能是标识符了
					{
						previousIsID = true;
						j++;
					}
				}
			}
			else if (i < codeLen&&IsDigit(ch[i + 1]))//若后一个字符是数字，则Token可能为标识符
			{
				do
				{
					i++;
					token[j] += ch[i];
				} while (i < codeLen && (IsLetter(ch[i + 1]) || IsDigit(ch[i + 1])));
				previousIsID = true;
				j++;
			}
			//若后一个字符是字母，继续扫描即可，故无else if (i < codeLen&&IsLetter(ch[i + 1]))
		}
		else if (IsDigit(ch[i]))//识别整数或字符串 
		{
			token[j] = ch[i];
			if (i < codeLen&&IsDigit(ch[i + 1]))//囊括尽可能多的数字
			{
				i++;
				do
				{
					token[j] += ch[i++];
				} while (i < codeLen&&IsDigit(ch[i]));
				i--;
			}
			if (i < codeLen&&IsLetter(ch[i + 1]))//数字后面紧跟的是字母的话Token肯定不是数字了
			{
				i++;
				do
				{
					token[j] += ch[i++];
				} while (i < codeLen && (IsLetter(ch[i]) || IsDigit(ch[i])));
				i--;
				OutputID(previousIsID, haveSpace, haveT, spaceOrT, outfile, j, token, colNum);
				outfile << endl << "第" << codeRow << "行错误：“" << token[j++] << "”为非法标识符。" << endl;//识别非法标识符
				colNum = 0;
			}
			else//Token为整数
			{
				OutputID(previousIsID, haveSpace, haveT, spaceOrT, outfile, j, token, colNum);
				outfile << "(TK_NUM," << token[j++] << ")\t";//识别整数
				OutputEndl(colNum, outfile);
			}
		}
		else//识别其它符号
		{
			switch (ch[i])
			{
			case '>':
			{
				if (i < codeLen&&ch[i + 1] == '=')//识别符号>=
				{
					token[j] = ch[i++];
					token[j] += ch[i];
					OutputID(previousIsID, haveSpace, haveT, spaceOrT, outfile, j, token, colNum);
					outfile << "(TK_GEQ," << token[j++] << ")\t";
				}
				else//识别符号>
				{
					token[j] += ch[i];
					OutputID(previousIsID, haveSpace, haveT, spaceOrT, outfile, j, token, colNum);
					outfile << "(TK_GTR," << token[j++] << ")\t";
				}
				OutputEndl(colNum, outfile);
			}; break;
			case '<':
			{
				if (i < codeLen&&ch[i + 1] == '=')//识别符号<=
				{
					token[j] = ch[i++];
					token[j] += ch[i];
					OutputID(previousIsID, haveSpace, haveT, spaceOrT, outfile, j, token, colNum);
					outfile << "(TK_LEQ," << token[j++] << ")\t";
				}
				else//识别符号<
				{
					token[j] += ch[i];
					OutputID(previousIsID, haveSpace, haveT, spaceOrT, outfile, j, token, colNum);
					outfile << "(TK_LSS," << token[j++] << ")\t";
				}
				OutputEndl(colNum, outfile);
			}; break;
			case ',':
			{
				token[j] += ch[i];
				OutputID(previousIsID, haveSpace, haveT, spaceOrT, outfile, j, token, colNum);
				outfile << "(TK_COMMA," << token[j++] << ")\t";
				OutputEndl(colNum, outfile);
			}; break;
			case ';':
			{
				token[j] += ch[i];
				OutputID(previousIsID, haveSpace, haveT, spaceOrT, outfile, j, token, colNum);
				outfile << "(TK_SEMICOLON," << token[j++] << ")\t";
				OutputEndl(colNum, outfile);
			}; break;
			case ':':
			{
				if (i < codeLen&&ch[i + 1] == '=')//识别符号:=
				{
					token[j] = ch[i++];
					token[j] += ch[i];
					OutputID(previousIsID, haveSpace, haveT, spaceOrT, outfile, j, token, colNum);
					outfile << "(TK_ASSIGN," << token[j++] << ")\t";
					OutputEndl(colNum, outfile);
				}
			}; break;
			case '+':
			{
				token[j] += ch[i];
				OutputID(previousIsID, haveSpace, haveT, spaceOrT, outfile, j, token, colNum);
				outfile << "(TK_ADD," << token[j++] << ")\t";
				OutputEndl(colNum, outfile);
			}; break;
			case '-':
			{
				token[j] += ch[i];
				OutputID(previousIsID, haveSpace, haveT, spaceOrT, outfile, j, token, colNum);
				outfile << "(TK_SUB," << token[j++] << ")\t";
				OutputEndl(colNum, outfile);
			}; break;
			case '*':
			{
				token[j] += ch[i];
				OutputID(previousIsID, haveSpace, haveT, spaceOrT, outfile, j, token, colNum);
				outfile << "(TK_MUL," << token[j++] << ")\t";
				OutputEndl(colNum, outfile);
			}; break;
			case '/':
			{
				token[j] += ch[i];
				OutputID(previousIsID, haveSpace, haveT, spaceOrT, outfile, j, token, colNum);
				outfile << "(TK_DIV," << token[j++] << ")\t";
				OutputEndl(colNum, outfile);
			}; break;
			case '(':
			{
				token[j] += ch[i];
				OutputID(previousIsID, haveSpace, haveT, spaceOrT, outfile, j, token, colNum);
				outfile << "(TK_LP," << token[j++] << ")\t";
				OutputEndl(colNum, outfile);
			}; break;
			case ')':
			{
				token[j] += ch[i];
				OutputID(previousIsID, haveSpace, haveT, spaceOrT, outfile, j, token, colNum);
				outfile << "(TK_RP," << token[j++] << ")\t";
				OutputEndl(colNum, outfile);
			}; break;
			case '{':
			{
				token[j] += ch[i];
				if (i < codeLen)
					i++;
				while (i < codeLen&&ch[i] != '{'&&ch[i] != '}'&&ch[i] != '\n')
					token[j] += ch[i++];
				if (i == codeLen)//txt到达文件末尾
				{
					OutputID(previousIsID, haveSpace, haveT, spaceOrT, outfile, j, token, colNum);
					outfile << endl << "第" << codeRow << "行错误：“" << token[j++] << "”没有匹配的右大括号“}”。" << endl;
					i--;
				}
				else if (ch[i] == '{' || ch[i] == '\n')
				{
					OutputID(previousIsID, haveSpace, haveT, spaceOrT, outfile, j, token, colNum);
					outfile << endl << "第" << codeRow << "行错误：“" << token[j++] << "”没有匹配的右大括号“}”。" << endl;
					i--;
					if (ch[i] == '\n')
						codeRow++;
				}
				else if (ch[i] == '}')
					token[j] = "";
			}; break;
			case '}':
			{
				token[j] += ch[i];
				OutputID(previousIsID, haveSpace, haveT, spaceOrT, outfile, j, token, colNum);
				outfile << endl << "第" << codeRow << "行错误：“" << token[j++] << "”没有匹配的左大括号“{”。" << endl;
			}; break;
			case '=':
			{
				token[j] += ch[i];
				OutputID(previousIsID, haveSpace, haveT, spaceOrT, outfile, j, token, colNum);
				outfile << "(TK_EQU," << token[j++] << ")\t";
				OutputEndl(colNum, outfile);
			}; break;
			case'\'':
			{
				if (i < codeLen)
				{
					i++;
					while (i < codeLen&&ch[i] != '\n' && ch[i] != '\'')
						token[j] += ch[i++];
				}
				if (i == codeLen)//txt到达文件末尾
				{
					OutputID(previousIsID, haveSpace, haveT, spaceOrT, outfile, j, token, colNum);
					outfile << endl << "第" << codeRow << "行错误：“\'" << token[j++] << "”没有匹配右引号。" << endl;
					i--;
				}
				if (ch[i] == '\'')
				{
					OutputID(previousIsID, haveSpace, haveT, spaceOrT, outfile, j, token, colNum);
					outfile << "(STRING," << token[j++] << ")\t";
					OutputEndl(colNum, outfile);
				}
				if (ch[i] == '\n')
				{
					OutputID(previousIsID, haveSpace, haveT, spaceOrT, outfile, j, token, colNum);
					outfile << endl << "第" << codeRow << "行错误：“\'" << token[j++] << "”没有匹配右引号。" << endl;
					colNum = 0;
					codeRow++;
				}
			}; break;
			case' ':
			{
				if (previousIsID)
				{
					spaceOrT += " ";
					haveSpace = true;
				}
			}; break;
			case'\t':
			{
				if (previousIsID)
				{
					spaceOrT += "\t";
					haveT = true;
				}
			}; break;
			case'\n':
			{
				codeRow++;
			}; break;
			default:
			{
				token[j] = ch[i];
				OutputID(previousIsID, haveSpace, haveT, spaceOrT, outfile, j, token, colNum);
				outfile << endl << "第" << codeRow << "行错误：“" << token[j++] << "”为非法字符。" << endl;
				colNum = 0;
			}break;
			}
		}
	}
	outfile.close();//关闭文件
	infile.close();//关闭文件
}