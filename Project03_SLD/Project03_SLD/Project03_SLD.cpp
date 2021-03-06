// Project03_SLD.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "TreeSLD.h"

int main()
{
	//create premises
	vector<string> premises;
	cout << ">>>   Input premises, type '-1' when finishing inputting" << endl;
	string inputtedPremise;
	int count = 1;
	while (inputtedPremise != "-1") {
		cout << "(" << count << ") ";
		getline(cin, inputtedPremise);
		if (inputtedPremise == "-1")	//condition to stop the loop
			break;
		premises.push_back(inputtedPremise);
		count++;
		cout << endl;
	}


	//input statement
	string statement;
	cout << ">>> Input statement: ";
	getline(cin, statement);

	//Get head of each md han dinh
	vector<string> head;
	vector<string> body;
	for (int i = 0; i < premises.size(); i++)
	{
		head.push_back(getHead(premises[i]));
		body.push_back(getBody(premises[i]));
	}
	outputArrStr(head);
	outputArrStr(body);


	//SLD tree
	TREE sld;
	initTree(sld);
	insertLeft(sld, parseBodyToLiteral(statement));
	insertSLD(sld, head, body);

	cout << "Final result: ";
	NLR(sld);
	cout << endl;

	return 0;
}

