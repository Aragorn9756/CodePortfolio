#include <iostream>
#include <iomanip>
#include <string>
#include "Books.h"
#include "Customers.h"

using namespace std;

//function declarations
char charValidation(char char1, char char2, char char3, char char4);
char charValidation(char char1, char char2, char char3, char char4, char char5, char char6);
int isbnValidation();
int intValidation();
int intValidation(int min);
int intValidation(int min, int max);
double priceValidation();
string strValidation();

int main() {

	//to force 2 decimal points on prices
	cout << fixed << setprecision(2);

	//declare arrays for books and customers
	const int BOOKS_MAX = 1000;
	const int CUST_MAX = 500;
	Books books[BOOKS_MAX];
	Customers customers[CUST_MAX];

	//declare 20 book objects
	books[0] = Books("Harry Potter and the Sorcerer's Stone", 1, "J.K. Rowling", "Scholastic", 1997, 97887006, 17.90, 25);
	books[1] = Books("Harry Potter and the Chamber of Secrets", 1, "J.K. Rowling", "Scholastic", 1998, 15648972, 18.50, 25);
	books[2] = Books("Harry Potter and the Prisoner of Azkaban", 1, "J.K. Rowling", "Scholastic", 1999, 98546547, 19.53, 25);
	books[3] = Books("Harry Potter and the Goblet of Fire", 1, "J.K. Rowling", "Scholastic", 2000, 65357895, 22.50, 25);
	books[4] = Books("Harry Potter and the Order of the Pheonix", 1, "J.K. Rowling", "Scholastic", 2003, 13548975, 24.75, 25);
	books[5] = Books("Harry Potter and the Half-Blood Prince", 1, "J.K. Rowling", "Scholastic", 2005, 32483217, 22.50, 25);
	books[6] = Books("Harry Potter and the Deathly Hallows", 1, "J.K. Rowling", "Scholastic", 2007, 65487798, 25.00, 25);
	books[7] = Books("The Lord of the Rings",1, "J.R.R. Tolkien", "Allen & Unwin", 1954, 73748941, 31.57, 15);
	books[8] = Books("The Hobbit", 1, "J.R.R. Tolkien", "Allen & Unwin", 1937, 25648793, 14.99, 20);
	books[9] = Books("The Silmarillion", 1, "J.R.R. Tolkien", "Allen & Unwin", 1977, 98457987, 32.50, 10);
	books[10] = Books("Elantris", 1, "Brandon Sanderson", "Tor Books", 2005, 58944868, 10);
	books[11] = Books("Mistborn", 1, "Brandon Sanderson", "Tor Books", 2006, 11987941, 10);
	books[12] = Books("Well of Ascension", 1, "Brandon Sanderson", "Tor Books", 2007, 71357897, 15);
	books[13] = Books("Hero of Ages", 1, "Brandon Sanderson", "Tor Books", 2008, 48973841, 18);
	books[14] = Books("Alloy of Law", 1, "Brandon Sanderson", "Tor Books", 2011, 56489569, 17);
	books[15] = Books("Shadows of Self", 1, "Brandon Sanderson", "Tor Books", 2015, 76691259, 18);
	books[16] = Books("Bands of Mourning", 1, "Brandon Sanderson", "Tor Books", 2016, 81324897, 18);
	books[17] = Books("WarBreaker", 1, "Brandon Sanderson", "Tor Books", 2009, 15512387, 10);
	books[18] = Books("Way of Kings", 1, "Brandon Sanderson", "Tor Books", 2010, 84132118, 15);
	books[19] = Books("Words of Radiance", 1, "Brandon Sanderson", "Tor Books", 2014, 87914652, 15);

	//declare 10 customer objects
	customers[0] = Customers("John Jacob Jingleheimer", true, 35791);
	customers[1] = Customers("John Shepard", false);
	customers[2] = Customers("Samus Aran", false);
	customers[3] = Customers("Hermione Granger", true, 98713);
	customers[4] = Customers("Sabriel Abhorsen", true, 13579);
	customers[5] = Customers("Frodo Baggins", true, 34981);
	customers[6] = Customers("Ben Kenobi", false);
	customers[7] = Customers("Peter Parker", true, 78913);
	customers[8] = Customers("Steve Rogers", false);
	customers[9] = Customers("Bruce Wayne", true, 46535);
	
	//declare vars
	string strSearchFor;//holds string to be searched for
	int count, memCount, foundIndex = -1, isbnSearchFor, numBooks;
	char userChoice;
	double newPrice;

	//greeting //Mnemosyne is the Greek titan of Memory
	cout << "Welcome to the Mnemosyne Bookstore Manager.";

	//overarching do-while
	do {

		cout << "\n\nWould you like to manage inventory or process a customer transaction?\n"
			<< "Press 'i' for inventory or 't' for transaction: ";
		userChoice = charValidation('I', 'i', 'T', 't');
		
		//if inventory
		if (userChoice == 'I' || userChoice == 'i') {
			do {

				cout << "\nWould you like to search for the book by title or 8-digit ISBN?"
					<< "\nPress 't' for title or 'i' for ISBN: ";
				userChoice = charValidation('T', 't', 'I', 'i');

				//reset foundIndex to -1 before searching for book
				foundIndex = -1;

				//if search by title
				if (userChoice == 'T' || userChoice == 't') {

					//get title to search for
						cout << "\nPlease enter the title of the book you would like to look for.\n";
						
						strSearchFor = strValidation();

					//search for matching title until either match found or empty book objects reached
					//if found save index in foundIndex

					//set count to -1 so when count is pre-incremented, initial searches are done at index 0
					count = -1;
					do {

						++count;

						if (books[count].compareTitle(strSearchFor))
							foundIndex = count;

					} while (books[count].getTitle() != "" && !books[count].compareTitle(strSearchFor));

				}//end search by title

				//else search by ISBN
				else if (userChoice == 'I' || userChoice == 'i') {

					cout << "\nPlease enter the numbers of the 8-digit ISBN.\n"
						<< "A valid ISBN contains only digits and does not begin with 0: ";
					isbnSearchFor = isbnValidation();

					//search for matching isbn until either match found or empty book objects reached
					//if found save index in foundIndex

					//set count to -1 so when count is pre-incremented, initial searches are done at index 0
					count = -1;
					do {

						++count;

						if (books[count].compareISBN(isbnSearchFor))
							foundIndex = count;

					} while (books[count].getTitle() != "" && !books[count].compareISBN(isbnSearchFor));

				}//end search by ISBN

				//display results of search
				if (foundIndex != -1) {
					cout << "\nBook found:\n";
					books[foundIndex].display();
				}
				
				//create book if it doesn't exist
				else {
					cout << "\nThat book is not in inventory.\n";
					
					//find empty spot or inform user that book inventory is full
					count = -1;

					//stops incrementing when empty book object is found
					do {
						++count;
					} while (books[count].getTitle() != "");

					//array full
					if (count == 999) {
						cout << "\nThere are no more available spots in inventory for"
							<< " more books.\n";
					}
					//book creation possible
					else {

						cout << "\nThere is room within inventory for more books. "
							<< "Would you like to add a new book to inventory?\n"
							<< "Press 'y' for yes or 'n' for no: ";
						userChoice = charValidation('Y', 'y', 'N', 'n');

						//if they want to make a new book object
						if (userChoice == 'Y' || userChoice == 'y') {

							//vars used in book creation
							string title, author1, author2 = "", author3 = "", author4 = "", publisher;
							int numAuthors, publYear, stock;//publYear = publication year
							long isbn;
							double price;

							//get book title
							cout << "\nPlease enter the title of the book\n";
							title = strValidation();

							//get num authors
							cout << "\nHow many Authors are there?\n"
								<< "A maximum of 4 authors is allowed: ";
							numAuthors = intValidation(1, 4);

							//get author names
							for (int i = 1; i <= numAuthors; i++) {
								cout << "\nWhat is the name of Author " << i << "?";

								//save name to corresponding author
								if (i == 1)
									author1 = strValidation();
								else if (i == 2)
									author2 = strValidation();
								else if (i == 3)
									author3 = strValidation();
								else if (i == 4)
									author4 = strValidation();
							}

							cout << "\nWho is the publisher? ";
							publisher = strValidation();

							cout << "\nWhat year was the book published? ";
							publYear = intValidation();

							cout << "\nWhat is the 8-digit ISBN.\n"
								<< "A valid ISBN contains only digits and does not begin with 0: ";
							isbn = isbnValidation();

							cout << "\nHow much will the books be sold for? ";
							price = priceValidation();

							cout << "\nHow many books are to be put in stock? ";
							stock = intValidation(0);

							//put all  elements into empty object
							books[count] = Books(title, numAuthors, author1, publisher, publYear, isbn, price, stock);
							books[count].setAuthors(author2, author3, author4);

							//display created book
							cout << endl << books[count].getTitle() << " has been added to inventory.\n";

							books[count].display();

						}//end book creation if

					}//end creation possiblility else


				}//end book object creation

				//allow user to manage stock and price of chosen book
				do {
					cout << "\nWould you like to manage the current stock of this book, or change the price?\n"
						<< "Press 's' for stock, 'p' for price or 'q' to quit: ";
					userChoice = charValidation('S', 's', 'P', 'p', 'Q', 'q');

					//if manage stock
					if (userChoice == 'S' || userChoice == 's') {

						do {
							cout << "\nThere are currently " << books[count].getStock() << " copies of "
								<< books[count].getTitle() << " in stock.\n"
								<< "Would you like to add or remove copies from inventory?\n"
								<< "Note: to update out-of-print books to unavailable, choose remove\n"
								<< "Press 'a' to add, 'r' to remove or 'q' to quit: ";
							userChoice = charValidation('A', 'a', 'R', 'r', 'Q', 'q');

							//if adding to inventory
							if (userChoice == 'A' || userChoice == 'a') {

								cout << "\nHow many books would you like to add into inventory? ";
								numBooks = intValidation(0);
								
								books[count].addStock(numBooks);

								cout << "\nThere are now " << books[count].getStock() << " copies of "
									<< books[count].getTitle() << " in stock.\n";

							}//end adding to inventory

							//if removing from inventory
							else if (userChoice == 'R' || userChoice == 'r') {

								cout << "\nHow many books would you like to remove from inventory?\n"
									<< "if setting out of print book to unavailable, enter -1: ";
								numBooks = intValidation(-1, books[count].getStock());

								if (numBooks == -1) {
									books[count].setStock(-1);
									cout << endl << books[count].getTitle() << " has been denoted as unavailable.\n";
								}
								else {
									books[count].booksSold(numBooks);

									cout << "\nThere are now " << books[count].getStock() << " copies of "
										<< books[count].getTitle() << " in stock.\n";
								}
							}

						} while (userChoice != 'Q' && userChoice != 'q');
						
						//set Userchoice to another char to avoid automatic exit from price and stock loop
						userChoice = 'h';

					}//end stock if
					
					//if price 
					else if (userChoice == 'P' || userChoice == 'p') {

						cout << endl << books[count].getTitle() << " is currently being sold at $" << books[count].getPrice()
							<< "\nWhat is the new price? ";
						newPrice = priceValidation();

						books[count].setPrice(newPrice);

						cout << endl << books[count].getTitle() << " is now being sold at $" << books[count].getPrice();

					}

				} while (userChoice != 'Q' && userChoice != 'q');

				//another book?
				cout << "\nWould you like to continue managing inventory?\n"
					<< "Press 'y' for yes or 'n' for no: ";
				userChoice = charValidation('Y', 'y', 'N', 'n');

			} while (userChoice == 'y' || userChoice == 'Y');
		}//end inventory loop
		
		 
		 //else if transaction
		else if (userChoice == 'T' || userChoice == 't') {
			do {

				cout << "\nPlease enter the customer name: ";
				strSearchFor = strValidation();

				//set count to -1 so when count is pre-incremented, initial searches are done at index 0
				memCount = -1;
				foundIndex = -1;
				do {

					++memCount;

					if (customers[memCount].compareName(strSearchFor)) {
						foundIndex = memCount;
					}

				} while (customers[memCount].getName() != "" && !customers[memCount].compareName(strSearchFor));

				 //if member exists
				if (foundIndex != -1) {
					cout << "\ncustomer found\n";
				}
				//create new customer
				else {
					cout << endl << strSearchFor << " is a new customer. Would they like to become a member?\n"
						<< "Press 'y' for yes or 'n' for no: ";
					userChoice = charValidation('Y', 'y', 'N', 'n');
					
					//create member customer
					if (userChoice == 'y' || userChoice == 'Y') {
						cout << "\nPlease have " << strSearchFor << " enter a 4 digit Member ID.\n"
							<< "IDs may not begin with a 0: ";
						
						//get userchosen pin no holds on pin other than 4 digits. combination of name and digit will set apart member
						//any number from 1000-9999 is valid id
						int memID = intValidation(1000, 9999);

						//creat new member customer
						customers[memCount] = Customers(strSearchFor, false, memID);
					}
					//create non-member customer
					else {
						customers[memCount] = Customers(strSearchFor, false);
					}
				}//end create new customer

				//display customer name and membership status
				if (customers[memCount].getMemberStat()) {
					cout << endl << customers[memCount].getName() << " is currently a member.\n";
					cout << "Their member ID is " << customers[memCount].getMemberID() << " and currently "
						<< " have $" << customers[memCount].getCredit() << " of credit available.\n";
				}
				else {
					cout << endl << customers[memCount].getName() << " is not currently a member.\n";
				}
				
				cout << "\nWould " << customers[memCount].getName() << " like to change membership status?\n"
					<< "Press 'y' for yes or 'n' for no: ";
				userChoice = charValidation('Y', 'y', 'N', 'n');

				//change membership status
				if (userChoice == 'Y' || userChoice == 'y') {
					
					//if currently member
					if (customers[memCount].getMemberStat()) {
						customers[memCount].setMembership();
						
						cout << endl << customers[memCount].getName() << " is no longer a member.\n";
					}
					else {
						customers[memCount].setMembership();

						//set member ID if it doesn't exist
						if (customers[memCount].getMemberID() == 0) {
							cout << "\nPlease have " << customers[memCount].getName() << " enter a 4 digit Member ID.\n"
								<< "IDs may not begin with a 0: ";
							int memID = intValidation(1000, 9999);
							customers[memCount].setMemberID(memID);
						}//end create member ID

						cout << endl << customers[memCount].getName() << " is now a member.\n";
						cout << "Their member ID is " << customers[memCount].getMemberID() << ".";

					}//end becoming member else
				}//end change membership status

				cout << "\nWould " << customers[memCount].getName() << " like to make a purchase?\n"
					<< "Press 'y' for yes or 'n' for no: ";
				userChoice = charValidation('Y', 'y', 'N', 'n');
				
				if (userChoice == 'y' || userChoice == 'Y') {

					//reset any previously saved transaction
					customers[memCount].newTrans();

					do {

						cout << "\nPlease enter the title of the book being purchased.\n";

						strSearchFor = strValidation();

						//search for matching title until either match found or empty book objects reached
						//if found save index in foundIndex

						//set count to -1 so when count is pre-incremented, initial searches are done at index 0
						count = -1;
						foundIndex = -1;
						do {

							++count;

							if (books[count].compareTitle(strSearchFor))
								foundIndex = count;

						} while (books[count].getTitle() != "" && !books[count].compareTitle(strSearchFor));

						//if book is found
						if (foundIndex != -1) {
							customers[memCount].purchase(books[count].getTitle(), books[count].getPrice());
							
							cout << endl << books[count].getTitle() << ", costing $" << books[count].getPrice()
								<< ", was added to the transaction.\n";
						}
						//if book wasn't found
						else {
							cout << "\nNo book of the title \"" << strSearchFor << "\" could be found in inventory.\n";
						}

						//display transaction so far
						cout << "\nCurrent Transaction:\n";
						customers[memCount].displayTrans();

						//purchase another book?
						cout << "\nWould you like to add another purchase to this transaction?\n"
							<< "Press 'y' for yes or 'n' for no: ";
						userChoice = charValidation('Y', 'y', 'N', 'n');

					} while (userChoice == 'y' || userChoice == 'Y');

					//print reciept
					customers[memCount].endTrans();

				}//end transaction

				//another transaction?
				cout << "\nWould you like to process another transaction?\n"
					<< "Press 'y' for yes or 'n' for no: ";
				userChoice = charValidation('Y', 'y', 'N', 'n');

			} while (userChoice == 'y' || userChoice == 'Y');
		}//end transaction if

		//ask if they would like to continue
		cout << "\nWould you like to make further adjustments?\n"
			<< "Press 'y' to continue making adjustments or 'n' to close the program: ";
		userChoice = charValidation('Y', 'y', 'N', 'n');

	} while (userChoice == 'y' || userChoice == 'Y');

	cout << endl << endl;
	system("pause");
}

/*****************************************************************************************************************/

char charValidation(char char1, char char2, char char3, char char4) {
	char userInput;

	cin >> userInput;

	while (userInput != char1 && userInput != char2 && userInput != char3 && userInput != char4) {
		cin.ignore(INT_MAX, '\n');
		cout << "That is not a valid choice. Please choose either '" << char2
			<< "' or '" << char4 << "': ";
		cin >> userInput;
	}

	cin.ignore(INT_MAX, '\n');

	return userInput;
}//end charValidation

/***************************************************************************************/

//overloaded for 3 char choices
char charValidation(char char1, char char2, char char3, char char4, char char5, char char6) {
	char userInput;

	cin >> userInput;

	while (userInput != char1 && userInput != char2 && userInput != char3 && userInput != char4 &&
		 userInput != char5 && userInput != char6) {
		cin.ignore(INT_MAX, '\n');
		cout << "That is not a valid choice. Please choose either '" << char2
			<< "', '" << char4 << "' or '" << char6 << "': ";
		cin >> userInput;
	}

	cin.ignore(INT_MAX, '\n');

	return userInput;
}//end charValidation

 /*****************************************************************************************************************/

int isbnValidation() {

	bool valid;
	int isbn;
	
	//loop until input is valid
	do {

		cin >> isbn;
		valid = true;

		//if cin busted
		if (!cin){
			//wipe and clear cin
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			valid = false;
			
			cout << "An ISBN may contain only digits. Please re-enter the ISBN: ";
		}
		//if the number enter is not 8 digits long, excluding any leading 0's
		else if (isbn < 10000000 || isbn > 99999999) {
			valid = false;
			cout << "An ISBN must be 8 digits long. Please make sure there are no leading 0s\n"
				<< "nor any non-digit characters: ";

			//clear buffer
			cin.ignore(INT_MAX, '\n');
		}

	} while (!valid);

	//clear buffer
	cin.ignore(INT_MAX, '\n');

	return isbn;
}//end isbn validation

 /*****************************************************************************************************************/

//int validation with no min or max
int intValidation() {

	bool valid;
	int num;

	//loop until input is valid
	do {

		cin >> num;
		valid = true;

		//if cin busted
		if (!cin) {
			//wipe and clear cin
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			valid = false;

			cout << "Please enter an integer; numbers only and no decimals: ";
		}

	} while (!valid);

	//clear buffer
	cin.ignore(INT_MAX, '\n');

	return num;
}//end int validation

 /*****************************************************************************************************************/

 // overloaded int validation with min
int intValidation(int min) {

	bool valid;
	int num;

	//loop until input is valid
	do {

		cin >> num;
		valid = true;

		//if cin busted
		if (!cin) {
			//wipe and clear cin
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			valid = false;

			cout << "\nPlease enter an integer; numbers only and no decimals: ";
		}
		else if (num < min) {
			valid = false;
			
			cout << "\nThat number is too small. Please choose a number greater than or equal to "
				<< min << ": ";

			//clear buffer
			cin.ignore(INT_MAX, '\n');
		}

	} while (!valid);

	//clear buffer
	cin.ignore(INT_MAX, '\n');

	return num;
}//end in validation with min

 /*****************************************************************************************************************/

 // overloaded int validation with min and max
int intValidation(int min, int max) {

	bool valid;
	int num;

	//loop until input is valid
	do {

		cin >> num;
		valid = true;

		//if cin busted
		if (!cin) {
			//wipe and clear cin
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			valid = false;

			cout << "\nPlease enter an integer, numbers only and no decimals: ";
		}
		else if (num < min || num > max) {
			valid = false;

			cout << "\nThat number is outside the correct range. \nPlease choose a number greater than or equal to "
				<< min << " and less than or equal to " << max << ": ";

			//clear buffer
			cin.ignore(INT_MAX, '\n');
		}

	} while (!valid);

	//clear buffer
	cin.ignore(INT_MAX, '\n');

	return num;
}//end in validation with min

/*************************************************************************************/

double priceValidation() {
	bool valid;
	double price;

	//loop until input is valid
	do {

		cin >> price;
		valid = true;

		//if cin busted
		if (!cin) {
			//wipe and clear cin
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			valid = false;

			cout << "\nPlease enter a price, numbers only with 1 decimal: ";
		}
		else if (price < 0.0) {
			valid = false;

			cout << "\nBooks cannot be sold for a negative value.\nPlease choose a number "
				<< "greater than or equal to 0: ";

			//clear buffer
			cin.ignore(INT_MAX, '\n');
		}

	} while (!valid);

	//clear buffer
	cin.ignore(INT_MAX, '\n');

	return price;
}

/*************************************************************************************/

string strValidation() {
	char userChoice;
	string strToReturn;
	
	do {

		cout << "\nBe mindful of spelling, capitalization and non-alphanumeric characters: ";
		getline(cin, strToReturn);

		cout << "\nYou entered \"" << strToReturn << "\". Is this correct?\n"
			<< "Press 'y' for yes or 'n' for no: ";
		userChoice = charValidation('Y', 'y', 'N', 'n');

	} while (userChoice == 'N' || userChoice == 'n');

	return strToReturn;
}