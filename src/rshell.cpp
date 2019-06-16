#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <stack>
#include <queue>
#include "rshell.h"
#include "commands.h"


void rshell::begin(){
	bool status = true;
	while(status == true){
		execute();
	}
}

void rshell::execute(){
	string args;
	vector<string> userArgs;
	stack<string> connectors;
	queue<Base*> output;
	
	cout << "$ ";
	getline(cin, args);

	if(args.find('#') != string::npos){
		args = args.substr(0, args.find('#'));
	}
	
	if(args.empty()){
		return;
	}

	int arg_sz = args.size();
	char* cstr = new char[arg_sz + 1];
	strcpy(cstr, args.c_str());
	char* tok = strtok(cstr, " ");

	while( tok != NULL){
		userArgs.push_back(tok);
		tok = strtok(NULL, " ");
	}
	
	for(vector<string>::iterator it = userArgs.begin(); it != userArgs.end(); it++){
		while( it->find("\"") != string::npos){
			it->erase(it->find("\""), 1);
		}
		if(*it == "(" || *it == ")" || *it == "[" || *it == "]" || *it  == "<" || *it == ">" || *it == ">>" || *it == "|" ){
			continue;
		}
		else if(it->at(it->size() - 1) == ';'){
			it->pop_back();
			it = userArgs.insert(it + 1, ";");
		}
		else if (it->at(0) == '('){
			string subs = it->substr(1, it->size() - 1);
			*it = "(";
			it = userArgs.insert(it + 1, subs) - 1;
		}
		else if (it->find(")") != string::npos){
			int count = 0;
			for (int i = 0; i < it->size(); ++i){
				if(it->at(i) == ')'){
					++count;
				}
			}
			*it = it->substr(0, it->find(")"));
			for(int i = 0; i < count; ++i){
				it = userArgs.insert(it + 1, ")");
			}
		}
		else if (it->at(0) == '['){
			string subs = it->substr(1, it->size()-1);
			*it = "[";
			it = userArgs.insert(it + 1, subs) - 1;
		}
		else if (it->at(it->size() - 1) == ']'){
			*it = it->substr(0, it->size() - 1);
			it = userArgs.insert(it + 1, "]") - 1;
		}
	
	}
	if(isConnector(userArgs.at(userArgs.size() - 1 ))){
		userArgs.pop_back();
	}
	
	if(!isBalancedParen(userArgs)){
		cout << "Parentheses aren't balanced" << endl;
		return;
	}

	vector<string> temp;
	for(int i = 0; i < userArgs.size(); i++){
		string elem = userArgs.at(i);
		if(!isConnector(elem) && !isLeftBrac(elem) && !isRightBrac(elem)){
			temp.push_back(elem);
		}
		else if (isConnector(elem)){
			if(!temp.empty()){
				output.push(new Commands(temp));
				temp.clear();
			}
			if(!connectors.empty()){
				while( !connectors.empty() && !isLeftBrac(connectors.top())){
					output.push(chooseConnector(connectors.top()));
					connectors.pop();
				}
			}
			connectors.push(elem);	
		}
		else if (isLeftBrac(elem)){
			connectors.push(elem);
		}
		else{
			if(!temp.empty()){
				output.push(new Commands(temp));
				temp.clear();
			}
			while(!isLeftBrac(connectors.top())){
				output.push(chooseConnector(connectors.top()));
				connectors.pop();
			}
			connectors.pop();
		}
	}

	if(!isRightBrac(userArgs.at(userArgs.size() - 1))){
		output.push(new Commands(temp));
		temp.clear();
	}
	while(!connectors.empty()){
		output.push(chooseConnector(connectors.top()));
		connectors.pop();
	}
	
	stack<Base*> comp;
	Base* leaf_1 = 0;
	Base* leaf_2 = 0;
	
	while(!output.empty()){
		if(isConnector(output.front()->elem())){
			leaf_1 = comp.top();
			comp.pop();
			leaf_2 = comp.top();
			comp.pop();
			output.front()->LeftSet(leaf_2);
			output.front()->RightSet(leaf_1);
			comp.push(output.front());
		}else{
			comp.push(output.front());
		}
		output.pop();
	}
	Base* root = comp.top();
	
	if(root->eval(0,1)){
	
	}

	delete[] cstr;

}

bool rshell::isBalancedParen(vector<string> vec){
	stack<string> paren;
	for(int i = 0; i < vec.size(); ++i){
		if(isLeftBrac(vec.at(i))){
			paren.push(vec.at(i));
		}
		else if (isRightBrac(vec.at(i))){
			if(paren.empty()){
				return false;
			}
			else{
				string temp = paren.top();
				paren.pop();
				
				if(isLeftBrac(temp)){
					continue;
				}else{
					return false;
				}
			}
		}
	}
	return paren.empty();
} 
bool rshell::isConnector(string arg){

	if(arg == "&&" || arg == "||" || arg == ";" || arg == "|"){
		return true;		//if args match cases, return true
	}
	return false;
}

Base* rshell::chooseConnector(string symbols){
	if(symbols == "&&"){
		return new ConnectorAnd();
	}
	else if (symbols == "||"){
		return new ConnectorOr();
	}
	else if (symbols == "|"){
		return new ConnectorPipe();
	}
	return new ConnectorSemiCol();
}

bool rshell::isLeftBrac(string arg){
	if(arg == "("){
		return true;
	}
	return false;
}

bool rshell::isRightBrac(string arg){
	if(arg == ")"){
		return true;
	}
	return false;
}

int main(){
        rshell shell;

        shell.begin();

        return 0;

}

