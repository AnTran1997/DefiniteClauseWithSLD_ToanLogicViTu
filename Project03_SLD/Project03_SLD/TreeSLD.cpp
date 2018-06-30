#include "stdafx.h"
#include "TreeSLD.h"


void initTree(TREE &T)
{
	T = NULL;
}

//TNode* getNode(string s)
//{
//	TNode* p = new TNode;
//	if (p == NULL)
//		return NULL;
//	p->data = s;
//	p->left = NULL;
//	p->right = NULL;
//	return p;
//}

TNode* getNode(string s)
{
	TNode* p = new TNode;
	if (p == NULL)
		return NULL;
	p->data.push_back(s);
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
		//cout << T->data << "  ";
		outputArr(T->data);
		LNR(T->right);
	}
}

void NLR(TREE T)
{
	if (T != NULL) {
		//cout << T->data << "  ";
		outputArr(T->data);
		NLR(T->left);
		NLR(T->right);
	}
}

void LRN(TREE T)
{
	if (T != NULL) {
		LRN(T->left);
		LRN(T->right);
		//cout << T->data << "  ";
		outputArr(T->data);
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

/*void insertSLD(TREE& sld, vector<string> body, vector<string> head,string statement)
{
	
	string root = statement;
	//vector<string> nodeHasManyChild;
	stack<string> nodeHasManyChild;
	do {
		int numberPre = theNumberOfHead(head, root);
		if (numberPre == 0)
			insertLeft(sld, "false");
		int index = 0;
		for (int i = 0; i < head.size(); i++) {
			if (head[i] == root) {
				if (body[i] == "_")
					insertLeft(sld, "true");
				if (index == 0)
					insertLeft(sld, body[i]);
				else {
					insertRight(sld, body[i]);
					nodeHasManyChild.push(root);
				}
				index++;
			}
		}
		NLR(sld);
		root = findMostLeft(sld)->data;
		cout << endl;
	} while (root != "false" && root != "true");
}*/

int numberLiteralInBody(string s)
{
	int number = 1;
	string sub;
	int posComma = s.find(",");
	if (posComma != -1)
		sub = s.substr(posComma);
	while (posComma != -1) {
		number++;
		sub = sub.substr(posComma + 1);
		cout << sub << endl;
		posComma = sub.find(",");
	}
	return number;
}


void insertSLD(TREE& sld, vector<string> head, vector<string> body)
{
	if (sld && sld->data[0] != "true" && sld->data[0] != "false") {
		string currentNode = sld->data[0];
		int numberPre = theNumberOfHead(head, currentNode);
		if (numberPre == 0)
			insertLeft(sld, "false");
		else {
			int index = 0;
			for (int i = 0; i < head.size(); i++) {
				if (head[i] == currentNode) {
					if (body[i] == "_")
						insertLeft(sld, "true");
					if (index == 0)
						insertLeft(sld, body[i]);
					else {
						insertRight(sld, body[i]);
						break;
					}
					index++;
				}
			}
		}
		NLR(sld);
		cout << endl;
		insertSLD(sld->left, head, body);
		insertSLD(sld->right, head, body);
	}
}

bool isLoop(vector<string> existClause, string toCheck)
{
	for (int i = 0; i < existClause.size(); i++) {
		if (existClause[i] == toCheck)
			return true;
	}
	return false;
}

void outputArr(vector<string> arr)
{
	for (int i = 0; i < arr.size(); i++) {
		cout << arr[i] << " ";
	}
}

vector<string> parseBodyToLiteral(string s)
{
	vector<string> literals;	//Array of literals which is in string s 
	string sub;
	int posComma = s.find(",");
	if (posComma != -1) {
		sub = s.substr(posComma + 1);
		literals.push_back(removeSpace(s.substr(0, posComma)));
	}
	while (posComma != -1) {
		posComma = sub.find(",");
		literals.push_back(removeSpace(sub.substr(0, posComma)));
		sub = sub.substr(posComma + 1);	
	}
	return literals;
}