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
	T* _dataptr;
	int _size;
	int _capacity;
public:
	MinHeap() = default;
	MinHeap(T a[], int capacity) : 
		_capacity(capacity), _size(0)
	{
		_dataptr = a;
	};
	// is destructor needed?
	/*
	~MinHeap() {
		delete _dataptr;
	}
	*/

	// Return the minimum (root)
	T get_min() const {
		return *_dataptr;
	}

	int get_size() const {
		return _size;
	}

	void incr_size() {
		++_size;
	}

	void set_root(T el) {
		_dataptr[0] = el;
	}

	// Adjust the subtree with root in i index to meet the definition of a MinHeap
	void heapify(int i) {
		int min = i;
		int left = 2 * i + 1;
		int right = 2 * i + 2;
		if (left < _size && _dataptr[min] > _dataptr[left]) {
			min = left;
		}
		if (right < _size && _dataptr[min] > _dataptr[right]) {
			min = right;
		}

		if (min != i) {
			swap(_dataptr[i], _dataptr[min]);
			heapify(min);
		}
	}

	// Build min heap on current data.
	void build_heap() {
		for (int i = _size / 2; i >= 0; --i) {
			this->heapify(i);
		}
	}

	//use make_heap??? - no, it creates MinHeap based on two given iterators. We have a stream and not a container.
	
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
void PrintXMax(int X, string fpath) {
	ifstream infile(fpath);
	Entry* earr = new Entry[X];
	MinHeap mh(earr, X);
	Entry tmp;
	bool isFull = false;
	while (infile >> tmp)
	{
		if (mh.get_size() < X) {
			earr[mh.get_size()] = tmp;
			// increase size somehow
			mh.incr_size();

			cout << "tmp = " << tmp << endl;
			for (int i = 0; i < X; ++i) {
				cout << "earr[" << i << "] = " << earr[i] << endl;
			}
		}
		else if (!isFull) {
			mh.build_heap();
			if (tmp > mh.get_min()) {
				mh.set_root(tmp);
			}
			mh.heapify(0);
			isFull = true;

			cout << "tmp = " << tmp << endl;
			for (int i = 0; i < X; ++i) {
				cout << "earr[" << i << "] = " << earr[i] << endl;
			}
		}
		else if (tmp > mh.get_min()) {
			mh.set_root(tmp);
			mh.heapify(0);

			cout << "tmp = " << tmp << endl;
			for (int i = 0; i < X; ++i) {
				cout << "earr[" << i << "] = " << earr[i] << endl;
			}
		}
	}
	for (int i = 0; i < mh.get_size(); ++i) {
		cout << earr[i] << endl;
	}
}

// when printing try to use flush
int main() {
	Entry* ptr = nullptr;
	{
		int z = 100500;
		Entry* a = new Entry[1000];
		ptr = a;
		MinHeap mh(a, 1000);
		cout << a[0] << endl;
		cout << a[999] << endl;
	}

	cout << ptr << endl;
	cout << ptr[999] << endl;

	PrintXMax(15, "D:\\fun\\Interviews\\tests\\wc\\test2.txt"s);
}