#include "binarySortTree.hpp"
#include "node.hpp"
#include <iostream>

void insert_value_into_tree(Node* root, double value)
{
    if(value < root->get_value())
    {
        if(root->get_left_child() == nullptr)
            root->set_left_child(new Node{value});
        else
            insert_value_into_tree(root->get_left_child(), value);
    }
    else
    {
        if(root->get_right_child() == nullptr)
            root->set_right_child(new Node{value});
        else
            insert_value_into_tree(root->get_right_child(), value);
    }
}

std::vector<double> get_values_using_inorder_traversal(const Node* node)
{
    std::vector<double> values;
    if(node != nullptr)
    {
        std::vector<double> leftValues = get_values_using_inorder_traversal(node->get_left_child());
        std::vector<double> rightValues = get_values_using_inorder_traversal(node->get_right_child());

        values.insert(values.end(), leftValues.begin(), leftValues.end());
        values.push_back(node->get_value());
        values.insert(values.end(), rightValues.begin(), rightValues.end());
    }
    return values;
}

std::vector<Node*> get_values_using_postorder_traversal(Node* node)
{
    std::vector<Node*> values;
    if(node != nullptr)
    {
        std::vector<Node*> leftValues = get_values_using_postorder_traversal(node->get_left_child());
        std::vector<Node*> rightValues = get_values_using_postorder_traversal(node->get_right_child());

        values.insert(values.end(), leftValues.begin(), leftValues.end());
        values.insert(values.end(), rightValues.begin(), rightValues.end());
        values.push_back(node);
    }
    return values;
}

void BinarySortTree::clearTree()
{
    std::vector<Node*> nodesToDelete{get_values_using_postorder_traversal(rootNode)};
    for(int i{0}; i < nodesToDelete.size(); i++)
    {
        delete nodesToDelete[i];
    }
}

BinarySortTree::~BinarySortTree()
{
    clearTree();
    rootNode = nullptr;
}

std::vector<double> BinarySortTree::get_sorted_values()
{
    return get_values_using_inorder_traversal(rootNode);
}

BinarySortTree::BinarySortTree(const BinarySortTree& other)
{
    std::vector<double> valuesInsert{get_values_using_inorder_traversal(other.rootNode)};
    for(int i{0}; i < valuesInsert.size(); i++)
    {
        this->insert_value(valuesInsert[i]);
    }
}

BinarySortTree::BinarySortTree(BinarySortTree&& other)
{
  //You need to use std::move for this to work.
    this->rootNode = other.rootNode;
    other.rootNode = nullptr;
}

BinarySortTree& BinarySortTree::operator=(BinarySortTree&& other) // move assignment operator
{
    if(this->rootNode != nullptr)
    {
        this->clearTree();
    }

    this->rootNode = other.rootNode;
    other.rootNode = nullptr;

    return *this;
}

BinarySortTree& BinarySortTree::operator=(const BinarySortTree& other)
{
  //This not the best way to proceed.  It is better to use preorder traversal to copy the nodes.
  //This implementation takes double the work.
    if(this != &other)
    {
        this->clearTree();
        this->rootNode = other.rootNode;
        std::vector<double> valuesFromOther{get_values_using_preorder_traversal(other.rootNode)};
        for(int i{0}; i < valuesFromOther.size(); i++)
        {
            this->insert_value(valuesFromOther[i]);
        }
    }

    return *this;
}

void BinarySortTree::insert_value(double value)
{
    if(rootNode == nullptr)
    {
        rootNode = new Node{value};
    }
    else
    {
        insert_value_into_tree(rootNode, value);
    }
}

std::vector<double> get_values_using_preorder_traversal(const Node* node)
{
    std::vector<double> values;
    if(node != nullptr)
    {
        values.push_back(node->get_value());

        std::vector<double> leftValues = get_values_using_preorder_traversal(node->get_left_child());
        std::vector<double> rightValues = get_values_using_preorder_traversal(node->get_right_child());

        values.insert(values.end(), leftValues.begin(), leftValues.end());
        values.insert(values.end(), rightValues.begin(), rightValues.end());
    }
    return values;
}
