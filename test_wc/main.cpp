#include <iostream>
#include <fstream>
#include <string>

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

struct Entry {
	int k;
	int v;

	Entry() = default;
	Entry(int key, int value) : k(key), v(value) {};

	bool operator<(Entry rhs) {
		if (v < rhs.v) {
			return true;
		}
		return false;
	}

	bool operator>(Entry rhs) {
		if (v > rhs.v) {
			return true;
		}
		return false;
	}
};

/*Print Entry obj to cout*/
ostream& operator<<(ostream& output, const Entry& e) {
	output << "{" << e.k << ", " << e.v << "}" << endl;
	return output;
}

// create Entity in heap memory and then move it to tree structure

// probably better to use uint in some places  

/*MinHeap data structure.
Interface: 
get_min() - return the root element;
add(T target_value) - in what place in tree?
heapify()
change_root(T target_value)
begin()
end()
*/
template <typename T>
class MinHeap {
private:
	T* _data;
	int _size;
	int _capacity;
public:
	MinHeap() = default;
	MinHeap(T a[], int capacity) : 
		_capacity(capacity), _size(0)
	{
		_data = a;
	};	
	~MinHeap() {
		delete _data;
	}

	// ¬озвращает итератор на начало массива
	// ƒл€ пустого массива может быть равен (или не равен) nullptr
	T* begin() noexcept {
		return _data;
	}
	// ¬озвращает итератор на элемент, следующий за последним
	// ƒл€ пустого массива может быть равен (или не равен) nullptr
	T* end() noexcept {
		return _data + _size;
	}

	// Return the minimum (root)
	T get_root() const {
		return *_data;
	}
	void set_root(T el) {
		_data[0] = el;
	}
	int get_size() const {
		return _size;
	}
	void incr_size() {
		++_size;
	}

	// Adjust the subtree with root in i index to meet the definition of a MinHeap.
	void heapify(int i) {
		int min = i;
		int left = 2 * i + 1;
		int right = 2 * i + 2;
		if (left < _size && _data[min] > _data[left]) {
			min = left;
		}
		if (right < _size && _data[min] > _data[right]) {
			min = right;
		}
		if (min != i) {
			swap(_data[i], _data[min]);
			heapify(min);
		}
	}

	// Build min heap on current data.
	void build_heap() {
		for (int i = _size / 2; i >= 0; --i) {
			this->heapify(i);
		}
	}
};

// Get Entry from cin
ifstream& operator>>(ifstream& input, Entry& e) {
	input >> e.k >> e.v;
	return input;
}

/*
Entry* GetXMax(int X) {
	
}
*/

// if X > number of given lines, we are not printing default objs
int* GetXMax(int X, string fpath) {
	ifstream infile(fpath);
	Entry* earr = new Entry[X];
	MinHeap mh(earr, X);
	Entry tmp;
	bool isFull = false;
	while (infile >> tmp)
	{
		if (mh.get_size() < X) {
			earr[mh.get_size()] = tmp;
			mh.incr_size();
		}
		else if (!isFull) {
			mh.build_heap();
			if (tmp > mh.get_root()) {
				mh.set_root(tmp);
			}
			mh.heapify(0);
			isFull = true;
		}
		else if (tmp > mh.get_root()) {
			mh.set_root(tmp);
			mh.heapify(0);
		}
	}

	int* karr = new int[mh.get_size()];
	int i = 0;
	// Forming output array of keys.
	for (auto node : mh) {
		karr[i] = node.k;
		++i;
	}
	return karr;
}

// when printing try to use flush
int main() {
	int X;
	cout << "Please enter the required number of entries(X): "s;
	cin >> X;
	cout << endl;
	int* result = GetXMax(X, "D:\\fun\\Interviews\\tests\\wc\\test0.txt"s);

	for (int i = 0; i < X; ++i) {
		cout << result[i] << endl;
	}
}