#include "node.hpp"

Node::Node(double value):mValue{value}
{

}

double Node::get_value() const
{
    return mValue;
}

void Node::set_value(double value)
{
    mValue = value;
}

Node* Node::get_left_child() const
{
    return mLeftChild;
}

void Node::set_left_child(Node* leftChild)
{
    mLeftChild = leftChild;
}

Node* Node::get_right_child() const
{
    return mRightChild;
}

void Node::set_right_child(Node* rightChild)
{
    mRightChild = rightChild;
}

