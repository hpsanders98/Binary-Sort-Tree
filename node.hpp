#ifndef NODE_HPP
#define NODE_HPP

class Node
{
public:
    Node(double value);
    virtual ~Node() = default;

    Node* get_left_child() const;
    void set_left_child(Node* leftChild);

    double get_value() const;
    void set_value(double value);

    Node* get_right_child() const;
    void set_right_child(Node* rightChild);

private:
    Node* mLeftChild{nullptr};
    Node* mRightChild{nullptr};
    double mValue{0};
};

#endif // NODE_HPP
