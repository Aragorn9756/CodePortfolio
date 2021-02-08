#include <iostream>

using std::cout;
using std::cin;
using std::endl;

void myFunFunction(int& data) {//passes the function the address of whatever is passed in
	data = 5;
}


//if you see * it could mean:
//declaring pointer data type
//dereferencing pointer
//multiplying

//if you see & it could mean:
//address of
//pass by reference
//bitwise &
int main() {

	int val = 42;// int val{42}; is newer way of initializing in C++
	int* ptr = &val;// int * (also written as int*) is the data type and & means address of

	cout << "The value is " << val << " at address " << ptr << endl;
	cout << "I can also get to the value this way: " << *ptr << endl; //dereferences
	//goes to the address and treats it as that data type

	myFunFunction(val);

	//int myArr[10];//not an object, just a chunk of set aside memory
	//
	//for (int i = 0; i < 10; i++) {
	//	myArr[i] = i * i;
	//}

	//myArr[10] = 666;//possible, because no bounds are set for the array
	////not a good idea, because you don't know what you might be overwriting

	//cout << "the array at index 10 is " << myArr[10] << endl;

	//int myArr[1000000] gives stack overflow error, exceeds space allocated for program

	int * myArr = new int[1000000];//the new asks the OS for extra space in memory, and is
								   //returned a pointer to where the array starts
								   //this is dynamic allocation'

	cout << "the data at the first element is: " << *myArr << endl;

	//pointer arithmetic
	//myArr++;//increments 4 bytes, becuause we said the array was an int
	//*(myArr + 1) = 42;
	//cout << "the data at the second element is: " << *(myArr + 1) << endl;
	//easiest way
	myArr[1] = 42;
	cout << "the data at the second element is: " << myArr[1] << endl;
	
	for (int i = 0; i < 1000000; i++) {
		myArr[i] = i;
	}
	cout << "The value at 123456 is " << myArr[123456] << endl;

	delete[] myArr;//allows other programs to use this memory spot
	myArr = nullptr;//clears out address, preventing accidental continued use.

	//memory leak - constantly asking for more data, but losing track of address
	//lost addresses CANNOT be recovered, essentially locking up memory space until
	//the program terminates, and the OS reclaims all requested memory slots
	/*for (int i = 0; i < 100000000; i++) {
		int *fun = new int[1];
	}*/

	system("pause");
	return 0;
}