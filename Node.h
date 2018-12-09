#ifndef NODE_H
#define NODE_H

class Node
{
	public:

    Node(int _info);
		~Node();
		int GetInfo();
	private:
	  int info;
};
#endif
