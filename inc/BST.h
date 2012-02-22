#ifndef CS240_BST_H
#define CS240_BST_H

#include <iostream>
#include "UnitTest.h"
using namespace std;

template<class Type>
class BST;

//!  BSTNode implements a binary search tree node
template<class Type>
class BSTNode 
{
		friend class BST<Type>;   //!< BST can access private members of BSTNode
	
	public:
		//!  Constructor
		BSTNode(const Type & v) :
		  value(v), left(NULL), right(NULL)
		{
		}
		
		//! Copy Constructor
		BSTNode(const BSTNode & other) : 
		  value(other.value),left(other.left),right(other.right)
		{
		}
		
	
		//!  Read-only public methods for use by clients of the BST class
		const Type & GetValue() const
		{
		  return value;
		}
	
		
	
		BSTNode * GetLeft()const
		{
		  return left;
		}
	
	
		BSTNode * GetRight()const
		{
		  return right;
		}
		
		//! Assignment operator 
		BSTNode & operator=(const BSTNode & other)
		{
			if(this!=&other)
			{
				value=other.value;
				left=other.left;
				right=other.right;
			}
			
			return *this;
		}

	
	private:
		Type value;  //!< value stored in the node
		BSTNode * left;     //!< pointer to the node's left child
		BSTNode * right;    //!< pointer to the node's right child
};


//!  BST implements a binary search tree
template<class Type>
class BST 
{
	
	public:
	
		//!  No-arg constructor.  Initializes an empty BST
		BST();
	
	
		//!  Copy constructor.  Makes a complete copy of its argument
		BST(const BST & other);
	
	
		//!  Destructor
		~BST();
	
	
		//!  Assignment operator.  Makes a complete copy of its argument
		//!  @return Reference to oneself
		BST& operator =(const BST & other);
	

    /**
     *  Unit test for this class
     *  
     *  @param os The output stream to write test results
     *
     *  @return true if all tests passed; false otherwise
     */
    static bool Test (ostream & os);

	
		//!  @return a pointer to the root node of the tree, or NULL if the tree is empty.
		//!  @note This is useful for BST clients that need to traverse the tree.)
		BSTNode<Type> * GetRoot()const;
	
	
		//!  @return true if the BST is empty, or false if the BST is not empty
		bool IsEmpty() const;
	
	
		//!  Removes all values from the BST
		void Clear();
	
	
		//!  @return the number of values in the BST
		int GetSize() const;
	
	
		//!  Inserts value v into the BST
		//!  
		//!  @param v The new value being inserted
		//!
		//!  @return a pointer to the newly inserted node, or NULL if v was already
		//!          in the tree (i.e., NULL is used to indicate a duplicate insertion)
		BSTNode<Type> * Insert(const Type & v);
	
	
		//!  Searches the tree for value v
		//!  
		//!  @param v The new value being searched for
		//!
		//!  @return a pointer to the node containing v, or NULL if v is not in the tree
		BSTNode<Type> * Find(const Type & v) const;
	
	
		//! @NOTE: YOU ARE NOT REQUIRED TO IMPLEMENT THE Remove METHOD BELOW
		//!        (BUT YOU CAN IF YOU WANT TO)
		//!
		//!  Removes value v from the tree
		//!  
		//!  @param v The value being removed from the tree
		//!
		//!  @return true if v was removed from the tree, or false if v was not in the tree
		//bool Remove(const Type & v);
	
	private:
    BSTNode<Type>* root; //!< The root node of this BST
    int size;      //!< The size of this BST

    //! Creates a deep copy of this BST. Use with copy constructor and
    //! assignment operator.
    //!
    //! @param bstCopy A reference to the BST to copy.
    //!
    //! @return A reference to this BST. 
    BST& copy (const BST & bstCopy);

    //! Recursive method for deep copy method.
    //!
    //! @param node The current node to duplicate
    //!
    //! @return The pointer to the duplicated BSTNode
    BSTNode<Type>* recursiveCopy (BSTNode<Type>* node);

    //! Deallocates object memory. Use with destructor and assignment operator.
    void freeBST (BSTNode<Type>* node);
};


template<class Type>
BST<Type>::BST() : root(NULL), size(0) {
}

template<class Type>
BST<Type>::BST(const BST<Type> & other) {
  copy(other);
}

template<class Type>
BST<Type>::~BST() {
  freeBST(root);
  root = NULL;
}

template<class Type>
BST<Type>& BST<Type>::operator = (const BST<Type> & other) {
  freeBST(root);
  root = NULL;
  size = 0;  
  return copy(other);
}

template<class Type>
bool BST<Type>::Test (ostream & os) {
  bool success = true;

  Type myType;

  BST<Type> bst;
  TEST(bst.IsEmpty() == true);

  bst.Insert(myType);
  TEST(bst.GetSize() == 1);

  return success;
}


template<class Type>
BSTNode<Type> * BST<Type>::GetRoot() const {
  return root;
}

template<class Type>
bool BST<Type>::IsEmpty() const {
  return (0 == size);
}

template<class Type>
void BST<Type>::Clear() {
  freeBST(root);
  root = NULL;
  size = 0;
}

template<class Type>
int BST<Type>::GetSize() const {
  return size;
}

template<class Type>
BSTNode<Type> * BST<Type>::Insert(const Type & v) {
  BSTNode<Type>* current = root;
  BSTNode<Type>* newNode;

  while (NULL != current) {
    if (v < current->value) {
      // add v to the left node
      if (NULL == current->left) {
        current->left = new BSTNode<Type>(v);
        newNode = current->left;
        break; 
      }
      current = current->left;
    } else if (current->value < v) {
      // add v to the right node
      if (NULL == current->right) {
        current->right = new BSTNode<Type>(v);
        newNode = current->right;
        break;
      }
      current = current->right;
    } else { // v already in tree
      return NULL;
    }
  }

  // BST was originally empty 
  if (NULL == root) {
    root = new BSTNode<Type>(v);
    newNode = root;
  }

  size++;
  return newNode;
}

template<class Type>
BSTNode<Type> * BST<Type>::Find(const Type & v) const {
  BSTNode<Type>* found = root;

  while (NULL != found) {
    if (v < found->value) {
      found = found->left;
    } else if (found->value < v) {
      found = found->right;
    } else {
      break;
    }
  } 
  return found;
}

//template<class Type>
//bool BST::Remove(const Type & v) { size--; return true; }

template<class Type>
BST<Type>& BST<Type>::copy (const BST<Type> & bstCopy) {
  if (this != &bstCopy) {
    root = recursiveCopy(bstCopy.root);
    size = bstCopy.size;    
  }
  return *this;
}

template<class Type>
BSTNode<Type>* BST<Type>::recursiveCopy (BSTNode<Type>* node) {
  BSTNode<Type>* nodeCopy; 
  if (NULL == node) { return NULL; }
  nodeCopy = new BSTNode<Type>(node->value);
  if (NULL != node->left) {
    nodeCopy->left = recursiveCopy(node->left);
  }
  if (NULL != node->right) {
    nodeCopy->right = recursiveCopy(node->right);
  }
  return nodeCopy;
}

template<class Type>
void BST<Type>::freeBST (BSTNode<Type>* node) {
  if (NULL == node) {
    return;
  }
  // freeBST left subtree
  freeBST(node->left);
  
  // freeBST right subtree
  freeBST(node->right);

  // freeBST node
  delete node;
}

#endif
