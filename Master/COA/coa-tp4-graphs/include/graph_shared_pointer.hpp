#ifndef __GRAPH_TEMP_HPP__
#define __GRAPH_TEMP_HPP__

#include <exception>
#include <map>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
#include <memory>
#include <decorator.hpp>

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

template<class ND, class ED>
class Graph {
    struct Node {
        int node_id;
		std::shared_ptr<ND> data;
    };
    struct Edge {
        int edge_id;
		std::shared_ptr<ED> data;
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

	Graph deep_copy() const{
        Graph<ND, ED> copied_graph;

        if constexpr (std::is_polymorphic<ND>::value) {
            for (const auto& node : nodes) {
                copied_graph.add_node(*node.data->clone());
            }
        } else {
            copied_graph.nodes = nodes;
        }

        if constexpr (std::is_polymorphic<ED>::value) {
            for (const auto& edge : edges) {
                copied_graph.add_edge(*edge.data->clone(), edge.source_id, edge.dest_id);
            }
        } else {
            copied_graph.edges = edges;
        }

        return copied_graph;
	}

    inline int add_node(const ND &m)
	{
		Graph::Node node;
		node.node_id = id_counter;
		node.data = std::make_shared<ND>(m);
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

    inline int add_edge(const ED &m, int source_id, int dest_id)
{
    Graph::Edge edge;
    edge.edge_id = edge_counter;
    edge.data = std::make_shared<ED>(m);
    edge.dest_id = dest_id;
    edge.source_id = source_id;
    edges.emplace(edge_counter, edge); 
    if (dests.find(source_id) == dests.end()) {
        std::vector<int> vector;
        dests.emplace(source_id, vector);
    }
    dests.at(source_id).push_back(dest_id);

    return edge_counter++;
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
    
    std::shared_ptr<ND> get_node_data(int node_id) const {
		typename std::map<int, Node>::const_iterator nodes_it;
		for (nodes_it = nodes.begin(); nodes_it != nodes.end(); nodes_it++) {
			if(nodes_it->first == node_id){
				return nodes_it->second.data;
			}	
		}
		return nullptr;
	}

    std::shared_ptr<ED> get_edge_data(int edge_id) const { 
		typename std::map<int, Edge>::const_iterator edges_it;
		for (edges_it = edges.begin(); edges_it != edges.end(); edges_it++) {
			if(edges_it->first == edge_id){
				return edges_it->second.data;
			}	
		}
		return nullptr;
	}

    inline int get_edge_source(int edge_id) const { 
		typename std::map<int, Edge>::const_iterator edges_it;
		for (edges_it = edges.begin(); edges_it != edges.end(); edges_it++) {
			if(edges_it->first == edge_id){
				return edges_it->second.source_id;
			}	
		}
		 return -1;
	}
    
    inline int get_edge_dest(int edge_id) const { 
		typename std::map<int, Edge>::const_iterator edges_it;
		for (edges_it = edges.begin(); edges_it != edges.end(); edges_it++) {
			if(edges_it->first == edge_id){
				return edges_it->second.dest_id;
			}	
		}
		 return -1;
	}

    std::vector<int> get_successors(int node_id) const { 
		typename std::map<int, Edge>::const_iterator edges_it;
		std::vector<int> vector;
		for (edges_it = edges.begin(); edges_it != edges.end(); edges_it++) {
			if(edges_it->second.source_id == node_id) vector.push_back(edges_it->second.dest_id);
		}
		return vector;
	}
    
    std::vector<int> get_predecessors(int node_id) const { 
		typename std::map<int, Edge>::const_iterator edges_it;
		std::vector<int> vector;
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
		
		std::vector<int> succesors = get_successors(from);
		for(auto successors_it = succesors.begin(); successors_it != succesors.end(); successors_it++){
			auto tmp = all_paths(*successors_it,to);
			for(auto paths_it = tmp.begin(); paths_it != tmp.end(); paths_it++){
				paths_it->insert(paths_it->begin(), from);
			}
			std::copy(tmp.begin(), tmp.end(), std::back_inserter(paths));
		}
		return paths;
	}

template<typename Func>
Path shortest_path(int from, int to, Func metricFunction) const {
    std::vector<bool> visited(this->nodes.size(), false);
    std::vector<int> dist(this->nodes.size(), std::numeric_limits<int>::max());
    std::vector<int> prev(this->nodes.size(), -1);

    std::queue<int> q;
    q.push(from);
    visited[from] = true;
    dist[from] = 0;

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        if (node == to) {
            break;
        }

        for (const auto& edge_pair : this->edges) {
            const auto& edge = edge_pair.second;
            if (edge.source_id == node && !visited[edge.dest_id]) {
                int dest = edge.dest_id;
                int weight = metricFunction(*(edge.data), *(get_edge_data(edge_pair.first)));
                if (dist[node] + weight < dist[dest]) {
                    dist[dest] = dist[node] + weight;
                    prev[dest] = node;
                    q.push(dest);
                    visited[dest] = true;
                }
            }
        }
    }

    Path path;
    for (int at = to; at != -1; at = prev[at]) {
        path.push_back(at);
    }
    std::reverse(path.begin(), path.end());
    return path;
}


};




#endif
