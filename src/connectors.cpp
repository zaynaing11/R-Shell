#include <iostream>
#include <unistd.h>
#include "connectors.h"

using namespace std;


//AND

bool ConnectorAnd::eval(int input, int output){	
	if(left->eval(0,1)){
		return right->eval(0,1);
	}
	return false;
}

string ConnectorAnd::elem(){
	return "&&";
}

void ConnectorAnd::LeftSet(Base* leftNode){
	left = leftNode;
}


void ConnectorAnd::RightSet(Base* rightNode){
	right = rightNode;
}

//OR


bool ConnectorOr::eval(int input, int output){
	if(!left->eval(0,1)){
		return right->eval(0,1);
	}
	return true;
}

string ConnectorOr::elem(){
	return "||";
}

void ConnectorOr::LeftSet(Base* leftNode){
	left = leftNode;
}

void ConnectorOr::RightSet(Base* rightNode){
	right = rightNode;
}


//SEMICOL

bool ConnectorSemiCol::eval(int input, int output){
	left->eval(0,1);
	return right->eval(0,1);
}

string ConnectorSemiCol::elem(){
	return ";";
}

void ConnectorSemiCol::LeftSet(Base* leftNode){
	left = leftNode;
}

void ConnectorSemiCol::RightSet(Base* rightNode){
	right = rightNode;
}

//PIPE

bool ConnectorPipe::eval(int input, int output){
	int fds[2];
	pipe(fds);
	
	left->eval(input, fds[1]);
	close(fds[1]);

	right->eval(fds[0], output);
	close(fds[0]);
	
	return true;
}

string ConnectorPipe::elem(){
	return "|";
}

void ConnectorPipe::LeftSet(Base* leftNode){
	left = leftNode;
}
void ConnectorPipe::RightSet(Base* rightNode){
	right = rightNode;
}
