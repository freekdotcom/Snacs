#include "Node.h"

Node::Node(int _index = -1)
{
	index = _index;
}

~Node::Node()
{

}

int Node::GetIndex()
{
	return index;
}
