#include "ListGraph.h"

ListGraph::ListGraph(int numNodes){
	num_edges = 0;
	edgeList = std::vector<EList>();
	for (int i = 0; i < numNodes; i++){
		edgeList.push_back(EList(NULL));
	}	
}

ListGraph::~ListGraph(){
	//delete &edgeList;
}


//TODO I think this method risks duplicates. Will need to deal with that.
void ListGraph::addEdge(NodeID u, NodeID v, EdgeWeight weight){
	bool duplicate_exists = false;
	//Validity check--No empty weight, self-referencing nodes. Nodes must be non-negative. They must fit within the bounds.
	if (weight > 0 && u != v && u >= 0 && u < edgeList.size() && v >= 0 && v < edgeList.size()){
		//Validity check--No duplicates. Because of the symmetric relationship 
		//of directed graphs, we should only have to test u, and not both u and v.
		//Code for list iterator modified from http://www.cplusplus.com/forum/general/22957/
		//TODO This would count as sorted--binary search might speed it up
		for(std::list<NWPair>::const_iterator iterator = edgeList.at(u).begin(), end = edgeList.at(u).end(); iterator != end; ++iterator){
			if(iterator->first == v && iterator->second == weight){
				duplicate_exists = true;
			}
		}
		if (!duplicate_exists){
			edgeList.at(u).push_back(NWPair(v,weight));
			edgeList.at(v).push_back(NWPair(u,weight));
			num_edges++;
		}
	}
}
 
EdgeWeight ListGraph::weight(NodeID u, NodeID v) const{
	if (u >= 0 && u < edgeList.size() && v >= 0 && v < edgeList.size()){
		//Code for list iterator modified from http://www.cplusplus.com/forum/general/22957/
		for(std::list<NWPair>::const_iterator iterator = edgeList.at(u).begin(), end = edgeList.at(u).end(); iterator != end; ++iterator){
			if(iterator->first == v){
				return iterator->second;
			}
		}
	}
	return 0;
}

std::list<NWPair> ListGraph::getAdj(NodeID u) const{
	//Validity checks
	if (u >= 0 && u < edgeList.size()){
			return edgeList.at(u);
		}
}

unsigned ListGraph::degree(NodeID u) const{
	if (u >= 0 && u < edgeList.size()){
		return getAdj(u).size();
	}
	else
		return 0;
}

unsigned ListGraph::size() const{
	//TODO what should the size do? Count the number of nodes? Count the number of existing pairs?
	return edgeList.size();
}

unsigned ListGraph::numEdges() const{
	return num_edges;
}