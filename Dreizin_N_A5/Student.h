//Names: Tyler Zastrow, Nikita Dreizin
//Student Ids: 2407642, 2403124
//Email: zastrow@chapman.edu, dreizin@chapman.edu
//Course: CPSC 350
//Assignment: PA5 Lazy BST
// Header file for student class
#ifndef STUDENT_H
#define STUDENT_H
#include <string> 

using namespace std; 

class Student{
  private:
  int studentID;
  string studentName; 
  string grade; 
  string major; 
  double gpa; 
  int advisor; 

  public:
  Student();
  ~Student(); 
  Student(int, string, string, string, double, int); 
  int getID() const;
  string getName() const;
  string getGrade() const;
  string getMajor() const;
  double getGpa() const;
  int getAdvisor() const; 
  void changeStudentAdvisor(int); 
  bool operator==(Student& student);
  bool operator!=(Student& student);
  bool operator<(Student& student); 
  bool operator>(Student& student); 
  friend ostream& operator<<(ostream& output, const Student& student); 

}; 

#endif