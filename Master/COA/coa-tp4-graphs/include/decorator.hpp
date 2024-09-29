#ifndef __DECORATOR_HPP_
#define __DECORATOR_HPP_

#include <vector>
#include <string>

template<typename ...Tp>
class EdgeData : public Tp ...{
	std::string str;
public:
	void set_string(const std::string &s){str = s;}
	std::string get_string() const {return str;}
};

class RouteLenght{
	double l;
public:
	void set_length(double len){l = len;}
	double get_lenght() const {return l;}
};

class AverageTime{
	uint64_t time;
public:
	void set_time(uint64_t new_time){time = new_time;}
	uint64_t get_time() const {return time;}
};


bool compare_average(const EdgeData<AverageTime>& edge1, const EdgeData<AverageTime>& edge2) {
    return edge1.get_time() < edge2.get_time();
}

bool compare_length(const EdgeData<RouteLenght>& edge1, const EdgeData<RouteLenght>& edge2) {
    return edge1.get_lenght() < edge2.get_lenght();
}

#endif 