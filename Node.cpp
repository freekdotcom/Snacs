#include "Node.h"

///			Created By	
///	E. Janssen	&	F. v.d. Meulen
///--------------------------------------
///	Project	:	Landmark System
/// Course	:	Social Network Analysis
/// Date	  :	30/11/2018
/// Classe	:	Node
///---------------------------------------

//  Function    : Constructor
//  Description :
//  @Param      : int _info
//  @Pre        :
//  @Post       :
Node::Node(int _info){
  info = _info;

}

//  Function    : Destructor
//  Description :
//  @Pre        :
//  @Post       :
Node::~Node(){
}

//  Function    : Getter Info
//  Description :
//  @Pre        :
//  @Post       :
int Node::GetInfo()
{
  return info;
}
