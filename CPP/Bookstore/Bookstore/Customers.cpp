#include "Customers.h"
#include <iostream>
#include <string>
#include <algorithm>//for forcing to lowercase
using namespace std;

//default constructor
Customers::Customers() : name(""), isMember(false) {}

//overloaded constructors
//used if new customer chooses NOT to become member
Customers::Customers(string name, bool isMember) : name(name), isMember(isMember) {}

Customers::Customers(string name, bool isMember, int memID) : name(name),
isMember(isMember), memberID(memID) {
	amountSpent += 10.0;
}

//setters
void Customers::setMembership() {
	if (isMember)
		isMember = false;
	else {
		isMember = true;
		amountSpent += 10.0;
	}
}

void Customers::setMemberID(int id) {
	memberID = id;
}

//resets currentTrans variables
void Customers::newTrans() {
	currentTransPrice = 0.0;
	currentTransBooks = "";
}

//getters
bool Customers::getMemberStat() {
	if (isMember)
		return true;
	else
		return false;
}

int Customers::getMemberID() {
	return memberID;
}

string Customers::getName() {
	return name;
}

double Customers::getCredit() {
	return availCredit;
}

//other functions
bool Customers::compareName(string nameToCompare) {

	//compare
	if (name == nameToCompare)
		return true;
	else 
		return false;
}

void Customers::purchase(string title, double price) {
	currentTransBooks += title + "\n";
	currentTransPrice += price;
	
	if (isMember) {
		//if 11th book purchased, apply discount and reset
		if (numPurchases == 10) {
			availCredit += amountSpent / 10;
			numPurchases = 1;
			amountSpent = price;
		}
		else {
			numPurchases++;
			amountSpent += price;
		}
	}
}

//displays books purchased and amount spent for current transaction
void Customers::displayTrans() {
	cout << currentTransBooks << "\nTotal: $" << currentTransPrice << endl;
}

//displays books purchased, amount spent, then applies credit if any
void Customers::endTrans() {
	double creditApplied;

	if (availCredit <= currentTransPrice) {
		creditApplied = availCredit;
		currentTransPrice -= availCredit;
		availCredit = 0;
	}
	else {
		creditApplied = currentTransPrice;
		availCredit -= currentTransPrice;
		currentTransPrice = 0.0;
	}

	cout << "\nTRANSACTION RECEIPT\nPURCHASES:"
		<< currentTransBooks << "\nSub-Total:\n\t$"
		<< (currentTransPrice + creditApplied) << endl
		<< "Credit Applied:\n\t$" << creditApplied << endl << endl
		<< "TOTAL:\n$" << currentTransPrice << endl << endl
		<< "Credit Available for Next Transaction:\n\t$"
		<< availCredit << endl << endl
		<< "Thank You For Your Patronage!\n\n";
}