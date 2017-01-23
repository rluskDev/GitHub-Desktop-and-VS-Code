#include "BSTInt.h"
#include "BST.hpp"
#include "BSTIterator.hpp"

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <set>

using namespace std;
/**
 * A test driver for the BST int class and class template.
 * PA1 CSE 100 2016
 * Author: Christine Alvarado and YOU
 * TODO: Add more tests
 */
int main() {

  /* Create an STL vector of some ints */
  /*test*/
  vector<int> v;
  v.push_back(3);
  v.push_back(3);
  v.push_back(4);
  v.push_back(1);
  v.push_back(100);
  v.push_back(100);
  v.push_back(101);
  v.push_back(102);
  v.push_back(103);
  v.push_back(104);
  v.push_back(-33);
  v.push_back(-20);
  v.push_back(-25);
  v.push_back(-5);
  v.push_back(-39);
  v.push_back(-34);
  v.push_back(-38);
  v.push_back(-35);
  v.push_back(-36);


  /* Create an instance of BST holding int */
  BSTInt b;
  /* int storing previous item to test for duplicates since my only duplicates 
   * are right next to eachother in the array, this should work */
  int prevItem;
  /*Test empty. */
  if(!b.empty()) {
    cout << "BSTInt not correctly initialized as empty" << endl;
    return -1;
  }
  /*Test height while empty. */
  if(b.height() != -1) {
    cout << "height should be initialized to -1!" << endl;
    return -1;
  }

  // Could use: for(auto item : v) { instead of the line below
  prevItem = 0;
  for(int item : v) {
    bool pr = b.insert(item);
    if(! pr &&  prevItem != item) {
      cout << "Incorrect bool return value when inserting " << item 
        << endl;
      return -1;
    }
    prevItem = item;
  }

  /* Test empty, this time with a non-empty tree */
  if(b.empty()) {
    cout << "BSTInt says it's still empty, even though it isn't!" << endl;
    return -1;
  }

  /* Test size. */
  cout << "Size is: " << b.size() << endl;
  if(b.size() != v.size()-2) {
    cout << "... which is incorrect." << endl;
    return -1;
  }

  /* Test find return value. */
  // Test the items that are already in the tree
  for(int item : v) {
    if(!b.find(item)) {
      cout << "Incorrect return value when finding " << item << endl;
      return -1;
    }
  }

  /* Test height. */
  if(b.height() != 7) {
    cout << "Height should be 7 but it is " << b.height() << endl;
  }
  else
    cout << "Height is 7, which is correct!" << endl;


  // Test the template version of the BST  with ints 
  BST<int> btemp;
  prevItem = 0;

  /*Test empty. */
  if(!btemp.empty()) {
    cout << "BSTInt not correctly initialized as empty" << endl;
    return -1;
  }
  /*Test height while empty. */
  if(btemp.height() != -1) {
    cout << "height should be initialized to -1!" << endl;
    return -1;
  }

  for (int item : v) {
    // The auto type here is the pair of BSTIterator<int>, bool
    cout << "Inserting " << item << " into the int template-based BST...";
    auto p = btemp.insert(item);
    if (*(p.first) != item) {
      cout << "Wrong iterator returned.  "
        << "Expected " << item << " but got " << *(p.first) << endl;
      return -1;
    }
    if (!p.second && prevItem != item) {
      cout << "Wrong boolean returned.  Expected true but got " 
        << p.second << endl;
      return -1;
    }
    if(prevItem != item)
      cout << "success!" << endl;
    else
      cout << "duplicate, not inserted but that's OK!" << endl;
    prevItem = item;
  }

  /* Test size. */
  cout << "Size is: " << b.size() << endl;
  if(btemp.size() != v.size()-2) {
    cout << "... which is incorrect." << endl;
    return -1;
  }

  /* Test height. */
  if(btemp.height() != 7) {
    cout << "Height should be 7 but it is " << b.height() << endl;
  }
  else
    cout << "Height is 7, which is correct!" << endl;

  /* Test empty, this time with a non-empty tree */
  if(btemp.empty()) {
    cout << "BSTInt says it's still empty, even though it isn't!" << endl;
    return -1;
  }

  // Now test finding the elements we just put in
  for (int item: v) {
    cout << "Finding " << item << "...." << endl;
    BSTIterator<int> foundIt = btemp.find(item);
    if (*(foundIt) != item) {
      cout << "incorrect value returned.  Expected iterator pointing to "
        << item << " but found iterator pointing to " << *(foundIt) 
        << endl;
      return -1;
    }
    cout << "success!" << endl;
  }

  // Test the iterator: The iterator should give an in-order traversal

  // Sort the vector, to compare with inorder iteration on the BST
  sort(v.begin(),v.end());

  cout << "traversal using iterator..." << endl;
  auto vit = v.begin();
  auto ven = v.end();

  // This is equivalent to BSTIterator<int> en = btemp.end();
  auto en = btemp.end();
  auto en2 = btemp.end();
  //Test comparisons using null iterators
  if(!(en == en2)) {
    cout << "overloaded == is incorrect" <<endl;
    return -1;
  }
  if(en != en2) {
    cout << "overloaded != is incorrect" <<endl;
    return -1;
  }


  //This is equivalent to BST<int>::iterator it = btemp.begin();
  auto it = btemp.begin();
  prevItem = 0;   //using prevItem to track duplicates
  for(; vit != ven; ++vit) {
    if(! (it != en) || (it == en)) {
      cout << *it << "," << *vit 
        << ": Early termination of BST iteration." << endl;
      return -1;

    }
    cout << *it << endl;
    if(prevItem == *vit) //if duplicate found, increment vit
      ++vit;
    prevItem = *vit;
    if(*it != *vit) {
      cout << *it << "," << *vit 
        << ": Incorrect inorder iteration of BST." << endl;
      return -1;
    }
    ++it;
  }

  cout << "success!" << endl;


  cout << "All tests passed!" << endl;
  return 0;
}
