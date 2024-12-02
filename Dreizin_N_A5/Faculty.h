//Names: Tyler Zastrow, Nikita Dreizin
//Student Ids: 2407642, 2403124
//Email: zastrow@chapman.edu, dreizin@chapman.edu
//Course: CPSC 350
//Assignment: PA5 Lazy BST
// Header file for faculty
#ifndef FACULTY_H
#define FACULTY_H
#include <string>

using namespace std; 

class Faculty{

private:
  int facultyID;
  string facultyName;
  string level;
  string department;
  int adviseeNum; 
  int* adviseeIDs = NULL; 

public:
  Faculty();
  ~Faculty(); 
  Faculty(int, string, string, string, int);
  int getID() const;
  string getName() const;
  string getLevel() const; 
  string getDepartment() const; 
  int* getAdviseeIDs() const; 
  int getSize() const; 
  void addAdviseeID(int, int); 
  void printAdviseeIDs(); 
  void removeFacultyAdvisee(int); 
  bool operator==(Faculty& faculty);
  bool operator!=(Faculty& faculty); 
  bool operator<(Faculty& faculty);
  bool operator>(Faculty& faculty); 
  void operator=(Faculty &faculty);
  friend ostream& operator<<(ostream& output, const Faculty& faculty);


};

#endif

