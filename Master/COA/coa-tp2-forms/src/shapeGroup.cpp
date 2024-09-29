#include "shapeGroup.hpp"


ShapeGroup::ShapeGroup(){

}

ShapeGroup::~ShapeGroup(){
	for(long i = sel_shapes.size() - 1; i >= 0; i--){
		Shape *selected = sel_shapes.at(i);
		if (selected != nullptr) {
			remove(selected);		
		}
	}
}

void ShapeGroup::move(int x, int y){
	for(long i = sel_shapes.size() - 1; i >= 0; i--){
		Shape *selected = sel_shapes.at(i);
		if (selected != nullptr) {
			selected->move(x,y);		
		}
	}
}


void ShapeGroup::add(Shape *s){
	sel_shapes.push_back(s);
}

void ShapeGroup::remove(Shape *s){
	auto it = find(sel_shapes.begin(), sel_shapes.end(), s);

		if (it != sel_shapes.end()) { // if found
			sel_shapes.erase(it);
		}      
}

bool ShapeGroup::is_in_group(Shape *s){
	auto it = find(sel_shapes.begin(), sel_shapes.end(), s);
	if (it != sel_shapes.end()) { // if found
		return true;	
	}else{
		return false;
	}
}
