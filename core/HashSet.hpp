// HashSet.hpp
//
// ICS 46 Spring 2017
// Project #3: Set the Controls for the Heart of the Sun
//
// A HashSet is an implementation of a Set that is a separately-chained
// hash table, implemented as a dynamically-allocated array of linked
// lists.  At any given time, the HashSet has a "size" indicating
// how many elements are stored within it, along with a "capacity"
// indicating the size of the array.
//
// As elements are added to the HashSet and the proportion of the HashSet's
// size to its capacity exceeds 0.8 (i.e., there are more than 80% as many
// elements as there are array cells), the HashSet should be resized so
// that it is twice as large as it was before.
//
// You are not permitted to use the containers in the C++ Standard Library
// (such as std::vector, std::list, or std::array).  Instead, you'll need
// to use a dynamically-allocated array and your own linked list
// implementation; the linked list doesn't have to be its own class,
// though you can do that, if you'd like.

#ifndef HASHSET_HPP
#define HASHSET_HPP

#include <functional>
#include "Set.hpp"



template <typename T>
class HashSet : public Set<T>
{
public:
    // The default capacity of the HashSet before anything has been
    // added to it.
    static constexpr unsigned int DEFAULT_CAPACITY = 10;

    // A HashFunction 
    typedef std::function<unsigned int(const T&)> HashFunction;

public:
    // Initializes a HashSet to be empty, so that it will use the given
    // hash function whenever it needs to hash an element.
    HashSet(HashFunction hashFunction);

    // Cleans up the HashSet so that it leaks no memory.
    virtual ~HashSet();

    // Initializes a new HashSet to be a copy of an existing one.
    HashSet(const HashSet& s);

    // Initializes a new HashSet whose contents are moved from an
    // expiring one.
    HashSet(HashSet&& s);

    // Assigns an existing HashSet into another.
    HashSet& operator=(const HashSet& s);

    // Assigns an expiring HashSet into another.
    HashSet& operator=(HashSet&& s);


    // isImplemented() should be modified to return true if you've
    // decided to implement a HashSet, false otherwise.
    virtual bool isImplemented() const;


    // add() adds an element to the set.  If the element is already in the set,
    // this function has no effect.  This function triggers a resizing of the
    // array when the ratio of size to capacity would exceed 0.8.  In the case
    // where the array is resized, this function runs in linear time (with
    // respect to the number of elements, assuming a good hash function);
    // otherwise, it runs in constant time (again, assuming a good hash
    // function).
    virtual void add(const T& element);


    // contains() returns true if the given element is already in the set,
    // false otherwise.  This function runs in constant time (with respect
    // to the number of elements, assuming a good hash function).
    virtual bool contains(const T& element) const;


    // size() returns the number of elements in the set.
    virtual unsigned int size() const;

    
    //need a function to use the hash element to make it fit into the array
    void insert(const T& element);


private:
   //create a strcut to make chaining possible
struct Nodes
{
   T words;
   Nodes* next = nullptr;
};
   HashFunction hashFunction;
   unsigned int hash_size;
   unsigned int capacity;
   Nodes** hash_set;

};



template <typename T>
HashSet<T>::HashSet(HashFunction hashFunction)
    : hashFunction{hashFunction}
{
//need to set up the hash table
    capacity = DEFAULT_CAPACITY;
    hash_set = new Nodes*[capacity];
    hash_size = 0;
}


template <typename T>
HashSet<T>::~HashSet()
{
    for(unsigned int i = 0 ; i < capacity; i++)
    {   //delete each element of pointers
        if(hash_set[i] != nullptr)
        {
            Nodes* temp = hash_set[i];
            while(temp != nullptr)
            {
                Nodes* del_temp = temp;
                temp = temp -> next;
                delete del_temp;
            }
        }
    }
    delete[] hash_set;
}


template <typename T>
HashSet<T>::HashSet(const HashSet& s)
    : hashFunction{nullptr}
{
    hash_set = s.hash_set;
    hash_size = s.hash_size;
    capacity = s.capacity;
}


template <typename T>
HashSet<T>::HashSet(HashSet&& s)
    : hashFunction{nullptr}
{
    std::swap(hash_set, s.hash_set);
    std::swap(hash_size, s.hash_size);
    std::swap(capacity, s.capacity);
}


template <typename T>
HashSet<T>& HashSet<T>::operator=(const HashSet& s)
{
    hashFunction = s.hashFunction;
    hash_set = s.hash_set;
    hash_size = s.hash_size;
    capacity = s.capacity;
    return *this;
}


template <typename T>
HashSet<T>& HashSet<T>::operator=(HashSet&& s)
{
    std::swap(hash_set, s.hash_set);
    std::swap(hash_size, s.hash_size);
    std::swap(capacity, s.capacity);
    return *this;
}


template <typename T>
bool HashSet<T>::isImplemented() const
{
    return true;
}


template <typename T>
void HashSet<T>::add(const T& element)
{
    insert(element);
    hash_size++;
    //need to check for resizing   
    if((float(hash_size) /float(capacity)) > .8)
    {
        //std::cout << "New HASH CAPACITY " << std::endl;
        //need the old hash to rewrite
        Nodes** prev_hash = hash_set;
        capacity = (capacity * 2);
        //makes a new hashset with a bigger capacity
        hash_set = new Nodes*[capacity];
        //need to put the old hash set into new hashset
        for(unsigned int i = 0; i < capacity/2; i++)
        {
            //need to check if the hash index is nullptr or not
            Nodes* temp = prev_hash[i];
            if(temp != nullptr)
            {
                 while(temp != nullptr)
                 {
                    insert(temp->words);
                    temp = temp -> next;
                 }
            }
        }
        //need to clean up the old hash 
        for(unsigned int i = 0; i < capacity/2; i++)
        {
            if(prev_hash[i] != nullptr)
            {
                //need to delete each node of that index
                Nodes* temp = prev_hash[i];
                while(temp != nullptr)
                {   
                    Nodes* del_temp = temp;
                    temp = temp->next;
                    delete del_temp;
                }

            }

        }
        delete[] prev_hash;
    }
}
template <typename T>
void HashSet<T>::insert(const T& element)
{   
    unsigned int index = hashFunction(element) % capacity;
    //need to check if that spot is empty or not
    Nodes* temp = hash_set[index];
    //if that spot is empty need to create a new node with taht value
    if(temp == nullptr)
    {
        hash_set[index] = new Nodes{element};
    }
    //its not a null so we gotta go to the next 
    else
    {
        //tries to get to the next nullptr
        while(temp->next != nullptr)
            temp = temp -> next;
        temp-> next = new Nodes{element};
           
    }
    //std::cout << element << ": " << index << std::endl;
}
template <typename T>
bool HashSet<T>::contains(const T& element) const
{
   unsigned int index = hashFunction(element) % capacity;
   Nodes* checker = hash_set[index];
   if(checker != nullptr)
   {
        while(checker != nullptr)
        {
            if(checker -> words == element)
                return true;
            checker = checker -> next;

        }    
                
   }
   return false;

}


template <typename T>
unsigned int HashSet<T>::size() const
{
    return hash_size;
}



#endif // HASHSET_HPP

