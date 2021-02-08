#pragma once
#ifndef BOOKS_H
#define BOOKS_H
#include <string>
using namespace std;

class Books {

private:
	const int MAX = 200;//max size of c-strings
	string title, author1, author2 = "", author3 = "", author4 = "", publisher;
	int numAuthors, publYear, stock;//publYear = publication year
	long isbn;
	double price;

public:
	//default constructor
	Books();

	//constructor 1, no price no stock
	Books(string title, int numAuthors, string author1, string publisher, int publYear, long isbn);

	//constructor 2, no stock
	Books(string title, int numAuthors, string author1, string publisher, int publYear, long isbn, 
		double price);
	
	//constructor 3
	Books(string title, int numAuthors, string author1, string publisher, int publYear, long isbn,
		double price, int stock);

	//setters
	void setAuthors(string author2, string author3, string author4);
	void setPrice(double price);
	void setStock(int stock);
	void booksSold(int numBooks);
	void addStock(int numBooks);

	//getters
	string getTitle();
	string getAuthors(int index);
	string getPublisher();
	int getNumAuthors();
	int getPublYear();
	long getISBN();
	double getPrice();
	int getStock();
	
	//other functions
	bool compareTitle(string otherTitle);
	bool compareISBN(long otherISBN);
	void display();
	void operator = (Books toBeCopied);

};//end class

#endif
