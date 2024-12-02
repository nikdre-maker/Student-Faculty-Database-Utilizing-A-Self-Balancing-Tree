//Names: Tyler Zastrow, Nikita Dreizin
//Student Ids: 2407642, 2403124
//Email: zastrow@chapman.edu, dreizin@chapman.edu
//Course: CPSC 350
//Assignment: PA5 Lazy BST
// File builds a faculty object will all relevant getters and overloaded operators
#include "Faculty.h"
#include <iostream>

using namespace std;

// default constructor
Faculty::Faculty() {
  facultyID = 0;
  facultyName = "";
  level = "";
  department = "";
  adviseeNum = 0;
  adviseeIDs = NULL;
}

// destructor
Faculty::~Faculty() {
  if (adviseeIDs != NULL)
    delete[] adviseeIDs;
  adviseeIDs = NULL;
}

// overloaded constructor
Faculty::Faculty(int ID, string name, string lev, string dep,
                 int adviseeCount) {
  facultyID = ID;
  facultyName = name;
  level = lev;
  department = dep;
  adviseeNum = adviseeCount;
  adviseeIDs = new int[adviseeNum];
}


// getters for private variables
int Faculty::getID() const { return facultyID; }

string Faculty::getName() const { return facultyName; }

string Faculty::getLevel() const { return level; }

string Faculty::getDepartment() const { return department; }

int* Faculty::getAdviseeIDs() const { return adviseeIDs; }

int Faculty::getSize() const { return adviseeNum; }

void Faculty::addAdviseeID(int ID, int position) { adviseeIDs[position] = ID; }

// method to print out advisee ID array
void Faculty::printAdviseeIDs() {
  for (int i = 0; i < getSize(); i++) {
    cout << "Advisee ID Number" << i << ": " << adviseeIDs[i];
    cout << "\n";
  }
}

// method to update the array once an advisee is removed
void Faculty::removeFacultyAdvisee(int studentID) {
  int position = 0;
  for (int i = 0; i < adviseeNum; i++) {
    if (adviseeIDs[i] == studentID) { // once position is found break
      position = i; 
      break; 
    }
  }
  // we "delete" the ID by shifting the ids over to the left 
  for (int i = position; i < adviseeNum -1; i++) {
    adviseeIDs[i] = adviseeIDs[i + 1]; 
  }
  adviseeNum--; 
}

// overloaded operators comparing of ID for BST ordering/printing 
bool Faculty::operator==(Faculty &faculty) { // based of ID
  if (facultyID == faculty.facultyID) {
    return true;
  } else {
    return false;
  }
}

bool Faculty::operator!=(Faculty &faculty) {
  if (facultyID != faculty.facultyID) {
    return true;
  }
  else {
    return false; 
  }
}

bool Faculty::operator<(Faculty &faculty) {
  if (facultyID < faculty.facultyID) {
    return true;
  } else {
    return false;
  }
}

bool Faculty::operator>(Faculty &faculty) {
  if (facultyID > faculty.facultyID) {
    return true;
  } else {
    return false;
  }
}

void Faculty::operator=(Faculty &faculty) {
  facultyID = faculty.getID();
  facultyName = faculty.getName();
  level = faculty.getLevel();
  department = faculty.getDepartment();
  adviseeNum = faculty.getSize();
  adviseeIDs = new int[adviseeNum];
  for (int i = 0; i < adviseeNum; i++) {
    adviseeIDs[i] = *(faculty.getAdviseeIDs() + i); 
  }
}

ostream &operator<<(ostream &output, const Faculty &faculty) { 
  output << " Faculty ID: " << faculty.getID();
  output << " Faculty Name: " << faculty.getName();
  output << " Faculty Level: " << faculty.getLevel();
  output << " Faculty Department: " << faculty.getDepartment();
  output << " Faculty advisee ID's: ";

  int *adviseeIDs = faculty.getAdviseeIDs();
  if (adviseeIDs != NULL) {
    for (int i = 0; i < faculty.getSize(); i++) {
      output << adviseeIDs[i] << " ";
    }
  }
  output << "\n";
  return output;
}