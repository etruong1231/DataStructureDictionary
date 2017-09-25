// AVLSet.hpp
//
// ICS 46 Spring 2017
// Project #3: Set the Controls for the Heart of the Sun
//
// An AVLSet is an implementation of a Set that is an AVL tree, which uses
// the algorithms we discussed in lecture to maintain balance every time a
// new element is added to the set.
//
// You are not permitted to use the containers in the C++ Standard Library
// (such as std::set, std::map, or std::vector).  Instead, you'll need
// to implement your AVL tree using your own dynamically-allocated nodes,
// with pointers connecting them, and with your own balancing algorithms
// used.

#ifndef AVLSET_HPP
#define AVLSET_HPP

#include "Set.hpp"
#include <algorithm>
#include <stdlib.h>

template <typename T>
class AVLSet : public Set<T>
{
public:
    // Initializes an AVLSet to be empty.
    AVLSet();

    // Cleans up the AVLSet so that it leaks no memory.
    virtual ~AVLSet();

    // Initializes a new AVLSet to be a copy of an existing one.
    AVLSet(const AVLSet& s);

    // Initializes a new AVLSet whose contents are moved from an
    // expiring one.
    AVLSet(AVLSet&& s);

    // Assigns an existing AVLSet into another.
    AVLSet& operator=(const AVLSet& s);

    // Assigns an expiring AVLSet into another.
    AVLSet& operator=(AVLSet&& s);


    // isImplemented() should be modified to return true if you've
    // decided to implement an AVLSet, false otherwise.
    virtual bool isImplemented() const;


    // add() adds an element to the set.  If the element is already in the set,
    // this function has no effect.  This function always runs in O(log n) time
    // when there are n elements in the AVL tree.
    virtual void add(const T& element);


    // contains() returns true if the given element is already in the set,
    // false otherwise.  This function always runs in O(log n) time when
    // there are n elements in the AVL tree.
    virtual bool contains(const T& element) const;


    // size() returns the number of elements in the set.
    virtual unsigned int size() const;


private:

struct Nodes{
    T data; 
    Nodes* parent = nullptr;
    Nodes* left = nullptr;
    Nodes* right = nullptr;
};

unsigned int AVL_size;
Nodes* root;
public:

    //insert nodes into tree
    void insertNodes(const T& element, Nodes* tree);
    //delete all nodes
    void deleteNodes(Nodes* tree);

    //checks the differences of height for checking imbalance
    int diffHeight(Nodes* height);

    //get the depth of the tree
    int height(Nodes* tree);    
    
    //does a right rotation
    void rightRotate(Nodes* tree);

    //does a left rotation
    void leftRotate(Nodes* tree);

    //does left left rotation
    void leftLeftRotate(Nodes* tree);

    //does a right right rotation
    void rightRightRotate(Nodes* tree);

    //does leftright rotation
    void leftRightRotate(Nodes* tree);

    //does rightleft rotation
    void rightLeftRotate(Nodes* tree);

    //print out 
    void preOrder(Nodes* root);


};

template <typename T>
void AVLSet<T>::preOrder(Nodes* tree)
{   
    if(tree)
    {
        if(root == tree)
            std::cout <<"top-root\n";
        if(tree->parent)
            std::cout << "\ntree-parent: " << tree->parent->data <<"\n";
        std::cout<< "tree: " << tree->data<<"\n";
        if(tree->left)
            std::cout << "left: " << tree->left->data;
        if(tree->right)
            std::cout << " right: " << tree->right->data;
        preOrder(tree->left);
        preOrder(tree->right);
    }
}
template <typename T>
AVLSet<T>::AVLSet()
{
    root = nullptr;
    AVL_size = 0;
}


template <typename T>
AVLSet<T>::~AVLSet()
{
    deleteNodes(root);
}

template <typename T>
void AVLSet<T>::deleteNodes(Nodes* tree)
{
    if(tree->left != nullptr)
        deleteNodes(tree->left);
    if(tree->right != nullptr)
        deleteNodes(tree->right);
    delete tree;
}

template <typename T>
AVLSet<T>::AVLSet(const AVLSet& s)
{
    root = s.root;
    AVL_size = s.AVL_size;
}


template <typename T>
AVLSet<T>::AVLSet(AVLSet&& s)
{
    std::swap(root, s.root);
    std::swap(AVL_size, s.AVL_size);
}


template <typename T>
AVLSet<T>& AVLSet<T>::operator=(const AVLSet& s)
{
    root = s.root;
    AVL_size = s.AVL_size;
    return *this;
}


template <typename T>
AVLSet<T>& AVLSet<T>::operator=(AVLSet&& s)
{
    std::swap(root, s.root);
    std::swap(AVL_size, s.AVL_size);
    return *this;
}


template <typename T>
bool AVLSet<T>::isImplemented() const
{
    return true;
}


template <typename T>
void AVLSet<T>::add(const T& element)
{
    if(root == nullptr)
        root = new Nodes{element};
    else
    {
       // std::cout << "\ninserting "<<element << std::endl; 
        insertNodes(element,root);
   }
   //std::cout << "tree format\n" << std::endl;
   //preOrder(root);
}


template <typename T>
int AVLSet<T>::height(Nodes* tree)
{
   if(tree == nullptr)
        return 0;
   
   int right_side = height(tree -> right);
   int left_side = height(tree-> left);
   return std::max(right_side,left_side) + 1;
}

template <typename T>
int AVLSet<T>::diffHeight(Nodes* tree)
{   
    if(tree == nullptr)
        return 0;
    return height(tree->left) - height(tree->right);
}


template <typename T>
void AVLSet<T>::insertNodes(const T& element, Nodes* tree)
{
    if(element > tree-> data)
    { 
        if(tree -> right == nullptr){
            tree -> right = new Nodes{element};
            tree -> right -> parent = tree;
            AVL_size++;
        }
        else
            insertNodes(element, tree->right);
   }
   else if (element < tree -> data)
   {
        if(tree -> left == nullptr){
            tree -> left = new Nodes{element};
            tree-> left -> parent = tree;
            AVL_size++;
        }
        else
            insertNodes(element, tree->left);
    }   
  //check the balancing backwards after the all recursion call
    int isBalanced = diffHeight(tree);

    //left situation
    if(isBalanced > 1 && !(tree->right))
    {
        
        //std::cout << element <<" rotating left "<< tree->right << std::endl;   
        leftRotate(tree);

        return;
        
    }
    //right situation
    if(isBalanced < -1 && !(tree->left))
    {
        //std::cout <<element<<" rotating right " << tree->left << std::endl;
        rightRotate(tree);
        return;
      
    }
    if(isBalanced > 1 && (tree->right))
    {
        
        //its either a left left or left right situation
        //need to checkif its left left or left right
        int left_side = diffHeight(tree->left);
        //std::cout << element <<" DOING LL OR LR " << tree->data << std::endl;
        //if its left heavy left left
        if(left_side == 1)
            leftLeftRotate(tree);
        else
            leftRightRotate(tree);
        return;

    }
    if(isBalanced <-1 && (tree->left))
    {
        int right_side = diffHeight(tree->right);

        //std::cout << element << " DOING RR OR RL " << right_side << std::endl;
        if(right_side == -1)
            rightRightRotate(tree);
        else
            rightLeftRotate(tree);

        return;
    }
 
}

template <typename T>
void AVLSet<T>::rightLeftRotate(Nodes* tree)
{
    Nodes* right_subtree = tree->right;
    Nodes* left_of_right_subtree = right_subtree->left;
    Nodes* bot_left = left_of_right_subtree->left;
    Nodes* bot_right = left_of_right_subtree-> right;

    right_subtree->left = bot_right;
    if(bot_right)
        bot_right->parent = right_subtree;
    tree->right = bot_left;
    if(bot_left)
        bot_left->parent = tree;
    left_of_right_subtree-> left = tree;
    left_of_right_subtree->right = right_subtree;
    right_subtree->parent = left_of_right_subtree;

    if(root== tree){
        left_of_right_subtree->parent = nullptr;
        tree->parent = left_of_right_subtree;
        root = left_of_right_subtree;
    }else{
        Nodes* tParent = tree->parent;
        if(tParent -> left == tree)
            tParent->left = left_of_right_subtree;
        else
            tParent -> right = left_of_right_subtree;
        left_of_right_subtree->parent = tParent;
        tree->parent = left_of_right_subtree;
    }
}

template <typename T>
void AVLSet<T>::leftRightRotate(Nodes* tree)
{
   Nodes* left_subtree = tree->left;
   Nodes* right_of_left_subtree = left_subtree->right;
   Nodes* bot_left = right_of_left_subtree->left;
   Nodes* bot_right = right_of_left_subtree->right;
    
   //change the positions
   left_subtree->right = bot_left;
   if(bot_left)
        bot_left->parent = left_subtree;
   tree->left = bot_right;
   if(bot_right)
        bot_right->parent = tree;

   right_of_left_subtree->right = tree;
   right_of_left_subtree->left = left_subtree;
   left_subtree->parent = right_of_left_subtree;

   if(root == tree){
        right_of_left_subtree->parent = nullptr;
        tree->parent = right_of_left_subtree;
        root = right_of_left_subtree;
   }else{
        Nodes* tParent = tree->parent;
        if(tParent->left == tree)
            tParent->left = right_of_left_subtree;
        else
            tParent->right = right_of_left_subtree;
        right_of_left_subtree-> parent = tParent;
        tree->parent = right_of_left_subtree;
   }
}
template <typename T>
void AVLSet<T>::rightRightRotate(Nodes* tree)
{
    Nodes* right_subtree = tree->right;
    Nodes* left_of_right_subtree = right_subtree->left;

    //mode the tree right to the left of right subtree
    tree->right = left_of_right_subtree;
    left_of_right_subtree->parent = tree;

    //need to change the right subtree left to the tree
    right_subtree->left = tree;

    if(root == tree){
        right_subtree->parent = nullptr;
        tree->parent = right_subtree;
        root = right_subtree;
    }
    else{
        Nodes* tParent = tree->parent;
        if(tParent->left == tree)
            tParent->left = right_subtree;
        else
            tParent->right = right_subtree;
        right_subtree->parent = tParent;
        tree->parent = right_subtree;

    }
}

template <typename T>
void AVLSet<T>::leftLeftRotate(Nodes* tree)
{
    Nodes* left_subtree = tree->left;
    Nodes* right_of_left_subtree = left_subtree->right;
    
    //change the top node left to child of left subtree
    tree->left = right_of_left_subtree;
    right_of_left_subtree -> parent = tree;

    //need to change the left_subtree right side to tree
    left_subtree->right = tree;
    //if the tree was a root need to change left_subtree parent to nullptr
    if(root == tree)
    {
        left_subtree->parent = nullptr;
        tree->parent = left_subtree;
        root = left_subtree;
    }
    //if the tree wasnt a root need to change the parent child to leftsubtree and vise versa
    else{
        Nodes* tParent = tree->parent;
        if(tParent->left == tree)
            tParent->left = left_subtree;
        else
            tParent->right = left_subtree;
        left_subtree->parent = tParent;
        tree->parent = left_subtree;
    }
    
}


template <typename T>
void AVLSet<T>::leftRotate(Nodes* tree)
{
   //check if the bottom node is on left or right
   Nodes* left_subtree = tree->left;
   Nodes* bot_subtree;
   //it is on the left
   if(left_subtree->right == nullptr)
   {
        //move the left subtree as parent of both
        left_subtree->right = tree;
        tree->left = nullptr;

        //need to change parent and root if tree was root
        if(root == tree){
            left_subtree->parent = nullptr;
            tree->parent = left_subtree;
            root = left_subtree;
        }
        //if theres a parent from tree
        else{
                Nodes* tParent = tree->parent;
                if(tParent->left == tree)
                    tParent->left = left_subtree;
                else
                    tParent->right = left_subtree;
                left_subtree->parent = tParent;
                tree->parent = left_subtree;
        }
   }
   //its on the right
   else{
        bot_subtree = left_subtree->right;

        tree->left = nullptr;
        bot_subtree->right = tree;
        

        left_subtree->parent = bot_subtree;
        bot_subtree->left = left_subtree;

        left_subtree->right = nullptr;

        if(root == tree)
        {
            bot_subtree->parent = nullptr;
            tree->parent = bot_subtree;
            root = bot_subtree;

        }
        else{
            Nodes * tParent = tree->parent;
            if(tParent->left == tree)
               tParent -> left = bot_subtree;
            else
                tParent-> right = bot_subtree;
            bot_subtree->parent = tParent;
            tree->parent = bot_subtree;

    }

   }


}

template<typename T>
void AVLSet<T>::rightRotate(Nodes* tree)
{
    //two options its on bottom left or right
    Nodes* right_subtree = tree->right;
    Nodes* bot_subtree;
    //its on the right
    if(right_subtree->left == nullptr){
       right_subtree->left = tree;
       tree->right = nullptr;
       if(root == tree){
            right_subtree -> parent = nullptr;
            tree->parent = right_subtree;
            root = right_subtree;
       }
       else{
            Nodes* tParent = tree->parent;
            if(tParent->left == tree)
                tParent->left = right_subtree;
            else
                tParent->right = right_subtree;
            right_subtree->parent = tParent;
            tree->parent = right_subtree;
            }

    }
    else{
        bot_subtree = right_subtree->left;

        right_subtree->left = nullptr;

        bot_subtree->right = right_subtree;
        right_subtree->parent = bot_subtree;
        tree->right = nullptr;

        bot_subtree->left = tree;
      
        if(root == tree){
            bot_subtree->parent = nullptr;
            tree->parent = bot_subtree;
            root = bot_subtree;
        }
        else{
            Nodes* tParent = tree->parent;
            if(tParent->left == tree)
                tParent -> left = bot_subtree;
            else
                tParent -> right = bot_subtree;
            bot_subtree->parent = tParent;
            tree->parent = bot_subtree;
        }
    }

}

template <typename T>
bool AVLSet<T>::contains(const T& element) const
{
    Nodes* temp = root;

    while(temp != nullptr)
    {
        if(element == temp -> data)
            return true;
        if(element > temp -> data)
            temp = temp ->right;
        else if(element < temp -> data)
            temp = temp ->left;
    }
    return false;


    
}


template <typename T>
unsigned int AVLSet<T>::size() const
{
    return AVL_size;
}



#endif // AVLSET_HPP

