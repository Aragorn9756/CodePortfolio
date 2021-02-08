#include <iostream>
#include <string>
#include <memory>

using std::shared_ptr;
using std::make_shared;

using std::cin;
using std::cout;
using std::endl;
using std::string;

//structs are common to communicate that this data structure 
//ONLY has data members
template <typename T>
struct Node {
	~Node() { cout << "Node destructor invoked!" << endl; }
	T data{};
	//The shared_ptr template keeps track of how many things are pointing to an object and
	//deletes it when no more things are pointing to it. That means no deletes are necessary,
	//only make sure you have nothing pointing to the object and it will delete itself.
	shared_ptr< Node<T> > forward;
	shared_ptr< Node<T> > backward;
};

template <typename T>
class DoublyLinkedList {
public:
	~DoublyLinkedList();
	void insertLast(const T& item);
	void insertFirst(const T& item);
	void deleteFirst();
	void deleteLast();

	unsigned int size() const { return count; }

private:
	shared_ptr< Node<T> > first;
	shared_ptr< Node<T> > last;
	unsigned int count{ 0 };
};

template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
	//while (first != nullptr) {
	//	Node<T> * temp = first;
	//	first = first->link;
	//	delete temp;
	//}
}

template <typename T>
void DoublyLinkedList<T>::insertLast(const T& item) {


	if (!first) {
		//Scenario #1 - The list is empty
		first = make_shared< Node<T> >();
		first->data = item;
		last = first;
	}
	else {
		//Scenario #2 - The list has at least one item
		shared_ptr< Node<T> > tempPtr = make_shared< Node<T> >();
		tempPtr->data = item;
		last->forward = tempPtr;
		tempPtr->backward = last;
		last = tempPtr;
	}
	count++;
}
template <typename T>
void DoublyLinkedList<T>::insertFirst(const T& item) {
	if (!first) {
		//Scenario #1 The list is empty
		first = make_shared< Node<T> >();
		first->data = item;
		last = first;
	}
	else {
		//Scenario #2 The list has at least one item in it
		shared_ptr< Node<T> > tempPtr = make_shared< Node<T> >();
		tempPtr->data = item;
		tempPtr->forward = first;
		first->backward = tempPtr;
		first = tempPtr;
	}
	count++;
}

template <typename T>
void DoublyLinkedList<T>::deleteFirst() {

	//Empty list 
	if (!first) {
		cout << "List is already empty" << endl;
		return;
	}

	//Scenario 1 or more nodes
	first = first->forward;

	if (!first) {
		//Must have been only 1 node in the list
		last.reset();
	}
	else {
		//first->backward = nullptr;
		first->backward.reset();
	}

	count--;

}

template <typename T>
void DoublyLinkedList<T>::deleteLast() {

	if (!first) {
		//empty list scenario
		cout << "The list is empty" << endl;

	}
	else {
		last = last->backward;
		if (!last) {
			//1 node scenario
			first.reset();
		}
		else {
			//2 or more node scenario
			last->forward.reset();
		}
		count--;
	}
}

int main() {

	DoublyLinkedList<string> myList;
	myList.insertLast("Snowball");
	myList.insertLast("Sauron");
	myList.insertLast("Waffles");
	myList.insertLast("Corgi");

	myList.deleteFirst();
	myList.deleteFirst();
	myList.deleteFirst();
	myList.deleteFirst();
	myList.deleteFirst();

	cin.get();
	return 0;
}
