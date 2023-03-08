#include "gtest/gtest.h"
#include "binarySortTree.hpp"
#include "node.hpp"

class BinarySortTreeSpy: public BinarySortTree
{
public:
    Node* get_root() {return rootNode;}
    void set_root(Node* node) {rootNode = node;}
};

class PreBuiltTree:public testing::Test
{
public:
    PreBuiltTree()
    {
        n7 = new Node{7.0};
        tree.set_root(n7);
        Node* root{tree.get_root()};
    }
    void TearDown()
    {
        tree.set_root(nullptr);
    }
    ~PreBuiltTree()
    {
        delete n7;
    }
protected:
    BinarySortTreeSpy tree;
    Node* n7{nullptr};
};

class PreBuiltTreeTwo:public testing::Test
{
public:
    PreBuiltTreeTwo()
    {
        n7 = new Node{7};
        n5 = new Node{5};
        n10 = new Node{10};
        n4 = new Node{4};
        tree.set_root(n7);
        Node* root{tree.get_root()};
        root->set_left_child(n5);
        root->set_right_child(n10);
        root->get_left_child()->set_left_child(n4);
    }
    void TearDown()
    {
        tree.set_root(nullptr);
    }
    ~PreBuiltTreeTwo()
    {
        delete n7;
        delete n5;
        delete n10;
        delete n4;
    }
protected:
    BinarySortTreeSpy tree;
    Node* n7{nullptr};
    Node* n5{nullptr};
    Node* n10{nullptr};
    Node* n4{nullptr};
};

//The actual tree doesn't have a get_root function
//So this should be GivenAnEmptyTree_ExpectRootNodeIsNullptr
TEST(BST, GivenAnEmptyTree_WhenGettingRootNode_ExpectRootNodeIsNull)
{
    BinarySortTreeSpy tree;

    ASSERT_TRUE(tree.get_root() == nullptr);
}

//The exact value isn't important here.
//And infact your test name is wrong because you are using 4
//So GivenANewNodeWithaValue_WhenGettingValueofNode_ExpectCorrectValue
TEST(BST, GivenANewNodeWithmValueThree_WhenGettingValueofNode_ExpectThree)
{
    double value{4.0};
    Node testNode(value); // testNodePointer is pointing to this node

    EXPECT_EQ(value, testNode.get_value());
}

//The exact value isn't important here.  So just refer to them in the test name as initialValue and newValue
TEST(BST, GivenANewNodeWithmValueZero_WhenSettingValueToFiveAndGettingValueBack_ExpectFive)
{
    Node testNode(0.0);
    double value{-5.0};

    testNode.set_value(value);

    EXPECT_EQ(value, testNode.get_value());
}

TEST(BST, GivenAnEmptyNode_WhenGettingLeftChild_ExpectNull)
{
    Node testNode(0.0);

    ASSERT_TRUE(testNode.get_left_child() == nullptr);
}

TEST(BST, GivenAnEmptyNode_WhenSettingLeftChild_ExpectCorrectValue)
{
    Node testNode(0.0);
    double value{-10.5};
    Node* leftChildPointer = new Node(value);

    testNode.set_left_child(leftChildPointer);

    ASSERT_TRUE(testNode.get_left_child() != nullptr);
    EXPECT_EQ(value, testNode.get_left_child()->get_value());
}

//This would be combined with the leftchild test above
TEST(BST, GivenAnEmptyNode_WhenGettingRightChild_ExpectNull)
{
    Node testNode(0.0);

    ASSERT_TRUE(testNode.get_right_child() == nullptr);
}

TEST(BST, GivenAnEmptyNode_WhenSettingRightChild_ExpectCorrectValue)
{
    Node testNode(0.0);
    double value{1000.0};
    Node* rightChildPointer = new Node(value);

    testNode.set_right_child(rightChildPointer);

    ASSERT_TRUE(testNode.get_right_child() != nullptr);
    EXPECT_EQ(value, testNode.get_right_child()->get_value());

    delete rightChildPointer;
}

TEST(BSTInsert, GivenAnEmptyTree_WhenInsertingAValue_ExpectRootNodeIsNotNullAndHasCorrectValue)
{
    BinarySortTreeSpy tree;
    double value{3.0};

    tree.insert_value(value);

    ASSERT_TRUE(tree.get_root() != nullptr);
    EXPECT_EQ(value, tree.get_root()->get_value());

    delete tree.get_root();
    tree.set_root(nullptr);
}

TEST_F(PreBuiltTree, GivenAPrebuiltTree_WhenInsertingALesserValue_ExpectLeftChildDescendentNotNullAndHasCorrectValue)
{
    double value{2.0};

    tree.insert_value(value);

    ASSERT_TRUE(tree.get_root()->get_left_child() != nullptr);
    EXPECT_EQ(value, tree.get_root()->get_left_child()->get_value());

    delete tree.get_root()->get_left_child();
}

TEST_F(PreBuiltTree, GivenAPrebuiltTreeWithALeftChild_WhenInsertingALesserValue_ExpectLeftGrandkidNotNullAndHasCorrectValue)
{
    double value{-10.0};

    tree.insert_value(3.0);
    tree.insert_value(value);

    ASSERT_TRUE(tree.get_root()->get_left_child()->get_left_child() != nullptr);
    EXPECT_EQ(value, tree.get_root()->get_left_child()->get_left_child()->get_value());

    delete tree.get_root()->get_left_child()->get_left_child();
    delete tree.get_root()->get_left_child();
}

TEST_F(PreBuiltTree, GivenAPrebuiltTree_WhenInsertingAGreaterValue_ExpectRightChildNotNullAndHasCorrectValue)
{
    double value{20.0};

    tree.insert_value(value);

    ASSERT_TRUE(tree.get_root()->get_right_child() != nullptr);
    EXPECT_EQ(value, tree.get_root()->get_right_child()->get_value());

    delete tree.get_root()->get_right_child();
}
//Well done on these inset tests
TEST_F(PreBuiltTree, GivenAPrebuiltTreeWithARightChild_WhenInsertingAGreaterValue_ExpectRightGrandkidNotNullAndHasCorrectValue)
{
    double value{11.0};

    tree.insert_value(10.0);
    tree.insert_value(value);

    ASSERT_TRUE(tree.get_root()->get_right_child()->get_right_child() != nullptr);
    EXPECT_EQ(value, tree.get_root()->get_right_child()->get_right_child()->get_value());

    delete tree.get_root()->get_right_child()->get_right_child();
    delete tree.get_root()->get_right_child();
}

TEST_F(PreBuiltTree, GivenAPrebuiltTree_WhenInsertingAnEqualValue_ExpectRightChildNotNullAndHasCorrectValue)
{
    double value{7.0};

    tree.insert_value(value);

    ASSERT_TRUE(tree.get_root()->get_right_child() != nullptr);
    EXPECT_EQ(value, tree.get_root()->get_right_child()->get_value());

    delete tree.get_root()->get_right_child();
}

//These tests should follow the same idea as the insert ones.
//There should be more tests here.
TEST_F(PreBuiltTree, GivenAPreBuiltAndPopulatedTree_WhenGettingSortedValues_ExpectValuesReturnedInCorrectOrder)
{
    double v1{1.0};
    double v2{3.0};
    double v3{.5};
    double v4{-10.0};
    std::vector<double> sortedVector{v4, v3, v1, v2, tree.get_root()->get_value()};

    tree.insert_value(v1);
    tree.insert_value(v2);
    tree.insert_value(v3);
    tree.insert_value(v4);

    EXPECT_EQ(sortedVector, tree.get_sorted_values());

    //**********DELETE STUFF HERE HALEY******************
}

TEST_F(PreBuiltTreeTwo, GivenAPreBuiltTree_WhenGettingInOrderTraversalVector_ExpectValuesReturnedInCorrectOrder)
{
    double v1{7.0};
    double v2{5.0};
    double v3{10.0};
    double v4{4.0};
    std::vector<double> sortedVector{v4, v2, v1, v3};

    EXPECT_EQ(sortedVector, get_values_using_inorder_traversal(tree.get_root()));
}

TEST_F(PreBuiltTreeTwo, GivenAPreBuiltTree_WhenGettingPreOrderTraversalVector_ExpectValuesReturnedInCorrectOrder)
{
    double v1{7.0};
    double v2{5.0};
    double v3{10.0};
    double v4{4.0};
    std::vector<double> sortedVector{v1, v2, v4, v3};

    EXPECT_EQ(sortedVector, get_values_using_preorder_traversal(tree.get_root()));
}

TEST_F(PreBuiltTreeTwo, GivenAPreBuiltTree_WhenGettingPostOrderTraversalVectorofNodes_ExpectNodesReturnedInCorrectOrder)
{
    double v1{7.0};
    double v2{5.0};
    double v3{10.0};
    double v4{4.0};
    std::vector<double> expectedSortedVector{v4, v2, v3, v1};

    std::vector<Node*> sortedVectorOfNodePointers{get_values_using_postorder_traversal(tree.get_root())};
    double sortedV1{sortedVectorOfNodePointers[0]->get_value()};
    double sortedV2{sortedVectorOfNodePointers[1]->get_value()};
    double sortedV3{sortedVectorOfNodePointers[2]->get_value()};
    double sortedV4{sortedVectorOfNodePointers[3]->get_value()};
    std::vector<double> sortedVector{sortedV1, sortedV2, sortedV3, sortedV4};

    EXPECT_EQ(expectedSortedVector, sortedVector);
}

//TEST_F(PreBuiltTreeTwo, GivenAPreBuiltTree_WhenDeletingTree_ExpectAllNodesToBeNullPtr)
//{
//    tree.clearTree();

//    std::vector<
//}

//Same thing here.  These tests should follow the structure of the insert tests
TEST_F(PreBuiltTreeTwo, GivenAPreBuiltTree_WhenUsingCopyConstructor_ExpectTreesToEqualEachOther)
{
    std::vector<double> originalTreeSortedValues{tree.get_sorted_values()};

    BinarySortTreeSpy treeCopy{tree};
//    tree.clearTree();

    EXPECT_EQ(treeCopy.get_sorted_values(), originalTreeSortedValues);
}

TEST_F(PreBuiltTreeTwo, GivenAPreBuiltTree_WhenUsingCopyOperator_ExpectTreesToEqualEachOther)
{
    std::vector<double> originalTreeSortedValues{tree.get_sorted_values()};

    BinarySortTreeSpy treeCopy = tree;
//    tree.clearTree();

    EXPECT_EQ(treeCopy.get_sorted_values(), originalTreeSortedValues);
}

TEST(BSTMoveAssignment, GivenAInitilizedTree_WhenUsingMoveConstructor_ExpectTreeNodesMovedCorrectly)
{
  BinarySortTreeSpy tree;
  Node* rootNode7 = new Node{7};
  Node* n5 = new Node{5};
  Node* n10 = new Node{10};
  tree.set_root(rootNode7);
  Node* root{tree.get_root()};
  root->set_left_child(n5);
  root->set_right_child(n10);

  BinarySortTreeSpy otherTree{std::move(tree)};

  EXPECT_TRUE(tree.get_root() == nullptr);
  EXPECT_EQ(rootNode7, otherTree.get_root());

  delete rootNode7;
  delete n5;
  delete n10;
  otherTree.set_root(nullptr);
}

TEST(BSTMoveAssignment, GivenAInitilizedTree_WhenUsingMoveAssignmentOperator_ExpectTreeNodesMovedCorrectly)
{
  BinarySortTreeSpy tree;
  Node* rootNode7 = new Node{7};
  Node* n5 = new Node{5};
  Node* n10 = new Node{10};
  tree.set_root(rootNode7);
  Node* root{tree.get_root()};
  root->set_left_child(n5);
  root->set_right_child(n10);

  BinarySortTreeSpy otherTree;

  otherTree = std::move(tree);

  EXPECT_TRUE(tree.get_root() == nullptr);
  EXPECT_EQ(rootNode7, otherTree.get_root());

  delete rootNode7;
  delete n5;
  delete n10;
  otherTree.set_root(nullptr);
}

















