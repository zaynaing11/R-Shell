#ifndef CONNECTORS_H
#define CONNECTORS_H

#include "commands.h"

class Connectors: public Base{
	public:
		virtual bool eval(int,int) = 0;
		virtual string elem() = 0;
		virtual void LeftSet(Base*) = 0;
		virtual void RightSet(Base*) = 0;
};

class ConnectorAnd: public Connectors{
	private:
		Base* left;
		Base* right;
	public:
		ConnectorAnd() {left = 0; right = 0;};
		bool eval(int,int);
		string elem();
		void LeftSet(Base*);
		void RightSet(Base*);
};

class ConnectorOr: public Connectors{
	private:
		Base* left;
		Base* right;
	public:
		ConnectorOr(){left = 0; right = 0;};
		bool eval(int, int);
		string elem();
		void LeftSet(Base*);
		void RightSet(Base*);
};

class ConnectorSemiCol: public Connectors{
	private:
                Base* left;
                Base* right;
        public:
		ConnectorSemiCol(){left = 0; right = 0;};
                bool eval(int, int);
                string elem();
                void LeftSet(Base*);
                void RightSet(Base*);
};

class ConnectorPipe: public Connectors{
	private: 
		Base* left;
		Base* right;
	public:
		ConnectorPipe(){left = 0; right = 0;};
		bool eval(int, int);
		string elem();
		void LeftSet(Base*);
		void RightSet(Base*);
};

#endif
