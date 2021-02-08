#include "Books.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>//for forcing to lowercase
using namespace std;

//constructors
Books::Books() : title(""), numAuthors(0), author1(""), publisher(""), publYear(0), isbn(0) {}

Books::Books(string title, int numAuthors, string author1, string publisher, 
	int publYear, long isbn) : title(title), numAuthors(numAuthors), author1(author1),
	publisher(publisher), publYear(publYear), isbn(isbn) {}

Books::Books(string title, int numAuthors, string author1, string publisher,
	int publYear, long isbn, double price) : title(title), numAuthors(numAuthors), 
	author1(author1), publisher(publisher), publYear(publYear), isbn(isbn), price(price) {}

Books::Books(string title, int numAuthors, string author1, string publisher,
	int publYear, long isbn, double price, int stock) : title(title), numAuthors(numAuthors), 
	author1(author1), publisher(publisher), publYear(publYear), isbn(isbn), price(price), 
	stock(stock) {}

//setters
void Books::setAuthors(string author2, string author3, string author4) {
	this->author2 = author2;
	this->author3 = author3;
	this->author4 = author4;
}
void Books::setPrice(double price) {
	this->price = price;
}
void Books::setStock(int stock) {
	this->stock = stock;
}
void Books::booksSold(int numBooks) {
	stock -= numBooks;
}
void Books::addStock(int numBooks) {
	stock += numBooks;
}

//getters
string Books::getTitle(){
	return title;
}
string Books::getAuthors(int index) {
	if (index == 0)
		return author1;
	else if (index == 1)
		return author2;
	else if (index == 2)
		return author3;
	else if (index == 3)
		return author4;
	else
		return "invalid author request";
}
string Books::getPublisher() {
	return publisher;
}
int Books::getNumAuthors() {
	return numAuthors;
}
int Books::getPublYear() {
	return publYear;
}
long Books::getISBN() {
	return isbn;
}
double Books::getPrice() {
	return price;
}
int Books::getStock() {
	return stock;
}

//other functions
bool Books::compareTitle(string otherTitle) {
	/*string tempTitle1;
	string tempTitle2;
	couldn't get to work
	//force title to lower
	transform(title.begin(), title.end(), tempTitle1.begin(), tolower);
	//force other title to lower
	transform(otherTitle.begin(), otherTitle.end(), tempTitle2.begin(), tolower);*/

	if (title == otherTitle)
		return true;
	else
		return false;
}
bool Books::compareISBN(long otherISBN) {
	if (isbn == otherISBN)
		return true;
	else
		return false;
}

void Books::display() {
	cout << fixed << setprecision(2);
	cout << title << "\nwritten by: " << author1;
	if (author2 != "")
		cout << ", " << author2;
	if (author3 != "")
		cout << ", " << author3;
	if (author4 != "")
		cout << ", " << author4;
	cout << "\npublished by: " << publisher << "\npublication year: " << publYear;
	cout << "\nISBN: " << isbn << endl
		<< "copies available: " << stock << endl
		<< "current price: $" << price << endl;
}

void Books::operator = (Books toBeCopied) {
	this->title = toBeCopied.getTitle();
	this->numAuthors = toBeCopied.getNumAuthors();
	this->author1 = toBeCopied.getAuthors(0);
	this->author2 = toBeCopied.getAuthors(1);
	this->author3 = toBeCopied.getAuthors(2);
	this->author4 = toBeCopied.getAuthors(3);
	this->publisher = toBeCopied.getPublisher();
	this->publYear = toBeCopied.getPublYear();
	this->isbn = toBeCopied.getISBN();
	this->price = toBeCopied.getPrice();
	this->stock = toBeCopied.getStock();
}