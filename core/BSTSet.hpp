// BSTSet.hpp
//
// ICS 46 Spring 2017
// Project #3: Set the Controls for the Heart of the Sun
//
// A BSTSet is an implementation of a Set that is a binary search tree,
// albeit one that makes no attempt to remain balanced.  (You explicitly
// should not do any balancing here; do that in AVLSet instead, if you
// choose to work on that one.)
//
// You are not permitted to use the containers in the C++ Standard Library
// (such as std::set, std::map, or std::vector).  Instead, you'll need
// to implement your binary search tree using your own dynamically-allocated
// nodes, with pointers connecting them.

#ifndef BSTSET_HPP
#define BSTSET_HPP

#include "Set.hpp"



template <typename T>
class BSTSet : public Set<T>
{
public:
    // Initializes a BSTSet to be empty.
    BSTSet();

    // Cleans up the BSTSet so that it leaks no memory.
    virtual ~BSTSet();

    // Initializes a new BSTSet to be a copy of an existing one.
    BSTSet(const BSTSet& s);

    // Initializes a new BSTSet whose contents are moved from an
    // expiring one.
    BSTSet(BSTSet&& s);

    // Assigns an existing BSTSet into another.
    BSTSet& operator=(const BSTSet& s);

    // Assigns an expiring BSTSet into another.
    BSTSet& operator=(BSTSet&& s);


    // isImplemented() should be modified to return true if you've
    // decided to implement a BSTSet, false otherwise.
    virtual bool isImplemented() const;


    // add() adds an element to the set.  If the element is already in the set,
    // this function has no effect.  This function runs in O(n) time when there
    // are n elements in the binary search tree, and is sometimes as fast as
    // O(log n) (when the tree is relatively balanced).
    virtual void add(const T& element);


    // contains() returns true if the given element is already in the set,
    // false otherwise.  This function runs in O(n) time when there
    // are n elements in the binary search tree, and is sometimes as fast as
    // O(log n) (when the tree is relatively balanced).
    virtual bool contains(const T& element) const;


    // size() returns the number of elements in the set.
    virtual unsigned int size() const;

   
private:

struct Nodes{
    T data;
    Nodes* left = nullptr;
    Nodes* right = nullptr;
};
int BST_size;
Nodes* root;

public:
//recurison function to find the node spot
    void insertNodes(const T& element, Nodes* tree);
//recursion to delete nodes 
    void deleteNodes(Nodes* tree);
};


template <typename T>
BSTSet<T>::BSTSet()
{
    //no Root
    root = nullptr;
    BST_size = 0;
}



template <typename T>
BSTSet<T>::~BSTSet()
{
   deleteNodes(root);
}
template <typename T>
void BSTSet<T>::deleteNodes(Nodes* tree)
{
    //transverse through all possible route and delete upwards
    if(tree->left != nullptr)
        deleteNodes(tree->left);
    if(tree->right != nullptr)
        deleteNodes(tree->right);
    delete tree;

}

template <typename T>
BSTSet<T>::BSTSet(const BSTSet& s)
{
    root = s.root;
    BST_size = s.BST_size;
}


template <typename T>
BSTSet<T>::BSTSet(BSTSet&& s)
{
    std::swap(root, s.root);
    std::swap(BST_size, s.BST_size);
}


template <typename T>
BSTSet<T>& BSTSet<T>::operator=(const BSTSet& s)
{
    root = s.root;
    BST_size = s.BST_size;
    return *this;
}


template <typename T>
BSTSet<T>& BSTSet<T>::operator=(BSTSet&& s)
{
    std::swap(root, s.root);
    std::swap(BST_size, s.BST_size);
    return *this;
}


template <typename T>
bool BSTSet<T>::isImplemented() const
{
    return true;
}


template <typename T>
void BSTSet<T>::add(const T& element)
{
    //check if the root has been intialized
    if(root == nullptr)
        root = new Nodes{element};
    else
    {
        insertNodes(element,root);
       // std::cout << "inserting: " << element << std::endl;
    }
    
}

template <typename T>
void BSTSet<T>::insertNodes(const T& element, Nodes* tree)
{   
   
    //element is equal or greater than 
    if(element > tree->data)
    {   //theres no data to the right
        if(tree-> right == nullptr){
            tree-> right = new Nodes{element};
            BST_size++;
        }
        //recursion to the next tree node
        else
          insertNodes(element,tree->right); 
    }
    //this means the element is smaller than the tree node
    else if (element < tree->data)
    {
        //no data to left so make it this new element
        if(tree -> left == nullptr){
            tree -> left = new Nodes{element};
            BST_size++;
        }
        else
        //if there is data keep traversing
            insertNodes(element,tree->left);
    }
    


}


template <typename T>
bool BSTSet<T>::contains(const T& element) const
{
  
    Nodes* temp = root;

    while(temp !=nullptr)
    {
        //if it has data return ture
        if(element == temp -> data)
            return true;
        //check if its bigger than that data then go to right tree
        if(element > temp -> data)
            temp = temp -> right;
        //check if its smaller than that data go to the left tree
        else if(element < temp -> data)
            temp = temp -> left;
    }
    return false;
    
}



template <typename T>
unsigned int BSTSet<T>::size() const
{
    return BST_size;
}



#endif // BSTSET_HPP

