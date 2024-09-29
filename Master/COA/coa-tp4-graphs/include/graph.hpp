#ifndef __GRAPH_HPP__
#define __GRAPH_HPP__

#include <exception>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

// Searches an element in the container, if it exists, it is removed
template<class C, class E>
void find_remove(C &cont, E elem)
{
    auto pos = cont.find(elem);
    if (pos != end(cont))
        cont.erase(pos);
}

// Exception : wrong node identifier
class NodeNotFound {
    const int id;
public:
    NodeNotFound(int node_id) : id(node_id) {}
    std::string msg() const {
        std::string m = "Node " + std::to_string(id) + " not found";
        return m;
    }
};

// Exception : wrong node identifier 
class EdgeNotFound {
    const int id;
public:
    EdgeNotFound(int edge_id) : id(edge_id) {}
    std::string msg() const {
        std::string m = "Edge " + std::to_string(id) + " not found";
        return m;
    }
};

class Graph {
    struct Node {
        int node_id;
        std::string data;
    };
    struct Edge {
        int edge_id;
        std::string data;
        int source_id;
        int dest_id;
    };

    /* data structures */
    std::map<int, Node> nodes;
    std::map<int, Edge> edges;
    std::map<int, std::vector<int>> dests;
    int id_counter;
    int edge_counter;

public:

    Graph() {
		this->nodes = std::map<int, Node>();
		this->edges = std::map<int, Edge>();
		this->dests = std::map<int, std::vector<int>>();
		this->id_counter = 0;
		this->edge_counter = 0;
	}

    Graph(const Graph &other) {
		this->nodes = other.nodes;
		this->edges = other.edges;
		this->dests = other.dests;
		this->id_counter = other.id_counter;
		this->edge_counter = other.edge_counter;
	}

    inline int add_node(const std::string &m)
	{
		Graph::Node node;
		node.node_id = id_counter;
		node.data = m;
		nodes.emplace(id_counter,node);
		if(node_exist(id_counter))
		{
			return id_counter++;
		}
		else
		{
			return -1; 
		}
	}

    inline bool node_exist(int id) const 
	{ 
		if(this->nodes.find(id) != this->nodes.end()) 
		{
			return true;
		}
		return false;
	}

    inline int add_edge(const std::string &m, int source_id, int dest_id)
	{
    Graph::Edge edge;
    edge.data = m;
    edge.dest_id = dest_id;
    edge.source_id = source_id;
    edge.edge_id = edge_counter;
    edges[edge_counter] = edge;
    if (node_exist(edge_counter))
    {
        if (dests.find(source_id) == dests.end()) {
            dests[source_id] = std::vector<int>(); 
        }
        dests[source_id].push_back(dest_id);
        return edge_counter++;
    }
	else{
    	return -1;
	}
}

    
    inline void remove_node(int node_id) 
	{
		if (node_exist(node_id)) {
        	find_remove(nodes, node_id);
    	}
	}

    inline int search_node(const std::string &m) const 
	{ 
		for(unsigned int i = 0; i < nodes.size(); i++)
		{
			if(nodes.at(i).data == m)
			{
				return nodes.at(i).node_id;
			}
		}
		return 0;
	}
    
    inline std::string get_node_data(int node_id) const {
		std::map<int, Node>::const_iterator nodes_it;
		for (nodes_it = nodes.begin(); nodes_it != nodes.end(); nodes_it++) {
			if(nodes_it->first == node_id){
				return nodes_it->second.data;
			}	
		}
		throw NodeNotFound(node_id);
	}

    inline std::string get_edge_data(int edge_id) const { 
		std::map<int, Edge>::const_iterator edges_it;
		for (edges_it = edges.begin(); edges_it != edges.end(); edges_it++) {
			if(edges_it->first == edge_id){
				return edges_it->second.data;
			}	
		}
		throw EdgeNotFound(edge_id);
	}

    inline int get_edge_source(int edge_id) const { 
		std::map<int, Edge>::const_iterator edges_it;
		for (edges_it = edges.begin(); edges_it != edges.end(); edges_it++) {
			if(edges_it->first == edge_id){
				return edges_it->second.source_id;
			}	
		}
		 return -1;
	}
    
    inline int get_edge_dest(int edge_id) const { 
		std::map<int, Edge>::const_iterator edges_it;
		for (edges_it = edges.begin(); edges_it != edges.end(); edges_it++) {
			if(edges_it->first == edge_id){
				return edges_it->second.dest_id;
			}	
		}
		 return -1;
	}

    std::vector<int> get_successors(int node_id) const { 
		std::vector<int> vector;
		std::map<int, Edge>::const_iterator edges_it;
		for (edges_it = edges.begin(); edges_it != edges.end(); edges_it++) {
			if(edges_it->second.source_id == node_id) vector.push_back(edges_it->second.dest_id);
		}
		return vector;
	}
    
    std::vector<int> get_predecessors(int node_id) const { 
		std::vector<int> vector;
		std::map<int, Edge>::const_iterator edges_it;
		for (edges_it = edges.begin(); edges_it != edges.end(); edges_it++) {
			if(edges_it->second.dest_id == node_id) vector.push_back(edges_it->second.source_id);
		}
		return vector;
	}

    using Path=std::vector<int>;



    std::vector<Path> all_paths(int from, int to) const
    {
		std::vector<Path> paths;
		std::vector<Path> tmp;
		Path path;
		
		if(from == to){
			path = Path();
			path.push_back(to);
			paths.push_back(path);
			return paths;
		}
		
		auto succesors = get_successors(from);
		std::cout << std::endl;
		for(auto successors_it = succesors.begin(); successors_it != succesors.end(); successors_it++){
			tmp = all_paths(*successors_it,to);
			for(auto paths_it = tmp.begin(); paths_it != tmp.end(); paths_it++){
				paths_it->insert(paths_it->begin(), from);
			}
			std::copy(tmp.begin(), tmp.end(), std::back_inserter(paths));
		}
		return paths;
	}


Path shortest_path(int from, int to) const {
    std::vector<int> queue;
    std::vector<int> visited(edges.size(), 0);
    std::vector<int> predecessor(edges.size(), -1);

    queue.push_back(from);
    visited[from] = 1;

    while (!queue.empty()) {
        int current = queue.front(); 
        queue.erase(queue.begin());

        if (current == to) {
            Path shortest_path;
            while (current != -1) {
                shortest_path.insert(shortest_path.begin(), current);
                current = predecessor[current];
            }
            return shortest_path;
        }

        std::vector<int> successors = get_successors(current);
        for (auto successor_id : successors) {
            if (!visited[successor_id]) {
                visited[successor_id] = 1;
                predecessor[successor_id] = current;
                queue.push_back(successor_id);
            }
        }
    }

    return {};
}

};


#endif
