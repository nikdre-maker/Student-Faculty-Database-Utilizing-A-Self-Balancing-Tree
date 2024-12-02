//Names: Tyler Zastrow, Nikita Dreizin
//Student Ids: 2407642, 2403124
//Email: zastrow@chapman.edu, dreizin@chapman.edu
//Course: CPSC 350
//Assignment: PA5 Lazy BST
// File makes a student object and all relevent getters and overloaded operators
#include <iostream>
#include "Student.h"

using namespace std; 

// default constructor
Student::Student(){
  int studentID;
  string studentName; 
  string grade; 
  string major; 
  double gpa;
  int advisor; 
}

//default destructor
Student::~Student(){

}

// overloaded constructor
Student::Student(int ID, string name, string gradeInput, string majorInput, double gpaInput, int advisorInput) {
  studentID = ID; 
  studentName = name; 
  grade = gradeInput;
  major = majorInput; 
  gpa = gpaInput; 
  advisor = advisorInput; 
}

// getters for private variables

int Student::getID() const {
  return studentID;
}

string Student::getName() const {
  return studentName;
}

string Student::getGrade() const {
  return grade;
}

string Student::getMajor() const {
  return major;
}

double Student::getGpa() const {
  return gpa;
}

int Student::getAdvisor() const {
  return advisor; 
}

void Student::changeStudentAdvisor(int facultyID) {
  advisor = facultyID; 
}

// overloaded operators for the BST
bool Student::operator==(Student& student) {
  if (studentID == student.studentID) {
    return true; 
  }
  else {
    return false; 
  }
}

bool Student::operator!=(Student& student) {
  if (studentID != student.studentID) {
    return true;
  }
  else {
    return false; 
  }
}


bool Student::operator<(Student& student) {
  if (studentID < student.studentID) {
    return true;
  }
  else {
    return false; 
  }
}

bool Student::operator>(Student& student) {
  if (studentID > student.studentID) {
    return true;
  }
  else {
    return false; 
  }
}

ostream& operator<<(ostream &output, const Student& student) {
  output << "Student ID: " << student.getID();
  output << " Student Name: " << student.getName();
  output << " Student GPA: " << student.getGpa();
  output << " Student Major: " << student.getMajor(); 
  output << " Student advisor: " << student.getAdvisor();
  output << "\n"; 
  return output; 
}
