#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
#include <vector>
#include <stack> 
#include <queue>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdio.h>
#include <fstream>
#include <fcntl.h>

#include "commands.h"

using namespace std;

Commands::Commands(vector<string> vec) {
	for (int i = 0; i < vec.size(); i++) {
		cmds.push_back(vec.at(i));
	}
}

bool Commands::eval(int input, int output){
	if(cmds.at(0) == "exit"){
		exit(0);
	}
	if(cmds.at(0) == "test" || cmds.at(0) == "["){
		if(cmds.at(0) == "["){
			if(cmds.at(cmds.size()-1) != "]"){
				cout << "Not the right [ ]" << endl;
				return false;
			}
		}
		if(cmds.at(1) == "-e"){
			struct stat infor;
			if(stat(const_cast<char*>(cmds.at(2).c_str()), &infor) != 0){
				cout << "Can't access " << cmds.at(2) << endl;
				cout << "False" << endl;
				return false;
			}
			else{
				cout << "True" << endl;
				return true;
			}
		}
		else if (cmds.at(1) == "-f"){
			struct stat infor;
			if(stat(const_cast<char*>(cmds.at(2).c_str()), &infor) != 0){
				cout << "Can't access " << cmds.at(2) << endl;
				cout << "False" << endl;
				return false;
			}
			else if (infor.st_mode & S_IFREG){
				cout << "True" << endl;
				return true;
			}
			else {
				cout << "False" << endl;
				return false;
			}
		}
		else if (cmds.at(1) == "-d"){
			struct stat infor;
			if(stat(const_cast<char*>(cmds.at(2).c_str()), &infor) != 0){
				cout << "Can't access " << cmds.at(2) << endl;
				cout << "False" << endl;
				return false;
			}
			else if(infor.st_mode & S_IFDIR){
				cout << "True" << endl;
				return true;
			}
			else{
				cout << "False" << endl;
				return false;
			}
		}
		else{
			struct stat infor;
			if(stat(const_cast<char*>(cmds.at(1).c_str()), &infor) != 0){
				cout << "Can't access " << cmds.at(1) << endl;
				cout << "False" << endl;
				return false;
			}
			else{
				cout << "True" << endl;
				return true;
			}
		}
	}

	else{
		int status = 0;
		pid_t pid = fork();
		pid_t w;
		
		if(pid < 0){
			cout << "Error: forking child process has failed\n" << endl;
			exit(1);
		}
		else if (pid == 0){
			vector <string> cmds_temp;
			for(int i = 0;  i < cmds.size(); i++){
				if(!isRedirection(cmds.at(i))){
					cmds_temp.push_back(cmds.at(i));
				}else{
					break;
				}
			}
			
			if(isRedirection(cmds.at(cmds.size() - 1))){
				cout << "Can't use redirector(s)" << endl;
				return false;
			} 
			for (int i = 0; i < cmds.size(); i++){
				if (isRedirection(cmds.at(i))){
					if(cmds.at(i) == "<"){
						inputFileSet(cmds.at(i + 1));
					}
					else if (cmds.at(i) == ">" || cmds.at(i) == ">>"){
						outputFileSet(cmds.at(i + 1));
					}
					else{
						cout << "Can't use redirector(s)" << endl;
					}
				}
			}
			
			int arr_size_io = cmds_temp.size() + 1;
			char* args_io[arr_size_io];

			for (int i = 0; i < arr_size_io - 1; i++ ){
				args_io[i] = const_cast<char*>(cmds_temp.at(i).c_str());
			}
			args_io[arr_size_io - 1] = NULL;
			
			if(!input_file.empty() && !output_file.empty()){
				if (find(cmds.begin(), cmds.end(), ">") != cmds.end()) {
					int input_descriptor = open(input_file.c_str(), O_RDONLY);
					int output_descriptor = open(output_file.c_str(), O_RDWR | O_TRUNC | O_CREAT, S_IRWXU | S_IRWXG);	
					if(input_descriptor < 0 || output_descriptor < 0){
						cout << "Can't open the file" << endl;
						return false;
					}	
				
					dup2(input_descriptor, STDIN_FILENO);
					dup2(output_descriptor, STDOUT_FILENO);
			
					close(input_descriptor);
					close(output_descriptor);

					dup2(input, 0);
					dup2(output, 1);

					if (input != 0){
						close(input);
					}
					else if (output != 1){
						close(output);
					}
				
					if(execvp(*args_io, args_io) < 0 ){
						cout << "Error: exec failed \n" << endl;
						exit(1);
					}

				}
				else {
					int input_descriptor = open(input_file.c_str(), O_RDONLY);
					int output_descriptor = open(output_file.c_str(), O_RDWR | O_APPEND| O_CREAT, S_IRWXU | S_IRWXG);
					
					if( input_descriptor < 0 || output_descriptor < 0 ){
						cout << "Error opening the file" << endl;
						return false;
					}
			
					dup2(input_descriptor, STDIN_FILENO);
					dup2(output_descriptor, STDOUT_FILENO);

					close(input_descriptor);
					close(output_descriptor);
					
					dup2(input, 0);
					dup2(output, 1);
					
					if(input != 0){
						close(input);
					}else if (output != 1){
						close(output);
					}
					
					if(execvp(*args_io, args_io) < 0 ){
						cout << "Error: exec failed \n" << endl;
						exit(1);
					}
				}
			}
			
			else if (!input_file.empty()){
				int file_descriptor = open(input_file.c_str(), O_RDONLY);
				
				if(file_descriptor < 0 ){
					cout << "Error opening the file" << endl;
					return false;
				}
				
				dup2(file_descriptor, STDIN_FILENO);
				close(file_descriptor);

				dup2(input, 0);
				dup2(output, 1);
			
				if (input != 0){
					close(input);
				}
				else if (output != 1){
					close(output);
				}
				
				if(execvp(*args_io, args_io) < 0 ){
					cout << "Error: exec failed \n" << endl;
					exit(1);
				}
			}
		 	else if (!output_file.empty()){
				if(find(cmds.begin(), cmds.end(), ">") != cmds.end()){
					int file_descriptor = open(output_file.c_str(), O_RDWR | O_TRUNC | O_CREAT, S_IRWXU | S_IRWXG);
					if (file_descriptor < 0){

						cout << "Error opening the file" << endl;
						return false;
					}	
					dup2(file_descriptor, STDOUT_FILENO);
					close(file_descriptor);
				

					dup2(input, 0);
					dup2(output, 1);

					if (input != 0){
						close(input);
					}else if (output != 1){
						close(output);
					}
					
					if(execvp(*args_io, args_io) < 0){
						cout << "Error: exec failed \n" << endl;
						exit(1);
					}
				
				}
				else{
					int file_descriptor = open(output_file.c_str(), O_RDWR | O_APPEND | O_CREAT, S_IRWXU | S_IRWXG);
					if (file_descriptor < 0 ){
						cout << "Error opening the file" << endl;
						return false;
					}
					
					dup2(file_descriptor, STDOUT_FILENO);
					
					close(file_descriptor);

					
					dup2(input, 0);
					dup2(output, 1);
					
					if(input != 0){
						close(input);
					}
					else if (output != 1){
						close(output);
					}
					
					if(execvp(*args_io, args_io) < 0){
						cout << "Error: exec failed \n" << endl;
						exit(1);
					}
				}
			}	
			else {
				int arr_size = cmds.size() + 1;
				char* args[arr_size];
				for(int i = 0; i < arr_size - 1; i++){
					args[i] = const_cast<char*> (cmds.at(i).c_str());
				}
				args[arr_size - 1] = NULL;
				
				dup2(input, 0);
				dup2(output, 1);
				
				if (input != 0){
					close(input);
				}
				else if (output != 1){
					close(output);
				}
				
				if(execvp(*args, args) < 0){
					cout << "Error: exec failed \n" << endl;
					exit(1);
				}
			
			}
		}	
		else{
			w = waitpid(pid, &status, 0);
			if(w == -1){
				cout << "Error: issue with waitpid" << endl;
				exit(EXIT_FAILURE);
			}	
			if(WEXITSTATUS(status) == 0){
				return true;
			}
		}
	}
	return false;
}

string Commands::elem(){
	string tot;
	for(int i = 0; i < cmds.size() - 1; i++){
		tot = tot + cmds.at(i) + " ";
	}
	tot = tot + cmds.at(cmds.size() - 1);
	return tot;
}
void Commands::LeftSet(Base* node) {}

void Commands::RightSet(Base* node) {}


bool Commands::isRedirection(string input){
	if (input == "<" || input == ">" || input == ">>"){
		return true;
	}
	return false;
}

void Commands::inputFileSet(string in_file){

	input_file = in_file;
}

void Commands::outputFileSet(string out_file){

	output_file = out_file;
}
