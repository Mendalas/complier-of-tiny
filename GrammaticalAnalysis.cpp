/*�������������txt�ļ�����Debug�ļ����У��뽫�����ļ�����Debug�м��ɡ�*/
#include"GrammaticalHeader.h"
list<Token> tokens;
Token token;
TreeNode * root;
int nodeID = 0;
list<Token>::iterator tokensIterator;
string setId()
{
	char str[4];
	_itoa_s(nodeID, str, 10); //_itoa_s��int ת��Ϊ char* �ĺ���
	string a = "node";
	a += str;
	nodeID++;
	return a;
}
list<Token> GetToken(ifstream& infile)//��������token��
{
	list<string> txtStr;//�洢txt�ı������ַ���
	list<Token> tokens;//�洢txt�ı�����token��
	for (int i = 0; !infile.eof(); i++)
	{
		string tempStr;//�������ַ�������txtStr
		getline(infile, tempStr);//һ��һ�еض�ȡ�ʷ����������token��tempStr��
		txtStr.push_back(tempStr);//���ַ�������txtStr
	}
	infile.close();//�ر��ļ�
	for (list<string>::iterator i = txtStr.begin(); i != txtStr.end(); i++)//��ʼ���д���token
	{
		string tempStr = *i;//�����ĵ���һ��
		istringstream is(tempStr);
		string tokenStr[5];//һ��5��token���ʷ�����ʱ���Լ������������򣩣��洢ÿ�е�token
		for (int i = 0; i < 5; i++)
			is >> tokenStr[i];
		for (int i = 0; i < 5; i++)
		{
			if (tokenStr[i] != "")
			{
				int index = tokenStr[i].find(',');//���Ҷ��ŵ�λ�ã���ȡ����ǰ��Token����
				Token tmpToken;//��ʱtoken������token����tokens��
				string tmpStr;//�洢token����
				tmpStr = tokenStr[i].substr(1, index - 1);//����token���ͣ���TK_IF
				//���ƥ�仹ԭ
				if (tmpStr == "TK_IF")
				{
					tmpToken.kind = TK_IF;
					tmpToken.sval.assign("if");
				}
				else if (tmpStr == "TK_THEN")
				{
					tmpToken.kind = TK_THEN;
					tmpToken.sval.assign("then");
				}
				else if (tmpStr == "TK_ELSE")
				{
					tmpToken.kind = TK_ELSE;
					tmpToken.sval.assign("else");
				}
				else if (tmpStr == "TK_END")
				{
					tmpToken.kind = TK_END;
					tmpToken.sval.assign("end");
				}
				else if (tmpStr == "TK_REPEAT")
				{
					tmpToken.kind = TK_REPEAT;
					tmpToken.sval.assign("repeat");
				}
				else if (tmpStr == "TK_UNTIL")
				{
					tmpToken.kind = TK_UNTIL;
					tmpToken.sval.assign("until");
				}
				else if (tmpStr == "TK_READ")
				{
					tmpToken.kind = TK_READ;
					tmpToken.sval.assign("read");
				}
				else if (tmpStr == "TK_WRITE")
				{
					tmpToken.kind = TK_WRITE;
					tmpToken.sval.assign("write");
				}
				else if (tmpStr == "TK_WHILE")
				{
					tmpToken.kind = TK_WHILE;
					tmpToken.sval.assign("while");
				}
				else if (tmpStr == "TK_DO")
				{
					tmpToken.kind = TK_DO;
					tmpToken.sval.assign("do");
				}
				else if (tmpStr == "TK_TRUE")
				{
					tmpToken.kind = TK_TRUE;
					tmpToken.sval.assign("true");
				}
				else if (tmpStr == "TK_FALSE")
				{
					tmpToken.kind = TK_FALSE;
					tmpToken.sval.assign("false");
				}
				else if (tmpStr == "TK_OR")
				{
					tmpToken.kind = TK_OR;
					tmpToken.sval.assign("or");
				}
				else if (tmpStr == "TK_AND")
				{
					tmpToken.kind = TK_AND;
					tmpToken.sval.assign("and");
				}
				else if (tmpStr == "TK_NOT")
				{
					tmpToken.kind = TK_NOT;
					tmpToken.sval.assign("not");
				}
				else if (tmpStr == "TK_INT")
				{
					tmpToken.kind = TK_INT;
					tmpToken.sval.assign("int");
				}
				else if (tmpStr == "TK_BOOL")
				{
					tmpToken.kind = TK_BOOL;
					tmpToken.sval.assign("bool");
				}
				else if (tmpStr == "TK_STRING")
				{
					tmpToken.kind = TK_STRING;
					tmpToken.sval.assign("string");
				}
				else if (tmpStr == "TK_ID")
				{
					tmpToken.kind = TK_ID;
					int indexEnd = tokenStr[i].find(')');//���ҡ�)����λ�ã���ȡ��)��ǰ�ı�ʶ��ֵ
					string tmp = tokenStr[i].substr(index + 1, indexEnd - index - 1);//���Ʊ�ʶ��ֵ
					tmpToken.sval.assign(tmp);
				}
				else if (tmpStr == "TK_LSS")
				{
					tmpToken.kind = TK_LSS;
					tmpToken.sval.assign("<");
				}
				else if (tmpStr == "TK_EQU")
				{
					tmpToken.kind = TK_EQU;
					tmpToken.sval.assign("=");
				}
				else if (tmpStr == "TK_GTR")
				{
					tmpToken.kind = TK_GTR;
					tmpToken.sval.assign(">");
				}
				else if (tmpStr == "TK_LEQ")
				{
					tmpToken.kind = TK_LEQ;
					tmpToken.sval.assign("<=");
				}
				else if (tmpStr == "TK_GEQ")
				{
					tmpToken.kind = TK_GEQ;
					tmpToken.sval.assign(">=");
				}
				else if (tmpStr == "TK_ADD")
				{
					tmpToken.kind = TK_ADD;
					tmpToken.sval.assign("+");
				}
				else if (tmpStr == "TK_SUB")
				{
					tmpToken.kind = TK_SUB;
					tmpToken.sval.assign("-");
				}
				else if (tmpStr == "TK_MUL")
				{
					tmpToken.kind = TK_MUL;
					tmpToken.sval.assign("*");
				}
				else if (tmpStr == "TK_DIV")
				{
					tmpToken.kind = TK_DIV;
					tmpToken.sval.assign("/");
				}
				else if (tmpStr == "TK_COMMA")
				{
					tmpToken.kind = TK_COMMA;
					tmpToken.sval.assign(",");
				}
				else if (tmpStr == "TK_SEMICOLON")
				{
					tmpToken.kind = TK_SEMICOLON;
					tmpToken.sval.assign(";");
				}
				else if (tmpStr == "TK_ASSIGN")
				{
					tmpToken.kind = TK_ASSIGN;
					tmpToken.sval.assign(":=");
				}
				else if (tmpStr == "TK_LP")
				{
					tmpToken.kind = TK_LP;
					tmpToken.sval.assign("(");
				}
				else if (tmpStr == "TK_RP")
				{
					tmpToken.kind = TK_RP;
					tmpToken.sval.assign(")");
				}
				else if (tmpStr == "TK_NUM")
				{
					tmpToken.kind = TK_NUM;
					int indexEnd = tokenStr[i].find(')');//���ҡ�)����λ�ã���ȡ��)��ǰ�ı�ʶ��ֵ
					string tmp = tokenStr[i].substr(index + 1, indexEnd - index - 1);//��������ֵ
					tmpToken.ival = atoi(tmp.c_str());//atoi��char* ת��Ϊ int �ĺ���
				}
				else if (tmpStr == "STRING")
				{
					tmpToken.kind = STRING;
					int indexEnd = tokenStr[i].find(')');//���ҡ�)����λ�ã���ȡ��)��ǰ���ַ���ֵ
					string tmp = tokenStr[i].substr(index + 1, indexEnd - index - 1);//�����ַ���ֵ
					tmpToken.sval.assign(tmp);
				}
				tokens.push_back(tmpToken);//�������õ���token����tokens��
			}
		}
	}
	return tokens;
}
void NextToken()
{
	if (tokensIterator != tokens.end())
		token = *tokensIterator++;//��ȡ��һ��token
}
bool match(int* kindSet,int setNum, ofstream& outfile)
{
	for (int i = 0; i < setNum; i++)
	{
		if (token.kind == kindSet[i])//ƥ��ɹ�
		{
			NextToken();
			return true;
		}
	}
	//��ƥ��ʧ��
	if (token.kind == TK_NUM)
		outfile << "����" << token.ival << "�����Ͳ�ƥ��" << endl;
	else
		outfile << "����" << token.sval << "�����Ͳ�ƥ��" << endl;
	return false;
}
TreeNode* GrammaticalExecute(ifstream& infile, ofstream& outfile)//�﷨����ִ�г���
{
	tokens = GetToken(infile);//��ȡ����token��token����
	tokensIterator = tokens.begin();//��ʼ��tokens��ָ��
	NextToken();//��ȡ��һ��token
	root = Program(outfile);//��ʼ��ȡ�﷨��,programΪ���,outfileΪ����ļ���ַ
	return root;//�����﷨���ĸ��ڵ�
}
TreeNode* Factor(ofstream& outfile)
{
	int factorType[6] = { TK_NUM, STRING, TK_ID, TK_TRUE, TK_FALSE, TK_LP };//Factor��Ӧ��token����
	Token tmpToken = token;
	if (!match(factorType, 6, outfile))//ƥ��Factor����
	{
		return NULL;
	}
	TreeNode *node = NULL;
	if (tmpToken.kind == TK_LP)//FactorΪһ������
	{
		//����Ҫ��ƥ��������
		node = LogOrExp(outfile);//ƥ��or����
		int tokenType[1] = { TK_RP }; 
		match(tokenType, 1, outfile);//ƥ��������
	}
	else//token��number��string��identifier��true��false�е�һ��
	{
		//����FACTOR�ڵ㣬û�к���
		node = new TreeNode{ FACTOR };//token��ΪFactor�ڵ�ĺ���
		node->token = tmpToken;
		//���������͸��ƣ�
		if (tmpToken.kind == TK_NUM)
		{
			node->valtype = INT_TYPE;
			node->intValue = tmpToken.ival;
		}
		else if (tmpToken.kind == TK_TRUE || tmpToken.kind == TK_FALSE)
			node->valtype = BOOL_TYPE;
		else
			node->valtype = STRING_TYPE;
	}
	node->id = setId();
	return node;
}
TreeNode* MulExp(ofstream& outfile)
{
	TreeNode *node = NULL, *factor = NULL, *nextMulExp = NULL;
	factor = Factor(outfile);//����factor����
	if (tokensIterator != tokens.end())
	{
		if (token.kind== TK_MUL|| token.kind == TK_DIV)//���˳��ź��滹�г˳���䣬��ƥ��˳���
		{
			switch (token.kind)
			{
			case TK_MUL:node = new TreeNode{ MUL_EXP }; break;
			case TK_DIV:node = new TreeNode{ DIV_EXP }; break;
			}
			NextToken();
			nextMulExp = MulExp(outfile);//�����˳��ź�������
		}
		else//��û�г˳���
			node = new TreeNode{ MUL_EXP };
	}
	else//��û�г˳���
		node = new TreeNode{ MUL_EXP };
	//����MUL_EXP�ڵ㣬��2�����ӣ��ֱ���factor��mul���
	node->child[0] = factor;
	node->child[1] = nextMulExp;
	node->id = setId();
	return node;
}
TreeNode* AddExp(ofstream& outfile)
{
	TreeNode *node = NULL, *mulExp = NULL, *nextAddExp = NULL;
	mulExp = MulExp(outfile);//�����˷���䲿��
	if (tokensIterator != tokens.end())
	{
		if (token.kind == TK_ADD || token.kind == TK_SUB)//���Ӽ��ź��滹�мӼ���䣬��ƥ��Ӽ���
		{
			switch (token.kind)
			{
			case TK_ADD:node = new TreeNode{ ADD_EXP }; break;
			case TK_SUB:node = new TreeNode{ SUB_EXP }; break;
			}
			NextToken();
			nextAddExp = AddExp(outfile);//�����Ӽ��ź�������
		}
		else//��û�мӼ���
			node = new TreeNode{ ADD_EXP };
	}
	else//��û�мӼ���
		node = new TreeNode{ ADD_EXP };
	//����ADD_EXP�ڵ㣬��2�����ӣ��ֱ���mul��䡢add���
	node->child[0] = mulExp;
	node->child[1] = nextAddExp;
	node->id = setId();
	return node;
}
TreeNode* CompExp(ofstream& outfile)
{
	TreeNode *node = NULL, *addExp = NULL, *nextComparisonExp = NULL;
	addExp = AddExp(outfile);//�����ӷ���䲿��
	if (tokensIterator != tokens.end())
	{
		int tokenType[5] = { TK_LSS, TK_EQU, TK_GTR, TK_LEQ,TK_GEQ };
		bool flag = false;//�ж�token�����Ƿ�Ϊ����5�������е�һ��
		for (int i = 0; i < 5; i++)
		{
			if (token.kind == tokenType[i])
			{
				flag = true;
				break;
			}
		}
		if (flag)//���ȽϷ��ź��滹�бȽ���䣬��ƥ��ȽϷ���
		{
			switch (token.kind)
			{
			case TK_GTR:node = new TreeNode{ GTR_EXP }; break;
			case TK_GEQ:node = new TreeNode{ GEQ_EXP }; break;
			case TK_LSS:node = new TreeNode{ LSS_EXP }; break;
			case TK_LEQ:node = new TreeNode{ LEQ_EXP }; break;
			case TK_EQU:node = new TreeNode{ EQU_EXP }; break;
			}
			NextToken();
			nextComparisonExp = CompExp(outfile);//��������Ƚ���䲿��
		}
		else//��û�бȽϷ���
			node = new TreeNode{ COMP_EXP };
	}
	else//��û�бȽϷ���
		node = new TreeNode{ COMP_EXP };
	//����COMP_EXP�ڵ㣬��2�����ӣ��ֱ���add��䡢�Ƚ����
	node->child[0] = addExp;
	node->child[1] = nextComparisonExp;
	node->id = setId();
	return node;
}
TreeNode* LogAndExp(ofstream& outfile)
{
	TreeNode *comparisonExp = NULL, *logicalAndExp = NULL;
	comparisonExp = CompExp(outfile);//�����Ƚ���䲿��
	if (tokensIterator != tokens.end())
	{
		if (token.kind == TK_AND)//�����滹��and��䣬��ƥ��and
		{
			NextToken();
			logicalAndExp = LogAndExp(outfile);//����and��䲿��
		}
	}	
	//����LOG_AND_EXP�ڵ㣬��2�����ӣ��ֱ��ǱȽ���䡢and���
	TreeNode *node = new TreeNode{ LOG_AND_EXP };
	node->child[0] = comparisonExp;
	node->child[1] = logicalAndExp;
	node->id = setId();
	return node;
}
TreeNode* LogOrExp(ofstream& outfile)
{
	TreeNode *logicalAndExp = NULL, *logicalOrExp = NULL;
	logicalAndExp = LogAndExp(outfile);//����and��䲿��
	if (tokensIterator != tokens.end())
	{
		if (token.kind == TK_OR)//�����滹��or���,��ƥ��or
		{
			NextToken();
			logicalOrExp = LogOrExp(outfile);//����or��䲿��
		}
	}
	//����LOG_OR_EXP�ڵ㣬��2�����ӣ��ֱ���and��䡢or���
	TreeNode *node = new TreeNode{ LOG_OR_EXP };
	node->child[0] = logicalAndExp;
	node->child[1] = logicalOrExp;
	node->id = setId();
	return node;
}
TreeNode* WriteStmt(ofstream& outfile)
{
	//����Ҫ����GetTokenƥ�䡰write�����ţ�ԭ��μ�StmtSequence
	TreeNode *logicalOrExp = NULL;
	logicalOrExp = LogOrExp(outfile);//����write����
	//����WRITE_STMT_STMT�ڵ㣬��1��������write���
	TreeNode* node = new TreeNode{ WRITE_STMT };
	node->child[0] = logicalOrExp;
	node->id = setId();
	return node;
}
TreeNode* ReadStmt(ofstream& outfile)
{
	//����Ҫ����GetTokenƥ�䡰read�����ţ�ԭ��μ�StmtSequence
	TreeNode *id = NULL;
	int tokenType[1] = { TK_ID };
	Token tmpToken = token;
	if (match(tokenType, 1, outfile))
	{
		id = new TreeNode{ FACTOR };
		//����Factor���������Ǳ�ʶ����token�����Բ���ʹ��Factor�������ɽ��
	}
	//����READ_STMT�ڵ㣬��1�����ӱ�ʶ��
	TreeNode* node = new TreeNode{ READ_STMT };
	id->token = tmpToken;
	id->valtype = STRING_TYPE;
	node->child[0] = id;
	node->id = setId();
	return node;
}
TreeNode* AssignStmt(ofstream& outfile, Token token)
{
	/*����Ҫ����GetTokenƥ���ʶ����ԭ��μ�StmtSequence��
	��Ҫ������ʶ���ӽ�㣬�������ʶ����token*/
	TreeNode *id = new TreeNode{ FACTOR }, *logicalOrExp = NULL;
	int tokenType[1] = { TK_ASSIGN };
	match(tokenType, 1, outfile);//ƥ�丳ֵ��
	logicalOrExp = LogOrExp(outfile);//������ֵ����
	//����ASSIGN_STMT�ڵ㣬��2�����ӣ��ֱ��Ǳ�ʶ������ֵ���
	TreeNode* node = new TreeNode{ ASSIGN_STMT };
	id->token = token;//��ʶ��������һ����ƥ��������޷�ʹ��Factor���������ɽ��
	id->valtype = STRING_TYPE;
	node->child[0] = id;
	node->child[1] = logicalOrExp;
	node->id = setId();
	return node;
}
TreeNode* RepeatStmt(ofstream& outfile)
{
	//����Ҫ����GetTokenƥ�䡰repeat�����ţ�ԭ��μ�StmtSequence
	TreeNode *stmtSequence = NULL, *logicalOrExp = NULL;
	stmtSequence = StmtSequence(outfile);//�����ظ���䲿��
	int tokenType[1] = { TK_UNTIL };
	match(tokenType, 1, outfile);
	logicalOrExp = LogOrExp(outfile);//����until����
	//����REPEAT_STMT�ڵ㣬��2�����ӣ��ֱ����ظ���䡢until���
	TreeNode* node = new TreeNode{ REPEAT_STMT };
	node->child[0] = stmtSequence;
	node->child[1] = logicalOrExp;
	node->id = setId();
	return node;
}
TreeNode* IfStmt(ofstream& outfile)
{
	//����Ҫ����GetTokenƥ�䡰if�����ţ�ԭ��μ�StmtSequence
	TreeNode *logOrExp = NULL, *thenStmt = NULL, *elseStmt = NULL;
	logOrExp = LogOrExp(outfile);//�����������ʽ����
	int tokenType[1] = { TK_THEN };
	match(tokenType, 1, outfile);
	thenStmt = StmtSequence(outfile);//����then����
	if (token.kind == TK_ELSE)
	{
		int tokenType[1] = { TK_ELSE };
		match(tokenType, 1, outfile);
		elseStmt = StmtSequence(outfile);//����else����
	}
	/*����IF_STMT�ڵ㣬��3�����ӣ��ֱ����������ʽ��then����
	else��䣻��û��else��䣬�����������Ϊnull*/
	TreeNode* node = new TreeNode{ IF_STMT };
	node->child[0] = logOrExp;
	node->child[1] = thenStmt;
	node->child[2] = elseStmt;
	node->id = setId();

	tokenType[0] = TK_END;
	match(tokenType, 1, outfile);
	return node;
}
TreeNode* WhileStmt(ofstream& outfile)
{
	//����Ҫ����GetTokenƥ�䡰while�����ţ�ԭ��μ�StmtSequence
	TreeNode *logOrExp = NULL, *doStmt = NULL;
	logOrExp = LogOrExp(outfile);//�����������ʽ����
	int tokenType[1] = { TK_DO };
	match(tokenType, 1, outfile);
	doStmt = StmtSequence(outfile);//����do����
	tokenType[0] = { TK_END };
	match(tokenType, 1, outfile);
	//����WHILE_STMT�ڵ㣬��2�����ӣ��ֱ����������ʽ��do���
	TreeNode* node = new TreeNode{ WHILE_STMT };
	node->child[0] = logOrExp;
	node->child[1] = doStmt;
	node->id = setId();
	return node;
}
TreeNode* StmtSequence(ofstream& outfile)
{
	TreeNode *stmtSequence = new TreeNode{ STMT_SEQUENCE }, *t1 = NULL, *t2 = NULL;
	//stmtSequence�������ڵ㣻t1�����ӽ�㣻t2���Һ��ӽ��
	//��俪ʼ��
	int stmtFirst[6] = { TK_WHILE, TK_IF, TK_REPEAT, TK_ID, TK_READ, TK_WRITE };
	Token first = token;
	if (match(stmtFirst, 6, outfile))//��һ������
	{
		/*ע�⣺���Ŀ�ʼ��if��while�����������match���ƥ��,
		�����������ķ���������IfStmt�ȣ�����Ҫƥ�俪ʼ����*/
		switch (first.kind)
		{
		case TK_WHILE:t1 = WhileStmt(outfile); break;
		case TK_IF:t1 = IfStmt(outfile); break;
		case TK_REPEAT:t1 = RepeatStmt(outfile); break;
		case TK_ID:t1 = AssignStmt(outfile, first); break;
		case TK_READ:t1 = ReadStmt(outfile); break;
		case TK_WRITE:t1 = WriteStmt(outfile); break;
		}
		if (tokensIterator != tokens.end())//�����滹������
		{
			if (token.kind == TK_SEMICOLON)
			{
				NextToken();//ƥ��ֺ�
				t2 = StmtSequence(outfile);//ƥ���������
			}
		}
	}
	stmtSequence->child[0] = t1;
	stmtSequence->child[1] = t2;
	stmtSequence->id = setId();
	return stmtSequence;
}
void Declarations(ofstream& outfile)
{
	//��û�б���������ֱ�������˺���
	//���б������壺
	while (token.kind == TK_INT || token.kind == TK_BOOL || token.kind == TK_STRING)
	{
		NextToken();
		int type[1] = { TK_ID };
		match(type, 1, outfile);//ƥ���һ����ʶ��
		while (token.kind == TK_COMMA)
		{
			NextToken();
			match(type, 1, outfile);//ƥ��������ʶ��
		}
		type[0] = TK_SEMICOLON;
		match(type, 1, outfile);//ƥ��ֺ�
	}
}
TreeNode* Program(ofstream& outfile)
{
	Declarations(outfile);//����Declarations������������������
	return StmtSequence(outfile);
	//����StmtSequence��������б�StmtSequence()�ķ���ֵ��������������﷨�����������������֣�
}