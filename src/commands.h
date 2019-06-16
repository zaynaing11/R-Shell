#ifndef COMMANDS_H
#define COMMANDS_H

#include <string>
#include <vector>

#include "base.h"

class Commands: public Base{
	private:
		string name;
		//string cmd;
		string input_file;
		string output_file;
		
		vector<string> cmds;
	public:
		Commands():Base() {};
		Commands(vector<string>);
		bool eval(int, int);
		string elem();
		void LeftSet(Base*);
		void RightSet(Base*);
		bool isRedirection(string);
		void inputFileSet(string);
		void outputFileSet(string);
};

#endif
