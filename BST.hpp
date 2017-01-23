#ifndef BST_HPP
#define BST_HPP
#include "BSTNode.hpp"
#include "BSTIterator.hpp"
#include <iostream>

template<typename Data>
class BST {

  public:

    /** define iterator as an aliased typename for BSTIterator<Data>. */
    typedef BSTIterator<Data> iterator;

    /** Default constructor.
      Initialize an empty BST.
      This is inlined because it is trivial.
      */
    BST() : root(nullptr), isize(0) {}


    /** Default destructor.
      Delete every node in this BST.
      */
    ~BST();

    /** Given a reference to a Data item, insert a copy of it in this BST.
     *  Return a pair where the first element is an iterator 
     *  pointing to either the newly inserted element or the element 
     *  that was already in the BST, and the second element is true if the 
     *  element was newly inserted or false if it was already in the BST.
     * 
     *  Note: This function should use only the '<' operator when comparing
     *  Data items. (should not use ==, >, <=, >=)  
     */
    std::pair<iterator, bool> insert(const Data& item);


    /** Find a Data item in the BST.
     *  Return an iterator pointing to the item, or pointing past
     *  the last node in the BST if not found.
     *  Note: This function should use only the '<' operator when comparing
     *  Data items. (should not use ==, >, <=, >=).  For the reasoning
     *  behind this, see the assignment writeup.
     */
    iterator find(const Data& item) const;


    /** Return the number of items currently in the BST.
    */ 
    unsigned int size() const;

    /** Return the height of the BST.
      height of a tree starts with root at height 0
      height of an empty tree is -1
      */ 
    int height() const;

    /** Return true if the BST is empty, else false.
    */
    bool empty() const;

    /** Return an iterator pointing to the first (smallest) item in the BST.
    */ 
    iterator begin() const;

    /** Return an iterator pointing past the last item in the BST.
    */
    iterator end() const;


  private:

    /** Pointer to the root of this BST, or 0 if the BST is empty */
    BSTNode<Data>* root;

    /** Number of Data items stored in this BST. */
    unsigned int isize;

    /** integer that tracks the max height, used in heightHelper 
     * needs to be marked mutable so that it can be changed in heightHelper, which
     * is a const function*/
    int mutable maxHeight;

    /**Height helper method that uses recursion (similar to deleteAll) to find
     * height. */
    void heightHelper(BSTNode<Data>* n, int height) const;

    /** Find the first element of the BST
     * Helper function for the begin method above.
     */ 
    static BSTNode<Data>* first(BSTNode<Data>* root);

    /** do a postorder traversal, deleting nodes
    */
    static void deleteAll(BSTNode<Data>* n);
};


// ********** Function definitions ****************


/** Default destructor.
  Delete every node in this BST.
  */
template <typename Data>
BST<Data>::~BST() {
  deleteAll(root);
}

/** Given a reference to a Data item, insert a copy of it in this BST.
 *  Return a pair where the first element is an iterator pointing to either the newly inserted
 *  element or the element that was already in the BST, and the second element is true if the 
 *  element was newly inserted or false if it was already in the BST.
 * 
 *  Note: This function should use only the '<' operator when comparing
 *  Data items. (should not use ==, >, <=, >=)  
 */
template <typename Data>
std::pair<BSTIterator<Data>, bool> BST<Data>::insert(const Data& item) {
  if (!root) {
    root = new BSTNode<Data>(item);
    ++isize;
    iterator itr(root);
    return std::pair<BSTIterator<Data>, bool>(itr, true);
  }

  BSTNode<Data>* curr = root;
  bool changedCurr = true;
  while ((curr->left ||  curr->right) && changedCurr) {
    changedCurr = false;
    if (curr->left && item < curr->data) {
      curr = curr->left;
      changedCurr = true;
    }
    else if (curr->right && curr->data < item) {
      curr = curr->right;
      changedCurr = true;
    }
  }

  // Ready to insert
  BSTNode<Data>* newNode = new BSTNode<Data>(item);
  if (item < curr->data) {
    curr->left = newNode;
    newNode->parent = curr;
    ++isize;
    iterator itr(newNode);
    return std::pair<BSTIterator<Data>, bool>(itr, true);
  }
  else if (curr->data < item) {
    curr->right = newNode;
    newNode->parent = curr;
    ++isize;
    iterator itr(newNode);
    return std::pair<BSTIterator<Data>, bool>(itr, true);
  }
  else { 
    delete newNode;
    iterator itr(curr);
    return std::pair<BSTIterator<Data>, bool>(itr, false);
  }

}


/** Find a Data item in the BST.
 *  Return an iterator pointing to the item, or pointing past
 *  the last node in the BST if not found.
 *  Note: This function should use only the '<' operator when comparing
 *  Data items. (should not use ==, >, <=, >=).  For the reasoning
 *  behind this, see the assignment writeup.
 */
template <typename Data>
BSTIterator<Data> BST<Data>::find(const Data& item) const {
  BSTNode<Data>* curr = root; 
  while (curr) {
    if (curr->data < item) {
      curr = curr->right;
    }
    else if (item < curr->data) {
      curr = curr->left;
    }
    else {
      iterator itr(curr);
      return itr;
    }
  }
  iterator itr(curr);
  return itr;

}


/** Return the number of items currently in the BST.
*/ 
template <typename Data>
unsigned int BST<Data>::size() const
{
  return isize;
}

/** Return the height of the BST.
*/
template <typename Data> 
int BST<Data>::height() const
{
  int height = -1;
  maxHeight = -1;
  heightHelper(root, height);
  return maxHeight;
}

/**Height helper method that uses recursion (similar to deleteAll) to find
 * height. */
template <typename Data>
void BST<Data>::heightHelper(BSTNode<Data>* n, int height) const
{
  if(n) {
    height++;
    heightHelper(n->left, height);
    heightHelper(n->right, height);
  }
  if (height > maxHeight)
    maxHeight = height;
}

/** Return true if the BST is empty, else false.
*/ 
template <typename Data>
bool BST<Data>::empty() const
{
  return (!root);
}

/** Return an iterator pointing to the first (smallest) item in the BST.
*/ 
template <typename Data>
BSTIterator<Data> BST<Data>::begin() const
{
  return BSTIterator<Data>(first(root));
}

/** Return an iterator pointing past the last item in the BST.
*/
template <typename Data>
BSTIterator<Data> BST<Data>::end() const
{
  return BSTIterator<Data>(nullptr);
}

/** Find the first element of the BST
 * Helper function for the begin method above.
 */ 
  template <typename Data>
BSTNode<Data>* BST<Data>::first(BSTNode<Data>* root)
{
  while(root->left)
    root = root->left;
  return root;
}

/** do a postorder traversal, deleting nodes
*/
  template <typename Data>
void BST<Data>::deleteAll(BSTNode<Data>* n)
{
  if(n) {
    deleteAll(n->left);
    deleteAll(n->right);
    delete(n);
  }
}



#endif //BST_HPP
