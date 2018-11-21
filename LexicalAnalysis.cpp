/*�������������txt�ļ�����Debug�ļ����У��뽫�����ļ�����Debug�м��ɡ�*/
#include<iostream>
#include<fstream>
#include"MainHeader.h"
void OutputID(bool& previousIsID, bool& haveSpace, bool& haveT, string& spaceOrT, ostream& outfile, int j, string* token, int& colNum)
//�ж��Ƿ�Ӧ�����ID��ʶ
{
	if (j == 0)
		return;
	if (previousIsID)//ǰһ��Token��ȷ��ΪID�����ַ����е��ַ���Ϊ����������裩
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
void OutputEndl(int& colNum, ostream& outfile)//�ж��Ƿ���Ҫ����
{
	colNum++;
	if (colNum % 5 == 0)
		outfile << endl;
}
bool IsDigit(char c)//�ж��ַ��Ƿ�������
{
	if (c >= '0'&&c <= '9')
		return true;
	return false;
}
bool IsLetter(char c)//�ж��ַ��Ƿ�����ĸ
{
	if (c >= 'a'&&c <= 'z' || c >= 'A'&&c <= 'Z')
		return true;
	return false;
}
void LexicalExecute(ifstream& infile, ofstream& outfile)//�ʷ�����ִ�г���
{
	char ch[10000];
	string token[10000], spaceOrT;//spaceOrT����ſո���Ʊ�����ַ������������ʱʹ�ã�
	int j = 0, codeLen = 0, colNum = 0, codeRow = 1;
	//codeLen��txt���ַ�������colNum������Ƿ���Ҫ���У���Ϊ����ܹ����ۣ���codeRow����ǰtxt������
	bool previousIsID = false, haveSpace = false, haveT = false;
	//previousIsID���ж�ǰһToken�Ƿ�Ϊ��ʶ����haveSpace���ж��ַ����ַ����Ƿ��пո�haveT���ж��ַ����ַ����Ƿ����Ʊ��
	for (int i = 0; !infile.eof(); i++)
	{
		ch[i] = infile.get();//һ���ַ�һ���ַ��ض�ȡtxt������ch[]��
		codeLen++;
	}
	codeLen--;
	for (int i = 0; i < codeLen; i++)//��ʼ��������ch[]���ַ�ʶ�� 
	{
		if (IsLetter(ch[i]))//ʶ�����ֻ��ʶ�����ַ���
		{
			token[j] += ch[i];
			if (i < codeLen && !(IsLetter(ch[i + 1]) || IsDigit(ch[i + 1])))//��һ���ַ��Ȳ�����ĸҲ��������
			{
				//ʶ������
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
				else//Token���������������֣���ȷ���Ǳ�ʶ������ȱʧ�����Ż��������
				{
					if (previousIsID)//ǰһ��token��ҲΪ��ʶ������һ���϶����Ǳ�ʶ����������ʶ�����ܽ�����
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
							//һֱ����������ַ�ֱ����Ҫ���ж�
						{
							token[j] += ch[i++];
						}
						if (i == codeLen)//����txtĩβ������ͬ�£�
							outfile << endl << "��" << codeRow << "�д��󣺡�" << token[j++] << "��Ϊ�Ƿ��ַ�����" << endl;
						else if (ch[i] == '\n' || ch[i] == '{')//û�д�С���Ż����Ű������ַ���
						{
							outfile << endl << "��" << codeRow << "�д��󣺡�" << token[j++] << "��Ϊ�Ƿ��ַ�����" << endl;
							colNum = 0;
							previousIsID = false;
							if (ch[i] == '\n')
								codeRow++;
						}
						else if (ch[i] == '}')
						{
							token[j] += ch[i];
							outfile << endl << "��" << codeRow << "�д��󣺡�" << token[j++] << "��û��ƥ���������š�{����" << endl;
							colNum = 0;
							previousIsID = false;
						}
						else if (ch[i] == '\'')
						{
							token[j] += ch[i];//�����������������ж�
							if (i < codeLen&&ch[i + 1] == '\n')//������Ϊ������
							{
								outfile << endl << "��" << codeRow << "�д��󣺡�" << token[j++] << "��û��ƥ�������š�" << endl;
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
								if (i == codeLen)//����txtĩβ������ͬ�£�
									outfile << endl << "��" << codeRow << "�д��󣺡�" << token[j] << "��Ϊ�Ƿ��ַ�����" << endl;
								else if (ch[i] == '\n')//û�д�С���Ż����Ű������ַ���
								{
									outfile << endl << "��" << codeRow << "�д��󣺡�" << token[j++] << "��Ϊ�Ƿ��ַ�����" << endl;
									colNum = 0;
									previousIsID = false;
									codeRow++;
								}
								else if (ch[i] == '}')
								{
									token[j] += ch[i];
									outfile << endl << "��" << codeRow << "�д��󣺡�" << token[j++] << "��û��ƥ���������š�{����" << endl;
									colNum = 0;
									previousIsID = false;
								}
							}
						}
					}
					else//��ǰһ��Token���Ǳ�ʶ��������һ��Tokenֻ���Ǳ�ʶ����
					{
						previousIsID = true;
						j++;
					}
				}
			}
			else if (i < codeLen&&IsDigit(ch[i + 1]))//����һ���ַ������֣���Token����Ϊ��ʶ��
			{
				do
				{
					i++;
					token[j] += ch[i];
				} while (i < codeLen && (IsLetter(ch[i + 1]) || IsDigit(ch[i + 1])));
				previousIsID = true;
				j++;
			}
			//����һ���ַ�����ĸ������ɨ�輴�ɣ�����else if (i < codeLen&&IsLetter(ch[i + 1]))
		}
		else if (IsDigit(ch[i]))//ʶ���������ַ��� 
		{
			token[j] = ch[i];
			if (i < codeLen&&IsDigit(ch[i + 1]))//���������ܶ������
			{
				i++;
				do
				{
					token[j] += ch[i++];
				} while (i < codeLen&&IsDigit(ch[i]));
				i--;
			}
			if (i < codeLen&&IsLetter(ch[i + 1]))//���ֺ������������ĸ�Ļ�Token�϶�����������
			{
				i++;
				do
				{
					token[j] += ch[i++];
				} while (i < codeLen && (IsLetter(ch[i]) || IsDigit(ch[i])));
				i--;
				OutputID(previousIsID, haveSpace, haveT, spaceOrT, outfile, j, token, colNum);
				outfile << endl << "��" << codeRow << "�д��󣺡�" << token[j++] << "��Ϊ�Ƿ���ʶ����" << endl;//ʶ��Ƿ���ʶ��
				colNum = 0;
			}
			else//TokenΪ����
			{
				OutputID(previousIsID, haveSpace, haveT, spaceOrT, outfile, j, token, colNum);
				outfile << "(TK_NUM," << token[j++] << ")\t";//ʶ������
				OutputEndl(colNum, outfile);
			}
		}
		else//ʶ����������
		{
			switch (ch[i])
			{
			case '>':
			{
				if (i < codeLen&&ch[i + 1] == '=')//ʶ�����>=
				{
					token[j] = ch[i++];
					token[j] += ch[i];
					OutputID(previousIsID, haveSpace, haveT, spaceOrT, outfile, j, token, colNum);
					outfile << "(TK_GEQ," << token[j++] << ")\t";
				}
				else//ʶ�����>
				{
					token[j] += ch[i];
					OutputID(previousIsID, haveSpace, haveT, spaceOrT, outfile, j, token, colNum);
					outfile << "(TK_GTR," << token[j++] << ")\t";
				}
				OutputEndl(colNum, outfile);
			}; break;
			case '<':
			{
				if (i < codeLen&&ch[i + 1] == '=')//ʶ�����<=
				{
					token[j] = ch[i++];
					token[j] += ch[i];
					OutputID(previousIsID, haveSpace, haveT, spaceOrT, outfile, j, token, colNum);
					outfile << "(TK_LEQ," << token[j++] << ")\t";
				}
				else//ʶ�����<
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
				if (i < codeLen&&ch[i + 1] == '=')//ʶ�����:=
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
				if (i == codeLen)//txt�����ļ�ĩβ
				{
					OutputID(previousIsID, haveSpace, haveT, spaceOrT, outfile, j, token, colNum);
					outfile << endl << "��" << codeRow << "�д��󣺡�" << token[j++] << "��û��ƥ����Ҵ����š�}����" << endl;
					i--;
				}
				else if (ch[i] == '{' || ch[i] == '\n')
				{
					OutputID(previousIsID, haveSpace, haveT, spaceOrT, outfile, j, token, colNum);
					outfile << endl << "��" << codeRow << "�д��󣺡�" << token[j++] << "��û��ƥ����Ҵ����š�}����" << endl;
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
				outfile << endl << "��" << codeRow << "�д��󣺡�" << token[j++] << "��û��ƥ���������š�{����" << endl;
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
				if (i == codeLen)//txt�����ļ�ĩβ
				{
					OutputID(previousIsID, haveSpace, haveT, spaceOrT, outfile, j, token, colNum);
					outfile << endl << "��" << codeRow << "�д��󣺡�\'" << token[j++] << "��û��ƥ�������š�" << endl;
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
					outfile << endl << "��" << codeRow << "�д��󣺡�\'" << token[j++] << "��û��ƥ�������š�" << endl;
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
				outfile << endl << "��" << codeRow << "�д��󣺡�" << token[j++] << "��Ϊ�Ƿ��ַ���" << endl;
				colNum = 0;
			}break;
			}
		}
	}
	outfile.close();//�ر��ļ�
	infile.close();//�ر��ļ�
}