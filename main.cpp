#include <iostream>
#include <algorithm>
#include <memory>
#include <utility>
#include <vector>
#include <list>
#include "MyVector.h"
#include "List.h"
template<class T> using CollectionType = List<T>;
template<typename T>
void print_collection(const CollectionType<T>& rhs) {
	for (auto i = rhs.begin(); i != rhs.end(); ++i) {
		std::cout << *i << " ";
	}
	std::cout << "\n" << std::endl;
}

using namespace std;
int main(){
	CollectionType<int> vec;
	vec.insert(vec.begin(), 5);
	vec.insert(vec.begin(), 4);
	vec.insert(vec.begin(), 3);
	vec.erase(vec.begin()+1);
	print_collection(vec);
	return 0;
}