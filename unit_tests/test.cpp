#include "../src/base.h"
#include "../src/connectors.h"
#include "../src/commands.h"
#include "../src/prototype.h"
#include "./gtest/gtest.h"
#include <string>
#include <iostream>

using namespace std;




//CONNECTORS

TEST(ConnectorsClassesTest, TestConnectorFunctions){
	Connectors* connectorAnd = new ConnectorAnd();
	Connectors* connectorOr = new ConnectorOr();
	Connectors* connectorSemiCol = new ConnectorSemiCol();

	Connectors* connectorPipe = new ConnectorPipe();	
	EXPECT_EQ("&&", connectorAnd->elem());
	cout << connectorAnd->elem() << endl;
	EXPECT_EQ("||", connectorOr->elem());
	cout << connectorOr->elem() << endl;
	EXPECT_EQ(";", connectorSemiCol->elem());
	cout << connectorSemiCol->elem() << endl;	
	EXPECT_EQ("|", connectorPipe->elem());
	cout << connectorPipe->elem() << endl;
}

//COMMANDS

TEST(CommandsTest, TestCommandsFunctions){
	vector<string> cmd;
	//string<Commands*> test;
	cmd.push_back("hello");
	Commands* cmds = new Commands(cmd);
	EXPECT_EQ("hello", cmds->elem());
	cmd.push_back("world!");
	Commands* cmds2 = new Commands(cmd);
	EXPECT_EQ("hello world!", cmds2->elem());
	//Connectors* connectorAnd = new ConnectorAnd();
	//Connectors* connectorAnd = ConnectorAnd();
	//commands->LeftSet(connectorAnd);
	//EXPECT_TRUE("&&", commands->LeftSet(connectorAnd));
	
	string test = "<";
	string test1 = ">";
	string test2 = ">>";
	string test3 = "<>";
	Commands* command = new Commands(cmd);
	EXPECT_TRUE( command->isRedirection(test));
	EXPECT_TRUE( command->isRedirection(test1));
	EXPECT_TRUE( command->isRedirection(test2));
	EXPECT_FALSE( command->isRedirection(test3));
}


// RSHELL
TEST(RShellTest, TestRShellFunction){
	rshell* shell = new rshell();
	EXPECT_TRUE(shell->isConnector("&&"));
	EXPECT_TRUE(shell->isConnector("||"));
	EXPECT_TRUE(shell->isConnector("|"));
	EXPECT_FALSE(shell->isConnector("xD"));
	vector<string> cmd;
	cmd.push_back("(hello");
	cmd.push_back("world)");
	EXPECT_TRUE(shell->isBalancedParen(cmd));
	cmd.push_back("(");
	cmd.push_back("(");
	EXPECT_FALSE(shell->isBalancedParen(cmd));
	EXPECT_FALSE(shell->isRightBrac("("));
	EXPECT_TRUE(shell->isRightBrac(")"));
	EXPECT_TRUE(shell->isLeftBrac("("));
	EXPECT_FALSE(shell->isLeftBrac(")"));
}

//Redirection Test
TEST(RedirectionTest, TestRedirectionFunctions){
	vector<string> cmd;
	
	Commands* cmds = new Commands(cmd);
	EXPECT_TRUE(cmds->isRedirection("<"));
	EXPECT_TRUE(cmds->isRedirection(">"));
	EXPECT_TRUE(cmds->isRedirection(">>"));
	EXPECT_FALSE(cmds->isRedirection("xD"));
}

int main(){
::testing::InitGoogleTest();
	return RUN_ALL_TESTS();
}
