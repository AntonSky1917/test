#include <iostream>
#include <vector>

#include "three.h"

Tree::Node::Node(int _number, Node* _parent): 
    number(_number), 
    parent(_parent),
    childCount(0) { 
    
}

Tree::Node::~Node() {
   for(int i=0;i < childCount;i++)
   {
       delete children[i];
   }
}

void Tree::Node::addChild(Node* newChild){
   children[childCount++] = newChild;
}

Tree::Tree() {
   root = nullptr;
}

Tree::~Tree() {
   if(root != nullptr)
   {
       delete root;
   }
}

void Tree::setRoot(int number) {
   if(root != nullptr)
   {
       delete root;
       root = nullptr;
   }
   root = new Node(number);
}

void Tree::addNode(int parentNumber, int newNodeNumber)
{
   Node* parentNode = getNodeByNumber(parentNumber, root);
   Node* newNode = new Node(newNodeNumber, parentNode);
   parentNode->addChild(newNode);
}

Tree::Node* Tree::getNodeByNumber(int number, Node* current) {
   if(current->number == number)
       return current;
   for(int i=0; i<current->childCount; i++)
   {
       Node* found = getNodeByNumber(number, current->children[i]);
       if(found)
           return found;
   }
   return nullptr;
}

void Tree::delNode(int number) {
    std::cout << "Deleting node " << number << std::endl;

    if (root == nullptr) {
        std::cout << "Tree is empty" << std::endl;
        return;
    }

    if (root->number == number) {
        std::cout << "Deleting root node" << std::endl;
        delete root;
        root = nullptr;
        return;
    }

    Node* parentNode = nullptr;
    Node* nodeToDelete = getNodeByNumber(number, root);
    if (nodeToDelete != nullptr) {
        parentNode = nodeToDelete->parent;
        parentNode->delChild(nodeToDelete);
        delete nodeToDelete;
        std::cout << "Node deleted successfully" << std::endl;
    } else {
        std::cout << "Node not found" << std::endl;
    }
}

void Tree::Node::delChild(Node* child) {
   for (int i = 0; i < childCount; i++) {
        if (children[i] == child) {
            for (int j = i; j < childCount - 1; j++) {
                children[j] = children[j + 1];
            }
            childCount--;
            std::cout << "Child node deleted" << std::endl;
            return;
        }
    }
    std::cout << "Child node not found" << std::endl;
}

int main() {
    Tree tree;
    tree.setRoot(1);
    tree.addNode(1, 2);
    tree.addNode(1, 3);
    tree.addNode(2, 4);
    tree.addNode(2, 5);
    tree.addNode(3, 6);

    tree.delNode(4);

    return 0;
}
