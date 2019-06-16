#ifndef RSHELL_H
#define RSHELL_H

#include <iostream>
#include <string>
#include <cstring>
#include <stack>
#include <queue>
#include "base.h"
#include "connectors.h"

using namespace std;

class rshell{
	public:
		rshell(){};
		void begin();
		void execute();
		bool isConnector(string);
		bool isBalancedParen(vector<string>);
		bool isLeftBrac(string);
		bool isRightBrac(string);
		Base* chooseConnector(string);	
};

#endif
