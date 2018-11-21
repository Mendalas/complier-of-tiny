#include <iostream>
#include "MainHeader.h"
#include <vector>
#include <string>
#include <cstdlib>

using namespace std;

int tNum = 0;
int CodeNum = 0;
int LabelNum = 0;

vector<string> codes;
string curCode;
string BufStr;

char buffer[10] = { 0 };




class mystring: public string, private vector<int>
{
};

void outputCode(TreeNode * TreeNode)
 {
	int curLabel = -1;
	int curLocation=0;
	int curLocation_1 = 0;

	if (TreeNode == NULL)
		return;

	if (TreeNode->nodetype ==PROGRAM)
	{
		for (auto& SubTree : TreeNode->child)
			outputCode(SubTree);
		return;
	}

	switch (TreeNode->nodetype)
	{
		case STMT_SEQUENCE:
			for (auto& SubTree : TreeNode->child)
				outputCode(SubTree);
			break;
		
		case READ_STMT:
			outputCode(TreeNode->child[0]);

			curCode = "";
			for (auto& letter : buffer)
				letter = 0;

			TreeNode->id = "T";
			TreeNode->id +=	itoa((tNum++),buffer,10);

			for (auto& letter : buffer)
				letter = 0;
			curCode += itoa((CodeNum++), buffer, 10);
			curCode += "): ";
			curCode += "READ " + TreeNode->child[0]->id;

			codes.push_back(curCode);
			
			//cout<<TreeNode->child[0];
			break;
		case WRITE_STMT:
			outputCode(TreeNode->child[0]);
			 
			curCode = "";
			for (auto& letter : buffer)
				letter = 0;

			TreeNode->id = "T";
			TreeNode->id += itoa((tNum++), buffer, 10);

			for (auto& letter : buffer)
				letter = 0;
			curCode += itoa((CodeNum++), buffer, 10);
			curCode += "): ";
			curCode += "WRITE " + TreeNode->child[0]->id;

			codes.push_back(curCode);

			//cout<<TreeNode->child[0];
			break;


		case IF_STMT:
			outputCode(TreeNode->child[0]);

			curCode = "";

			for (auto& letter : buffer)
				letter = 0;
			curCode += itoa((CodeNum++), buffer, 10);
			curCode += "): ";
			curCode += "if Not  " + TreeNode->child[0]->id + " goto " + " L";

			curLocation = codes.size();

			codes.push_back(curCode);

			outputCode(TreeNode->child[1]);

			curCode = "";
			for (auto& letter : buffer)
				letter = 0;
			curCode += itoa((CodeNum++), buffer, 10);
			curCode += "): ";
			curCode += "label L";

			for (auto& letter : buffer)
				letter = 0;
			curCode+= itoa((LabelNum++), buffer, 10);

			codes.push_back(curCode);
			for (auto& letter : buffer)
				letter = 0;
			codes[curLocation] += itoa(LabelNum - 1,buffer,10);

			if (TreeNode->child[2] != NULL)
			{
				outputCode(TreeNode->child[2]);
			}

			break;
		case REPEAT_STMT:

			curLabel = -1;
			curCode = "";

			for (auto& letter : buffer)
				letter = 0;
			curCode += itoa(CodeNum++, buffer, 10);
			curCode +=	"): ";
			curCode += "label L";

			for (auto& letter : buffer)
					letter = 0;
			curCode += itoa((LabelNum++), buffer, 10);
			codes.push_back(curCode);


			curLabel = LabelNum - 1;

			outputCode(TreeNode->child[0]);
			outputCode(TreeNode->child[1]);

			curCode = "";
			for (auto& letter : buffer)
				letter = 0;
			curCode += itoa(CodeNum++,buffer,10);
			curCode	+="): ";

			curCode += "if " + TreeNode->child[1]->id + " goto " + " L";
			for (auto& letter : buffer)
				letter = 0;
			curCode += itoa(curLabel, buffer, 10);

			codes.push_back(curCode);


			break;
		case ASSIGN_STMT:
			outputCode(TreeNode->child[0]);
			if (TreeNode->child[1] != NULL)
			{
				outputCode(TreeNode->child[1]);

				curCode = "";

				TreeNode->id = "T";
				for (auto& letter : buffer)
					letter = 0;
				TreeNode->id += itoa(tNum++, buffer, 10);

				for (auto& letter : buffer)
					letter = 0;
				curCode += itoa(CodeNum++, buffer, 10);
				curCode += +"): ";
				curCode += TreeNode->id + ":=";

				if (TreeNode->child[0]->valtype == INT_TYPE)
				{
					for (auto& letter : buffer)
						letter = 0;
					curCode += itoa(TreeNode->child[0]->intValue, buffer, 10);
					curCode += " := ";
				}
				else
					curCode += TreeNode->child[0]->id + " := ";

				if (TreeNode->child[1]->valtype == INT_TYPE)
				{
					for (auto& letter : buffer)
						letter = 0;
					curCode += itoa(TreeNode->child[1]->intValue, buffer, 10);
				}
				else
					curCode += TreeNode->child[1]->id;

				codes.push_back(curCode);
			}
			else
				if (TreeNode->child[0]->valtype == INT_TYPE)
				{
					TreeNode->valtype = INT_TYPE;
					TreeNode->intValue = TreeNode->child[0]->intValue;
				}
				else
					TreeNode->id = TreeNode->child[0]->id;
			break;

			break;
		case WHILE_STMT:
			curLabel = -1;
			curCode = "";

			for (auto& letter : buffer)
				letter = 0;
			curCode += itoa(CodeNum++, buffer, 10);
			curCode += "): ";
			curCode += "label L";
			for (auto& letter : buffer)
				letter = 0;
			curCode += itoa(LabelNum, buffer, 10);


			curLabel = LabelNum++;

			curLocation_1 = codes.size();


			codes.push_back(curCode);

			outputCode(TreeNode->child[0]);

			curCode = "";

			for (auto& letter : buffer)
				letter = 0;
			curCode += itoa(CodeNum++, buffer, 10);
			curCode += "): ";
			curCode += "if Not " + TreeNode->child[0]->id + " goto " + " L";
			
			curLocation = codes.size();
			codes.push_back(curCode);

			outputCode(TreeNode->child[1]);

			curCode = "";
			for (auto& letter : buffer)
				letter = 0;
			curCode += itoa(CodeNum++,buffer,10);
			curCode	+= "): ";
			curCode += "goto L";
			for (auto& letter : buffer)
				letter = 0;
			curCode += itoa(curLabel, buffer, 10);

			codes.push_back(curCode);

			curCode = "";
			for (auto& letter : buffer)
				letter = 0;
			curCode += itoa(CodeNum++, buffer, 10);
			curCode += "): ";
			curCode += "label L";

			for (auto& letter : buffer)
				letter = 0;
			curCode+=itoa(LabelNum++,buffer,10);

			codes.push_back(curCode);

			for (auto& letter : buffer)
				letter = 0;

			codes[curLocation]+= itoa(LabelNum - 1,buffer,10);


			break;
		case GTR_EXP:
			outputCode(TreeNode->child[0]);
			if (TreeNode->child[1] != NULL)
			{
				outputCode(TreeNode->child[1]);

				curCode = "";

				TreeNode->id = "T";
				for (auto& letter : buffer)
					letter = 0;
				TreeNode->id += itoa(tNum++, buffer, 10);

				for (auto& letter : buffer)
					letter = 0;
				curCode += itoa(CodeNum++, buffer, 10);
				curCode += +"): ";
				curCode += TreeNode->id + ":=";

				if (TreeNode->child[0]->valtype == INT_TYPE)
				{
					for (auto& letter : buffer)
						letter = 0;
					curCode += itoa(TreeNode->child[0]->intValue, buffer, 10);
					curCode += " > ";
				}
				else
					curCode += TreeNode->child[0]->id + " > ";

				if (TreeNode->child[1]->valtype == INT_TYPE)
				{
					for (auto& letter : buffer)
						letter = 0;
					curCode += itoa(TreeNode->child[1]->intValue, buffer, 10);
				}
				else
					curCode += TreeNode->child[1]->id;

				codes.push_back(curCode);
			}
			else 

				if (TreeNode->child[0]->valtype == INT_TYPE)
				{
					TreeNode->valtype = INT_TYPE;
					TreeNode->intValue = TreeNode->child[0]->intValue;
				}
				else
				TreeNode->id = TreeNode->child[0]->id;
			break;

		case GEQ_EXP:
			outputCode(TreeNode->child[0]);
			if (TreeNode->child[1] != NULL)
			{
				outputCode(TreeNode->child[1]);

				curCode = "";

				TreeNode->id = "T";
				for (auto& letter : buffer)
					letter = 0;
				TreeNode->id += itoa(tNum++, buffer, 10);

				for (auto& letter : buffer)
					letter = 0;
				curCode += itoa(CodeNum++, buffer, 10);
				curCode += +"): ";
				curCode += TreeNode->id + ":=";

				if (TreeNode->child[0]->valtype == INT_TYPE)
				{
					for (auto& letter : buffer)
						letter = 0;
					curCode += itoa(TreeNode->child[0]->intValue, buffer, 10);
					curCode += " >= ";
				}
				else
					curCode += TreeNode->child[0]->id + " >= ";

				if (TreeNode->child[1]->valtype == INT_TYPE)
				{
					for (auto& letter : buffer)
						letter = 0;
					curCode += itoa(TreeNode->child[1]->intValue, buffer, 10);
				}
				else
					curCode += TreeNode->child[1]->id;

				codes.push_back(curCode);
			}
			else 
				if (TreeNode->child[0]->valtype == INT_TYPE)
				{
					TreeNode->valtype = INT_TYPE;
					TreeNode->intValue = TreeNode->child[0]->intValue;
				}
			else
				TreeNode->id = TreeNode->child[0]->id;
			break;
		case LSS_EXP:
			outputCode(TreeNode->child[0]);
			if (TreeNode->child[1] != NULL)
			{
				outputCode(TreeNode->child[1]);

				curCode = "";

				TreeNode->id = "T";
				for (auto& letter : buffer)
					letter = 0;
				TreeNode->id += itoa(tNum++, buffer, 10);

				for (auto& letter : buffer)
					letter = 0;
				curCode += itoa(CodeNum++, buffer, 10);
				curCode += +"): ";
				curCode += TreeNode->id + ":=";

				if (TreeNode->child[0]->valtype == INT_TYPE)
				{
					for (auto& letter : buffer)
						letter = 0;
					curCode += itoa(TreeNode->child[0]->intValue, buffer, 10);
					curCode += " < ";
				}
				else
					curCode += TreeNode->child[0]->id + " < ";

				if (TreeNode->child[1]->valtype == INT_TYPE)
				{
					for (auto& letter : buffer)
						letter = 0;
					curCode += itoa(TreeNode->child[1]->intValue, buffer, 10);
				}
				else
					curCode += TreeNode->child[1]->id;

				codes.push_back(curCode);
			}
			else 
				if (TreeNode->child[0]->valtype == INT_TYPE)
				{
					TreeNode->valtype = INT_TYPE;
					TreeNode->intValue = TreeNode->child[0]->intValue;
				}
				else
					TreeNode->id = TreeNode->child[0]->id;
			break;
		case LEQ_EXP:
			outputCode(TreeNode->child[0]);
			if (TreeNode->child[1] != NULL)
			{
				outputCode(TreeNode->child[1]);

				curCode = "";

				TreeNode->id = "T";
				for (auto& letter : buffer)
					letter = 0;
				TreeNode->id += itoa(tNum++, buffer, 10);

				for (auto& letter : buffer)
					letter = 0;
				curCode += itoa(CodeNum++, buffer, 10);
				curCode += +"): ";
				curCode += TreeNode->id + ":=";

				if (TreeNode->child[0]->valtype == INT_TYPE)
				{
					for (auto& letter : buffer)
						letter = 0;
					curCode += itoa(TreeNode->child[0]->intValue, buffer, 10);
					curCode += " <= ";
				}
				else
					curCode += TreeNode->child[0]->id + " <= ";

				if (TreeNode->child[1]->valtype == INT_TYPE)
				{
					for (auto& letter : buffer)
						letter = 0;
					curCode += itoa(TreeNode->child[1]->intValue, buffer, 10);
				}
				else
					curCode += TreeNode->child[1]->id;

				codes.push_back(curCode);
			}
			else 
				if (TreeNode->child[0]->valtype == INT_TYPE)
				{
					TreeNode->valtype = INT_TYPE;
					TreeNode->intValue = TreeNode->child[0]->intValue;
				}
				else
					TreeNode->id = TreeNode->child[0]->id;
			break;
		case EQU_EXP:
			outputCode(TreeNode->child[0]);
			if (TreeNode->child[1] != NULL)
			{
				outputCode(TreeNode->child[1]);

				curCode = "";

				TreeNode->id = "T";
				for (auto& letter : buffer)
					letter = 0;
				TreeNode->id += itoa(tNum++, buffer, 10);

				for (auto& letter : buffer)
					letter = 0;
				curCode += itoa(CodeNum++, buffer, 10);
				curCode += +"): ";
				curCode += TreeNode->id + ":=";

				if (TreeNode->child[0]->valtype == INT_TYPE)
				{
					for (auto& letter : buffer)
						letter = 0;
					curCode += itoa(TreeNode->child[0]->intValue, buffer, 10);
					curCode += " == ";
				}
				else
					curCode += TreeNode->child[0]->id + " == ";

				if (TreeNode->child[1]->valtype == INT_TYPE)
				{
					for (auto& letter : buffer)
						letter = 0;
					curCode += itoa(TreeNode->child[1]->intValue, buffer, 10);
				}
				else
					curCode += TreeNode->child[1]->id;

				codes.push_back(curCode);
			}
			else 
				if (TreeNode->child[0]->valtype == INT_TYPE)
				{
					TreeNode->valtype = INT_TYPE;
					TreeNode->intValue = TreeNode->child[0]->intValue;
				}
				else
					TreeNode->id = TreeNode->child[0]->id;
			break;

		case COMP_EXP:
			outputCode(TreeNode->child[0]);
			if (TreeNode->child[1] != NULL)
				outputCode(TreeNode->child[1]);
			else 
				if (TreeNode->child[0]->valtype == INT_TYPE)
				{
					TreeNode->valtype = INT_TYPE;
					TreeNode->intValue = TreeNode->child[0]->intValue;
				}
				else
					TreeNode->id = TreeNode->child[0]->id;
			break;


		case LOG_NOT_EXP:
			if (TreeNode->child[0] != NULL)
			{
				outputCode(TreeNode->child[0]);

				curCode = "";

				TreeNode->id = "T";

				for (auto& letter : buffer)
					letter = 0;
				TreeNode->id += itoa(tNum++, buffer, 10);

				for (auto& letter : buffer)
					letter = 0;
				curCode += itoa(CodeNum++, buffer, 10);
				curCode += "): ";
				curCode += TreeNode->id + ":=";

				curCode += " NOT " + TreeNode->child[0]->id;
			}
			else
				if (TreeNode->child[0]->valtype == INT_TYPE)
				{
					TreeNode->valtype = INT_TYPE;
					TreeNode->intValue = TreeNode->child[0]->intValue;
				}
				else
					TreeNode->id = TreeNode->child[0]->id;
			break;
		
		case LOG_OR_EXP:
			outputCode(TreeNode->child[0]);
			if (TreeNode->child[1] != NULL)
			{
				outputCode(TreeNode->child[1]);

				curCode = "";

				TreeNode->id = "T";
				for (auto& letter : buffer)
					letter = 0;
				TreeNode->id += itoa(tNum++, buffer, 10);

				for (auto& letter : buffer)
					letter = 0;
				curCode += itoa(CodeNum++, buffer, 10);
				curCode += +"): ";
				curCode += TreeNode->id + ":=";

				if (TreeNode->child[0]->valtype == INT_TYPE)
				{
					for (auto& letter : buffer)
						letter = 0;
					curCode += itoa(TreeNode->child[0]->intValue, buffer, 10);
					curCode += " OR ";
				}
				else
					curCode += TreeNode->child[0]->id + " OR ";

				if (TreeNode->child[1]->valtype == INT_TYPE)
				{
					for (auto& letter : buffer)
						letter = 0;
					curCode += itoa(TreeNode->child[1]->intValue, buffer, 10);
				}
				else
					curCode += TreeNode->child[1]->id;

				codes.push_back(curCode);
			}
			else
				if (TreeNode->child[0]->valtype == INT_TYPE)
				{
					TreeNode->valtype = INT_TYPE;
					TreeNode->intValue = TreeNode->child[0]->intValue;
				}
				else
					TreeNode->id = TreeNode->child[0]->id;
			break;
			break;

		case LOG_AND_EXP:
			outputCode(TreeNode->child[0]);
			if (TreeNode->child[1] != NULL)
			{
				outputCode(TreeNode->child[1]);

				curCode = "";

				TreeNode->id = "T";
				for (auto& letter : buffer)
					letter = 0;
				TreeNode->id += itoa(tNum++, buffer, 10);

				for (auto& letter : buffer)
					letter = 0;
				curCode += itoa(CodeNum++, buffer, 10);
				curCode += +"): ";
				curCode += TreeNode->id + ":=";

				if (TreeNode->child[0]->valtype == INT_TYPE)
				{
					for (auto& letter : buffer)
						letter = 0;
					curCode += itoa(TreeNode->child[0]->intValue, buffer, 10);
					curCode += " AND ";
				}
				else
					curCode += TreeNode->child[0]->id + " AND ";

				if (TreeNode->child[1]->valtype == INT_TYPE)
				{
					for (auto& letter : buffer)
						letter = 0;
					curCode += itoa(TreeNode->child[1]->intValue, buffer, 10);
				}
				else
					curCode += TreeNode->child[1]->id;

				codes.push_back(curCode);
			}
			else
				if (TreeNode->child[0]->valtype == INT_TYPE)
				{
					TreeNode->valtype = INT_TYPE;
					TreeNode->intValue = TreeNode->child[0]->intValue;
				}
				else
					TreeNode->id = TreeNode->child[0]->id;
			break;

		case FACTOR:
			if (TreeNode->valtype == INT_TYPE)
				TreeNode->intValue = TreeNode->token.ival;
			else
				TreeNode->id = TreeNode->token.sval;
			break;

		case ADD_EXP:
			outputCode(TreeNode->child[0]);
			if (TreeNode->child[1] != NULL)
			{
				outputCode(TreeNode->child[1]);

				curCode = "";

				TreeNode->id = "T";
				for (auto& letter : buffer)
					letter = 0;
				TreeNode->id += itoa(tNum++, buffer, 10);

				for (auto& letter : buffer)
					letter = 0;
				curCode += itoa(CodeNum++, buffer, 10);
				curCode += +"): ";
				curCode += TreeNode->id + ":=";

				if (TreeNode->child[0]->valtype == INT_TYPE)
				{
					for (auto& letter : buffer)
						letter = 0;
					curCode += itoa(TreeNode->child[0]->intValue, buffer, 10);
					curCode += " + ";
				}
				else
					curCode += TreeNode->child[0]->id + " + ";

				if (TreeNode->child[1]->valtype == INT_TYPE)
				{
					for (auto& letter : buffer)
						letter = 0;
					curCode += itoa(TreeNode->child[1]->intValue, buffer, 10);
				}
				else
					curCode += TreeNode->child[1]->id;

				codes.push_back(curCode);
			}
			else 
				if (TreeNode->child[0]->valtype == INT_TYPE)
				{
					TreeNode->valtype = INT_TYPE;
					TreeNode->intValue = TreeNode->child[0]->intValue;
				}
				else
					TreeNode->id = TreeNode->child[0]->id;
			break;

		case SUB_EXP:
			outputCode(TreeNode->child[0]);
			if (TreeNode->child[1] != NULL)
			{
				outputCode(TreeNode->child[1]);

				curCode = "";

				TreeNode->id = "T";
				for (auto& letter : buffer)
					letter = 0;
				TreeNode->id += itoa(tNum++, buffer, 10);

				for (auto& letter : buffer)
					letter = 0;
				curCode += itoa(CodeNum++, buffer, 10);
				curCode += +"): ";
				curCode += TreeNode->id + ":=";

				if (TreeNode->child[0]->valtype == INT_TYPE)
				{
					for (auto& letter : buffer)
						letter = 0;
					curCode += itoa(TreeNode->child[0]->intValue, buffer, 10);
					curCode += " - ";
				}
				else
					curCode += TreeNode->child[0]->id + " - ";

				if (TreeNode->child[1]->valtype == INT_TYPE)
				{
					for (auto& letter : buffer)
						letter = 0;
					curCode += itoa(TreeNode->child[1]->intValue, buffer, 10);
				}
				else
					curCode += TreeNode->child[1]->id;

				codes.push_back(curCode);
			}
			else 
				if (TreeNode->child[0]->valtype == INT_TYPE)
				{
					TreeNode->valtype = INT_TYPE;
					TreeNode->intValue = TreeNode->child[0]->intValue;
				}
				else
					TreeNode->id = TreeNode->child[0]->id;
			break;

		case MUL_EXP:
			outputCode(TreeNode->child[0]);
			if (TreeNode->child[1] != NULL)
			{
				outputCode(TreeNode->child[1]);

				curCode = "";

				TreeNode->id = "T";
				for (auto& letter : buffer)
					letter = 0;
				TreeNode->id += itoa(tNum++, buffer, 10);

				for (auto& letter : buffer)
					letter = 0;
				curCode += itoa(CodeNum++, buffer, 10);
				curCode += +"): ";
				curCode += TreeNode->id + ":=";

				if (TreeNode->child[0]->valtype == INT_TYPE)
				{
					for (auto& letter : buffer)
						letter = 0;
					curCode += itoa(TreeNode->child[0]->intValue, buffer, 10);
					curCode += " * ";
				}
				else
					curCode += TreeNode->child[0]->id + " * ";

				if (TreeNode->child[1]->valtype == INT_TYPE)
				{
					for (auto& letter : buffer)
						letter = 0;
					curCode += itoa(TreeNode->child[1]->intValue, buffer, 10);
				}
				else
					curCode += TreeNode->child[1]->id;

				codes.push_back(curCode);
			}
			else 
				if (TreeNode->child[0]->valtype == INT_TYPE)
				{
					TreeNode->valtype = INT_TYPE;
					TreeNode->intValue = TreeNode->child[0]->intValue;
				}
				else
					TreeNode->id = TreeNode->child[0]->id;
			break;


		case DIV_EXP:
			outputCode(TreeNode->child[0]);
			if (TreeNode->child[1] != NULL)
			{
				outputCode(TreeNode->child[1]);

				curCode = "";

				TreeNode->id = "T";
				for (auto& letter : buffer)
					letter = 0;
				TreeNode->id += itoa(tNum++, buffer, 10);

				for (auto& letter : buffer)
					letter = 0;
				curCode += itoa(CodeNum++, buffer, 10);
				curCode += +"): ";
				curCode += TreeNode->id + ":=";

				if (TreeNode->child[0]->valtype == INT_TYPE)
				{
					for (auto& letter : buffer)
						letter = 0;
					curCode += itoa(TreeNode->child[0]->intValue, buffer, 10);
					curCode += " / ";
				}
				else
					curCode += TreeNode->child[1]->id + " / ";

				if (TreeNode->child[1]->valtype == INT_TYPE)
				{
					for (auto& letter : buffer)
						letter = 0;
					curCode += itoa(TreeNode->child[1]->intValue, buffer, 10);
				}
				else
					curCode += TreeNode->child[1]->id;

				codes.push_back(curCode);
			}
			else 
				if (TreeNode->child[0]->valtype == INT_TYPE)
				{
					TreeNode->valtype = INT_TYPE;
					TreeNode->intValue = TreeNode->child[0]->intValue;
				}
				else
					TreeNode->id = TreeNode->child[0]->id;
			break;

	}
		
}

void CodeGen(TreeNode* syntaxTree)
{
    outputCode(syntaxTree);	
	for (string& code : codes)
		cout << code<<endl;
}
