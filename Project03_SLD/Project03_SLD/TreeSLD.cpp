#include "stdafx.h"
#include "TreeSLD.h"


void initTree(TREE &T)
{
	T = NULL;
}

TNode* getNode(string s)
{
	TNode* p = new TNode;
	if (p == NULL)
		return NULL;
	p->data = s;
	p->left = NULL;
	p->right = NULL;
	return p;
}

void insertLeft(TREE &T, string s)
{
	if (T == NULL) {
		T = getNode(s);
	}
	else {
		insertLeft(T->left, s);
	}
}

void insertRoot(TREE &T, string s) {
	if (T == NULL)
		T = getNode(s);
	else
	{
		cout << "Root is already exist";
	}
}

void insertRight(TREE &T, string s)
{
	if (T == NULL)
		T = getNode(s);
	else
		insertRight(T->right, s);
}



void LNR(TREE T)
{
	if (T != NULL) {
		LNR(T->left);
		cout << T->data << "  ";
		LNR(T->right);
	}
}

void NLR(TREE T)
{
	if (T != NULL) {
		cout << T->data << "  ";
		NLR(T->left);
		NLR(T->right);
	}
}

void LRN(TREE T)
{
	if (T != NULL) {
		LRN(T->left);
		LRN(T->right);
		cout << T->data << "  ";
	}
}


/**************************************/
void outputArrStr(vector<string> premises)
{
	cout << " >>>  Premises:" << endl;
	for (int i = 0; i < premises.size(); i++)
	{
		cout << "(" << i + 1 << ") " << premises[i] << endl;
	}
}

//Removing spaces which is before string and after string
string removeSpace(string s)
{
	//Find position of first whitespace in 's'
	int firstSpace = s.find_first_of(" ");
	if (firstSpace == 0)	//Check if whitespace is before the first character
		s = s.substr(s.find_first_not_of(" "), s.length());

	//Find position of last whitespace in 's'
	int lastSpace = s.find_last_of(" ");
	if (lastSpace == s.length() - 1)	//Check if whitespace is the last character of string 's'
		s = s.substr(0, lastSpace);
	return s;
}

//Get Head Of Definite Clause
string getHead(string premise)
{
	string tempHead;	//include space characters
						//	finding arrowhead
	int leftArrowhead = premise.find("<");	//check if arrowhead is to left
	int rightArrowhead = premise.find(">");	//check if arrowhead is to right
	if (leftArrowhead != -1 && rightArrowhead == -1)
		tempHead = premise.substr(0, leftArrowhead);
	else if (rightArrowhead != -1 && leftArrowhead == -1)
		tempHead = premise.substr(rightArrowhead + 1, premise.size() - 1);
	else	//if there is no arrowhead in premise
		tempHead = premise;
	return removeSpace(tempHead);
}

//Get Body Of Definite Clause
string getBody(string premise)
{
	string tempHead;	//include space characters
						//	finding arrowhead
	int leftArrowhead = premise.find("<");	//check if arrowhead is to left
	int rightArrowhead = premise.find(">");	//check if arrowhead is to right
	if (leftArrowhead != -1 && rightArrowhead == -1)
		tempHead = premise.substr(leftArrowhead + 1, premise.size());
	else if (rightArrowhead != -1 && leftArrowhead == -1)
		tempHead = premise.substr(0, rightArrowhead);
	else	//if there is no arrowhead in premise
		tempHead = "_";
	return removeSpace(tempHead);
}

int theNumberOfHead(vector<string> head, string foundStr)
{
	int count = 0;
	for (int i = 0; i < head.size(); i++)
	{
		if (head[i] == foundStr)
			count++;
	}
	return count;
}

TNode* findMostLeft(TREE sld)	//the nex parent is the most left/right leaf node
{
	if (sld->left != NULL)
		findMostLeft(sld->left);
	else
		return sld;

}

bool findNode(TNode*currentNode, string s)
{
	if (currentNode->data == s || currentNode->left->data == s || currentNode->right->data == s)
		return true;
	return false;
}

TNode* find(TREE T, string s) {
	if (T) {
		if (T->data == s)
			return T;
		else {
			find(T->left, s);
			find(T->right, s);
		}
	}
}
