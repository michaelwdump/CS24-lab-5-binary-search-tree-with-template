#include "intbst.h"

#include <iostream>
using std::cout;
// Daryon Roshanzaer 5701388
// Michael Wong 6209282


// constructor sets up empty tree
template <class T>
IntBST<T>::IntBST() { 
    root = nullptr;
}

// destructor deletes all nodes
template <class T>
IntBST<T>::~IntBST() {
    clear(root);
    root = nullptr;
}

// recursive helper for destructor
template <class T>
void IntBST<T>::clear(Node *n) {
    if (!n) return;
    clear(n->left);
    clear(n->right);
    delete n;
}

// insert value in tree; return false if duplicate
template <class T>
bool IntBST<T>::insert(T value) {
	if (!root) {
        Node *temp = new Node {value};
        root = temp;
        return true;
    }
    else {
        return insert(value, root);
    }
}


// recursive helper for insert (assumes n is never 0)
template <class T>
bool IntBST<T>::insert(T value, Node *n) {
    if (value > n->info) {
        if (!n->right) {
            Node *temp = new Node {value};
	    temp->parent = n;
            n->right = temp;
            return true;
        } else{
            return insert(value, n->right);
        }
    }
    else if ( value < n->info) {
        if (!n->left) {
            Node *temp = new Node {value};
	    temp->parent = n;
            n->left = temp;
            return true;
        } else{
           return insert(value, n->left);
        }
    }
    else { // is equal
        return false;
    }
}

// print tree data pre-order
template <class T>
void IntBST<T>::printPreOrder() const {
    printPreOrder(root);
}

// recursive helper for printPreOrder()
template <class T>
void IntBST<T>::printPreOrder(Node *n) const {
    if (!n) {
        return;
    }
    cout << n->info << " ";
    printPreOrder(n->left);
    printPreOrder(n->right);
}

// print tree data in-order, with helper
template <class T>
void IntBST<T>::printInOrder() const {
    printInOrder(root);
}

template <class T>
void IntBST<T>::printInOrder(Node *n) const {
    if (!n) {
        return;
    }
    printInOrder(n->left);
    cout << n->info << " ";
    printInOrder(n->right);
}

// prints tree data post-order, with helper
template <class T>
void IntBST<T>::printPostOrder() const {
    printPostOrder(root);
}

template <class T>
void IntBST<T>::printPostOrder(Node *n) const {
    if (!n) {
        return;
    }
    printPostOrder(n->left);
    printPostOrder(n->right);
    cout << n->info << " ";
}

// return sum of values in tree
template <class T>
T IntBST<T>::sum() const {
    return sum(root);
}
// recursive helper for sum
template <class T>
T IntBST<T>::sum(Node *n) const {
   T null = {};
   if (!n) { return null; }
   return (n->info + sum(n->left) + sum(n->right)); 
}

// return count of values
template <class T>
int IntBST<T>::count() const {
    return count(root);
}

// recursive helper for count
template <class T>
int IntBST<T>::count(Node *n) const {
    if (!n) { return 0; }
    return (1 + count(n->left) + count(n->right));
}

template <class T>
typename IntBST<T>::Node* IntBST<T>::getNodeFor(T value, Node *n) const{
    if (!n) {
        return nullptr;
    }
    if (value > n->info) {
	if (!n->right) {
		return nullptr;
	} else {
        	return  getNodeFor(value, n->right);
	}
    }
    else if ( value < n->info) {
    	if (!n->left) {
		return nullptr;
	} else {
		return getNodeFor(value, n->left);
	}
    }
    else {
        return n; //this returns address right
    }
}

// returns true if value is in the tree; false if not
template <class T>
bool IntBST<T>::contains(T value) const {
    if (getNodeFor(value, root)) return true;
    else return false;
}

// returns the Node containing the predecessor of the given value
template <class T>
typename IntBST<T>::Node* IntBST<T>::getPredecessorNode(T value) const{

    if (!root) return nullptr;
    Node *currNode = getNodeFor(value, root);
    if (!currNode) return nullptr;
    if (!currNode->left) {
        if (!currNode->parent) return nullptr;
        else {
            while (currNode->parent) {
                if (currNode->parent->info < value) {
                    return currNode->parent;
                }
                currNode = currNode->parent;
            }
            if (!currNode->parent) return nullptr;
        }
    } else {
        currNode = currNode->left;
        while (currNode->right) {
            currNode = currNode->right;
        }
    }
    return currNode;
}

// returns the predecessor value of the given value or 0 if there is none
template <class T>
T IntBST<T>::getPredecessor(T value) const{
    T null = {};
    if (!root) return null;
    Node *currNode = getNodeFor(value, root);
    if (!currNode) return null;
    if (!currNode->left) {
        if (!currNode->parent) return null;
        else {
            while (currNode->parent) {
                if (currNode->parent->info < value) {
                    return currNode->parent->info;
                }
                currNode = currNode->parent;
            }
            if (!currNode->parent) return null;
        }
    } else {
        currNode = currNode->left;
        while (currNode->right) {
            currNode = currNode->right;
        }
    }
    return currNode->info;
}
// returns the Node containing the successor of the given value
template <class T>
typename IntBST<T>::Node* IntBST<T>::getSuccessorNode(T value) const{

    if (!root) return nullptr;
    Node *currNode = getNodeFor(value, root);
    if (!currNode) return nullptr;
    if (!currNode->right) {
        if (!currNode->parent) return nullptr;
        else {
            while (currNode->parent) {
                if (currNode->parent->info > value) {
                    return currNode->parent;
                }
                currNode = currNode->parent;
            }
            if (!currNode->parent) return nullptr;
        }
    } 
    else {
        currNode = currNode->right;
        while (currNode->left) {
            currNode = currNode->left;
        }
    }
    return currNode;
}


// returns the successor value of the given value or 0 if there is none
template <class T>
T IntBST<T>::getSuccessor(T value) const{
    T null = {};
    if (!root) return null;
    Node *currNode = getNodeFor(value, root);
    if (!currNode) return null;
    if (!currNode->right) {
        if (!currNode->parent) return null;
        else {
            while (currNode->parent) {
                if (currNode->parent->info > value) {
                    return currNode->parent->info;
                }
                currNode = currNode->parent;
            }
            if (!currNode->parent) return null;
        }
    } 
    else {
        currNode = currNode->right;
        while (currNode->left) {
            currNode = currNode->left;
        }
    }
    return currNode->info;
}

// deletes the Node containing the given value from the tree
// returns true if the node exist and was deleted or false if the node does not exist
template <class T>
bool IntBST<T>::remove(T value){
    Node *currNode = getNodeFor(value, root);
    if (!currNode) return false;
    if (currNode == root && !root->left && !root->right) {
        delete currNode;
        root = nullptr;
        return true;
    }
    else {
        if (!currNode->left && !currNode->right) { // no children
            if (currNode->parent->right == currNode) {
            	currNode->parent->right = nullptr;
            	delete currNode;
            	return true;
            } 
	    else {
            	currNode->parent->left = nullptr;
            	delete currNode;
            	return true;
            }
        } 
	else if (currNode->left && currNode->right) { // two children
		Node* newNode = getSuccessorNode(value);
		T newData = newNode->info;
		remove(newNode->info); 
		currNode->info = newData;
		return true;
        } 
	else { // only has one child
		if (!currNode->parent) { // checking if the currNode is a root node
			if (currNode->left) {
				currNode->left->parent = nullptr;
				root = currNode->left;
				delete currNode;
				return true;
			}
			else {
				currNode->right->parent = nullptr;
				root = currNode->right;
				delete currNode;
				return true;
			}
		}
		else if (currNode->left) { // only has left child which is left
                	currNode->left->parent = currNode->parent;
                	if (currNode->parent->info > value) {
				currNode->parent->left = currNode->left;
               		} 
			else {
				currNode->parent->right = currNode->left;
                	}
                	delete currNode;
                	return true;
            	}
		else { // only has right child
                	currNode->right->parent = currNode->parent;
                	if (currNode->parent->info > value) {
        	            	currNode->parent->left = currNode->right;
                	} 
			else {
	                    	currNode->parent->right = currNode->right;
               		}
                	delete currNode;
                	return true;
           		}
        	}
    	}
}
