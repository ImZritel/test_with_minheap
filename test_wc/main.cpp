#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>

#include "testing.h"

/* Represents one given entry.*/
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
std::ostream& operator<<(std::ostream& output, const Entry& e) {
	output << "{"s << e.k << ", "s << e.v << "}"s << std::endl;
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
			std::swap(_data[i], _data[min]);
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
std::istream& operator>>(std::istream& input, Entry& e) {
	input >> e.k >> e.v;
	return input;
}

std::vector<int> GetXMax(int X) {
	Entry* earr = new Entry[X];
	MinHeap mh(earr, X);
	Entry tmp;
	bool isFull = false;
	while (std::cin >> tmp)
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
	
	// Forming output array of keys.
	std::vector<int> karr;
	karr.reserve(mh.get_size());
	for (auto node : mh) {
		karr.push_back(node.k);
	}
	return karr;
}

// if X > number of given lines, we are not printing default objs
std::vector<int> GetXMax(int X, std::string fpath) {
	std::ifstream infile(fpath);
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

	// Forming output vector of keys.
	std::vector<int> karr;
	karr.reserve(mh.get_size());
	for (auto node : mh) {
		karr.push_back(node.k);
	}
	return karr;
}


#define TEST_RESULT(res, X, p) TestResult((res), (X), (p), #res, #p, __FILE__, __FUNCTION__, __LINE__, ""s)

// Reads X and file path or stream data, runs the logic, prints output in std::cin.
void ReadRunPrint() {
	// Read parameters.
	int X;
	std::cout << "Please enter the required number of entries(X): "s;
	std::cin >> X;
	//cout << endl;
	char FileInputYN;
	std::cout << "Read data from file? (Y/N): "s;
	std::cin >> FileInputYN;
	//cout << endl;

	// Run logic.
	std::vector<int> result;
	result.reserve(X);
	if (FileInputYN == 'Y' || FileInputYN == 'y') {
		std::cout << "Please enter the file path: "s;
		std::string fPath = ""s;
		std::cin >> fPath;
		std::cout << std::endl;
		result = GetXMax(X, fPath);
	}
	else if (FileInputYN == 'N' || FileInputYN == 'n') {
		std::cout << "Please enter the data: "s << std::endl;
		result = GetXMax(X);
	}

	// Print result (if any).
	if (!result.empty()) {
		for (int i = 0; i < X; ++i) {
			std::cout << result[i] << "\n"s;
		}
		std::cout << std::flush;
	}
}

int main() {
	// Some relevant values occur twice.
	std::set<int> p0{ 1000000005, 1000000006, 1000000007, 1000000008, 1000000009 };
	TEST_RESULT(GetXMax(4, "test0.txt"s), 4, p0);

	// X > number of entries.
	std::set<int> p1{ 1000000000, 1000000001, 1000000002, 1000000003, 1000000004 };
	TEST_RESULT(GetXMax(10, "test1.txt"s), 10, p1);

	// X < number of entries having maximum value.
	std::set<int> p2{ 1000000004, 1000000005, 1000000006, 1000000007, 1000000008, 1000000009 };
	TEST_RESULT(GetXMax(3, "test2.txt"s), 4, p2);

	ReadRunPrint();
}