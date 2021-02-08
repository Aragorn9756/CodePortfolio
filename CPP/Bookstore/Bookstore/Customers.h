#pragma once
#ifndef CUSTOMERS_H
#define CUSTOMERS_H
#include <string>
#include <iomanip> //for setprecision
using namespace std;
//can I put cin << fixed << setprecision(2) here to make it global? ask professor
class Customers {

private:
	string name, currentTransBooks;
	int memberID = 0, numPurchases = 0;
	double amountSpent = 0.0, availCredit = 0.0, currentTransPrice = 0.0;
	bool isMember;

public:
	//default constructor
	Customers();
	
	//overloaded constructors
	Customers(string name, bool isMember);//used if new customer chooses NOT to become member

	Customers(string name, bool isMember, int memID);

	//setters
	void setMembership();
	void setMemberID(int id);
	void newTrans();//resets currentTrans variables

	//getters
	bool getMemberStat();
	int getMemberID();
	string getName();
	double getCredit();

	//other functions
	bool compareName(string nameToCompare);
	void purchase(string title, double price);
	void displayTrans();//displays books purchased and amount spent for current transaction
	void endTrans();//displays books purchased, amount spent, then applies credit if any
	
	


};

#endif