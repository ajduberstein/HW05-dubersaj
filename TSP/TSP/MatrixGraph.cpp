#include "MatrixGraph.h"
#include "Graph.h"

MatrixGraph::MatrixGraph(unsigned num_nodes)
{
	num_edges = 0;
	M = std::vector<std::vector<EdgeWeight> >(num_nodes);
	for (int i = 0; i < num_nodes; i++){
		M[i] = std::vector<EdgeWeight>(num_nodes);
		for (int j = 0; j < num_nodes; j++){
			M[i][j] = 0;
		}
	}
}

MatrixGraph::~MatrixGraph(){

}

void MatrixGraph::addEdge(NodeID u, NodeID v, EdgeWeight weight)
{
	if (weight > 0 && M.at(u).at(v) == 0 && M.at(v).at(u) == 0 && u != v && u >= 0 && u < M.size() && v >= 0 && v < M.size())
	{
		M[u][v] = weight;
		M[v][u] = weight;
		num_edges++;
	}
	else{
	}
}

EdgeWeight MatrixGraph::weight(NodeID u, NodeID v) const
{
	if (u >= 0 && u < M.size() && v >= 0 && v < M.size())
		return M.at(u).at(v);	
	else
		return 0;
}

std::list<NWPair> MatrixGraph::getAdj(NodeID u) const
{
	if (u >= 0 && u < M.size()){
		std::list<NWPair> neighbors;
		for (int i = 0; i < M[u].size(); i++){
				if(M[u][i] != 0){
					neighbors.push_back(NWPair(i,M[u][i]));
				}
		}
		return neighbors;
	}
}

unsigned MatrixGraph::degree(NodeID u) const{
	if (u >= 0 && u < M.size()){
		return getAdj(u).size();
	}
	else
		return 0;
}

unsigned MatrixGraph::size() const
{
	return M.size();
}

unsigned MatrixGraph::numEdges() const
{
	return num_edges;	
}
