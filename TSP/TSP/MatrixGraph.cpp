#include "MatrixGraph.h"
#include "Graph.h"

MatrixGraph::MatrixGraph(unsigned num_nodes)
{
	num_edges = 0;
	M = std::vector<std::vector<EdgeWeight> >();
	for (int i = 0; i < num_nodes; i++){
		M.push_back(std::vector<EdgeWeight>(num_nodes));
	}
}

MatrixGraph::~MatrixGraph()
{
	delete &M;
}

void MatrixGraph::addEdge(NodeID u, NodeID v, EdgeWeight weight)
{
	if (weight > 0 && M.at(u).at(v) == 0 && M.at(v).at(u) == 0 && u != v && u >= 0 && u < M.size() && v >= 0 && v < M.size())
	{
		M.at(u).at(v) = weight;
		M.at(v).at(u) = weight;
		num_edges++;
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
		int list_len = 0;
		NWPair* list;
		for (int i = 0; i < M[u].size(); i++){
				if(M.at(u).at(i) != 0){
					list = &NWPair(i, M.at(u).at(i));
					list++;
					list_len++;
				}
		}
		for (int i = 0; i < list_len; i++){
			neighbors.push_back(list[i]);
		}
		return neighbors;
	}
}

unsigned MatrixGraph::size() const
{
	return M.size();
}

unsigned MatrixGraph::numEdges() const
{
	return num_edges;	
}
