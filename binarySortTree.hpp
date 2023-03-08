#ifndef BINARYSORTTREE_HPP
#define BINARYSORTTREE_HPP
#include <vector>

class Node;

class BinarySortTree
{
public:
    BinarySortTree() = default;
    BinarySortTree(const BinarySortTree& other);
    BinarySortTree(BinarySortTree&& other);
    virtual ~BinarySortTree();

    BinarySortTree& operator=(const BinarySortTree& other);
    BinarySortTree& operator=(BinarySortTree&& other);

    void insert_value(double value);
    std::vector<double> get_sorted_values();
    void clearTree();

protected:
    Node* rootNode{nullptr};
};

//These functions should be in another file.
void insert_value_into_tree(Node* root, double value);
std::vector<double> get_values_using_inorder_traversal(const Node* node);
std::vector<double> get_values_using_preorder_traversal(const Node* node);
std::vector<Node*> get_values_using_postorder_traversal(Node *node);

#endif
