#include "Landmarks.h"
#include "Strategy.h"

///			Created By	
///	E. Janssen	&	F. v.d. Meulen
///--------------------------------------
///	Project	:	Landmark System
/// Course	:	Social Network Analysis
/// Date	  :	10/12/2018
/// Classe	:	Main
///---------------------------------------

//  Function    : Parse CSV
//  Description :
//  @Param      : std::string parseFile
//	@Param		: bool header
//	@Param		: std::string delimeter
//  @Pre        :
//  @Post       :
boost::tuple<Graph*, std::set<int>*> ParseCSV(std::string parseFile, int header, std::string delimiter)
{
	std::ifstream file(parseFile);

	if (!file)
	{
		std::cerr << "Could not open the file!" << std::endl;
		throw "Could not open the file!";
	}

	std::vector<std::string> a;
	boost::algorithm::split(a, parseFile, boost::is_any_of("/"));
	std::cout	<< "Parsing: " << a.back()	<< std::endl
				<< "Status: Starting"		<< std::endl;
	
	//Creating temporary stprage to read per line.
	std::string line = "";

	//Instances of our return values
	std::set<int>* nodes = new std::set<int>();
	std::map<int,int>* dict = new std::map<int,int>();
	int teller = 0;
	Graph* G = new Graph();

	//Loop through all line in the file
	while (getline(file, line))
	{
	  
		//Skipping any headers.
		if (header > 0)
		{
			header--;
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

			if(nodes->find(A) == nodes->end())
			{
			  nodes->insert(A);
			  dict->insert(std::pair<int,int>(A,teller));			  
			  teller++;
			}				

			if(nodes->find(B) == nodes->end())
			{
				nodes->insert(B);
				dict->insert(std::pair<int,int>(B,teller));			  
				 teller++;
			}

			int indexA = dict->find(A)->second;
			int indexB = dict->find(B)->second;

			boost::add_edge(indexA, indexB, 1, *G);
			boost::add_edge(indexB, indexA, 1, *G);
		}
		else
				std::cerr << "ERROR - PARSECSV";
	}
	std::cout << "Status: Complete - " << a.back() << std::endl << std::endl;	
	return boost::make_tuple( G, nodes );
}

//  Function    : Main Application
//  Description :
//	@Param		: Graph* G
//	@Param		: Node* s
//	@Param		: Node* t
//  @Pre        :
//  @Post       :
int trueDistance(const Graph* G, Node* s, Node* t)
{
	std::vector<Vertex> p(num_vertices(*G));
	std::vector<int> d(num_vertices(*G));

	// Create descriptor for the source node
	Vertex begin = vertex(s->GetInfo(), *G);
	Vertex goal = vertex(t->GetInfo(), *G);

	// Evaluate Dijkstra on graph g with source s, predecessor_map p and distance_map d
	boost::dijkstra_shortest_paths(*G, begin, boost::predecessor_map(&p[0]).distance_map(&d[0]));

	//Create Vector to store the traversal path.
	std::vector<boost::graph_traits<Graph>::vertex_descriptor > path;
	boost::graph_traits<Graph>::vertex_descriptor current = goal;

	int max = 20;
	while (current != begin && max > 0)
	{
		path.push_back(current);
		current = p[current];
		max--;
	}
	path.push_back(begin);

	//Find Length of Shortest Path
	if(max != 0)
  	    return path.size();
 	else
  	    return INT_MAX;
}

//  Function    : Main Application
//  Description :
//  @Param      : int argc
//	@Param		: char** argv
//  @Pre        :
//  @Post       :
int main(int argc, char **argv)
{
	std::cout	<< "\t  Created By"								<< std::endl
				<< "----------------------------------"			<< std::endl
				<< "    E. Janssen & F. v.d. Meulen"			<< std::endl
				<< "----------------------------------"			<< std::endl
				<< " Project :\t Landmark System "				<< std::endl
				<< " Course :\t Social Network Analysis"		<< std::endl
				<< " Data :\t\t 10/12/2018"						<< std::endl
				<< "----------------------------------"			<< std::endl << std::endl;

	srand(time(NULL));
  
    if(argc != 6)
    {
        std::cout << "Please use : {Filename} {Delimiter} {HeaderLines} {Runs} {Landmarks}" << std::endl;
        return 0;
    }

	//Parser
	std::string filename = argv[1];
	std::string delimiter = argv[2];
	int header = std::stoi(argv[3]);
	
	int runs = std::stoi(argv[4]);
	int landmarks = std::stoi(argv[5]);

	
	boost::tuple<Graph*, std::set<int>*> x = ParseCSV(filename,header,delimiter);

	//Tuple Extraction
	const Graph* graph = boost::get<0>(x);
	std::set<int>* nodes = boost::get<1>(x);

	//Converting Set of Unique Nodes to Easy acces Vector
	std::vector<Node* >* nodesList = new std::vector<Node*>();
	for (std::set<int>::iterator it = nodes->begin(); it != nodes->end(); ++it)
	{
		nodesList->push_back(new Node(*it));
	}
	
	//Testing
	std::cout	<< "Testing Graph"						<< std::endl
				<< "----------------------------------" << std::endl;		
	std::vector<std::string>* stringStrat = new std::vector<std::string>({ "Random","Degree","Clustering" });
	
	std::vector<Delegate>* strategies = new std::vector<Delegate>({ RandomStrategy, DegreeStrategy, ClusteringStrategy });

	std::ofstream outputFile;
	outputFile.open("output.txt");
	outputFile << "Strategy | Average Error | Average Ratio | Average Upperbound | Average Lowerbound | Time" << std::endl;
	int loopsize = strategies->size();
	for (int i = 0; i < loopsize; i++)
	{
		const clock_t begin_time = clock();
		//Creating Our System Representation
		std::cout<<"New Strategy" << std::endl; 
		Landmarks* system = new Landmarks(graph, nodesList, strategies->at(i), landmarks);

		float AverageError = 0;
		float AverageRatio = 0;
		float AverageUpperbound = 0;
		float AverageLowerbound = 0;
		
		std::vector<int>* lowerVector = new std::vector<int>();
		std::vector<int>* upperVector = new std::vector<int>();

		for (int i = 0; i < runs; i++)
		{
		  
			int indexA = rand() % (nodes->size());
			int indexB = rand() % (nodes->size());
			
			std::cout << "Run - " << i              << std::endl
			          << "\tNode #ID: " << indexA << "\tpath to\tNode #ID: " << indexB  << std::endl;
			Node* Anode = nodesList->at(indexA);
			Node* Bnode = nodesList->at(indexB);

			boost::tuple<int, int, int, int> approx = system->DistanceLandmarks(Anode, Bnode);
			int U = boost::get<0>(approx);
			int L = boost::get<1>(approx);
			
			int distance = trueDistance(graph, Anode, Bnode);
      
      if( distance == 0 )
        std::cout<<"NOPE" <<std::endl;
      
			float error = abs(U - distance) / distance;
			float ratio = ((double)(U - L)) / ((double)U);
      
      lowerVector->push_back(L);
      upperVector->push_back(U);
      
      
			AverageRatio += ratio;
  		AverageError += error;
		}
		AverageError /= runs;
		AverageRatio /= runs;
		
		sort(lowerVector->begin(), lowerVector->end());
		sort(upperVector->begin(), upperVector->end());
		
		AverageUpperbound = upperVector->at(runs/2);
		AverageLowerbound = lowerVector->at(runs/2);

		outputFile << stringStrat->at(i) << " | " << AverageError << " | " << AverageRatio << " | " << AverageUpperbound << " | " << AverageLowerbound << " | " <<  float(clock() - begin_time) / CLOCKS_PER_SEC  << std::endl;

		std::cout	<< "Executed: \t" << stringStrat->at(i)								<< std::endl
					<< "Average Error: \t" << AverageError								<< std::endl
					<< "Average Ratio: \t" << AverageRatio								<< std::endl
					<< "Average Upperbound: \t" << AverageUpperbound << std::endl
					<< "Average Lowerbound: \t" << AverageLowerbound << std::endl
					<< float(clock() - begin_time) / CLOCKS_PER_SEC << std::endl
					<< "---------------------------------------------"	<< std::endl	<< std::endl;

		std::cout <<" End of Strategy " << std::endl;
		delete system;
		system = NULL;
	}
	outputFile.close();
	return 0;
}
