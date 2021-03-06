/*! \file */ 
/*! \brief RedBlackTree.cpp.
 *
 *  Implements the functions from Tree class.
*/

#include "RedBlackTree.h"

/*! Constants*/
const int MinValue = -999999;

/*!
 * Class constructor
 * Initialize the red black tree
 *
 * @return => void
*/
template <class Comparable>
RedBlackTree<Comparable>::RedBlackTree( void )
{
	theLeaf = new RBTreeNode<Comparable>; // create a new leaf
	theLeaf->lChildPtr = theLeaf->rChildPtr = NULL;
	theLeaf->color = RBTreeNode<Comparable>::Black;

	m_root = new RBTreeNode<Comparable>(); // pseudo root
	m_root->lChildPtr = m_root->rChildPtr = theLeaf;
	m_root->color = RBTreeNode<Comparable>::Black;
	m_root->value = MinValue; // initialize
}

/*!
 * Method to swap the node color (applied in the split method)
 * swaps the colors of nodeptr, parentptr, and grandptr. 
 *
 * @param nodePtr 	=> node itself
 * @param parentPtr => parent node
 * @param grandPtr 	=> grandpa node
 *
 * @return => void
*/
template <class Comparable>
void RedBlackTree<Comparable>::swapColor( RBTreeNode<Comparable>*& nodePtr, RBTreeNode<Comparable>*& parentPtr, RBTreeNode<Comparable>*& grandPtr )
{
	/*! Node is black*/
	if ( nodePtr->color == RBTreeNode<Comparable>::Black )
		nodePtr->color = RBTreeNode<Comparable>::Red;
	/*! Node is red*/
	else if ( nodePtr->color == RBTreeNode<Comparable>::Red )
		nodePtr->color = RBTreeNode<Comparable>::Black;

	/*! Parent node is black*/
	if ( parentPtr->color == RBTreeNode<Comparable>::Black )
		parentPtr->color = RBTreeNode<Comparable>::Red;
	/*! Parent node is red*/
	else if ( parentPtr->color == RBTreeNode<Comparable>::Red )
		parentPtr->color = RBTreeNode<Comparable>::Black;

	/*! Grandpa node is black*/
	if ( grandPtr->color == RBTreeNode<Comparable>::Black )
		grandPtr->color = RBTreeNode<Comparable>::Red;
	/*! Grandpa node is red*/
	else if ( grandPtr->color == RBTreeNode<Comparable>::Red )
		grandPtr->color = RBTreeNode<Comparable>::Black;
}

/*!
 * Copy constructor
 * Initialize the red black tree
 *
 * @param nodePtr => old tree pointer
 *
 * @return => void
*/
template <class Comparable>
RedBlackTree<Comparable>::RedBlackTree( const RedBlackTree<Comparable>& old )
{
	nil = new RBTreeNode<Comparable>; // new node for the leaf
	nil->lChildPtr = nil->rChildPtr = nil;

	m_root = new RBTreeNode<Comparable>; // create the new node
	m_root->lChildPtr = m_root->rChildPtr = nil;
	*this = old; // set the new node to our old parameter
}

/*!
 * Assignment operator
 *
 * @param rhs => tree pointer
 *
 * @return => void
*/
template <class Comparable>
const RedBlackTree<Comparable>& RedBlackTree<Comparable>::operator=( const RedBlackTree<Comparable> & rhs )
{
	//! Check if the reference pointer it's a self assignment
	if ( this != &rhs )
	{
		//! Clear the memory
		reclaimMemory(m_root->rChildPtr);
		m_root->rChildPtr = theLeaf;

		//! Deep copy
		m_root->rChildPtr = clone(rhs.m_root->rChildPtr);
	}

	return *this; // return current tree object
}

/*!
 * Class destructor
 * realeases the allocated memory block
 *
 * @return => void
*/
template <class Comparable>
RedBlackTree<Comparable>::~RedBlackTree()
{
	//! Delete the tree itself
	reclaimMemory(m_root);

	//! Delete the leaf node
	delete theLeaf;

	//! Dele the root node
	delete m_root;
}

/*!
 * Insertion function
 * inserts a new node in the red black tree
 * it throws a bad_alloc exception if no enough space
 *
 * @param newNode => the value to the new node
 *
 * @return => void
*/
template <class Comparable>
void RedBlackTree<Comparable>::insert( Comparable newNode )
{
	//! References the root
	RBTreeNode<Comparable>* nodePtr = m_root->rChildPtr;

	//! References the pseudo root
	RBTreeNode<Comparable>* parentPtr = m_root;
	RBTreeNode<Comparable>* grandPtr = m_root;
	RBTreeNode<Comparable>* greatPtr = m_root;

	//! Check if the referee node is different from the leaf
	while ( nodePtr != theLeaf )
	{
		//! Check if both children are red
		if ( (nodePtr->lChildPtr->color == RBTreeNode<Comparable>::Red) && (nodePtr->rChildPtr->color == RBTreeNode<Comparable>::Red) )
		{
			//! Split the sub tree
			split(nodePtr, parentPtr, grandPtr, greatPtr);

			//! Change the pseudo root color
			m_root->color = RBTreeNode<Comparable>::Black;

			//! Change the real root color
			m_root->rChildPtr->color = RBTreeNode<Comparable>::Black;

			//! Change the leaf color
			theLeaf->color = RBTreeNode<Comparable>::Black;
		}

		//! Proceed a deep copy to the local pointers
		greatPtr = grandPtr;
		grandPtr = parentPtr;
		parentPtr = nodePtr;

		//! Check the new node value
		if ( newNode <= parentPtr->value )
			nodePtr = nodePtr->lChildPtr; //! LEFT
		else
			nodePtr = nodePtr->rChildPtr; // RIGHT
	}

	//! Check the new node value
	if ( newNode <= parentPtr->value )
	{
		//! It's smaller, so place in the left
		parentPtr->lChildPtr = new RBTreeNode<Comparable>(newNode, theLeaf, theLeaf, RBTreeNode<Comparable>::Black);
		nodePtr = parentPtr->lChildPtr;
	}
	else
	{
		//! It's bigger, so place in the right
		parentPtr->rChildPtr = new RBTreeNode<Comparable>(newNode, theLeaf, theLeaf, RBTreeNode<Comparable>::Black);
		nodePtr = parentPtr->rChildPtr;
	}

	//! Split the node
	split(nodePtr, parentPtr, grandPtr, greatPtr);

	//! Change the pseudo root color
	m_root->color = RBTreeNode<Comparable>::Black;

	//! Change the real root color
	m_root->rChildPtr->color = RBTreeNode<Comparable>::Black;

	//! Change the leaf color
	theLeaf->color = RBTreeNode<Comparable>::Black;
}

/*!
 * Remove function
 * removes a new node in the red black tree
 *
 * @param node => node's value to be removed
 *
 * @return => void
*/
template <class Comparable>
void RedBlackTree<Comparable>::remove( Comparable node )
{
	//! Temp node
	RBTreeNode<Comparable>* temp = new RBTreeNode<Comparable>;

    //! References the root (left)
	RBTreeNode<Comparable>* nodePtr = m_root->lChildPtr;

	//! References the pseudo root
	RBTreeNode<Comparable>* parentPtr = m_root;
	RBTreeNode<Comparable>* grandPtr = m_root;
	RBTreeNode<Comparable>* greatPtr = m_root;
}

/*!
 * Search function
 * search a new node in the red black tree
 *
 * @param node => node's value to be removed
 *
 * @return => void
*/
template <class Comparable>
const Comparable RedBlackTree<Comparable>::search( Comparable node )
{
	//! Set the nil node as the search parameter
	nil = new RBTreeNode<Comparable>; // new node for the leaf
	nil->value = node;

    //! References the root
	RBTreeNode<Comparable>* nodePtr = m_root->rChildPtr;

	//! Check if the referee node is different from the leaf
	while ( nodePtr != theLeaf )
	{
		//! Searched node is smaller than current node
        if ( node < nodePtr->value )
        {
            nodePtr = nodePtr->lChildPtr;
        }
        //! Searched node is bigger than current node
        else if ( nodePtr->value < node )
        {
            nodePtr = nodePtr->rChildPtr;
        }
        //! Current node is different from the searched
        else if ( nodePtr != nil )
        {
            return nodePtr->value;
        }
        //! Not found
        else
        {
            return ITEM_NOT_FOUND;
        }
    }

    return ITEM_NOT_FOUND;
}

/*!
 * Print trigger function
 *
 * @return => void
*/
template <class Comparable>
void RedBlackTree<Comparable>::print( void ) const
{
	//! Call the print function (encapsulation)
	print(m_root->rChildPtr, 0);
}

/*!
 * Right rotation function
 * rotates the node around its left child
 *
 * @param nodePtr 	=> the node itself (pointer)
 * @param parentPtr => the parent node (pointer)
 *
 * @return => void
*/
template <class Comparable>
void RedBlackTree<Comparable>::rightRotate( RBTreeNode<Comparable>*& nodePtr, RBTreeNode<Comparable>*& parentPtr )
{
	//! Temporaly variable to keep the left child
	RBTreeNode<Comparable>* temp = nodePtr->lChildPtr;

	//! Change the left child for the right's one
	nodePtr->lChildPtr = temp->rChildPtr;

	//! Check if it's the right child
	if ( parentPtr->rChildPtr == nodePtr )
	{
		//! The temporaly variable receive the right child
		parentPtr->rChildPtr = temp;
	}
	else
	{
		//! The temporaly variable receive the left child
		parentPtr->lChildPtr = temp;
	}

	//! Finalize the rotation
	temp->rChildPtr = nodePtr;
}

/*!
 * Left rotation function
 * rotates the node around its right child
 *
 * @param nodePtr 	=> the node itself (pointer)
 * @param parentPtr => the parent node (pointer)
 *
 * @return => void
*/
template <class Comparable>
void RedBlackTree<Comparable>::leftRotate( RBTreeNode<Comparable>*& nodePtr, RBTreeNode<Comparable>*& parentPtr )
{
	//! Temporaly variable to keep the right child
	RBTreeNode<Comparable>* temp = nodePtr->rChildPtr;

	//! Change the right child for the left's one
	nodePtr->rChildPtr = temp->lChildPtr;

	//! Check if it's the right child
	if ( parentPtr->rChildPtr == nodePtr )
	{
		//! The temporaly variable receive the right child
		parentPtr->rChildPtr = temp;
	}
	else // if were dealing with the left child
	{
		//! The temporaly variable receive the left child
		parentPtr->lChildPtr = temp;
	}

	//! Finalize the rotation
	temp->lChildPtr = nodePtr;
}

/*!
 * Split function
 * splits a 4_node
 *
 * @param nodePtr 	=> the node itself 	(pointer)
 * @param parentPtr => the parent node 	(pointer)
 * @param grandPtr => the grandpa node 	(pointer)
 * @param greatPtr => the great node 	(pointer)
 *
 * @return => void
*/
template <class Comparable>
void RedBlackTree<Comparable>::split ( RBTreeNode<Comparable>* nodePtr, RBTreeNode<Comparable>* parentPtr,
 									   RBTreeNode<Comparable>* grandPtr, RBTreeNode<Comparable>* greatPtr )
{
	//! Change the color to black
	nodePtr->rChildPtr->color = RBTreeNode<Comparable>::Black;
	nodePtr->lChildPtr->color = RBTreeNode<Comparable>::Black;

	//! Check if it's a 2_node
	if ( parentPtr->color == RBTreeNode<Comparable>::Black )
	{
		//! Change the color to red
		nodePtr->color = RBTreeNode<Comparable>::Red;
	}
	else
	{
		//! Check if the colors are different
		if ( parentPtr->lChildPtr->color != parentPtr->rChildPtr->color )
		{
			// Change the color to red
			nodePtr->color = RBTreeNode<Comparable>::Red;
		}
		//! If nodePtr is left child of its parent and parentPtr is left child of its parent
		else if ( (parentPtr->lChildPtr == nodePtr) && (grandPtr->lChildPtr == parentPtr) ) 
		{
			rightRotate(grandPtr, greatPtr); // rotate

			swapColor(nodePtr, parentPtr, grandPtr); // swap the colors of nodePtr, parentPtr, and grandPtr
		}
		else if ( (parentPtr->lChildPtr == nodePtr) && (grandPtr->rChildPtr == parentPtr) )
		{
			rightRotate(parentPtr, grandPtr); // rotate
			leftRotate(grandPtr, greatPtr);

			swapColor(nodePtr, parentPtr, grandPtr); // swap the colors of nodePtr, parentPtr, and grandPtr
		}
		else if ( (parentPtr->rChildPtr == nodePtr) && (grandPtr->lChildPtr == parentPtr) )
		{
			leftRotate(parentPtr, grandPtr); // rotate
			rightRotate(grandPtr, greatPtr);

			swapColor(nodePtr, parentPtr, grandPtr); // swap the colors of nodePtr, parentPtr, and grandPtr
		}
		else if ( (parentPtr->rChildPtr == nodePtr) && (grandPtr->rChildPtr == parentPtr) )
		{
			leftRotate(grandPtr, greatPtr); // rotate

			swapColor(nodePtr, parentPtr, grandPtr); // swap the colors of nodePtr, parentPtr, and grandPtr
		}
	}
}

/*!
 * Clone function
 *
 * @param nodePtr 	=> the node itself 	(pointer)
 *
 * @return => void
*/
template <class Comparable>
RBTreeNode<Comparable> * RedBlackTree<Comparable>::clone( RBTreeNode<Comparable> * nodePtr ) const
{ 
	//! If points to special leaf node
	if ( nodePtr == nodePtr->lChildPtr )
		return theLeaf;
	else
		return new RBTreeNode<Comparable>( nodePtr->value, clone( nodePtr->lChildPtr ), clone( nodePtr->rChildPtr ), nodePtr->color); // recursive function calls
}

/*!
 * Function to release the allocated memory
 *
 * @param nodePtr 	=> the node itself 	(pointer)
 *
 * @return => void
*/
template <class Comparable>
void RedBlackTree<Comparable>::reclaimMemory( RBTreeNode<Comparable> *nodePtr ) const
{
	//! Check if it's the leaf node
	if ( nodePtr != theLeaf )
	{
		//! Realease the left subtree memory
		reclaimMemory(nodePtr->lChildPtr);

		//! Realease the right subtree memory
		reclaimMemory(nodePtr->rChildPtr);

		//! Delete the node
		delete nodePtr;
	}
}

/*!
 * Print function
 * prints the tree from nodePtr
 *
 * @param nodePtr 	=> the node itself 	(pointer)
 * @param level		=> the tree's depth
 *
 * @return => void
*/
template <class Comparable>
void RedBlackTree<Comparable>::print( RBTreeNode<Comparable> *nodePtr, int level ) const
{
	//! Check if the node is not the leaf
	if ( nodePtr != theLeaf )
	{
		//! Call the print function recursively
		print( nodePtr->rChildPtr, (level + 1) );

		//! Print blank spaces accordingly to the depth
		for ( int i = 0; i < level; i++ )
		{
			cout << "    ";
		}

		//! Print the node
		cout << ((nodePtr->color==RBTreeNode<Comparable>::Black) ? "b[" : "r[") << nodePtr->value << "]" << endl;

		//! Call the print function recursively
		print( nodePtr->lChildPtr, level+1 );
	}
}