//Names: Tyler Zastrow, Nikita Dreizin
//Student Ids: 2407642, 2403124
//Email: zastrow@chapman.edu, dreizin@chapman.edu
//Course: CPSC 350
//Assignment: PA5 Lazy BST
// Header file for Database
#ifndef DATABASE_H
#define DATABASE_H
#include "LazyBST.h"
#include "Student.h"
#include "Faculty.h"

class Database {
private:
  LazyBST<Student> studentTable; 
  LazyBST<Faculty> facultyTable; 

public: 
  Database();
  ~Database();
  void printAllStudents();
  void printAllFaculty();
  void printOneStudent(int);
  void printOneFaculty(int); 
  void addStudent();
  void deleteStudent();
  void addFaculty();
  void deleteFaculty(); 
  void removeAdvisee(int, int);
  void changeAdvisor(int, int); 
  void exit(); 
  void runProgram(); 
  void displayMenu(); 
  bool inputCheck(); 
}; 

#endif