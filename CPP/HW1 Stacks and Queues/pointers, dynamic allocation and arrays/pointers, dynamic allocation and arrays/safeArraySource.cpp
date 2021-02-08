#include <iostream>

using std::cout;
using std::cin;
using std::endl;

template <typename T>//template command
class SafeArray {
public:
	SafeArray(const unsigned int size);
	~SafeArray();//destructor
	void insert(const unsigned int index, const T& item);
	T get(const unsigned int index) const;//means the method is constant, can't change data members
	unsigned int capacity() const { return capacity; }
private:
	T * arr{ nullptr };//arr initialized to null and size initialized to int.
						 //negates the need for a default constructor
	unsigned int capacity{ 0 };//unsigned forces ints to all positives
};

template <typename T>
SafeArray<T>::SafeArray(const unsigned int size) {
	this->capacity = size;
	arr = new T[capacity];
}

template <typename T>
SafeArray<T>::~SafeArray() {
	delete[] arr;
}

template <typename T>
void SafeArray<T>::insert(const unsigned int index, const T& item) {
	if (index >= capacity) {//negatives are turned into high positives thanks to twos complement and trip the test
		cout << "Index " << index << " is out of bounds." << endl;
		return;
	}
	arr[index] = item;
}

template <typename T>
T SafeArray<T>::get(const unsigned int index) const {
	if (index >= capacity) {//negatives are turned into high positives thanks to twos complement and trip the test
		cout << "Index " << index << " is out of bounds." << endl;
		throw 1;
	}
	return arr[index];
}

int main() {

	SafeArray<int> myArr(100);//<int> specifies which template to use. in this case, T will be replaced with int
	myArr.insert(0, 42);
	myArr.insert(1, 55);
	myArr.insert(-1, 666);
	myArr.insert(100, 666);
	cout << "the data at index 1 is " << myArr.get(1) << endl;
	try {
		cout << "the data at index 666 is " << myArr.get(666) << endl;
	}
	catch (int error) {
		cout << "Caught an error!";
	}
	cout << "The array has this many items: " << myArr.capacity() << endl;

	cin.get();
	return 0;
}