#include "stack.h"

#include <iostream>

using namespace std;

int main()
{
    Stack s;

	cout << "Is empty: " << s.isEmpty() << endl;
    s.push(9);
	cout << "Max size is : " << s.maxsize() << endl;
	cout << "Size is : " << s.size() << endl;
	s.push(8);
	cout << "Size is : " << s.size() << endl;
    cout << "Is empty: " << s.isEmpty() << endl;
    cout << s.top() << endl;

	cout << "Create a new stack with the same elements" << endl;
    Stack s2{s};
	Stack s3{s2};

	cout << s2.top() << endl;
	s2.pop();
	cout << s2.top() << endl;
	s2.pop();
	cout << "Is empty: " << s2.isEmpty() << endl;
	cout << s << endl;
	cout << s2 << endl;

	if(s2==s3){
		cout << "S2 equal S3" << endl;
	}else{
		cout << "S2 not equal S3" << endl;
	}
	if(s3==s){
		cout << "S3 equal S" << endl;
	}else{
		cout << "S3 not equal S" << endl;
	}
	if(s==s){
		cout << "S equal S" << endl;
	}else{
		cout << "S not equal S" << endl;
	}

	return 0;
}

