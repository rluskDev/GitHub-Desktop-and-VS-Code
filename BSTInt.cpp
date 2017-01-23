
#include "BSTInt.h"

/* Function definitions for a int-based BST class */
//test publish changes
/** Default destructor.
  Delete every node in this BST.
  */
BSTInt::~BSTInt()
{
  deleteAll(root);
}

/** Given a reference to a Data item, insert a copy of it in this BST.
 *  Return  true if the item was added to this BST
 *  as a result of this call to insert,
 *  false if an item equal to this one was already in this BST.
 *  Note: This function should use only the '<' operator when comparing
 *  Data items. (should not use ==, >, <=, >=)  For the reasoning
 *  behind this, see the assignment writeup.
 */

bool BSTInt::insert(int item)
{
  if (!root)
  {
    root = new BSTNodeInt(item);
    ++isize;
    return true;
  }
  BSTNodeInt *curr = root;
  bool changedCurr = true;
  while ((curr->left || curr->right) && changedCurr)
  {
    changedCurr = false;
    if (curr->left && item < curr->data)
    {
      curr = curr->left;
      changedCurr = true;
    }
    else if (curr->right && curr->data < item)
    {
      curr = curr->right;
      changedCurr = true;
    }
  }

  // Ready to insert
  BSTNodeInt *newNode = new BSTNodeInt(item);
  if (item < curr->data)
  {
    curr->left = newNode;
    newNode->parent = curr;
  }
  else if (curr->data < item)
  {
    curr->right = newNode;
    newNode->parent = curr;
  }
  else
  {
    delete newNode;
    return false;
  }
  ++isize;
  return true;
}

/** Find a Data item in the BST.
 *  Return true if the item is in the BST or false otherwise
 *  Note: This function should use only the '<' operator when comparing
 *  Data items. (should not use ==, >, <=, >=).  For the reasoning
 *  behind this, see the assignment writeup.
 */
bool BSTInt::find(int item) const
{
  BSTNodeInt *curr = root;
  while (curr)
  {
    if (curr->data < item)
    {
      curr = curr->right;
    }
    else if (item < curr->data)
    {
      curr = curr->left;
    }
    else
    {
      return true;
    }
  }
  return false;
}

/** Return the number of items currently in the BST.
*/
unsigned int BSTInt::size() const
{
  return isize;
}

/** Return the height of the BST.
  Height of tree with just root node is 0
  */
int BSTInt::height() const
{
  int height = -1;
  maxHeight = -1;
  heightHelper(root, height);
  return maxHeight;
}

/**Height helper method that uses recursion (similar to deleteAll) to find
 * height. */
void BSTInt::heightHelper(BSTNodeInt *n, int height) const
{
  if (n)
  {
    height++;
    heightHelper(n->left, height);
    heightHelper(n->right, height);
  }
  if (height > maxHeight)
    maxHeight = height;
}

/** Return true if the BST is empty, else false. 
*/
bool BSTInt::empty() const
{
  return (!root);
}

/** do a postorder traversal, deleting nodes
 * This is a helper for the destructor
 * This method is static because it acts on BSTNodeInts
 *   and not on the BSTInt object directly.
 */
void BSTInt::deleteAll(BSTNodeInt *n)
{
  if (n)
  {
    deleteAll(n->left);
    deleteAll(n->right);
    delete (n);
  }
}
