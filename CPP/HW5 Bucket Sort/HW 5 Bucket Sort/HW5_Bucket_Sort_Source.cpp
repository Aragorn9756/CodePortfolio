//Copyright 2017, Bradley Peterson, Weber State University, all rights reserved.

#include <cstdio>
#include <random>
#include <thread> //C++11 support!   Visual studio 2012+ users can use this if they want.
#include <mutex> 
#include <iostream>
#include <vector>
#include <memory>
#include <string>


//To prevent those using g++ from trying to use a library
//they don't have
#ifndef __GNUC__
#include <conio.h>
#else
#include <stdio.h>
#endif

using std::cout;
using std::endl;
using std::vector;
using std::unique_ptr;
using std::string;

//*** Prototypes ***
void recQuickSort(vector<unsigned long>& arr, int first, int last);
void pressAnyKeyToContinue();
class BucketsCollection;

//***GLOBAL VARIABLES***
unique_ptr<unsigned long[]> list;
int listSize;
int numBuckets;
int numThreads;
unique_ptr<BucketsCollection> globalBuckets;

const unsigned long ULONGMAX = 4294967295;

class BucketsCollection {
public:
	BucketsCollection(const unsigned int numBuckets);
	~BucketsCollection() {}
	void addItem(unsigned long item);
	unsigned int getNumBuckets() const;
	unsigned int getNumItemsInABucket(const unsigned int bucket) const;
	vector<unsigned long>& getBucket(const unsigned int bucket);
	void copyOneBucketsIntoAnotherBuckets(BucketsCollection& smallBucket);
	void printAllBuckets() const;

private:
	vector< vector<unsigned long> > arr;
	unsigned int buckets;
	unsigned long range;

};

//*** Provide methods for the bucket class ***
BucketsCollection::BucketsCollection(const unsigned int numBuckets) {
	arr.resize(numBuckets);
	buckets = numBuckets;
	if (numBuckets > 1) {
		range = (ULONGMAX / buckets) + 1;
	}
	else {
		range = ULONGMAX;
	}
}


void BucketsCollection::addItem(unsigned long item) {

	unsigned int bucketNo = item / range;//find the bucket
	arr[bucketNo].push_back(item);//place item in back of correct bucket vector
}

unsigned int BucketsCollection::getNumBuckets() const {
	return buckets;
}

unsigned int BucketsCollection::getNumItemsInABucket(const unsigned int bucket) const {
	return arr[bucket].size();
}

void BucketsCollection::printAllBuckets() const {
	//Displays the contents of all buckets to the screen.

	// just uncomment this code when you have arr properly declared as a data member
	printf("******\n");
	for (int i = 0; i < numBuckets; i++) {
		printf("bucket number %d\n", i);
		for (unsigned int j = 0; j < arr[i].size(); j++) {
			printf("%08x ", arr[i][j]);

		}
		printf("\n");
	}
	printf("\n");
}

vector<unsigned long>& BucketsCollection::getBucket(const unsigned int bucket) {
	return arr[bucket];
}

void BucketsCollection::copyOneBucketsIntoAnotherBuckets(BucketsCollection& smallBucket) {
	//Copies all items in all buckets from one BucketsCollection object into another BucketsCollection object.  
	//Not for the first part of the homework assignment, only the multithreaded part.

	//for ( )

}


//***Functions that help our bucket sort work.***
void printList() {
	for (int i = 0; i < listSize; i++) {
		//cout << list[i] << " ";
		printf("%08x ", list[i]);
	}
}

void createList() {
	list = std::make_unique<unsigned long[]>(listSize);

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<unsigned long> dis(0, ULONGMAX);

	for (int i = 0; i < listSize; i++) {
		list[i] = dis(gen);
	}
}
void placeIntoBuckets() {

	//Put the values into the appropriate buckets.
	for (int i = 0; i < listSize; i++) {
		globalBuckets->addItem(list[i]);
	}

}


void sortEachBucket() {

	//Sort each individual bucket
	for (int i = 0; i < numBuckets; i++) {
		vector<unsigned long> &myBucket = globalBuckets->getBucket(i);
		recQuickSort(myBucket, 0, globalBuckets->getNumItemsInABucket(i));
	}

}


void combineBuckets() {
	//Copy each bucket back out to the original list[] array
	int index = 0;//holds current index in list

	//Loop for the amount of buckets
	for (int i = 0; i < numBuckets; i++) {
		
		//Get the individual bucket out of the globalBuckets
		vector<unsigned long> currBucket = globalBuckets->getBucket(i);
		
		for (int j = 0; j < currBucket.size(); j++) {
			
			//Copy all items from that individual bucket into the list array.
			list[index] = currBucket[j];

			index++;
		}//end copying to list for
	}//end buckets for

}


void bucketSort(bool displayOutput) {

	//For the upcoming homeowork assignment, I think it will help you the most to split your work into these three functions.  
	placeIntoBuckets();

	if (displayOutput) {
		printf("Displaying each bucket's contents before sorting: \n");
		globalBuckets->printAllBuckets();
	}

	sortEachBucket();

	combineBuckets();

	if (displayOutput) {
		printf("Displaying each bucket's contents after sorting: \n");
		globalBuckets->printAllBuckets();
		pressAnyKeyToContinue();
		printf("Displaying what is hopefully a sorted array: \n");
		printList(); //See if it's all sorted.
	}
}


int partition(vector<unsigned long>& arr, int first, int last) {
	unsigned long pivot;
	int index, smallIndex;

	unsigned long temp;

	//Take the middle value as the pivot.
	//swap(first, (first + last) / 2);
	pivot = arr[first];
	smallIndex = first;
	for (index = first + 1; index < last; index++) {
		if (arr[index] < pivot) {
			smallIndex++;
			//swap the two
			temp = arr[smallIndex];
			arr[smallIndex] = arr[index];
			arr[index] = temp;
		}
	}

	//Move pivot into the sorted location
	temp = arr[first];
	arr[first] = arr[smallIndex];
	arr[smallIndex] = temp;

	//Tell where the pivot is
	return smallIndex;

}


void recQuickSort(vector<unsigned long>& arr, int first, int last) {
	//first is the first index
	//last is the one past the last index (or the size of the array
	//if first is 0)

	if (first < last) {
		//Get this sublist into two other sublists, one smaller and one bigger
		int pivotLocation = partition(arr, first, last);
		recQuickSort(arr, first, pivotLocation);
		recQuickSort(arr, pivotLocation + 1, last);
	}
}


void verifySort(unique_ptr<unsigned long[]>& arr, unsigned int arraySize, std::chrono::duration<double, std::milli>& diff, const string& sortTest) {
	double val = diff.count();
	for (unsigned int i = 1; i < arraySize; i++) {
		if (arr[i] < arr[i - 1]) {
			printf("\n");
			printf("------------------------------------------------------\n");
			printf("SORT TEST %s\n", sortTest.c_str());

			if (val != 0.0) {
				printf("Finished bucket sort in %1.16lf milliseconds\n", diff.count());
			}
			printf("ERROR - This list was not sorted correctly.  At index %d is value %08X.  At index %d is value %08X\n", sortTest.c_str(), i - 1, arr[i - 1], i, arr[i]);
			printf("------------------------------------------------------\n");


			return;
		}
	}
	printf("\n");
	printf("------------------------------------------------------\n");
	printf("SORT TEST %s\n", sortTest.c_str());
	if (val != 0.0) {
		printf("Finished bucket sort in %1.16lf milliseconds\n", diff.count());
	}
	printf("PASSED SORT TEST - The list was sorted correctly\n", sortTest.c_str());
	printf("------------------------------------------------------\n");
}


void pressAnyKeyToContinue() {
	printf("Press any key to continue\n");

	//Linux and Mac users with g++ don't need this
	//But everyone else will see this message.
#ifndef __GNUC__
	_getch();
#else
	int c;
	fflush(stdout);
	do c = getchar(); while ((c != '\n') && (c != EOF));
#endif

}

int main() {

	std::chrono::duration<double, std::milli> diff{ 0 };

	//Set the listSize, numBuckets, and numThreads global variables.  
	listSize = 100;

	numBuckets = 2;
	numThreads = 2;
	createList();
	globalBuckets = std::make_unique<BucketsCollection>(numBuckets);
	printf("\nStarting bucket sort for listSize = %d, numBuckets = %d, numThreads = %d\n", listSize, numBuckets, numThreads);
	// printf("Displaying the unsorted list array:\n");
	// printList(); //useful for debugging small amounts of numbers.  
	pressAnyKeyToContinue();
	bucketSort(true);
	verifySort(list, listSize, diff, "2 buckets");
	pressAnyKeyToContinue();


	numBuckets = 4;
	numThreads = 4;
	createList();
	printf("\nStarting bucket sort for listSize = %d, numBuckets = %d, numThreads = %d\n", listSize, numBuckets, numThreads);
	globalBuckets = std::make_unique<BucketsCollection>(numBuckets);
	pressAnyKeyToContinue();
	bucketSort(true);
	verifySort(list, listSize, diff, "4 buckets");
	pressAnyKeyToContinue();

	printf("\nFor timing purposes, please make sure any debugging printf statements you added are commented out\n");
	pressAnyKeyToContinue();

	listSize = 900000;
	numBuckets = 1;
	numThreads = 1;
	createList();
	globalBuckets = std::make_unique<BucketsCollection>(numBuckets);
	//printf("Starting bucket sort for listSize = %d, numBuckets = %d, numThreads = %d, this is effectively a quick sort\n", listSize, numBuckets, numThreads);
	auto start = std::chrono::high_resolution_clock::now();
	bucketSort(false);
	auto end = std::chrono::high_resolution_clock::now();
	verifySort(list, listSize, diff, "4000000 items in 1 bucket - BASELINE");


	numBuckets = 2;
	numThreads = 2;
	createList();
	globalBuckets = std::make_unique<BucketsCollection>(numBuckets);
	// printf("Starting bucket sort for listSize = %d, numBuckets = %d, numThreads = %d\n", listSize, numBuckets, numThreads);
	start = std::chrono::high_resolution_clock::now();
	bucketSort(false);
	end = std::chrono::high_resolution_clock::now();
	diff = end - start;
	verifySort(list, listSize, diff, "4000000 items in 2 buckets");

	numBuckets = 4;
	numThreads = 4;
	createList();
	globalBuckets = std::make_unique<BucketsCollection>(numBuckets);
	//printf("Starting bucket sort for listSize = %d, numBuckets = %d, numThreads = %d\n", listSize, numBuckets, numThreads);
	start = std::chrono::high_resolution_clock::now();
	bucketSort(false);
	end = std::chrono::high_resolution_clock::now();
	diff = end - start;
	verifySort(list, listSize, diff, "4000000 items in 4 buckets");

	numBuckets = 8;
	numThreads = 8;
	createList();
	globalBuckets = std::make_unique<BucketsCollection>(numBuckets);
	//printf("Starting bucket sort for listSize = %d, numBuckets = %d, numThreads = %d\n", listSize, numBuckets, numThreads);
	start = std::chrono::high_resolution_clock::now();
	bucketSort(false);
	end = std::chrono::high_resolution_clock::now();
	diff = end - start;
	verifySort(list, listSize, diff, "4000000 items in 8 buckets");

	numBuckets = 16;
	numThreads = 16;
	createList();
	globalBuckets = std::make_unique<BucketsCollection>(numBuckets);
	//printf("Starting bucket sort for listSize = %d, numBuckets = %d, numThreads = %d\n", listSize, numBuckets, numThreads);
	start = std::chrono::high_resolution_clock::now();
	bucketSort(false);
	end = std::chrono::high_resolution_clock::now();
	diff = end - start;
	verifySort(list, listSize, diff, "4000000 items in 16 buckets");

	pressAnyKeyToContinue();
	return 0;
}