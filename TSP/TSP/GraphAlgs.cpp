#include "GraphAlgs.h"
#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <math.h>

std::pair<std::vector<NodeID>, EdgeWeight> TSP(Graph* G){
	int num_nodes = G->size();
	int* nodes = new int[num_nodes];
	int* shortest_trip = new int[num_nodes];
	double tmp_len, shortest_len;
	tmp_len = 0.0;
	shortest_len = 0.0;
	for (int i = 0; i < num_nodes; i++){
		nodes[i] = i;
	}
	std::vector<NodeID> best_path = std::vector<NodeID>(num_nodes);
	//Find the length of the current nodes array arrangement.
	do{
		for(int i = 0; i < num_nodes-1; i++){
			tmp_len += G->weight(nodes[i],nodes[i+1]);
			if (tmp_len > shortest_len && shortest_len != 0){
				break;
			}
		}
		//If we have a new minimum (not on the first try), then copy it as such and load up the list
		if (tmp_len < shortest_len || shortest_len == 0){
			shortest_len = tmp_len;
			std::copy(nodes,nodes+num_nodes,shortest_trip);
		}
		//Permute that array.
	} while(std::next_permutation(nodes,nodes+num_nodes));
	for (int j = 0; j < num_nodes; j++)
		best_path.at(j) = shortest_trip[j];
	return std::pair<std::vector<NodeID>,EdgeWeight>(best_path,shortest_len);
}