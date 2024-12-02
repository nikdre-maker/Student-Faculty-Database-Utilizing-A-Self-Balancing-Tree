//Names: Tyler Zastrow, Nikita Dreizin
//Student Ids: 2407642, 2403124
//Email: zastrow@chapman.edu, dreizin@chapman.edu
//Course: CPSC 350
//Assignment: PA5 Lazy BST
// Templated implementation of a node for the BST 
#ifndef TREE_NODE_H
#define TREE_NODE_H

#include <cstdlib>
#include <iostream>
using namespace std;

template <typename T> class TreeNode {
public:
  TreeNode(T &d);
  virtual ~TreeNode();
  T& getData();
  int getDepth();

  template <typename S> friend class LazyBST;

private:
  TreeNode<T> *m_left;
  TreeNode<T> *m_right;
  T m_data;
  int m_iLeftSubTreeDepth;  // depth of subtree anchored to this nodes left
  int m_iRightSubTreeDepth; // right
};

// changed parameter to reference 
template <typename T> TreeNode<T>::TreeNode(T &d) {
  m_left = NULL;
  m_right = NULL;
  m_data = d;
  m_iLeftSubTreeDepth = m_iRightSubTreeDepth = 0;
}

template <typename T> TreeNode<T>::~TreeNode() {
  if (m_left != NULL) {
    delete m_left;
  }

  if (m_right != NULL) {
    delete m_right;
  }
}
// changed to reference so I can directly access objects and update them 
template <typename T> 
T& TreeNode<T>::getData() { return m_data; }

// gets max depth of the BST left and right subtrees
template <typename T> int TreeNode<T>::getDepth() 
{
  if (m_iLeftSubTreeDepth > m_iRightSubTreeDepth)
    return m_iLeftSubTreeDepth;
  else
    return m_iRightSubTreeDepth;
}

#endif