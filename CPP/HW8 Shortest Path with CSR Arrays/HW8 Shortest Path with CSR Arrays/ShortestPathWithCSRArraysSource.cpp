//Copyright 2017, Bradley Peterson, Weber State University, all rights reserved.

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <memory>

//To prevent those using g++ from trying to use a library
//they don't have
#ifndef __GNUC__
#include <conio.h>
#endif

using std::cout;
using std::cerr;
using std::cin;
using std::endl;
using std::ifstream;
using std::vector;
using std::string;
using std::istringstream;
using std::unique_ptr;
using std::make_unique;

struct graphEdge;

//The collection of edge objects
vector<graphEdge> edges;
int numEdges;
int numNodes;

//Declare *four* arrays (columns, graphWeights, rows, and smallestWeight)
unique_ptr<int[]> columns;
unique_ptr<int[]> graphWeights;
unique_ptr<int[]> rows;
unique_ptr<int[]> smallestWeight;

const int LARGE_NUMBER = 99999999;

//The class for an edge object.  
struct graphEdge {
public:
	int sourceNode;
	int destNode;
	int weight;
	graphEdge() {};
	graphEdge(int sourceNode, int destNode, int weight) {
		this->sourceNode = sourceNode;
		this->destNode = destNode;
		this->weight = weight;

	}
};

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

int getWeight(int sourceNode, int destNode) {
	//get holders for searching through the columns array
	int currIndex;
	int endIndex;
	bool found = false;//for stopping when right column is found
	
	//go to the rows table to find the start index, then ++ for the end index
	currIndex = rows[sourceNode];
	endIndex = rows[++sourceNode];

	//search for a column matching destNode within sourceNode's range
	do
	{
		//if a match is found
		if (columns[currIndex] == destNode) {
			//leave currIndex unchanged so we can check that index in the
			//weights array the change found to true
			found = true;
		}
		//otherwise increment and keep going
		else {
			currIndex++;
		}
	} while (currIndex < endIndex && !found);
	
	//if no matching destNode was found
	if (!found) {
		//return outrageous number
		return LARGE_NUMBER;
	}

	//if code gets here, something must have been found
	//return the value in graphWeights array at the index held in currIndex
	return graphWeights[currIndex];
}

void shortestPath(int vertex) {

	//The argument is the vertex to search from

	for (int j = 0; j < numNodes; j++) {
		//intialization step
		smallestWeight[j] = getWeight(vertex, j);
	}
	//continue initializing
	unique_ptr<bool[]> weightFound = make_unique<bool[]>(numNodes);
	for (int j = 0; j < numNodes; j++) {
		weightFound[j] = false;
	}

	//The node we're at we assume we can get to with a cost of zero.
	weightFound[vertex] = true;
	smallestWeight[vertex] = 0;

	//For every node...
	for (int i = 0; i < numNodes - 1; i++) {
		if (i % 100 == 0) {
			cout << "Looking up shortest path for " << i << " of " << numNodes - 1 << " amount of nodes" << endl;

		}
		else if (i == numNodes - 2) {
			cout << "Looking up the shortest path for the last node" << endl;
		}
		int minWeight = LARGE_NUMBER;
		int v = -1;

		//Of the nodes who haven't been marked as completed,
		//or in other words, nodes which we aren't sure if we've found the
		//smallest path weight
		//Of those ndoes...find the node with the smallest current weight.
		for (int j = 0; j < numNodes; j++) {
			if (!weightFound[j]) {
				if (smallestWeight[j] < minWeight) {
					v = j;
					minWeight = smallestWeight[v];
				}
			}
		}

		//Ignore non connected nodes.
		if (v != -1) {

			//When I drew the red line on my notes.  
			weightFound[v] = true;
			//Now that we've found a new shortest possible weight (at node v)
			//look at all of v's neighborly costs, and see if we can get to v's neighbors
			//using v, at a better weight than what we already know.
			for (int j = 0; j < numNodes; j++) {
				if (!weightFound[j]) {
					if (minWeight + getWeight(v, j) < smallestWeight[j]) {
						smallestWeight[j] = minWeight + getWeight(v, j);
					}
				}
			}
		}
	}
}

//overloaded method for displaying the path taken along the shortest route.
void shortestPath(int sourceNode, int destNode) {
	//TODO Record each node taken along the shortest path and display
	cout << "still needs to be written";
}

//Some functions I wrote to help the stable sort know what to sort against.  
//You don't need to worry about these or modify them.  
bool compareFirstColumn(const graphEdge& x, const graphEdge& y) {
	if (x.sourceNode < y.sourceNode) {
		return true;
	}
	else {
		return false;
	}
}
bool compareSecondColumn(const graphEdge& x, const graphEdge& y) {
	if (x.destNode < y.destNode) {
		return true;
	}
	else {
		return false;
	}
}

void testRun() {
	//This loads the same values found in the book:
	edges.push_back(graphEdge(0, 1, 16));
	edges.push_back(graphEdge(0, 3, 2));
	edges.push_back(graphEdge(0, 4, 3));
	edges.push_back(graphEdge(1, 2, 5));
	edges.push_back(graphEdge(2, 1, 3));
	edges.push_back(graphEdge(3, 1, 12));
	edges.push_back(graphEdge(3, 4, 7));
	edges.push_back(graphEdge(4, 1, 10));
	edges.push_back(graphEdge(4, 2, 4));
	edges.push_back(graphEdge(4, 3, 5));


	numNodes = 5;
	numEdges = 10;

}


void readFile() {
	ifstream inFile("rome99.gr");
	int counter = 0;
	int largestNode = 0;
	char throwaway;
	if (!inFile.good())
	{
		cerr << "The file wasn't found.  For Visual Studio users, make sure it's in the same directory as your solution's .vcxproj file." << endl;
		pressAnyKeyToContinue();
		exit(-1);
	}
	else {
		string line;
		graphEdge edge;
		while (getline(inFile, line)) {


			if (line.at(0) == 'a' && line.at(1) == ' ') {
				if (counter % 10000 == 0) {
					cout << "Reading edge # " << counter << endl;
				}
				//this line is one we keep, read in the data
				istringstream iss(line);
				iss >> throwaway >> edge.sourceNode >> edge.destNode >> edge.weight;
				if (edge.sourceNode > largestNode) {
					largestNode = edge.sourceNode;
				}

				if (edge.destNode > largestNode) {
					largestNode = edge.destNode;
				}
				edges.push_back(edge);
				counter++;
			}
		}
		numNodes = largestNode;
		numEdges = counter;


		//Create a zero node with an edge that points to itself with a weight of 0.
		//The file node data starts at node #1, so we want to make 
		//everything clean by letting edge 1 take index 1 in our graphWeights array,
		//and this zero node can take index 0.  
		graphEdge zeroEdge(0, 0, 0);
		edges.push_back(zeroEdge);
		numNodes++;
		numEdges++;
		//Because we started a zero node, increase the numNodes by 1., 
		cout << "Finished reading " << numNodes << " nodes and " << numEdges << " edges." << endl;
	}
}

void createCsrArrays() {

	//initialize graphWeights, columns and rows
	//in the case of arrays, () in make_unique hold size of array
	graphWeights = make_unique<int[]>(numEdges);
	columns = make_unique<int[]>(numEdges);
	rows = make_unique<int[]>(numNodes);

	//create an int holder to keep track of which node we are working with
	//this helps with populating the row array
	int currRow = -1; //set to -1 to ensure rows is update on the first pass of the loop

	//populate the arrays. edges vector is already sorted, so no need to worry about that
	for (int i = 0; i < edges.size(); i++) {

		//fill graphWeights and columns at i with the weight and destNode at i respectively
		graphWeights[i] = edges[i].weight;
		columns[i] = edges[i].destNode;

		//if the source node at i doesn't match currRow, update rows[currRow] with i
		if (edges[i].sourceNode != currRow) {
			currRow = edges[i].sourceNode;
			rows[currRow] = i;
		}
	}
	//set the last value in the row array to 1 more than the number of edges so that
	//the shortest path will stop at the end of the arrays rather than going over.
	rows[numNodes] = edges.size();

	//initial smallestWeight
	smallestWeight = make_unique<int[]>(numNodes);

}

void deleteArrays() {
	graphWeights.reset();
	columns.reset();
	rows.reset();
	smallestWeight.reset();
}

int main() {

	cout << "Would you like to do: " << endl << "1. Test run" << endl << "2. Full run" << endl << "Enter your selection: ";
	int selection;
	cin >> selection;
	if (selection == 1) {
		testRun();
	}
	else if (selection == 2) {
		readFile();

	}

	//The collection of edge objects is just an unsorted collection.  
	//So use a stable sort to sort by first column and second column so 
	//they are in a clean order ready to go into CSR format.
	stable_sort(edges.begin(), edges.end(), compareSecondColumn);
	cout << "Halfway done sorting..." << endl;
	stable_sort(edges.begin(), edges.end(), compareFirstColumn);
	cout << "Finished sorting..." << endl;

	createCsrArrays();

	if (selection == 1) {
		cout << "Test run debugging.  Your CSR arrrays are: " << endl;
		cout << "weights: ";
		for (int i = 0; i < numEdges; i++) {
			cout << graphWeights[i] << " ";
		}
		cout << endl;
		cout << "columns: ";
		for (int i = 0; i < numEdges; i++) {
			cout << columns[i] << " ";
		}
		cout << endl;
		cout << "row: ";
		for (int i = 0; i < numNodes + 1; i++) {
			cout << rows[i] << " ";
		}
		cout << endl;
	}


	int userSourceNode = 0;
	int userDestNode = 0;
	cout << "Which node would you like to search from: ";
	cin >> userSourceNode;

	//call our shortest path algorithm
	shortestPath(userSourceNode);

	do {
		cout << "Which node do you want to see weights for (-1 to exit): ";
		cin >> userDestNode;

		if (userDestNode == -1) {
			break;
		}
		if (userDestNode >= 0 && userDestNode < numNodes) {
			cout << "For node " << userDestNode << " the cost is " << smallestWeight[userDestNode] << endl;
		}
		else {
			cerr << "Error: That's no node with that ID!" << endl;
		}
		/* Ran out of time...
		cout << "Would you like to know the path taken along this route?(1 for yes): ";
		cin >> selection;

		//find the shortest path again, this time recording the nodes hopped along
		if (selection == 1) {
			//call overloaded Shortest path method
			shortestPath(userSourceNode, userDestNode);
		}
		*/
	} while (true);


	deleteArrays();

	pressAnyKeyToContinue();
}
