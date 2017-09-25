// BSTSet_SanityCheckTests.cpp
//
// ICS 46 Spring 2017
// Project #3: Set the Controls for the Heart of the Sun
//
// This is a set of "sanity checking" unit tests for your BSTSet<T>
// implementation, provided primarily as a mechanism for ensuring that
// your implementation is compatible with the unit tests we'll be using
// to test it.  The goal here is to ensure that you have all of the
// necessary member functions, that their type declarations are as they
// should be, and that you've organized your code correctly as a template
// so that these tests will compile and link.  These tests don't verify
// the functionality; that'll be up to you to test on your own.
//
// As with the sanity-checking tests you saw in Project #0, you should
// not modify these in any way -- don't add #include directives, don't
// change the code within the tests.  Initially, these will compile
// correctly.  They should all compile and pass before you submit your
// BSTSet implementation.

#include <string>
#include <gtest/gtest.h>
#include "BSTSet.hpp"


TEST(BSTSet_SanityCheckTests, inheritFromSet)
{
    BSTSet<int> s1;
    Set<int>& ss1 = s1;
    int sz1 = ss1.size();
    sz1 = 0;

    BSTSet<std::string> s2;
    Set<std::string>& ss2 = s2;
    int sz2 = ss2.size();
    sz2 = 0;
}


TEST(BSTSet_SanityCheckTests, canCreateAndDestroy)
{
    BSTSet<int> s1;
    BSTSet<std::string> s2;
}


TEST(BSTSet_SanityCheckTests, canCopyConstructToCompatibleType)
{
    BSTSet<int> s1;
    BSTSet<std::string> s2;

    BSTSet<int> s1Copy{s1};
    BSTSet<std::string> s2Copy{s2};
}


TEST(BSTSet_SanityCheckTests, canMoveConstructToCompatibleType)
{
    BSTSet<int> s1;
    BSTSet<std::string> s2;

    BSTSet<int> s1Copy{std::move(s1)};
    BSTSet<std::string> s2Copy{std::move(s2)};
}


TEST(BSTSet_SanityCheckTests, canAssignToCompatibleType)
{
    BSTSet<int> s1;
    BSTSet<std::string> s2;

    BSTSet<int> s3;
    BSTSet<std::string> s4;

    s1 = s3;
    s2 = s4;
}


TEST(BSTSet_SanityCheckTests, canMoveAssignToCompatibleType)
{
    BSTSet<int> s1;
    BSTSet<std::string> s2;

    BSTSet<int> s3;
    BSTSet<std::string> s4;

    s1 = std::move(s3);
    s2 = std::move(s4);
}


TEST(BSTSet_SanityCheckTests, isImplemented)
{
    BSTSet<int> s1;
    EXPECT_TRUE(s1.isImplemented());

    BSTSet<std::string> s2;
    EXPECT_TRUE(s2.isImplemented());
}


TEST(BSTSet_SanityCheckTests, canAddElementsOfTheAppropriateType)
{
    BSTSet<int> s1;
    s1.add(11);
    s1.add(1);
    s1.add(5);

    BSTSet<std::string> s2;
    s2.add("Boo");
    s2.add("is");
    s2.add("happy");
}


TEST(BSTSet_SanityCheckTests, canCheckIfContainsElementOfTheAppropriateType)
{
    BSTSet<int> s1;
    bool b1 = s1.contains(3);
    b1 = false;

    BSTSet<std::string> s2;
    bool b2 = s2.contains("Boo");
    b2 = false;
}


TEST(BSTSet_SanityCheckTests, canCheckSize)
{
    BSTSet<int> s1;
    unsigned int i1 = s1.size();
    i1 = 0;

    BSTSet<std::string> s2;
    unsigned int i2 = s2.size();
    i2 = 0;
}

