#include <gtest/gtest.h>
#include "arr.cpp"

TEST(ArrayTest, DefaultConstructor) {
    Array<int> arr;
    EXPECT_EQ(arr.size(), 0);
}

TEST(ArrayTest, ConstructorWithCapacity) {
    Array<int> arr(20);
    EXPECT_EQ(arr.size(), 0);
}

TEST(ArrayTest, InsertToEnd) {
    Array<int> arr;
    arr.insert(10);
    arr.insert(20);
    EXPECT_EQ(arr.size(), 2);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
}

TEST(ArrayTest, InsertAtIndex) {
    Array<int> arr;
    arr.insert(10);
    arr.insert(0, 5);
    EXPECT_EQ(arr.size(), 2);
    EXPECT_EQ(arr[0], 5);
    EXPECT_EQ(arr[1], 10);
}

TEST(ArrayTest, RemoveAtIndex) {
    Array<int> arr;
    arr.insert(10);
    arr.insert(20);
    arr.remove(0);
    EXPECT_EQ(arr.size(), 1);
    EXPECT_EQ(arr[0], 20);
}

TEST(ArrayTest, AccessByIndex) {
    Array<int> arr;
    arr.insert(10);
    arr.insert(20);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);

    arr[0] = 30;
    EXPECT_EQ(arr[0], 30);
}

TEST(ArrayTest, IteratorPrefixIncrement) {
    Array<int> arr;
    arr.insert(10);
    arr.insert(20);
    auto it = arr.begin();
    EXPECT_EQ(*it, 10);
    ++it;
    EXPECT_EQ(*it, 20);
}

TEST(ArrayTest, IteratorPostfixIncrement) {
    Array<int> arr;
    arr.insert(10);
    arr.insert(20);
    auto it = arr.begin();
    EXPECT_EQ(*it, 10);
    it++;
    EXPECT_EQ(*it, 20);
}

TEST(ArrayTest, RangeForLoop) {
    Array<int> arr;
    arr.insert(1);
    arr.insert(2);
    arr.insert(3);

    int expected[] = { 1, 2, 3 };
    int index = 0;
    for (int x : arr) {
        EXPECT_EQ(x, expected[index]);
        index++;
    }
    EXPECT_EQ(index, 3);
}

TEST(ArrayTest, ConstIterator) {
    Array<int> arr;
    arr.insert(10);
    arr.insert(20);
    const Array<int>& constArr = arr;

    auto it = constArr.cbegin();
    EXPECT_EQ(*it, 10);
    ++it;
    EXPECT_EQ(*it, 20);
}

TEST(ArrayTest, InsertWithResize) {
    Array<int> arr(2);
    arr.insert(1);
    arr.insert(2);
    arr.insert(3);
    EXPECT_EQ(arr.size(), 3);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr[2], 3);
}

TEST(ArrayTest, RemoveAllElements) {
    Array<int> arr;
    arr.insert(10);
    arr.insert(20);
    arr.remove(0);
    arr.remove(0);
    EXPECT_EQ(arr.size(), 0);
}

TEST(ArrayTest, ConstIteratorPostfixIncrement) {
    Array<int> arr;
    arr.insert(10);
    arr.insert(20);
    const Array<int>& constArr = arr;
    auto it = constArr.cbegin();
    EXPECT_EQ(*it, 10);
    it++;
    EXPECT_EQ(*it, 20);
}

TEST(ArrayTest, ReverseIterator) {
    Array<int> arr;
    arr.insert(1);
    arr.insert(2);
    arr.insert(3);

    auto it = arr.reverseIterator();
    EXPECT_EQ(*it, 3);
    it++;
    EXPECT_EQ(*it, 2);
    it++;
    EXPECT_EQ(*it, 1);
}

TEST(ArrayTest, Destructor) {
    Array<int>* arr = new Array<int>();
    arr->insert(42);
    delete arr;
    SUCCEED();
}

TEST(ArrayTest, CopyConstructor) {
    Array<int> arr;
    arr.insert(10);
    arr.insert(20);

    Array<int> copy(arr);
    EXPECT_EQ(copy.size(), 2);
    EXPECT_EQ(copy[0], 10);
    EXPECT_EQ(copy[1], 20);
}

TEST(ArrayTest, MoveConstructor) {
    Array<int> arr;
    arr.insert(10);
    arr.insert(20);

    Array<int> moved(std::move(arr));
    EXPECT_EQ(moved.size(), 2);
    EXPECT_EQ(moved[0], 10);
    EXPECT_EQ(moved[1], 20);

    EXPECT_EQ(arr.size(), 0);
}

TEST(ArrayTest, StringType) {
    Array<std::string> arr;
    arr.insert("456");
    arr.insert("123");
    EXPECT_EQ(arr.size(), 2);
    EXPECT_EQ(arr[0], "456");
    EXPECT_EQ(arr[1], "123");
}

TEST(ArrayTest, StringRemove) {
    Array<std::string> arr;
    arr.insert("12");
    arr.insert("34");
    arr.insert("56");
    arr.remove(1);
    EXPECT_EQ(arr.size(), 2);
    EXPECT_EQ(arr[0], "12");
    EXPECT_EQ(arr[1], "56");
}