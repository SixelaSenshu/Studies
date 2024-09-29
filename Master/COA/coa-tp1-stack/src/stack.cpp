#include <stack.h>

Stack::Stack()
{
    this->s = new int[1000];
	this->capacity = 1000;
	this->count = 0;  
}

Stack::Stack(const Stack &other)
{
    this->s = new int[other.capacity];
	this->capacity = other.capacity;
	this->count = other.count;
	for(int i = 0; i < other.count; i++){
		this->s[i] = other.s[i];
	}
}

Stack::~Stack()
{
    delete[] s;
}
    
int* Stack::getStack() const{
	return this->s;
}

bool Stack::isEmpty() const
{
	if (this->count == 0)
		return true;
    return false;
}

int Stack::top() const 
{
	if(this->count == 0)
    	throw EmptyExc{};
	int value = this->s[this->count - 1];
    return value;
}

void Stack::pop()
{

    if(!this->isEmpty()){
		this->s[this->count - 1] = 0;
		this->count--;
	}
}

void Stack::push(int elem)
{
    if(this->count <= capacity){
		this->s[this->count] = elem;
		this->count++;
	}
}

void Stack::clear()
{
    for(int i = 0; i < this->count; i++){
		this->s[i] = 0;
	}
	this->count = 0;
}

bool Stack::operator==(const Stack &other) const
{
	if(this->count != other.count)
		return false;
	int * other_stack = other.getStack();
	int * current_stack = this->getStack();
	for(int i = 0; i < other.size(); i++){
		if(other_stack[i] != current_stack[i])
			return false;
	}
	return true;
}

Stack &Stack::operator=(const Stack &other)
{
	if (this != &other) { 
            this->count = other.size();
            capacity = other.capacity;
            this->s = new int[capacity];
            for (int i = 0; i < this->size(); ++i) {
                this->s[i] = other.s[i];
            }
        }
        return *this; 
}

Stack &Stack::operator+=(int elem){
	int size = this->size();
	if (size < capacity) {
		this->s[size++] = elem; 
	} else {
		int newCapacity = (capacity == 0) ? 1 : capacity * 2; 
		int* newData = new int[newCapacity]; 
		for (int i = 0; i < size; ++i) {
			newData[i] = this->s[i]; 
		}
		delete[] this->s; 
		this->s = newData; 
		capacity = newCapacity; 
		this->s[size++] = elem; 
	}
	return *this;

}

void Stack::reduce() {
		int size = this->size();
		if (size < capacity) {
        int* newData = new int[size]; 
        for (int i = 0; i < size; ++i) {
            newData[i] = this->s[i]; 
        }
        delete[] this->s;
        this->s = newData;
        capacity = size; 
    }
    }

std::ostream &operator<<(std::ostream &os, const Stack &stack)
{
	int * s = stack.getStack();
	os << "Stack: [";
	for(int i = 0; i < stack.size(); i++){
		if(i == stack.size() - 1)
			os << s[i];
		else	
			os << s[i] << ",";
	}
	os << "]" << std::endl;
	return os;
}

int Stack::size() const
{
    return this->count;
}

int Stack::maxsize() const
{
    return this->capacity;
}

