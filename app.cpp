#include "Landmarks.h"
#include "Strategy.h"

///			Created By	
///	E. Janssen	&	F. v.d. Meulen
///--------------------------------------
///	Project	:	Landmark System
/// Course	:	Social Network Analysis
/// Date	  :	30/11/2018
/// Classe	:	Main
///---------------------------------------

//  Function    : Parse CSV
//  Description :
//  @Param      : std::string parseFile
//	@Param		: bool header
//	@Param		: std::string delimeter
//  @Pre        :
//  @Post       :
boost::tuple<Graph*, std::set<int>*> ParseCSV(std::string parseFile, bool header, std::string delimiter)
{
	bool headerTrigger = header;

	std::ifstream file(parseFile);

	if (!file)
		std::cerr << "Could not open the file!" << std::endl;

	//Creating Storage for edges and weights of edges
	std::vector<Edge>* edge_vec = new std::vector<Edge>();
	std::vector<int>* weights_vec = new std::vector<int>();

	//Creating temporary stprage to read per line.
	std::string line = "";

	//Instances of our return values
	std::set<int>* nodes = new std::set<int>();
	Graph* G = new Graph();

	//Loop through all line in the file
	while (getline(file, line))
	{
		//Skipping any headers.
		if (headerTrigger == true && header == true)
		{
			headerTrigger = false;
			continue;
		}

		//Splitting on delimiter
		std::vector<std::string> vec;
		boost::algorithm::split(vec, line, boost::is_any_of(delimiter));

		//Undirected and Unweighted
		if (vec.size() == 2)
		{
			std::string a = vec.at(0);
			std::string b = vec.at(1);
			int A = std::stoi(a);
			int B = std::stoi(b);

			nodes->insert(A);
			nodes->insert(B);

			boost::add_edge(A, B, 1, *G);
			boost::add_edge(B, A, 1, *G);
		}
	}

	return boost::make_tuple( G, nodes );
}

//  Function    : Main Application
//  Description :
//  @Param      : int argc
//	@Param		: char** argv
//  @Pre        :
//  @Post       :
int main(int argc, char **argv)
{
	//Parser
	bool header = true;
	std::string delimiter = ",";
	boost::tuple<Graph*, std::set<int>*> x = ParseCSV(argv[1],header,delimiter);

	//Tuple Extraction
	const Graph* graph = boost::get<0>(x);
	std::set<int>* nodes = boost::get<1>(x);

	//Converting Set of Unique Nodes to Easy acces Vector
	std::vector<Node* >* nodesList = new std::vector<Node*>();
	for (std::set<int>::iterator it = nodes->begin(); it != nodes->end(); ++it)
	{
		nodesList->push_back(new Node(*it));
	}
	
	//Creating Our System Representation
	Landmarks* system = new Landmarks(graph, nodesList,RandomStrategy,1);
	
	//Testing
	//std::cout << "Distance between A - D: \t" << system->DistanceLandmarks(Anode, Dnode) << std::endl;
	
	return 0;
}
