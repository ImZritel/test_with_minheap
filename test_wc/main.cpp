#include <iostream>

/*
We can't use order statistics algorithm (O(N)) by virtue of the assumption that available memory can't contain all input data.

algorithm:
while there is values in stream:
0. read key, value from file stream to new structure Entry. Entry has constructor and operator>.
1. if MinHeap.size() < X || entry > MinHeap[0], add entry and rearrange MinHeap (should I fill all MinHeap object in constructor with nown minimum value?) 
return MinHeap object.

Needed:
MinHeap class (constructor, add(add to the end and rearrange), swap_root(Entity, MinHeap[0])l);
Entry class (constructor, operator>)

ALSO try MinHeap based on array in the stack memory

*/


using namespace std;  //убрать в финальной версии

class Entry {
private:
	int k;
	int v;
public:
	Entry(int key, int value) : k(key), v(value) {};

	bool operator<(Entry rhs) {
		if (v < rhs.v || (v == rhs.v && k < rhs.k)) {    // we have no need in comparing k, because there is no such task
			return true;
		}
		return false;
	}

	bool operator>(Entry rhs) {
		if (v > rhs.v || (v == rhs.v && k > rhs.k)) {
			return true;
		}
		return false;
	}
};

/*MinHeap data structure.
Interface: 
get_min() - return the root element;
add(T target_value) - in what place in tree?
heapify()
change_root(T target_value)
begin()
end()
*/

// create Entity in heap memory and then move it to tree structure

template <typename T>
class MinHeap {
private:
	T* _data;
	int _size;
	int _capacity;
public:
	MinHeap() = default;
	MinHeap(int capacity) : 
		_capacity(capacity), _size(0), _data(new T[capacity]) 
	{};
	// is destructor needed?
	/*
	~MinHeap() {
		delete _data;
	}
	*/

	// Return the minimum
	T get_min() {
		return *_data;
	}

	void heapify() {
		
	}

	//use make_heap??? - no, it creates MinHeap based on two given iterators. We have a stream and not a container.

};

int main() {
	
}