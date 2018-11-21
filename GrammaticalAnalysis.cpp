/*所有输入输出的txt文件都在Debug文件夹中，请将输入文件放在Debug中即可。*/
#include"GrammaticalHeader.h"
list<Token> tokens;
Token token;
TreeNode * root;
int nodeID = 0;
list<Token>::iterator tokensIterator;
string setId()
{
	char str[4];
	_itoa_s(nodeID, str, 10); //_itoa_s：int 转换为 char* 的函数
	string a = "node";
	a += str;
	nodeID++;
	return a;
}
list<Token> GetToken(ifstream& infile)//返回所有token串
{
	list<string> txtStr;//存储txt文本所有字符串
	list<Token> tokens;//存储txt文本所有token串
	for (int i = 0; !infile.eof(); i++)
	{
		string tempStr;//辅助将字符串加入txtStr
		getline(infile, tempStr);//一行一行地读取词法分析输出的token到tempStr中
		txtStr.push_back(tempStr);//将字符串加入txtStr
	}
	infile.close();//关闭文件
	for (list<string>::iterator i = txtStr.begin(); i != txtStr.end(); i++)//开始逐行处理token
	{
		string tempStr = *i;//读入文档的一行
		istringstream is(tempStr);
		string tokenStr[5];//一行5个token（词法分析时我自己定义的输出规则），存储每行的token
		for (int i = 0; i < 5; i++)
			is >> tokenStr[i];
		for (int i = 0; i < 5; i++)
		{
			if (tokenStr[i] != "")
			{
				int index = tokenStr[i].find(',');//查找逗号的位置，截取逗号前的Token类型
				Token tmpToken;//临时token辅助将token加入tokens中
				string tmpStr;//存储token类型
				tmpStr = tokenStr[i].substr(1, index - 1);//复制token类型，如TK_IF
				//逐个匹配还原
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
					int indexEnd = tokenStr[i].find(')');//查找“)”的位置，截取“)”前的标识符值
					string tmp = tokenStr[i].substr(index + 1, indexEnd - index - 1);//复制标识符值
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
					int indexEnd = tokenStr[i].find(')');//查找“)”的位置，截取“)”前的标识符值
					string tmp = tokenStr[i].substr(index + 1, indexEnd - index - 1);//复制整数值
					tmpToken.ival = atoi(tmp.c_str());//atoi：char* 转换为 int 的函数
				}
				else if (tmpStr == "STRING")
				{
					tmpToken.kind = STRING;
					int indexEnd = tokenStr[i].find(')');//查找“)”的位置，截取“)”前的字符串值
					string tmp = tokenStr[i].substr(index + 1, indexEnd - index - 1);//复制字符串值
					tmpToken.sval.assign(tmp);
				}
				tokens.push_back(tmpToken);//将分析得到的token加入tokens中
			}
		}
	}
	return tokens;
}
void NextToken()
{
	if (tokensIterator != tokens.end())
		token = *tokensIterator++;//读取下一个token
}
bool match(int* kindSet,int setNum, ofstream& outfile)
{
	for (int i = 0; i < setNum; i++)
	{
		if (token.kind == kindSet[i])//匹配成功
		{
			NextToken();
			return true;
		}
	}
	//若匹配失败
	if (token.kind == TK_NUM)
		outfile << "符号" << token.ival << "的类型不匹配" << endl;
	else
		outfile << "符号" << token.sval << "的类型不匹配" << endl;
	return false;
}
TreeNode* GrammaticalExecute(ifstream& infile, ofstream& outfile)//语法分析执行程序
{
	tokens = GetToken(infile);//获取所有token到token表中
	tokensIterator = tokens.begin();//初始化tokens的指针
	NextToken();//获取第一个token
	root = Program(outfile);//开始获取语法树,program为入口,outfile为输出文件地址
	return root;//返回语法树的根节点
}
TreeNode* Factor(ofstream& outfile)
{
	int factorType[6] = { TK_NUM, STRING, TK_ID, TK_TRUE, TK_FALSE, TK_LP };//Factor对应的token类型
	Token tmpToken = token;
	if (!match(factorType, 6, outfile))//匹配Factor类型
	{
		return NULL;
	}
	TreeNode *node = NULL;
	if (tmpToken.kind == TK_LP)//Factor为一个句子
	{
		//不需要再匹配左括号
		node = LogOrExp(outfile);//匹配or句型
		int tokenType[1] = { TK_RP }; 
		match(tokenType, 1, outfile);//匹配右括号
	}
	else//token是number、string、identifier、true、false中的一个
	{
		//构建FACTOR节点，没有孩子
		node = new TreeNode{ FACTOR };//token做为Factor节点的孩子
		node->token = tmpToken;
		//给变量类型复制：
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
	factor = Factor(outfile);//分析factor部分
	if (tokensIterator != tokens.end())
	{
		if (token.kind== TK_MUL|| token.kind == TK_DIV)//若乘除号后面还有乘除语句，则匹配乘除号
		{
			switch (token.kind)
			{
			case TK_MUL:node = new TreeNode{ MUL_EXP }; break;
			case TK_DIV:node = new TreeNode{ DIV_EXP }; break;
			}
			NextToken();
			nextMulExp = MulExp(outfile);//分析乘除号后面的语句
		}
		else//若没有乘除号
			node = new TreeNode{ MUL_EXP };
	}
	else//若没有乘除号
		node = new TreeNode{ MUL_EXP };
	//构建MUL_EXP节点，有2个孩子，分别是factor、mul语句
	node->child[0] = factor;
	node->child[1] = nextMulExp;
	node->id = setId();
	return node;
}
TreeNode* AddExp(ofstream& outfile)
{
	TreeNode *node = NULL, *mulExp = NULL, *nextAddExp = NULL;
	mulExp = MulExp(outfile);//分析乘法语句部分
	if (tokensIterator != tokens.end())
	{
		if (token.kind == TK_ADD || token.kind == TK_SUB)//若加减号后面还有加减语句，则匹配加减号
		{
			switch (token.kind)
			{
			case TK_ADD:node = new TreeNode{ ADD_EXP }; break;
			case TK_SUB:node = new TreeNode{ SUB_EXP }; break;
			}
			NextToken();
			nextAddExp = AddExp(outfile);//分析加减号后面的语句
		}
		else//若没有加减号
			node = new TreeNode{ ADD_EXP };
	}
	else//若没有加减号
		node = new TreeNode{ ADD_EXP };
	//构建ADD_EXP节点，有2个孩子，分别是mul语句、add语句
	node->child[0] = mulExp;
	node->child[1] = nextAddExp;
	node->id = setId();
	return node;
}
TreeNode* CompExp(ofstream& outfile)
{
	TreeNode *node = NULL, *addExp = NULL, *nextComparisonExp = NULL;
	addExp = AddExp(outfile);//分析加法语句部分
	if (tokensIterator != tokens.end())
	{
		int tokenType[5] = { TK_LSS, TK_EQU, TK_GTR, TK_LEQ,TK_GEQ };
		bool flag = false;//判断token类型是否为上述5个类型中的一个
		for (int i = 0; i < 5; i++)
		{
			if (token.kind == tokenType[i])
			{
				flag = true;
				break;
			}
		}
		if (flag)//若比较符号后面还有比较语句，则匹配比较符号
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
			nextComparisonExp = CompExp(outfile);//分析后面比较语句部分
		}
		else//若没有比较符号
			node = new TreeNode{ COMP_EXP };
	}
	else//若没有比较符号
		node = new TreeNode{ COMP_EXP };
	//构建COMP_EXP节点，有2个孩子，分别是add语句、比较语句
	node->child[0] = addExp;
	node->child[1] = nextComparisonExp;
	node->id = setId();
	return node;
}
TreeNode* LogAndExp(ofstream& outfile)
{
	TreeNode *comparisonExp = NULL, *logicalAndExp = NULL;
	comparisonExp = CompExp(outfile);//分析比较语句部分
	if (tokensIterator != tokens.end())
	{
		if (token.kind == TK_AND)//若后面还有and语句，则匹配and
		{
			NextToken();
			logicalAndExp = LogAndExp(outfile);//分析and语句部分
		}
	}	
	//构建LOG_AND_EXP节点，有2个孩子，分别是比较语句、and语句
	TreeNode *node = new TreeNode{ LOG_AND_EXP };
	node->child[0] = comparisonExp;
	node->child[1] = logicalAndExp;
	node->id = setId();
	return node;
}
TreeNode* LogOrExp(ofstream& outfile)
{
	TreeNode *logicalAndExp = NULL, *logicalOrExp = NULL;
	logicalAndExp = LogAndExp(outfile);//分析and语句部分
	if (tokensIterator != tokens.end())
	{
		if (token.kind == TK_OR)//若后面还有or语句,则匹配or
		{
			NextToken();
			logicalOrExp = LogOrExp(outfile);//分析or语句部分
		}
	}
	//构建LOG_OR_EXP节点，有2个孩子，分别是and语句、or语句
	TreeNode *node = new TreeNode{ LOG_OR_EXP };
	node->child[0] = logicalAndExp;
	node->child[1] = logicalOrExp;
	node->id = setId();
	return node;
}
TreeNode* WriteStmt(ofstream& outfile)
{
	//不需要调用GetToken匹配“write”符号，原因参见StmtSequence
	TreeNode *logicalOrExp = NULL;
	logicalOrExp = LogOrExp(outfile);//分析write部分
	//构建WRITE_STMT_STMT节点，有1个孩子是write语句
	TreeNode* node = new TreeNode{ WRITE_STMT };
	node->child[0] = logicalOrExp;
	node->id = setId();
	return node;
}
TreeNode* ReadStmt(ofstream& outfile)
{
	//不需要调用GetToken匹配“read”符号，原因参见StmtSequence
	TreeNode *id = NULL;
	int tokenType[1] = { TK_ID };
	Token tmpToken = token;
	if (match(tokenType, 1, outfile))
	{
		id = new TreeNode{ FACTOR };
		//由于Factor含有其它非标识符的token，所以不能使用Factor函数生成结点
	}
	//构建READ_STMT节点，有1个孩子标识符
	TreeNode* node = new TreeNode{ READ_STMT };
	id->token = tmpToken;
	id->valtype = STRING_TYPE;
	node->child[0] = id;
	node->id = setId();
	return node;
}
TreeNode* AssignStmt(ofstream& outfile, Token token)
{
	/*不需要调用GetToken匹配标识符，原因参见StmtSequence。
	需要构建标识符子结点，故引入标识符的token*/
	TreeNode *id = new TreeNode{ FACTOR }, *logicalOrExp = NULL;
	int tokenType[1] = { TK_ASSIGN };
	match(tokenType, 1, outfile);//匹配赋值号
	logicalOrExp = LogOrExp(outfile);//分析赋值部分
	//构建ASSIGN_STMT节点，有2个孩子，分别是标识符、赋值语句
	TreeNode* node = new TreeNode{ ASSIGN_STMT };
	id->token = token;//标识符已在上一步被匹配过，故无法使用Factor函数来生成结点
	id->valtype = STRING_TYPE;
	node->child[0] = id;
	node->child[1] = logicalOrExp;
	node->id = setId();
	return node;
}
TreeNode* RepeatStmt(ofstream& outfile)
{
	//不需要调用GetToken匹配“repeat”符号，原因参见StmtSequence
	TreeNode *stmtSequence = NULL, *logicalOrExp = NULL;
	stmtSequence = StmtSequence(outfile);//分析重复语句部分
	int tokenType[1] = { TK_UNTIL };
	match(tokenType, 1, outfile);
	logicalOrExp = LogOrExp(outfile);//分析until部分
	//构建REPEAT_STMT节点，有2个孩子，分别是重复语句、until语句
	TreeNode* node = new TreeNode{ REPEAT_STMT };
	node->child[0] = stmtSequence;
	node->child[1] = logicalOrExp;
	node->id = setId();
	return node;
}
TreeNode* IfStmt(ofstream& outfile)
{
	//不需要调用GetToken匹配“if”符号，原因参见StmtSequence
	TreeNode *logOrExp = NULL, *thenStmt = NULL, *elseStmt = NULL;
	logOrExp = LogOrExp(outfile);//分析条件表达式部分
	int tokenType[1] = { TK_THEN };
	match(tokenType, 1, outfile);
	thenStmt = StmtSequence(outfile);//分析then部分
	if (token.kind == TK_ELSE)
	{
		int tokenType[1] = { TK_ELSE };
		match(tokenType, 1, outfile);
		elseStmt = StmtSequence(outfile);//分析else部分
	}
	/*构建IF_STMT节点，有3个孩子，分别是条件表达式、then语句和
	else语句；若没有else语句，则第三个孩子为null*/
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
	//不需要调用GetToken匹配“while”符号，原因参见StmtSequence
	TreeNode *logOrExp = NULL, *doStmt = NULL;
	logOrExp = LogOrExp(outfile);//分析条件表达式部分
	int tokenType[1] = { TK_DO };
	match(tokenType, 1, outfile);
	doStmt = StmtSequence(outfile);//分析do部分
	tokenType[0] = { TK_END };
	match(tokenType, 1, outfile);
	//构建WHILE_STMT节点，有2个孩子，分别是条件表达式、do语句
	TreeNode* node = new TreeNode{ WHILE_STMT };
	node->child[0] = logOrExp;
	node->child[1] = doStmt;
	node->id = setId();
	return node;
}
TreeNode* StmtSequence(ofstream& outfile)
{
	TreeNode *stmtSequence = new TreeNode{ STMT_SEQUENCE }, *t1 = NULL, *t2 = NULL;
	//stmtSequence：根树节点；t1：左孩子结点；t2：右孩子结点
	//语句开始符
	int stmtFirst[6] = { TK_WHILE, TK_IF, TK_REPEAT, TK_ID, TK_READ, TK_WRITE };
	Token first = token;
	if (match(stmtFirst, 6, outfile))//第一个语句块
	{
		/*注意：语句的开始符if、while等已由上面的match语句匹配,
		因此下面各语句的分析函数（IfStmt等）不需要匹配开始符。*/
		switch (first.kind)
		{
		case TK_WHILE:t1 = WhileStmt(outfile); break;
		case TK_IF:t1 = IfStmt(outfile); break;
		case TK_REPEAT:t1 = RepeatStmt(outfile); break;
		case TK_ID:t1 = AssignStmt(outfile, first); break;
		case TK_READ:t1 = ReadStmt(outfile); break;
		case TK_WRITE:t1 = WriteStmt(outfile); break;
		}
		if (tokensIterator != tokens.end())//若后面还有语句块
		{
			if (token.kind == TK_SEMICOLON)
			{
				NextToken();//匹配分号
				t2 = StmtSequence(outfile);//匹配后续语句块
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
	//若没有变量定义则直接跳过此函数
	//若有变量定义：
	while (token.kind == TK_INT || token.kind == TK_BOOL || token.kind == TK_STRING)
	{
		NextToken();
		int type[1] = { TK_ID };
		match(type, 1, outfile);//匹配第一个标识符
		while (token.kind == TK_COMMA)
		{
			NextToken();
			match(type, 1, outfile);//匹配其它标识符
		}
		type[0] = TK_SEMICOLON;
		match(type, 1, outfile);//匹配分号
	}
}
TreeNode* Program(ofstream& outfile)
{
	Declarations(outfile);//调用Declarations函数分析变量的声明
	return StmtSequence(outfile);
	//调用StmtSequence分析语句列表StmtSequence()的返回值就是整个程序的语法树（不包括声明部分）
}