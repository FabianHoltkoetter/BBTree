//
// Created by Fabian on 25.07.2016.
//

#include "BBTree.h"

bool BBTree::search(const int searchVal) const {
    return root->search(searchVal);
}

void BBTree::insert(const int insertVal) {
    Node n(insertVal);

    if (root == nullptr) {
        root = &n;
    } else {
        root->insert(insertVal, alpha);
    }

}

void BBTree::remove(const int removeVal) {
    if (root != nullptr) {
        Node *pNode = root->remove(removeVal, alpha);
        delete (pNode);
    }
}

bool BBTree::Node::search(const int searchVal) const {
    if (key == searchVal) {
        return true;
    } else if (left != nullptr && left->search(searchVal)) {
        return true;
    } else if (right != nullptr && right->search(searchVal)) {
        return true;
    }
    return false;
}

BBTree::Node *BBTree::Node::insert(const int insertVal, const double alpha) {
    Node *returnNode;

    if (insertVal < key) {
        if (left == nullptr) {
            Node newNode(insertVal);
            left = &newNode;
        } else {
            left->insert(insertVal, alpha);
        }
        returnNode = left;
    } else if (insertVal > key) {
        if (right == nullptr) {
            Node newNode(insertVal);
            right = &newNode;
        } else {
            right->insert(insertVal, alpha);
        }
        returnNode = right;
    } else {
        returnNode = this;
    }
    reBalance(alpha);
    return returnNode;
}

BBTree::Node *BBTree::Node::remove(const int removeVal, const double alpha) {
    Node *returnNode = nullptr;

    if (removeVal < key) {
        if (left != nullptr) {
            if (left->key == removeVal) {
                returnNode = left;
                if (left->left == nullptr && left->right == nullptr) {
                    left = nullptr;
                } else {

                }
            }
        }
    } else if (removeVal > key) {
        if (right != nullptr) {
            if (right->key == removeVal) {
                returnNode = right;
                if (right->left == nullptr && right->right == nullptr) {
                    right = nullptr;
                } else {
                    // TODO left und right von kindknoten umbiegen
                }
            }
        }
    }

    reBalance(alpha);
    return returnNode;
}

void BBTree::Node::reBalance(const double alpha) {
    weight = 0;
    if (left == nullptr) {
        weight += 1;
    } else {
        weight += left->weight;
    }
    if (right == nullptr) {
        weight += 1;
    } else {
        weight += right->weight;
    }


    //Linken Teilknoten prüfen
    if (left != nullptr) {
        double balance = calcChildBalance(left);
        if (balance < alpha && calcChildBalance(left->right) < alpha) {
            // Fall 1.1:
            rotateLeft(&left);
        } else if (balance < alpha && calcChildBalance(left->right) > (1 - alpha)) {
            // Fall 1.2:
            rotateRightLeft(&left);
        } else if (balance > (1 - alpha) && calcChildBalance(left->left) < alpha) {
            // Fall 2.1:
            rotateLeftRight(&left);
        } else if (balance > (1 - alpha) && calcChildBalance(left->left) > (1 - alpha)) {
            // Fall 2.2:
            rotateRight(&left);
        }
    }

    // Rechten Teilknoten Prüfen
    if (right != nullptr) {
        double balance = calcChildBalance(right);
        if (balance < alpha && calcChildBalance(right->right) < alpha) {
            // Fall 1.1:
            rotateLeft(&right);
        } else if (balance < alpha && calcChildBalance(right->right) > (1 - alpha)) {
            // Fall 1.2:
            rotateRightLeft(&right);
        } else if (balance > (1 - alpha) && calcChildBalance(right->right) < alpha) {
            // Fall 2.1:
            rotateLeftRight(&right);
        } else if (balance > (1 - alpha) && calcChildBalance(right->right) > (1 - alpha)) {
            // Fall 2.2:
            rotateRight(&right);
        }
    }
}

void BBTree::Node::rotateLeft(BBTree::Node **root) {
    Node *temp = (*root)->right;
    (*root)->right = (*root)->right->left;
    temp->left = (*root);
    (*root) = temp;
}

void BBTree::Node::rotateRight(BBTree::Node **root) {
    Node *temp = (*root)->left;
    (*root)->left = (*root)->left->right;
    temp->right = (*root);
    (*root) = temp;
}

void BBTree::Node::rotateLeftRight(BBTree::Node **node) {
    rotateLeft(&(*node)->left);
    rotateRight(node);
}

void BBTree::Node::rotateRightLeft(BBTree::Node **node) {
    rotateRight(&(*node)->right);
    rotateLeft(node);
}

double BBTree::Node::calcChildBalance(BBTree::Node *child) {
    if (child != nullptr) {
        int leftWeight;
        if (child->left != nullptr) {
            leftWeight = 1;
        } else {
            leftWeight = child->left->weight;
        }
        return leftWeight / child->weight;
    }
    return 1 / 2;
}
