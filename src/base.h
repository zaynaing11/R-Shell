#ifndef BASE_H
#define BASE_H

#include <iostream>

using namespace std;

class Base{
	private:
		Base* left;
		Base* right;
	public:
		Base(){left = 0; right = 0;};
		virtual bool eval(int,int) = 0;
		virtual string elem() = 0;
		Base* LeftGet(){return left;}
		Base* RightGet(){return right;}
		virtual void LeftSet(Base*) = 0;
		virtual void RightSet(Base*) = 0;
};
#endif
