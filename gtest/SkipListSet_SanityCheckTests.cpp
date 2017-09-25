// SkipListSet_SanityCheckTests.cpp
//
// ICS 46 Spring 2017
// Project #3: Set the Controls for the Heart of the Sun
//
// This is a set of "sanity checking" unit tests for your SkipListSet<T>
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
// SkipListSet implementation.

#include <string>
#include <gtest/gtest.h>
#include "SkipListSet.hpp"


TEST(SkipListSet_SanityCheckTests, inheritFromSet)
{
    SkipListSet<int> s1;
    Set<int>& ss1 = s1;
    int sz1 = ss1.size();
    sz1 = 0;

    SkipListSet<std::string> s2;
    Set<std::string>& ss2 = s2;
    int sz2 = ss2.size();
    sz2 = 0;
}


TEST(SkipListSet_SanityCheckTests, canCreateAndDestroy)
{
    SkipListSet<int> s1;
    SkipListSet<std::string> s2;
}


TEST(SkipListSet_SanityCheckTests, canCopyConstructToCompatibleType)
{
    SkipListSet<int> s1;
    SkipListSet<std::string> s2;

    SkipListSet<int> s1Copy{s1};
    SkipListSet<std::string> s2Copy{s2};
}


TEST(SkipListSet_SanityCheckTests, canMoveConstructToCompatibleType)
{
    SkipListSet<int> s1;
    SkipListSet<std::string> s2;

    SkipListSet<int> s1Copy{std::move(s1)};
    SkipListSet<std::string> s2Copy{std::move(s2)};
}


TEST(SkipListSet_SanityCheckTests, canAssignToCompatibleType)
{
    SkipListSet<int> s1;
    SkipListSet<std::string> s2;

    SkipListSet<int> s3;
    SkipListSet<std::string> s4;

    s1 = s3;
    s2 = s4;
}


TEST(SkipListSet_SanityCheckTests, canMoveAssignToCompatibleType)
{
    SkipListSet<int> s1;
    SkipListSet<std::string> s2;

    SkipListSet<int> s3;
    SkipListSet<std::string> s4;

    s1 = std::move(s3);
    s2 = std::move(s4);
}


TEST(SkipListSet_SanityCheckTests, isImplemented)
{
    SkipListSet<int> s1;
    EXPECT_TRUE(s1.isImplemented());

    SkipListSet<std::string> s2;
    EXPECT_TRUE(s2.isImplemented());
}


TEST(SkipListSet_SanityCheckTests, canAddElementsOfTheAppropriateType)
{
    SkipListSet<int> s1;
    s1.add(11);
    s1.add(1);
    s1.add(5);

    SkipListSet<std::string> s2;
    s2.add("Boo");
    s2.add("is");
    s2.add("happy");
}


TEST(SkipListSet_SanityCheckTests, canCheckIfContainsElementOfTheAppropriateType)
{
    SkipListSet<int> s1;
    bool b1 = s1.contains(3);
    b1 = false;

    SkipListSet<std::string> s2;
    bool b2 = s2.contains("Boo");
    b2 = false;
}


TEST(SkipListSet_SanityCheckTests, canCheckSize)
{
    SkipListSet<int> s1;
    unsigned int i1 = s1.size();
    i1 = 0;

    SkipListSet<std::string> s2;
    unsigned int i2 = s2.size();
    i2 = 0;
}

