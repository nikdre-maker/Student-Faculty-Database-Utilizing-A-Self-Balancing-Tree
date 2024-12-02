//Names: Tyler Zastrow, Nikita Dreizin
//Student Ids: 2407642, 2403124
//Email: zastrow@chapman.edu, dreizin@chapman.edu
//Course: CPSC 350
//Assignment: PA5 Lazy BST
// File handles all of the databaes methods that the user will employ when using the program
#include <iostream>
#include <string>
#include <fstream>
#include "Database.h"
#include "LazyBST.h"
#include "Student.h"
#include "Faculty.h"

using namespace std;

Database::Database() {
  LazyBST<Student> studentTable; 
  LazyBST<Faculty> facultyTable; 
}

Database::~Database() {

}

// Print all students and their information (sorted by ascending id #)
void Database::printAllStudents() {
  studentTable.printTreeInOrder(); 
  cout << "\n";
}

// Print all faculty and their information (sorted by ascending id #)
void Database::printAllFaculty() {
  facultyTable.printTreeInOrder(); 
  cout << "\n"; 
}

// Find and display student information given the student id
void Database::printOneStudent(int studentID) {
    TreeNode<Student>* studentNode = studentTable.find(studentID);
    if (studentNode == NULL) { // make sure object exists
        cout << "Error! Student ID: " << studentID << " does not exist. " << "\n"; 
        return;
    }
    cout << studentNode->getData();
    cout << "\n"; 
}

// Find and display faculty information given the faculty id
void Database::printOneFaculty(int facultyID) {
    TreeNode<Faculty>* facultyNode = facultyTable.find(facultyID);
    if (facultyNode == NULL) { // make sure object exists
        cout << "Error! Faculty ID: " << facultyID << " does not exist. " << "\n";
        return; 
    }
    cout << facultyNode->getData();
    cout << "\n"; 
}

// Add a new student, method assumes that the string input will be a correct input of letters
void Database::addStudent() {
  cout << "Enter student ID: ";
  int id = 0; 
  cin >> id;
  if (inputCheck()) {
      return; 
  } 

  // check to see if ID already exists
  TreeNode<Student>* studentNode = studentTable.find(id);
  if (studentNode != NULL) {
    cout << "Error! Student ID: " << id << " already exists. Please try again. " << "\n";
    return; 
  }

  cout << "Enter student name: ";
  string name = ""; 
  cin >> name; 

  cout << "Enter student grade level: ";
  string grade = "";
  cin >> grade; 

  cout << "Enter student major: ";
  string major = ""; 
  cin >> major; 

  // if an int is entered first then invalid chars are entered, gpa defaults to the int and advisor ID is set to 0
  cout << "Enter student GPA: "; 
  double gpa = 0;
  cin >> gpa; 
  if (inputCheck()) {
    return; 
  }

  // provides option for student to be made without an advisor ID, as without it neither Student nor faculty would
  // be able to added as they'd be checking for existance for both
  cout << "Would you like to enter an Advisor ID? Click y or n " << "\n";
  char enterAdvisor = 'a';
  cin >> enterAdvisor;
  if (inputCheck()) {
      return; 
  } 
  int advisorID = 0; 

  if (enterAdvisor == 'y') {
    cout << "Enter advisor ID: ";
    cin >> advisorID; 
    if (inputCheck()) {
      return; 
    } 
    // check for object existance
    TreeNode<Faculty>* facultyNode = facultyTable.find(advisorID);
    if (facultyNode == NULL) { 
        cout << "Error! Faculty ID:" << advisorID << " does not exist in the faculty Database. " << "\n";
        cout << "The student has not been entered. Please try again. " << "\n"; 
        return; 
    }
  }
    else if (enterAdvisor == 'n') { // sets Advisor ID to zero when not specified 
        cout << "AdvisorID has been set to 0. " << "\n"; 
        advisorID = 0;
    }
  

  Student newStudent(id, name, grade, major, gpa, advisorID);
  studentTable.insert(newStudent);

}
// checks to see if our input is a valid input, if not aborts the entire command
bool Database::inputCheck() {
  if (cin.fail()) {
    cout << "Error! Invalid input entered. Command has been aborted. Please try again. " << "\n"; 
    cin.clear(); 
    cin.ignore(256, '\n');
    return true;
  }
  else {
    return false; 
  }
}

// Add a new faculty member 
void Database::addFaculty() {
  cout << "Be aware! To add student IDs to the faculty member students must first exist" << "\n"; 
  
  cout << "Enter faculty ID ";
  int id = 0; 
  cin >> id;
  // check to see if value entered is actually an int
  if (inputCheck()) {
    return; 
  } 

  // check to see if faculty ID already exists
  TreeNode<Faculty>* facultyNode = facultyTable.find(id); 
  if (facultyNode != NULL) {
    cout << "Error! Faculty ID: " << id << " already exists. Command has been aborted. Please try again" << "\n"; 
  }

  cout << "Enter faculty name ";
  string name = ""; 
  cin >> name;


  cout << "Enter faculty level ";
  string level = "";
  cin >> level;


  cout << "Enter faculty department ";
  string dep = "";
  cin >> dep;


  cout << "How many advisee ID's would you like to enter?" << "\n";
  cout << "If none enter zero. Be aware that no advisees may be added after a Faculty Member is made." << "\n"; // asgn prompt doesn't ask for an add advisee option
  int IDs = 0; 
  cin >> IDs; 
  if (inputCheck()) {
    return; 
  } 

  Faculty newFaculty(id , name, level, dep, IDs);
  cout << "Please add your advisee IDs ";
  int adviseeID = 0; 
  for (int i = 0; i < IDs; i++) {
    cout << "Type the ID ";
    cin >> adviseeID; 
    if (inputCheck()) {
      return; 
    } 
    TreeNode<Student>* studentNode = studentTable.find(adviseeID);
    if (studentNode == NULL) {
        cout << "Error! The student ID: " << adviseeID << " does not exist in the student database. " << "\n";
        cout << "Command has been aborted. Please try again. " << "\n";
        return; 
    }
    else {
        newFaculty.addAdviseeID(adviseeID, i); 
        //Assuming a student can only have one advisor, then once they're ID is added to the array their advisor ID must be updated
        changeAdvisor(adviseeID, id);
        // This can lead to multiple faculty holding a student ID in their list, but only the most recent one is listed as the advisor
        
    }
  }

  facultyTable.insert(newFaculty); 
}

// Delete a student given the ID
void Database::deleteStudent() {
  cout << "Enter a student ID of a student you would like to delete " << "\n"; 
  int studentID = 0; 
  cin >> studentID;
  if (inputCheck()) {
      return; 
  } 
  
  TreeNode<Student>* studentNode = studentTable.find(studentID); 
  // make sure it exists   
  if (studentNode == NULL) {
    cout << "StudentID: " << studentID << " does not exist" << "\n";
    return; 
  }
  
  // get the advisor ID from the student we plan to delete
  Student studentToDelete = studentNode->getData(); 
  int advisorID = studentToDelete.getAdvisor();

  // then need to remove the student using the remove function (if i had more time I'd adjust the remove function to be done of id)
  // so there would be no need to make a temporary student object that takes up memory
  studentTable.remove(studentToDelete);

  // now using the advisor ID we need to go to the advisor and update his array using our database remove advisee method
  removeAdvisee(studentID, advisorID); 
  
}

// Delete a faculty member given the ID
void Database::deleteFaculty() {
    cout << "Enter a faculty ID of a faculty member you would like to delete. " << "\n";
    int facultyID = 0;
    cin >> facultyID;
    if (inputCheck()) {
      return; 
    } 
     
    TreeNode<Faculty>* facultyNode = facultyTable.find(facultyID);
    if (facultyNode == NULL) { // make sure faculty exists
        cout << "Error! FacultyID: " << facultyID << " does not exist. " << "\n";
    }

    Faculty facultyToDelete = facultyNode->getData();

    facultyTable.remove(facultyToDelete);

    // need to go through the faculty's array, look at each student ID, find that student, and update his advisor ID to 0
    for (int i = 0; i < facultyToDelete.getSize(); i++) {
        int studentID = facultyToDelete.getAdviseeIDs()[i]; // getAdviseeIDs points to our array, then we access each element

        TreeNode<Student>* studentNode = studentTable.find(studentID);
        if (studentNode == NULL) {
            return;
        }
        else {
          studentNode->getData().changeStudentAdvisor(0);
        }
    }

}

// Change a student’s advisor given the student id and the new faculty id.
void Database::changeAdvisor(int studentID, int facultyID) {
  TreeNode<Student>* studentNode = studentTable.find(studentID);
  if (studentNode == NULL) {
    cout << "Error! StudentID: " << studentID << " does not exist." << "\n"; 
    return;
  }
  studentNode->getData().changeStudentAdvisor(facultyID); 
}

// remove an advisee given student id and the faculty it's being deleted at
void Database::removeAdvisee(int studentID, int facultyID) {
  TreeNode<Faculty>* facultyNode = facultyTable.find(facultyID); 
  if (facultyNode == NULL) {
    cout << "Error! FacultyID: " << facultyID << " does not exist." << "\n"; 
    return;
  }
  facultyNode->getData().removeFacultyAdvisee(studentID);
}


// Exit out the program, print out tables into a text file 
void Database::exit() {
    cout << "Exiting out the database" << "\n"; 
    string fileName = "runLog.txt";
    ofstream textFile;
    textFile.open(fileName);
    if (!textFile.is_open()) {
        cout << "Error file not open. " << "\n";
        return; 
    }
    // redirecting cout output to a file to not have to pass file handle down to each object
    streambuf *coutbuf = cout.rdbuf();
    cout.rdbuf(textFile.rdbuf());
    printAllStudents();
    printAllFaculty(); 
    cout.rdbuf(coutbuf); 

    // exit out of the program don't need to redirect cout back due to the last call 
    textFile.close(); 
    return; 
}

// runs the actual program 
void Database::runProgram() {
  cout << "Welcome to the Database" << "\n"; 
  displayMenu(); 
}

// displays menu with switch options until exit is called
void Database::displayMenu() {
  bool showMenu = true; 
  while (showMenu == true) {
    cout << "Please select an option: " << "\n"; 
    cout << "1. Print all Students." << "\n";
    cout << "2. Print all Faculty." << "\n";
    cout << "3. Find and print one student based of ID." << "\n";
    cout << "4. Find and print one faculty based of ID." << "\n";
    cout << "5. Add a new student" << "\n"; 
    cout << "6. Delete a student given the ID" << "\n";
    cout << "7. Add a new faculty member" << "\n";
    cout << "8. Delete a faculty member given the ID" << "\n";
    cout << "9. Change a students advisor given the student id and the new faculty id." << "\n"; 
    cout << "10. Remove an advisee from a faculty member given the IDs" << "\n"; 
    cout << "11. Exit" << "\n";
    int switchCase = 0; 
    cin >> switchCase; 
    // intialize new IDs every time the run program is called
    int studentID = 0;
    int facultyID = 0; 
    switch (switchCase) {
      case 1:
        printAllStudents(); 
        break;
      case 2:
        printAllFaculty();
        break;
      case 3: 
        cout << "Please enter a studentID " << "\n";
        cin >> studentID;
        if (inputCheck()) {
          break; 
        }
        printOneStudent(studentID); 
        break;
      case 4:
        cout << "Please enter a faculty ID " << "\n";
        cin >> facultyID; 
        if (inputCheck()) {
          break;
        }
        printOneFaculty(facultyID);
        break;
      case 5: 
        addStudent();
        break;
      case 6:
        deleteStudent();
        break;
      case 7:
        addFaculty();
        break;
      case 8:
        deleteFaculty(); 
        break;
      case 9: 
        cout << "Please enter the students ID: " << "\n";
        cin >> studentID; 
        if (inputCheck()) {
          break;
        }
        cout << "Please enter the new Faculty ID you would like to enter: " << "\n"; 
        cin >> facultyID;
        if (inputCheck()) {
          break;
        }
        changeAdvisor(studentID, facultyID);
        break;
      case 10:
        cout << "Please enter the facultys ID: " << "\n";
        cin >> facultyID;
        if (inputCheck()) {
          break;
        }
        cout << "Please enter the students ID you would like to remove: " << "\n";
        cin >> studentID; 
        if (inputCheck()) {
          break; 
        }
        removeAdvisee(studentID, facultyID); 
        break;
      case 11:
        showMenu = false; 
        exit(); 
        break;
    }
  }
}