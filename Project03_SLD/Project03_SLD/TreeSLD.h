
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
TNode* getNode(string s);

void insertLeft(TREE &T, string s);

void insertRoot(TREE &T, string s);

void insertRight(TREE &T, string s);


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
