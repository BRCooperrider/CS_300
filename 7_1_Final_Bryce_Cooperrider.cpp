//============================================================================
// Name        : 7_1_Final_Bryce_Cooperrider.cpp
// Author      : Bryce Cooperrider
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <stdlib.h>

using namespace std;

//========================================================
// Global definitions
//========================================================

const unsigned int DEFAULT_SIZE = 500;

// Structure to hold course information
struct Course {

	string courseId;
	string courseName;
	string preReq1;
	string preReq2;
	vector<string> preReqList;
};
//========================================================
// Hash Table class definition
//========================================================

class HashTable {

private:
	// Structure to hold courses
	struct Node {
		Course course;
		unsigned int key;
		Node *next;
		Node *prev;

		// Default constructor
		Node() {
			key = UINT_MAX;
			next = nullptr;
			prev = nullptr;
		}

		// Initialize with a course
		Node(Course aCourse) : Node() {
			course = aCourse;
			next = nullptr;
			prev = nullptr;
		}

		// Initialize with a course and a key
		Node(Course aCourse, unsigned int aKey) : Node(aCourse) {
			course = aCourse;
			key = aKey;
			next = nullptr;
			prev = nullptr;
		}
	};

	vector<Node> nodes;
	Node *head;
	Node *tail;

	unsigned int hash(int key);

public:
	HashTable();
	HashTable(unsigned int size);
	virtual ~HashTable();
	void Insert(Course course);
	void Print();
	Course Search(string courseId);
	unsigned int tableSize = DEFAULT_SIZE;
};

// Default constructor
HashTable::HashTable() {
	// Initialize node structure by resizing tableSize
	head = NULL;
	tail = NULL;
	nodes.resize(tableSize);
}

HashTable::HashTable(unsigned int size) {
	this->tableSize = size;
	nodes.resize(tableSize);
}

// Destructor
HashTable::~HashTable() {
	// Erase nodes beginning
	nodes.erase(nodes.begin());
}

// Calculate the hash of a given key
unsigned int HashTable::hash(int key) {

	HashTable(size);
	// Return key tableSize
	unsigned int hashVal = key % tableSize;
	return hashVal;
}

// Insert a course
void HashTable::Insert(Course course) {

	//hash function taking the 3 integers of the course
	unsigned int key = hash(stoi(course.courseId.substr(4)));

	//check to see if node exists
	if (nodes.at(key).key == UINT_MAX) {

		// Create a new node
		Node newNode = Node(course, key);

		//Add the new course to the node
		nodes.at(key) = newNode;
	}

	else {

		Node *currNode = &nodes.at(key);

		Node *newNode = new Node(course, key);

		while (currNode->next != NULL) {

			currNode = currNode->next;
		}

		currNode->next = newNode;
		nodes.resize(tableSize);
	}
}

// Print all courses
void HashTable::Print() {

	for (unsigned int i = 0; i < tableSize; i++) {

		Node *node = &nodes.at(i);

		if (node->key != UINT_MAX) {

			cout << node->course.courseId << ", " << node->course.courseName << endl;

			while (node->next != nullptr) {

				node = node->next;

				cout << node->key << node->course.courseId << ", " << node->course.courseName << endl;
			}
		}
	}
}

Course HashTable::Search(string courseId) {
	Course course;

	//Hash function to recall the correct bucket
	unsigned int key = hash(stoi(courseId.substr(4)));

	Node* node = &(nodes.at(key));

	if (node != nullptr && node->key != UINT_MAX && (node->course.courseId.compare(courseId)) == 0) {
		return node->course;
	}

	if (node == nullptr || node->key == UINT_MAX) {
		return course;
	}

	while (node != nullptr) {

		if (node->key != UINT_MAX && node->course.courseId.compare(courseId) == 0) {

			return node->course;
		}
		node = node->next;
	}

	return course;
}

// Function to load courses
void loadCourses(string csvPath, HashTable* courseTable) {

Course course;
cout << "Loading csv file" << endl;

ifstream file;
string line;

try {
	file.open(csvPath);

	if (file.is_open()) {

		while (file.good()) {

			cout << line << endl;

			while (getline(file, line)) {

				stringstream ss(line);

				string courseId;
				string courseName;
				string preReq1;
				string preReq2;

				getline(ss, courseId, ',');
				getline(ss, courseName, ',');
				getline(ss, preReq1, ',');
				getline(ss, preReq2, ',');

				course.courseId = courseId;
				course.courseName = courseName;
				course.preReq1 = preReq1;
				course.preReq2 = preReq2;

				course.preReqList.push_back(preReq1);
				course.preReqList.push_back(preReq2);

				courseTable->Insert(course);
				ss.clear();

				cout << course.courseId << " " << course.courseName << " " << course.preReq1 << " " << course.preReq2 << endl;
			}
		}
	}
}
catch(exception &e) {
	cerr << e.what() << endl;
}

}

//Function to display courses
void displayCourse(Course aCourse) {

	cout << aCourse.courseId << ", " << aCourse.courseName << endl;
	cout << "Prerequisites: ";

	if (aCourse.preReq1.empty() && aCourse.preReq2.empty()) {

		cout << "None" << endl;
	}

	else {

		cout << aCourse.preReq1 << ", " << aCourse.preReq2 << endl;

	}

	cout << endl;
}

void convertCase(string &toConvert) {

	for (unsigned int i = 0; i < toConvert.length(); i++) {

		if (isalpha(toConvert[i])) {

			toConvert[i] = toupper(toConvert[i]);
		}
	}
}

int main(int argc, char* argv[]) {

	// Process command line arguments
	string csvPath, aCourseKey;

	switch(argc) {
	case 2:
		csvPath = argv[1];
		break;
	case 3:
		csvPath = argv[1];
		aCourseKey = argv[2];
		break;
	default:
		csvPath = "Project_Sample_Input.csv";
	}

	// Define a hash tale to hold the courses
	HashTable* courseTable = new HashTable();

	Course course;
	bool goodInput;
	int choice = 0;

	while (choice != 9) {
		cout << "Menu:" << endl;
		cout << "1. Load Data Structure" << endl;
		cout << "2. Print Course List" << endl;
		cout << "3. Print Course" << endl;
		cout << "9. Exit" << endl;
		cout << "Enter choice: " << endl;

		aCourseKey = "";
		string anyKey;
		choice = 0;

		try {

			cin >> choice;

			if ((choice > 0 && choice < 4) || (choice == 9)) {
				goodInput = true;
			}
			else {
				goodInput = false;
				throw 1;
			}

			switch (choice) {
			case 1:

				loadCourses(csvPath, courseTable);

				break;

			case 2:
				courseTable->Print();

				break;

			case 3:

				cout << "What course do you want to know about?" << endl;
				cin >> aCourseKey;

				convertCase(aCourseKey);

				course = courseTable->Search(aCourseKey);

				if (!course.courseId.empty()) {
					displayCourse(course);
				}
				else {
					cout << "Course ID " << aCourseKey << " not found" << endl;
				}

				break;

			case 9:

				break;

			default:

				throw 2;
			}
		}

		catch(int err) {

			cout << "Please check your input" << endl;
		}

		cin.clear();
		cin.ignore();

	}
	cout << "Good bye" << endl;

	return 0;

}
