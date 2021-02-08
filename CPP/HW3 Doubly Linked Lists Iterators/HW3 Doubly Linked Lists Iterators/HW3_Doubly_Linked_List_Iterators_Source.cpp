//Copyright 2017, Bradley Peterson, Weber State University, All rights reserved.

#include <iostream>
#include <map>
#include <algorithm>
#include <list>
#include <vector>
#include <memory>

//To prevent those using g++ from trying to use a library
//they don't have
#ifndef __GNUC__
#include <conio.h>
#else
#include <stdio.h>
#endif

#include <sstream>

template <typename T> class DoublyLinkedList;

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::shared_ptr;
using std::weak_ptr;
using std::make_shared;
using std::stringstream;

//************************************************************************
//A class I designed to help keep track of how much memory you allocate
//Do not modify, this is not part of your assignment, it just helps test it.
//For this to work, a class needs to inherit off of this one. 
//Then this does the rest of the work, since it 
//overloads new, new[], delete, and delete[].
//************************************************************************
class ManageMemory {
public:

	static std::size_t getTotalSize() {
		std::size_t total = 0;
		std::map<void *, std::size_t>::iterator iter;
		for (iter = mapOfAllocations.begin(); iter != mapOfAllocations.end(); ++iter) {
			total += iter->second;
		}
		return total;
	}

	//I overloaded the new and delete keywords so I could manually track allocated memory.
	void* operator new(std::size_t x) {
		void *ptr = ::operator new(x);
		mapOfAllocations[ptr] = x;
		return ptr;
	}
	void* operator new[](std::size_t x) {
		void *ptr = ::operator new[](x);
		mapOfAllocations[ptr] = x;
		return ptr;
	}
		void operator delete(void* x) {
		mapOfAllocations.erase(x);
		::operator delete(x);
	}
	void operator delete[](void* x) {
		mapOfAllocations.erase(x);
		::operator delete[](x);
	}
private:
	static std::map<void *, std::size_t> mapOfAllocations;
};
std::map<void *, std::size_t> ManageMemory::mapOfAllocations;


//******************
//The node class
//******************
template <typename T>
struct Node {
	T data{};
	shared_ptr< Node<T> > forward;
	shared_ptr< Node<T> > backward;
};



//******************
//The Iterator class
//******************	
template <typename T>
class Iterator : public ManageMemory, public std::iterator<std::bidirectional_iterator_tag, T> {
	friend class DoublyLinkedList<T>;
public:
	T& operator*();
	Iterator<T> operator++();// prefix  return *this;
	Iterator<T> operator++(int); //postfix  auto temp = *this;  move the "this"...;   return temp;
	Iterator<T> operator--(); // prefix
	bool operator!=(Iterator<T> that);
	bool operator==(Iterator<T> that);

private:
	weak_ptr< Node<T> > current;
	bool pastTheEnd = false;
};

//***********************************
//The Iterator class methods
//***********************************

template <typename T>
T& Iterator<T>::operator*() {
	auto sharedPtrCopy = current.lock();  //Creates a shared pointer to access data
	return sharedPtrCopy->data;           //Returns the data
}

template <typename T>
bool Iterator<T>::operator!=(Iterator<T> that) {

	//make shared_ptr instances of weak_ptrs
	auto thisShared_ptrCopy = current.lock();
	auto thatShared_ptrCopy = that.current.lock();

	//return inverse of statement evaluation
	return !(this->pastTheEnd == that.pastTheEnd
		&& thisShared_ptrCopy == thatShared_ptrCopy);
}

template <typename T>
bool Iterator<T>::operator==(Iterator<T> that) {

	//make shared_ptr instances of weak_ptrs
	auto thisShared_ptrCopy = current.lock();
	auto thatShared_ptrCopy = that.current.lock();

	//return statement evaluation
	return (this->pastTheEnd == that.pastTheEnd
		&& thisShared_ptrCopy == thatShared_ptrCopy);
}

template <typename T>
Iterator<T> Iterator<T>::operator++() {

	auto shared_ptrCopy = current.lock();

	//make sure there is a list
	auto sharedPtrCopy = current.lock();  //Creates a shared pointer to access data
	if (!sharedPtrCopy) {
		cout << "There is no list." << endl;
		throw 1;
	}
	//check to see if we are already at the end
	//if already at the end
	else if (this->pastTheEnd) {
		cout << "You are already at the end of the list." << endl;
	}
	//if moving past the end
	//see if we're at the end now
	else if (sharedPtrCopy->forward == nullptr) {
		this->pastTheEnd = true;
	}
	//if not past the end
	else {
		sharedPtrCopy = sharedPtrCopy->forward;

		current = sharedPtrCopy;  //Put it back in the weak pointer
	}

	return *this;
}

template <typename T>
Iterator<T> Iterator<T>::operator++(int) {

	//create temp iterator
	Iterator<T> temp = *this;

	//create shared_ptr instance of weak_ptr
	auto shared_ptrCopy = current.lock();

	//make sure there is a list
	if (!shared_ptrCopy) {
		cout << "There is no list." << endl;
		throw 1;
	}
	//check to see if we are already at the end
	//if already at the end
	else if (this->pastTheEnd) {
		cout << "You are already at the end of the list." << endl;
	}
	//see if we're at the end now
	else if (shared_ptrCopy->forward == nullptr) {
		this->pastTheEnd = true;
	}
	//if not past the end
	else {
		shared_ptrCopy = shared_ptrCopy->forward;

		current = shared_ptrCopy;  //Put it back in the weak pointer
	}

	return temp;
}

template <typename T>
Iterator<T> Iterator<T>::operator--() {

	//make shared_ptr instance of weak_ptr
	auto shared_ptrCopy = current.lock();

	//make sure the list is not empty
	if (!shared_ptrCopy) {
		cout << "There is no list." << endl;
		throw 1;
	}
	//make sure we're not at the end
	else if (this->pastTheEnd == true) {
		this->pastTheEnd = false;
	}
	// decrement
	else {
		shared_ptrCopy = shared_ptrCopy->backward;

		current = shared_ptrCopy;
	}

	return *this;
}

//****************************
//The DoublyLinkedList class
//****************************
template <typename T>
class DoublyLinkedList : public ManageMemory {

public:

	//public members of the DoublyLinkedList class
	DoublyLinkedList();
	~DoublyLinkedList();
	string getStringFromList();

	void insertFirst(const T&);
	void insertLast(const T&);
	void deleteFirst();
	void deleteLast();

	Iterator<T> begin();
	Iterator<T> end();

protected:
	shared_ptr< Node<T> > first;
	shared_ptr< Node<T> > last;
	unsigned int count;
};

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList() {
	count = 0;
	first = nullptr;
	last = nullptr;
}

template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
	while (first) {
		first->backward.reset();
		first = first->forward;
	}
	last.reset();
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


//This method helps return a string representation of all nodes in the linked list
template <typename T>
string DoublyLinkedList<T>::getStringFromList() {
	stringstream ss;
	if (first == nullptr) {
		ss << "The list is empty.";
	}
	else {

		Node<T> *currentNode = first;
		ss << currentNode->data;
		currentNode = currentNode->forward;

		while (currentNode != nullptr) {
			ss << " " << currentNode->data;
			currentNode = currentNode->forward;
		}
	}
	return ss.str();
}

//***********************************
//The DoublyLinkedList class methods
//***********************************
template <typename T>
Iterator<T> DoublyLinkedList<T>::begin() {

	//create temp iterator
	Iterator<T> temp;

	//if no list exists
	if (!first) {
		temp.pastTheEnd = true;
	}
	//list exists
	else {
		temp.pastTheEnd = false;
		temp.current = first;
	}

	return temp;
}//end begin() method

template <typename T>
Iterator<T> DoublyLinkedList<T>::end() {

	Iterator<T> temp;

	temp.pastTheEnd = true;

	//if list is NOT empty
	if (first) {
		temp.current = last;
	}

	return temp;

}//end end() method


 
template <typename T>
void ourReverse(T begin, T end) {
	--end;
	//make sure at least 2 items are there
	if (begin == end) {
		cout << "There must be at least 2 items in order to reverse.";
		throw 1;
	}

	T prevBegin; //holds whatever begin was before it was incremented

	do {
		
		prevBegin = begin;
		
		iter_swap(begin, end);  //Swaps the values pointed at by two iterators.  This sure comes in handy....
								
		++begin;
		--end;

	} while (begin != end && prevBegin != end); //we'll know we're at the end when  begin and end are the same, 
												//in the case of an odd number of items, or end arrives at where
												//begin just was, i.e. end and begin pass each other
		
	return;
}


//----------------------------------------------------------------------------------------------------------------------------------------
//This helps with testing, do not modify.
bool checkTest(string testName, string whatItShouldBe, string whatItIs) {

	if (whatItShouldBe == whatItIs) {
		cout << "Passed " << testName << endl;
		return true;
	}
	else {
		cout << "****** Failed test " << testName << " ****** " << endl << "     Output was " << whatItIs << endl << "     Output should have been " << whatItShouldBe << endl;
		return false;
	}
}

//This helps with testing, do not modify.
bool checkTest(string testName, int whatItShouldBe, int whatItIs) {

	if (whatItShouldBe == whatItIs) {
		cout << "Passed " << testName << endl;
		return true;
	}
	else {
		cout << "****** Failed test " << testName << " ****** " << endl << "     Output was " << whatItIs << endl << "     Output should have been " << whatItShouldBe << endl;
		return false;
	}
}

//This helps with testing, do not modify.
bool checkTestMemory(string testName, int whatItShouldBe, int whatItIs) {

	if (whatItShouldBe == whatItIs) {
		cout << "Passed " << testName << endl;
		return true;
	}
	else {
		cout << "***Failed test " << testName << " *** " << endl << "  There are " << whatItIs << " bytes of memory yet to be reclaimed!" << endl;
		return false;
	}
}


//This helps with testing, do not modify.
void testIteratorFundamentals() {

	DoublyLinkedList<int> d;

	//Our test data should have all even numbers from 2 to 20
	for (int i = 2; i <= 20; i += 2) {
		d.insertLast(i);
	}

	//Get an iterator which points at the beginning of the list
	Iterator<int> iter = d.begin();

	//Test the operator* operator
	checkTest("testIteratorFundamentals #1", 2, *iter);

	//Test the ++ prefix increment opreator
	++iter;
	checkTest("testIteratorFundamentals #2", 4, *iter);

	//Test the != operator
	//reset them back to the start
	iter = d.begin();
	Iterator<int> anotherIter = d.begin();
	if (iter != anotherIter) {
		cout << "****** Failed testIteratorFundamentals #3 ****** " << endl << "     The two iteraters held the same data." << endl;
	}
	else {
		cout << "Passed testIteratorFundamentals #3" << endl;
	}

	//Again test the != operator
	++iter;
	if (iter != anotherIter) {
		cout << "Passed testIteratorFundamentals #4" << endl;
	}
	else {
		cout << "****** Failed testIteratorFundamentals #4 ****** " << endl << "     The two iteraters held different data." << endl;
	}

	//Test the ++postfix increment
	iter = d.begin(); //reset it back to the start
	anotherIter = iter++;  //anotherIter should be at the data 2

	checkTest("testIteratorFundamentals #5", 4, *iter);
	checkTest("testIteratorFundamentals #6", 2, *anotherIter);

	cout << "testIteratorFundamentals test #7, this should display 2 4 6 8 10 12 14 16 18 20." << endl;

	for (auto i : d) {
		cout << i << " ";
	}
	cout << endl;

}

//This helps with testing, do not modify.
void testIteratorIncrement() {

	DoublyLinkedList<int> *d = new DoublyLinkedList<int>;

	//Our test data should have all even numbers from 2 to 20
	for (int i = 2; i <= 20; i += 2) {
		d->insertLast(i);
	}

	//Get an iterator which points at the beginning of the list
	Iterator<int> iter = d->begin();

	//Test that it does point to the first
	checkTest("testIteratorsIncrement #1", 2, *iter);

	//Test that our Iterator can move forward;
	++iter;	checkTest("testIteratorsIncrement #2", 4, *iter);


	//Test that our Iterator can move forward again;
	++iter;
	checkTest("testIteratorsIncrement #3", 6, *iter);

	//move it some more
	for (int i = 0; i < 6; i++) {
		++iter;
	}
	checkTest("testIteratorsIncrement #4", 18, *iter);

	//Hit the end
	++iter;
	checkTest("testIteratorsIncrement #5", 20, *iter);

	//Verify we move the iterator past the end without crashing
	++iter;
	checkTest("testIteratorsIncrement #6", "did not crash", "did not crash");


	delete d;
}

//This helps with testing, do not modify.
void testIteratorDecrement() {
	
	DoublyLinkedList<int> *d = new DoublyLinkedList<int>;

	//Our test data should have all even numbers from 2 to 20
	for (int i = 2; i <= 20; i += 2) {
	d->insertLast(i);
	}

	//Get an Iterator which points at the end of the list
	Iterator<int> iter = d->end();
	--iter;  //We have to do a decrement otherwise it crashes

	//Test that it does point to the first
	checkTest("testIteratorsDecrement #1", 20, *iter);

	//Test that our Iterator can move forward;
	--iter;
	checkTest("testIteratorsDecrement #2", 18, *iter);

	//move it some more
	for (int i = 0; i < 7; i++) {
	--iter;
	}
	checkTest("testIteratorsDecrement #3", 4, *iter);

	//Hit the end
	--iter;
	checkTest("testIteratorsDecrement #4", 2, *iter);

	//Now go back forward
	++iter;
	checkTest("testIteratorsDecrement #5", 4, *iter);

	delete d;
	
}

//This helps with testing, do not modify.
void testIterationTricky() {

	DoublyLinkedList<int> myListOneNode;

	myListOneNode.insertLast(42);
	cout << "TestIterationTricky test #1, the next line should display 42" << endl;
	//see if we can just iterator through one item.
	for (auto i : myListOneNode) {
		cout << i << " ";
	}
	cout << endl;

	DoublyLinkedList<int> myListEmpty;
	cout << "TestIterationTricky test #2, the next line shouldn't display anything" << endl;
	//see if we can just iterator through one item.
	for (auto i : myListEmpty) {
		cout << i << " ";
	}
	cout << endl;

}


//This helps with testing, do not modify.
void testAlgorithms() {

	
	DoublyLinkedList<int> myList;

	//Our test data should have all even numbers from 2 to 20
	for (int i = 2; i <= 6; i += 2) {
	myList.insertLast(i);
	}
	myList.insertLast(100);
	for (int i = 8; i <= 12; i += 2) {
	myList.insertLast(i);
	}
	myList.insertLast(100);
	for (int i = 14; i <= 20; i += 2) {
	myList.insertLast(i);
	}

	cout << "testAlgorithms test #1, this should display 2 4 6 100 8 10 12 100 14 16 18 20." << endl;
	for (auto i : myList) {
	cout << i << " ";
	}
	cout << endl;

	//Test the STL reverse algorithm on our iterator
	cout << "testAlgorithms test #2, this should display 20 18 16 14 100 12 10 8 100 6 4 2." << endl;
	reverse(myList.begin(), myList.end());
	for (auto i : myList) {
	cout << i << " ";
	}
	cout << endl;

	//Test our reverse algorithm
	cout << "testAlgorithms test #3, this should display 20 18 16 14 100 12 10 8 100 6 4 2." << endl;
	//Get it back in ascending order using the STL reverse algorithm
	reverse(myList.begin(), myList.end());
	//Now reverse it using our algorithm
	ourReverse(myList.begin(), myList.end());
	for (auto i : myList) {
	cout << i << " ";
	}
	cout << endl;

	//Test our reverse algorithm on an STL vector collection
	vector<int> v;
	for (int i = 2; i <= 20; i += 2) {
	v.push_back(i);
	}
	cout << "testAlgorithms test #4, this should display 20 18 16 14 12 10 8 6 4 2." << endl;
	ourReverse(v.begin(), v.end());
	for (auto i : v) {
	cout << i << " ";
	}
	cout << endl;


	//Now test an odd sized list
	DoublyLinkedList<int> oddList;
	for (int i = 2; i <= 6; i += 2) {
	oddList.insertLast(i);
	}
	oddList.insertLast(100);
	for (int i = 8; i <= 12; i += 2) {
	oddList.insertLast(i);
	}
	oddList.insertLast(100);
	for (int i = 14; i <= 18; i += 2) {
	oddList.insertLast(i);
	}
	cout << "testAlgorithms test #5, this should display 18 16 14 100 12 10 8 100 6 4 2." << endl;
	ourReverse(oddList.begin(), oddList.end());
	for (auto i : oddList) {
	cout << i << " ";
	}
	cout << endl;

	//Delete all of occurrence using an STL algorithm.
	cout << "testAlgorithms test #6, this should display 4 2 5 1 2." << endl;
	DoublyLinkedList<int> manyNines;
	manyNines.insertLast(9);
	manyNines.insertLast(9);
	manyNines.insertLast(4);
	manyNines.insertLast(2);
	manyNines.insertLast(9);
	manyNines.insertLast(9);
	manyNines.insertLast(5);
	manyNines.insertLast(1);
	manyNines.insertLast(9);
	manyNines.insertLast(2);
	manyNines.insertLast(9);
	manyNines.insertLast(9);
	auto beginIter = manyNines.begin();
	auto endIter = manyNines.end();
	endIter = remove(beginIter, endIter, 9);

	while (beginIter != endIter) {
	cout << *beginIter << " ";
	++beginIter;
	}
	cout << endl;
	
}

void pressAnyKeyToContinue() {
	cout << "Press any key to continue...";

	//Linux and Mac users with g++ don't need this
	//But everyone else will see this message.
#ifndef __GNUC__
	_getch();

#else
	int c;
	fflush(stdout);
	do c = getchar(); while ((c != '\n') && (c != EOF));
#endif
	cout << endl;
}

int main() {

	cout << "This first test can run forever until you get operators *, != and ++ implemented." << endl;
	pressAnyKeyToContinue();

	testIteratorFundamentals();
	checkTestMemory("Memory Leak/Allocation Test #1", 0, ManageMemory::getTotalSize());
	pressAnyKeyToContinue();

	testIteratorIncrement();
	checkTestMemory("Memory Leak/Allocation Test #2", 0, ManageMemory::getTotalSize());
	pressAnyKeyToContinue();

	testIteratorDecrement();
	checkTestMemory("Memory Leak/Allocation Test #3", 0, ManageMemory::getTotalSize());
	pressAnyKeyToContinue();

	testIterationTricky();
	checkTestMemory("Memory Leak/Allocation Test #4", 0, ManageMemory::getTotalSize());
	pressAnyKeyToContinue();

	testAlgorithms();
	checkTestMemory("Memory Leak/Allocation Test #5", 0, ManageMemory::getTotalSize());
	pressAnyKeyToContinue();

	return 0;
}