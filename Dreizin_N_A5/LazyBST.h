//Names: Tyler Zastrow, Nikita Dreizin
//Student Ids: 2407642, 2403124
//Email: zastrow@chapman.edu, dreizin@chapman.edu
//Course: CPSC 350
//Assignment: PA5 LazyBST
// Templated implementation of a lazy BST
#ifndef BST_H
#define BST_H
#include "TreeNode.h"

template <typename T> class LazyBST {
public:
  LazyBST();
  virtual ~LazyBST();
  int getSize();
  void insertNoBalance(T &d);
  void remove(T &d);
  bool contains(T &d);
  TreeNode<T>* find(int id);
  TreeNode<T>* findHelper(TreeNode<T> *root, int id); 
  T getMin();
  T getMax();
  void printTreeInOrder();
  void printTreeGraphical();
  bool isUnbalanced(TreeNode<T> *m_root);
  LazyBST<T> *rebalanceTree();
  void rebalanceTreeInPlace();
  void insert(T &d);

  void copyToArray(T pArray[], TreeNode<T> *subTreeRoot, int *index);
  void insertMedians(T pArray[], LazyBST<T> *newBST, int startIndex, int endIndex);
  void deleteTree(TreeNode<T> *node);


private:
  TreeNode<T> *m_root;
  int m_size;
  void insertHelper(TreeNode<T> *&subTreeRoot, TreeNode<T> *newNode);
  bool containsHelper(TreeNode<T> *subTreeRoot, TreeNode<T> *target);
  T getMinHelper(TreeNode<T> *subTreeRoot);
  T getMaxHelper(TreeNode<T> *subTreeRoot);
  void printTreeInOrderHelper(TreeNode<T> *subTreeRoot);
  void printTreeGraphicalHelper(TreeNode<T> *subTreeRoot, int Level);
  void findTarget(T key, TreeNode<T> *&target, TreeNode<T> *&parent);
  TreeNode<T> *getSuccessor(TreeNode<T> *rightChild);
  int index = 0;
};

template <typename T> LazyBST<T>::LazyBST() {
  m_root = NULL;
  m_size = 0;
}

template <typename T> LazyBST<T>::~LazyBST() {
  if (m_root != NULL) {
    delete m_root;
  }
}

template <typename T> int LazyBST<T>::getSize() { return m_size; }

// made an insert function that doesn't call rebalance that can be used with the methods
template <typename T> void LazyBST<T>::insertNoBalance(T &d) {
  TreeNode<T> *newNode = new TreeNode<T>(d);
  insertHelper(m_root, newNode);
  ++m_size;
}

// changed parameter to reference as to not take a copy of the object, every insert checks for proper balance
template <typename T> void LazyBST<T>::insert(T &d) {
  insertNoBalance(d);
  if (isUnbalanced(m_root)) {
    rebalanceTree();
  }
}

template <typename T>
void LazyBST<T>::insertHelper(TreeNode<T> *&subTreeRoot, TreeNode<T> *newNode) {

  if (subTreeRoot == NULL) {
    subTreeRoot = newNode;
    return;
    // depth of a leaf node is 0, initialize by node constructor
  }

  if (newNode->m_data < subTreeRoot->m_data) {
    insertHelper(subTreeRoot->m_left, newNode);
    // depth logic built into insert helper
    if (subTreeRoot->m_iLeftSubTreeDepth == 0)
      subTreeRoot->m_iLeftSubTreeDepth = 1;
    else
      subTreeRoot->m_iLeftSubTreeDepth = subTreeRoot->m_left->getDepth() + 1;
  } else {

    insertHelper(subTreeRoot->m_right, newNode);
    // same for right subtree
    if (subTreeRoot->m_iRightSubTreeDepth == 0)
      subTreeRoot->m_iRightSubTreeDepth = 1;
    else
      subTreeRoot->m_iRightSubTreeDepth = subTreeRoot->m_right->getDepth() + 1;
  }
}

template <typename T> void LazyBST<T>::remove(T &d) {
  // check if tree is empty
  if (m_root == NULL) {
    return; 
  }
  TreeNode<T> *target = NULL;
  TreeNode<T> *parent = NULL;
  target = m_root;
  findTarget(d, target, parent);
  if (target == NULL) { // value doesn't exist
    return;
  }
  if (target->m_left == NULL && target->m_right == NULL) { // it's a leaf
    if (target == m_root) { // leaf we found is the root
      m_root = NULL;
    } else { // leaf isn't the root
      if (target == parent->m_left) {
        parent->m_left = NULL;
      } else {
        parent->m_right = NULL;
      }
    }
  } else if (target->m_left != NULL && target->m_right != NULL) { // 2 child
                                                                  // case
    TreeNode<T> *suc = getSuccessor(target->m_right);
    T value = suc->m_data;
    remove(value);
    target->m_data = value;
  } else {              // 1 child case
    TreeNode<T> *child; // the thing to replace the target with
    // which side is the child on?
    if (target->m_left != NULL) { // child on left
      child = target->m_left;
    } else { // child is on the right
      child = target->m_right;
    }
    if (target == m_root) {
      m_root = child;
    } else { // the thing to delete isn't the root
      if (target == parent->m_left) {
        parent->m_left = child;
      } else {
        parent->m_right = child;
      }
    }
  }
  --m_size;
}

// changed parameter to reference 
template <typename T> bool LazyBST<T>::contains(T &d) {
  TreeNode<T> *newNode = new TreeNode<T>(d);
  bool ret = containsHelper(m_root, newNode);
  delete newNode;
  return ret;
}


template <typename T>
bool LazyBST<T>::containsHelper(TreeNode<T> *subTreeRoot, TreeNode<T> *target) {
  if (subTreeRoot == NULL) {
    return false;
  } else if (target->m_data < subTreeRoot->m_data) {
    return containsHelper(subTreeRoot->m_left, target);
  } else if (target->m_data > subTreeRoot->m_data) {
    return containsHelper(subTreeRoot->m_right, target);
  } else {
    return true;
  }
}

template <typename T>
TreeNode<T>* LazyBST<T>::find(int id) {
  return findHelper(m_root, id);
}

// find method that finds an node based of ID, returns a pointer to the node
template <typename T>
TreeNode<T>* LazyBST<T>::findHelper(TreeNode<T>* subTreeRoot, int id) {
  if (subTreeRoot == NULL) {
    return NULL;
  } else if (id < subTreeRoot->m_data.getID()) {
    return findHelper(subTreeRoot->m_left, id);
  } else if (id > subTreeRoot->m_data.getID()) {
    return findHelper(subTreeRoot->m_right, id);
  } else {
    return subTreeRoot; 
  }
}

template <typename T> T LazyBST<T>::getMin() {
  // what if the tree is empty?
  if (m_root == NULL) {
    return; 
  }
  return getMinHelper(m_root);
}

template <typename T> T LazyBST<T>::getMinHelper(TreeNode<T> *subTreeRoot) {
  if (subTreeRoot->m_left == NULL) {
    return subTreeRoot->m_data;
  } else {
    return getMinHelper(subTreeRoot->m_left);
  }
}

template <typename T> T LazyBST<T>::getMax() {
  // what if the tree is empty?
  if (m_root == NULL) {
    return; 
  }
  return getMaxHelper(m_root);
}

template <typename T> T LazyBST<T>::getMaxHelper(TreeNode<T> *subTreeRoot) {
  if (subTreeRoot->m_right == NULL) {
    return subTreeRoot->m_data;
  } else {
    return getMaxHelper(subTreeRoot->m_right);
  }
}

template <typename T> void LazyBST<T>::printTreeInOrder() {
  if (m_root != NULL) {
    printTreeInOrderHelper(m_root);
  }
  else {
    cout << "No records found." << "\n";
  }
}

// method to print out the LazyBST
template <typename T>
void LazyBST<T>::printTreeInOrderHelper(TreeNode<T> *subTreeRoot) {
  if (subTreeRoot->m_left != NULL) {
    printTreeInOrderHelper(subTreeRoot->m_left);
  }

  cout << subTreeRoot->m_data; 

  if (subTreeRoot->m_right != NULL) {
    printTreeInOrderHelper(subTreeRoot->m_right);
  }
}

template <typename T> void LazyBST<T>::printTreeGraphical() {
  printTreeGraphicalHelper(m_root, 0);
}

// created print method to ensure LazyBST is balancing out properly, when called prints LazyBST left to right
template <typename T>
void LazyBST<T>::printTreeGraphicalHelper(TreeNode<T> *subTreeRoot, int Level) {
  if (subTreeRoot == NULL)
    return;

  if (subTreeRoot->m_right != NULL)
    printTreeGraphicalHelper(subTreeRoot->m_right, Level + 1);

  for (int i = 0; i < Level; i++)
    cout << "          ";

  cout << subTreeRoot->m_data; 

  if (subTreeRoot->m_left != NULL)
    printTreeGraphicalHelper(subTreeRoot->m_left, Level + 1);

  return;
}

template <typename T>
void LazyBST<T>::findTarget(T key, TreeNode<T> *&target, TreeNode<T> *&parent) {
  while (target != NULL && target->m_data != key) {
    parent = target;
    if (key < target->m_data) {
      target = target->m_left;
    } else {
      target = target->m_right;
    }
  }
}

template <typename T>
TreeNode<T> *LazyBST<T>::getSuccessor(TreeNode<T> *rightChild) {
  while (rightChild->m_left != NULL) {
    rightChild = rightChild->m_left;
  }
  return rightChild;
}

// method checks for an unbalanced LazyBST after every insertion 
template <typename T> bool LazyBST<T>::isUnbalanced(TreeNode<T> *m_root) {
  // assuming root never null
  if ((m_root->m_iLeftSubTreeDepth == 1 && m_root->m_iRightSubTreeDepth == 2) ||
      (m_root->m_iLeftSubTreeDepth == 2 && m_root->m_iRightSubTreeDepth == 1)) {
    return false;
  }

  // assuming we rebalance when one depth is zero and other depth is > 1
  if (m_root->m_iLeftSubTreeDepth == 0) {
    if (m_root->m_iRightSubTreeDepth > 1)
      return true;
    else
      return false;
  }

  if (m_root->m_iRightSubTreeDepth == 0) {
    if (m_root->m_iLeftSubTreeDepth > 1)
      return true;
    else
      return false;
  }

  // our base rebalance condition 
  if (float(m_root->m_iLeftSubTreeDepth) / float(m_root->m_iRightSubTreeDepth) >
      1.5) {
    return true;
  }

  if (float(m_root->m_iRightSubTreeDepth) / float(m_root->m_iLeftSubTreeDepth) >
      1.5) {
    return true;
  }

  return false;
}

// method to rebalance the tree by creating a new LazyBST
template <typename T> LazyBST<T> *LazyBST<T>::rebalanceTree() {

  int BSTSize = getSize();
  if (BSTSize == 0) {
    return NULL;
  }

  // create a array with size of the old LazyBST
  T *valueArray = new T[BSTSize];
  int index = 0;

  // populate the array in acsending order with the LazyBST elements
  copyToArray(valueArray, m_root, &index);

  // populate the new LazyBST
  LazyBST<T> *newBST = new LazyBST<T>;
  int startIndex = 0;
  insertMedians(valueArray, newBST, startIndex, BSTSize - 1);

  // delete the previous tree 
  deleteTree(m_root);
  m_root = newBST->m_root;
  delete[] valueArray;
  return newBST;
}

// method that finds the median of the array, going left and right and inserts into the new LazyBST
template <typename T>
void LazyBST<T>::insertMedians(T pArray[], LazyBST<T> *newBST, int startIndex,
                           int endIndex) {
  // what is our base case -- when all values have been added
  if (startIndex > endIndex) {
    return;
  }
  // Find the median of our array and insert it as the root of our new LazyBST
  int median = (startIndex + endIndex) / 2;

  newBST->insertNoBalance(pArray[median]);

  // Find the median of all things left and insert
  insertMedians(pArray, newBST, startIndex, median - 1);

  // Find the median of all things right and insert
  insertMedians(pArray, newBST, median + 1, endIndex);
  // Do this until all values have been inserted

  return;
}

// copy node values in to array in ascending order
template <typename T>
void LazyBST<T>::copyToArray(T pArray[], TreeNode<T> *subTreeRoot, int *index) {

  if (subTreeRoot->m_left != NULL) {
    copyToArray(pArray, subTreeRoot->m_left, index);
  }

  pArray[*index] = subTreeRoot->m_data;
  (*index)++;

  if (subTreeRoot->m_right != NULL) {
    copyToArray(pArray, subTreeRoot->m_right, index);
  }
  return;
}

// method to delete the old LazyBST once a new balanced one has been made 
template <typename T> void LazyBST<T>::deleteTree(TreeNode<T> *node) {
  if (node == nullptr) {
    return;
  }
  deleteTree(node->m_left);
  node->m_left = NULL;
  deleteTree(node->m_right);
  node->m_right = NULL;
  delete node;
}

#endif

