# CS 100 RShell

# Project Information

Winter 2019\
Kadhirash Sivakumar SID: 861264257\
Zay Naing SID: 861167224

# Introduction
Hello! Welcome to rshell. In this program we will make a basic command shell that can print a command prompt ("$") and read in a line of commands such as "hello".  We can also extend this command by using connectors such as "&&" , "||" , "|" and ";" to make it say "hello && goodbye", as well as certain flags such as "-e", "-f", and "-d" that allows a user to check if a file exists/is a file/is a directory. It uses the test command in rshell to run, which can be interpreted as "[ ]." There will aslo be precedence operators invovled with brackets "( )" that will be combined with other commands. To run the commands, we will be using "execvp" and will always have the format "$ executable [argumentList] [connector] [cmd] ..." We will do this this by using a composite design pattern, which will have rshell as the client, a Base class as the component, a Connectors and Commands classes as the composites, and a "semicolon", "and," , "pipe," and "or" classes as the leaves to the Connectors class.

# Diagram
![UML Diagram](https://github.com/cs100/assignment-zaddy/blob/master/images/UML%20zaddy.png?raw=true)
# Classes
## **rshell**
This is the client which will start off the entire program by prompting the user to enter a command or commands after displaying a "$" on the terminal. After the user types in their commands, it will read the commands in and execute accordingly.
## **Base**
The Base class acts as a component and has a virtual function, "execute", which the other Connectors and Commands classes inherit, which literally "executes" commands passed in. The base parent pointer connects these expressions together. 
## **Commands**
The Commands class acts as a composite and stores the user's input(s) as a vectors of strings to execute the program. 
## **Connectors**
The Connectors class also acts as a composite and has three different children classes, the leaves. In this class, there is a left and right pointer in case the user decides to use multiple commands in a line, thus would allow the program to connect them.
## **ConnectorSemiCol**
One of the three classes that acts as a leaf and inherits the traits from the parents Connectors class. This allows all the commands following the symbol ";" to execute.
## **ConnectorAnd**
Another one of the three classes that acts as a leaf and inherits the traits from the parents Connectors class. This allows all the commands following the symbol "&&" to execute ONLY if the previous command before the "&&" SUCCEEDS.
## **ConnectorOr**
The last of the three classes that acts as a leaf and inherits the traits from the parents Connectors class. This allows all the commands following the symbol "||" to execute ONLY if the previous command before the "&&" FAILS.

## **ConnectorPipe**
A fourth class that was later implemented which inherits the traits from the parents Connectors class as well. This allows for data to be sent from one program to another, following the "|" symbol.

# Prototypes/Research
**_Prototypes:_** <br/>
In the prototype directory, under the prototype.cpp file (g++ prototype.cpp then ./a.out to execute), it can now echo commands but only up to 4 words. It can, however, use vim for file names greater than 4 words. Unsure of why echo only works for up to 4 words. <br/> 
**_Research:_** <br/>
execvp(): Provides an array of pointers to the null-terminated strings that represent the argument list available to the new program. The first argument points to the filename associated with the file being executed. The array of pointers must be terminated by a NULL pointer. <br/>
fork(): This creates a new process (child) by duplicating the calling process (parent). On success, the PID of the child process is returned in the parent, and 0 is returned in the child. On failure, -1 is returned in the parent, and no child process is created, and errno is set appropriately.\
waitpid(): This call suspends execution of the calling process until a "child" specified by pid argument has changed state. For example, a value less than -1 means to wait for any child process whose process group ID is equal to the absolute value of pid. A value of -1 means waiting for any child process. A value of 0 means to wait for any child process whose process group ID is equal to that of the calling process. Lastly, a value greater than 0 means to wait for the child whose process ID is equal to the value of pid.

# Development and Testing Roadmap
- [x] 1. [Prototype.cpp file] (https://github.com/cs100/assignment-zaddy/issues/1)
- [x] 2. [Class descriptions] (https://github.com/cs100/assignment-zaddy/issues/2)
- [x] 3. [UML Diagram] (https://github.com/cs100/assignment-zaddy/issues/3)
- [x] 4. [Introduction] (https://github.com/cs100/assignment-zaddy/issues/4)
- [x] 5. [Shell] (https://github.com/cs100/assignment-zaddy/issues/5)
- [x] 6. [Shell Connectors] (https://github.com/cs100/assignment-zaddy/issues/6)
- [x] 7. [Shell rshell] (https://github.com/cs100/assignment-zaddy/issues/7)
- [x] 8. [Shell Commands] (https://github.com/cs100/assignment-zaddy/issues/8)
- [x] 9. [Shell Base] (https://github.com/cs100/assignment-zaddy/issues/9)
- [x] 10. [Test Files] (https://github.com/cs100/assignment-zaddy/issues/10)
- [x] 11. [Piping and Redirection] (https://github.com/cs100/assignment-zaddy/issues/11)
- [x] 12. [Final Tests] (https://github.com/cs100/assignment-zaddy/issues/12)
