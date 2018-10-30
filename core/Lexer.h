/*
参考 Modern Compiler Implementation in C P24 figure 2.5
保存两个状态变量，一个表示上一次进入accept state时，state上的标号。一个表示当前进入的状态的标号。
扫描的过程，保存三个位置变量，一个变量在不断的前进，一个变量保存这一轮扫描开始时的位置，
还有一个变量保存这一轮上一次前进成功的位置。如果可以前进，要更新第三个变量。
如果不能前进，那么输出第二个变量到第三个变量这个位置范围的字符，并且输出上一次进入accpet state的状态的标号。
然后更新三个位置变量为第二位置变量的数值。

使用的时候，要注意优先级高的规则要后加入（addPattern)。
*/

#pragma once
#include "stdafx.h"
#include "DFA.h"
#include "RegularExpression.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;
class Lexer
{
public:
	Lexer();
	~Lexer();

	vector<string> patterns;
	vector<NFA> NFAs;
	NFA mixNFA;;
	DFA dfa;
	string text;

	void readText(const char *fileName);
	void addPattern(string pattern);
	void convertToDFA();
	void inputSample(string x, string y);
	vector<pair<string, string>> scan();
};



Lexer::Lexer()
{
}


Lexer::~Lexer()
{
}


/*
Reference:
https://stackoverflow.com/questions/2602013/read-whole-ascii-file-into-c-stdstring
https://www.tutorialspoint.com/Read-whole-ASCII-file-into-Cplusplus-std-string
*/
void Lexer::readText(const char *fileName)
{
	ifstream t(fileName);
	stringstream buffer;
	buffer << t.rdbuf();
	text = buffer.str();
}


void Lexer::addPattern(string pattern)
{
	patterns.push_back(pattern);
}


void Lexer::convertToDFA()
{
	for (int i = 0; i < patterns.size(); i++) {
		NFAs.push_back(re_to_NFA(patterns[i]));
	}
	NFA nfa = NFAs[0];
	for (int i = 1; i < NFAs.size(); i++) {
		nfa = nfa_union(nfa, NFAs[i]);
	}
	mixNFA = nfa;
	dfa = nfa.convertToDFA();
}


/*
input: x
stateID: y
*/
void Lexer::inputSample(string x, string y)
{
	dfa.reset();
	bool accepted;
	int acceptedID;
	for (int i = 0; i < x.length(); i++)
	{
		dfa.runOneStep(x[i], accepted, acceptedID);
	}
	dfa.addStateID(acceptedID, y);
	//dfa.stateIDs[acceptedID] = y;
}


vector<pair<string, string>> Lexer::scan()
{
	int startIndex = 0, lastAcceptIndex = 0, indexExplorer = 0;
	bool accepted;
	int currentState;
	vector<pair<string, string>> result;
	dfa.reset();
	bool haveAccepted = false;
	int lastAcceptState = 0;
	while (indexExplorer < text.length())
	{
		dfa.runOneStep(text[indexExplorer], accepted, currentState);
		if (accepted)
		{
			lastAcceptState = currentState;
			haveAccepted = true;
			lastAcceptIndex = indexExplorer;
			indexExplorer++;
			if (indexExplorer == text.length()) {
				string input = text.substr(startIndex, lastAcceptIndex - startIndex + 1);
				string stateID = dfa.stateIDs[dfa.getLastAcceptState()];
				result.push_back(pair<string, string>(input, stateID));
				break;
			}
		}
		else if (!accepted && (currentState == -1) && haveAccepted)
		{
			string input = text.substr(startIndex, lastAcceptIndex - startIndex + 1);
			string stateID = dfa.stateIDs[lastAcceptState];
			startIndex = lastAcceptIndex + 1;
			indexExplorer = lastAcceptIndex + 1;
			lastAcceptIndex++;
			result.push_back(pair<string, string>(input, stateID));

			dfa.reset();
			haveAccepted = false;
		}
		else {
			indexExplorer++;
			if (indexExplorer == text.length()) cerr << "EOF" << endl;
		}
	}
	return result;
}
