#include "stdafx.h"
#include "TreeSLD.h"

vector<string> existNode;

void initTree(TREE &T)
{
	T = NULL;
}

TNode* getNode(vector<string> s)
{
	TNode* p = new TNode;
	if (p == NULL)
		return NULL;
	p->data = s;
	p->left = NULL;
	p->right = NULL;
	return p;
}

void insertLeft(TREE &T, vector<string> s)
{
	if (T == NULL) {
		T = getNode(s);
	}
	else {
		insertLeft(T->left, s);
	}
}


void insertRight(TREE &T, vector<string> s)
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
		outputArr(T->data);
		cout << "  ";
		LNR(T->right);
	}
}

void NLR(TREE T)
{
	if (T != NULL) {
		outputArr(T->data);
		cout << "  ";
		NLR(T->left);
		NLR(T->right);
	}
}

void LRN(TREE T)
{
	if (T != NULL) {
		LRN(T->left);
		LRN(T->right);
		outputArr(T->data);
		cout << "  ";
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
	if (sld && sld->data[0] != "true" && sld->data[0] != "false" && sld->data[0] != "loop") {
		//Kiểm tra trực kiện hiện tại có bị lặp hay không

		string currentNode = sld->data[0];	//Trực kiện trái nhất trong một node
		vector<string> leftLit = leftLiteralsInNode(sld->data);	//nhung truc kien con lai trong node sau truc kien trai nhat
		int numberPre = theNumberOfHead(head, currentNode);	//Số lượng trưc kiện có trong các head các mđ hạn định
		if (numberPre == 0)
			insertLeft(sld, parseBodyToLiteral("false"));
		else {
			int index = 0;
			for (int i = 0; i < head.size(); i++) {
				if (head[i] == currentNode) {
					if (body[i] == "_")	//Nếu giá trị của node là true
					{
						if (leftLit.size() > 0)
							insertLeft(sld, leftLit);
						else {
							insertLeft(sld, parseBodyToLiteral("true"));
							break;
						}
					}
					else if (index == 0)	//thêm vào nhánh con trái
					{
						if (leftLit.size() > 0) {
							insertLeft(sld, mergeParentAndChild(leftLit, body[i]));
						}
						else
							insertLeft(sld, parseBodyToLiteral(body[i]));
					}
					else {
						if (leftLit.size() > 0) {
							insertRight(sld, mergeParentAndChild(leftLit, body[i]));
						}
						else {
							insertRight(sld, parseBodyToLiteral(body[i]));
							break;
						}
					}
					index++;
				}
			}
		}
		existNode.push_back(currentNode);
		
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
		cout << arr[i] << ", ";
	}
}

vector<string> parseBodyToLiteral(string s)
{
	vector<string> literals;	//Array of literals which is in string s 
	string sub;
	int posComma = isInLiteral(s);

	//Kiểm tra có dấu phẩy trong chuỗi hay không
	if (posComma != -1) {
		sub = s.substr(posComma + 1);
		literals.push_back(removeSpace(s.substr(0, posComma)));
	}
	else {
		literals.push_back(removeSpace(s));
	}

	while (posComma != -1) {
		posComma = isInLiteral(sub);
		literals.push_back(removeSpace(sub.substr(0, posComma)));
		sub = sub.substr(posComma + 1);
	}
	return literals;
}

vector<string> leftLiteralsInNode(vector<string> nodeData)
{
	vector<string> leftLiterals;
	for (int i = 1; i < nodeData.size(); i++)
		leftLiterals.push_back(nodeData[i]);
	return leftLiterals;
}

void removeSameValue(vector<string>& arr)
{
	for (int i = 0; i < arr.size()-1; i++) {
		for (int j = i + 1; j < arr.size(); j++)
		{
			if (arr[i] == arr[j])
				arr.erase(arr.begin() + j);
		}
	}
}

vector<string> mergeParentAndChild(vector<string> leftLiterals, string childValue)
{
	vector<string> child = parseBodyToLiteral(childValue);
	child.insert(child.end(), leftLiterals.begin(), leftLiterals.end());
	removeSameValue(child);
	return child;
}

bool checkIfLoop(vector<string> arr, string s)
{
	for (int i = 0; i < arr.size(); i++)
		if (arr[i] == s)
			return true;
	return false;
}

int isInLiteral(string s)
{
	int posOpenBracket = s.find_first_of("(");
	int posCloseBracket = s.find_first_of(")");
	int posComma = s.find_first_of(",");
	while (posComma > posOpenBracket && posComma < posCloseBracket) {
		posComma = s.find(",", posComma + 1);
		posOpenBracket = s.find("(", posOpenBracket + 1);
		posCloseBracket = s.find(")", posOpenBracket + 1);
	}
	return posComma;
}