#include "stdafx.h"
#include "Lexer.h"
#include <string>
#include <iostream>
using namespace std;

extern "C" _declspec(dllexport) int Sum(int a, int b)
{
	return a + b;
}

extern "C" _declspec(dllexport) void generate_dot(const char *str)
{
	if (str[0] == '\0')
	{
		return;
	}
	Lexer lexer;
	lexer.addPattern(str);
	lexer.convertToDFA();

	lexer.mixNFA.generate_DOT("nfa.dt");
	
	lexer.dfa.removeUnreachableStates();
	lexer.dfa.generate_DOT("dfa.dt");

	lexer.dfa.mergeNondistinguishableStates();
	lexer.dfa.removeUnreachableStates();
	lexer.dfa.generate_DOT("miniDfa.dt");

	const char * dotTool = "..\\..\\..\\bin\\dot.exe ";
	string argument = "-Tjpg -O ";

	string nfaDot = "nfa.dt";
	string dfaDot = "dfa.dt";
	string miniDfaDot = "miniDfa.dt";
	
	system((dotTool + argument + nfaDot).c_str());
	system((dotTool + argument + dfaDot).c_str());
	system((dotTool + argument + miniDfaDot).c_str());
}
