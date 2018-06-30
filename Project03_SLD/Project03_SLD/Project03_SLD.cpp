// Project03_SLD.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "TreeSLD.h"

int main()
{
	//create premises
	//vector<string> premises;
	//cout << ">>>   Input premises, type '-1' when finishing inputting" << endl;
	//string inputtedPremise;
	//int count = 1;
	//while (inputtedPremise != "-1") {
	//	cout << "(" << count << ") ";
	//	getline(cin, inputtedPremise);
	//	if (inputtedPremise == "-1")	//condition to stop the loop
	//		break;
	//	premises.push_back(inputtedPremise);
	//	count++;
	//	cout << endl;
	//}


	////input statement
	//string statement;
	//cout << ">>> Input statement: ";
	//getline(cin, statement);

	////Get head of each md han dinh
	//vector<string> head;
	//vector<string> body;
	//for (int i = 0; i < premises.size(); i++)
	//{
	//	head.push_back(getHead(premises[i]));
	//	body.push_back(getBody(premises[i]));
	//}
	//outputArrStr(head);
	//outputArrStr(body);


	//SLD tree
	TREE sld;
	initTree(sld);
	//insertLeft(sld, statement);
	//string root = statement;
	////vector<string> nodeHasManyChild;
	//stack<string> nodeHasManyChild;
	//do {
	//	int numberPre = theNumberOfHead(head, root);
	//	if (numberPre == 0)
	//		insertLeft(sld, "false");
	//	int index = 0;
	//	for (int i = 0; i < head.size(); i++) {
	//		if (head[i] == root) {
	//			if (body[i] == "_")
	//				insertLeft(sld, "true");
	//			if (index == 0)
	//				insertLeft(sld, body[i]);
	//			else {
	//				insertRight(sld, body[i]);
	//				nodeHasManyChild.push(root);
	//			}
	//			index++;
	//		}
	//	}
	//	NLR(sld);
	//	root = findMostLeft(sld)->data;
	//	cout << endl;
	//} while (root != "false" && root != "true");

	insertLeft(sld, "A");
	insertLeft(sld, "B");
	insertRight(sld, "C");
	insertLeft(sld->left, "D");
	insertRight(sld->left, "E");
	insertLeft(sld->left->left, "F");
	cout << findMostLeft(sld)->data << endl;
	cout << find(sld, "E")->data << endl;
	

	return 0;
}

