
#include <iostream>
#include <string>
#include <vector>
#include <stack>
using namespace std;



//struct TNode
//{
//	string data;
//	TNode* left;
//	TNode* right;
//};
//typedef TNode *TREE;

struct TNode
{
	vector<string> data;
	TNode* left;
	TNode* right;
};
typedef TNode *TREE;

void initTree(TREE &T);
TNode* getNode(vector<string> s);

void insertLeft(TREE &T, vector<string> s);

void insertRight(TREE &T, vector<string> s);


void LNR(TREE T);

void NLR(TREE T);

void LRN(TREE T);

void outputArrStr(vector<string> premises);

//Removing spaces which is before string and after string
string removeSpace(string s);

//Get Head Of Definite Clause
string getHead(string premise);

//Get Body Of Definite Clause
string getBody(string premise);

int theNumberOfHead(vector<string> head, string foundStr);

TNode* findMostLeft(TREE sld);	//the nex parent is the most left/right leaf node


void insertSLD(TREE&, vector<string>, vector<string>);

int numberLiteralInBody(string);

bool isLoop(vector<string>, string);

void outputArr(vector<string>);

vector<string> parseBodyToLiteral(string);	//Chuyển đổi body dạng string thành chuỗi các trực kiện

vector<string> leftLiteralsInNode(vector<string>);		//Những trực kiện còn lại chưa được xử lý trong một node

void removeSameValue(vector<string>&);

vector<string> mergeParentAndChild(vector<string>, string);	//merge left literals in parent to its child

bool checkIfLoop(vector<string>, string);	//Kiểm tra data của node hiện tại có thuộc node trươc đó đã thêm hay chưa

int isInLiteral(string);