// HashSet_SanityCheckTests.cpp
//
// ICS 46 Spring 2017
// Project #3: Set the Controls for the Heart of the Sun
//
// This is a set of "sanity checking" unit tests for your HashSet<T>
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
// HashSet implementation.

#include <string>
#include <gtest/gtest.h>
#include "HashSet.hpp"


namespace
{
    template <typename T>
    unsigned int zeroHash(const T& t)
    {
        return 0;
    }
}


TEST(HashSet_SanityCheckTests, inheritFromSet)
{
    HashSet<int> s1{zeroHash<int>};
    Set<int>& ss1 = s1;
    int sz1 = ss1.size();
    sz1 = 0;

    HashSet<std::string> s2{zeroHash<std::string>};
    Set<std::string>& ss2 = s2;
    int sz2 = ss2.size();
    sz2 = 0;
}


TEST(HashSet_SanityCheckTests, canCreateAndDestroy)
{
    HashSet<int> s1{zeroHash<int>};
    HashSet<std::string> s2{zeroHash<std::string>};
}


TEST(HashSet_SanityCheckTests, canCopyConstructToCompatibleType)
{
    HashSet<int> s1{zeroHash<int>};
    HashSet<std::string> s2{zeroHash<std::string>};

    HashSet<int> s1Copy{s1};
    HashSet<std::string> s2Copy{s2};
}


TEST(HashSet_SanityCheckTests, canMoveConstructToCompatibleType)
{
    HashSet<int> s1{zeroHash<int>};
    HashSet<std::string> s2{zeroHash<std::string>};

    HashSet<int> s1Copy{std::move(s1)};
    HashSet<std::string> s2Copy{std::move(s2)};
}


TEST(HashSet_SanityCheckTests, canAssignToCompatibleType)
{
    HashSet<int> s1{zeroHash<int>};
    HashSet<std::string> s2{zeroHash<std::string>};

    HashSet<int> s3{zeroHash<int>};
    HashSet<std::string> s4{zeroHash<std::string>};

    s1 = s3;
    s2 = s4;
}


TEST(HashSet_SanityCheckTests, canMoveAssignToCompatibleType)
{
    HashSet<int> s1{zeroHash<int>};
    HashSet<std::string> s2{zeroHash<std::string>};

    HashSet<int> s3{zeroHash<int>};
    HashSet<std::string> s4{zeroHash<std::string>};

    s1 = std::move(s3);
    s2 = std::move(s4);
}


TEST(HashSet_SanityCheckTests, isImplemented)
{
    HashSet<int> s1{zeroHash<int>};
    EXPECT_TRUE(s1.isImplemented());

    HashSet<std::string> s2{zeroHash<std::string>};
    EXPECT_TRUE(s2.isImplemented());
}


TEST(HashSet_SanityCheckTests, canAddElementsOfTheAppropriateType)
{
    HashSet<int> s1{zeroHash<int>};
    s1.add(11);
    s1.add(1);
    s1.add(5);

    HashSet<std::string> s2{zeroHash<std::string>};
    s2.add("Boo");
    s2.add("is");
    s2.add("happy");
}


TEST(HashSet_SanityCheckTests, canCheckIfContainsElementOfTheAppropriateType)
{
    HashSet<int> s1{zeroHash<int>};
    bool b1 = s1.contains(3);
    b1 = false;

    HashSet<std::string> s2{zeroHash<std::string>};
    bool b2 = s2.contains("Boo");
    b2 = false;
}


TEST(HashSet_SanityCheckTests, canCheckSize)
{
    HashSet<int> s1{zeroHash<int>};
    unsigned int i1 = s1.size();
    i1 = 0;

    HashSet<std::string> s2{zeroHash<std::string>};
    unsigned int i2 = s2.size();
    i2 = 0;
}

