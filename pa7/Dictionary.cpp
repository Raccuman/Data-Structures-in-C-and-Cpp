/***
* Catherine Bronte
* cebronte 1969208
* 2024 Fall CSE101 PA7
* Dictionary.cpp
*  this is where the Dictionary classes and functions get written
***/

#include"Dictionary.h"
#include<iostream>
#include<string>
#include<stdexcept>

// the node constructor, makes a NIL node
Dictionary::Node::Node(keyType k, valType v) {
    key = k;
    val = v;
    parent = nullptr;
    left = nullptr;
    right = nullptr;
}

//////////////////////////////////////////// the private side /////////////////////////////////////////////////////////

// very recursive
void Dictionary::inOrderString(std::string& s, Node* R) const {
    if (R != nil) { // if the right node isnt there, go back, else go left
        inOrderString(s, R->left);

        s.append(R->key + " : " +  std::to_string(R->val) + "\n");

        // when you come back go right
        inOrderString(s, R->right);
    }
}


void Dictionary::preOrderString(std::string& s, Node* R) const {
    if (R != nil) { // if the right node isnt there, go back, else go left
        // since it is pre-order, append the node first, then go somewhere
        s.append(R->key + "\n");

        preOrderString(s, R->left);

        // when you come back go right
        preOrderString(s, R->right);
    }
}


void Dictionary::preOrderCopy(Node* R, Node* N) { // this meaning cat.preOrderCopy(A, B); Cat is the one being copied into
    if (R != nil && R != N) {
        setValue(R->key, R->val);
        preOrderCopy(R->left, N);
        // you have to do right as well because it acts as a seperate tree if you start at the root
        preOrderCopy(R->right, N);

    }
}


void Dictionary::postOrderDelete(Node* R) { //??//
    if (num_pairs > 0 && R != nil) {
        postOrderDelete(R->left);
        postOrderDelete(R->right);
        R->left = nil;
        R->right = nil;
        delete R;
        num_pairs -= 1;
    }
}


Dictionary::Node* Dictionary::search(Node* R, keyType k) const {
    if (R == nil || k.compare(R->key) == 0) {
        return R;
    }
    else if (k < (R->key)) {
        return search(R->left, k);
    }
    else {
        return search(R->right, k);
    }
}


Dictionary::Node* Dictionary::findMin(Node* R) {
    if (R == nil) {
        throw std::logic_error("Dictionary: findMin: a NIL node was passed in, BAD!");
    }
    while (R->left != nil) {
        R = R->left;
    }
    return R;
}


Dictionary::Node* Dictionary::findMax(Node* R) {
    if (R == nil) {
        throw std::logic_error("Dictionary: findMax: a NIL node was passed in, BAD!");
    }
    while (R->right != nil) {
        R = R->right;
    }
    return R;
}


Dictionary::Node* Dictionary::findNext(Node* N) {
    if (N == nil || N == findMax(root)) {
        return nil;
    }
    if (N->right != nil) {
        return findMin(N->right);
    }
    // inch worm style
    Node* pre = N->parent;
    // as long as it was the right node
    while (pre != nil && N == pre->right) {
        N = pre;
        pre = pre->parent;
    }
    return pre;

}


Dictionary::Node* Dictionary::findPrev(Node* N) {
    if (N == nil || N == findMin(root)) {
        return nil;
    }
    if (N->left != nil) {
        return findMax(N->left);
    }
    Node *pre = N->parent;
    while (pre != nil && N == pre->left) {
        N = pre;
        pre = pre->parent;
    }
    return pre;
}


////////////////////////////////////////////// How to Make a Dictionary ////////////////////////////////////////////////////////

Dictionary::Dictionary() {
    // starts as an empty dictionary
    nil = nullptr; // the nill node
    root = nullptr; // gets defined later
    current = nullptr; // the current node, the cursor system
    num_pairs = 0; 
}

// its like dictionary but you gave it some stuff to start with, it copies over the dict
Dictionary::Dictionary(const Dictionary& D) {
    nil = nullptr; // the nill node
    root = nullptr; // gets defined later
    current = nullptr; // the current node, the cursor system
    num_pairs = 0; 
    (*this).preOrderCopy(D.root, nil);
}


Dictionary::~Dictionary() {
    clear();
}


///////////////////////////////////////// Finding stuff in the Dictionary //////////////////////////////////////////////////////////


int Dictionary::size() const {
    return num_pairs;
}


bool Dictionary::contains(keyType k) const {
    if (search(root, k) != nil) {
        return true;
    }
    return false;
}


valType& Dictionary::getValue(keyType k) const {
    if (!contains(k)) {
        throw std::logic_error("Dictionary: getValue: the key is not in the dictionary, BAD!");
    }
    Node* T = search(root, k);
    return T->val;
}


bool Dictionary::hasCurrent() const {
    if (current != nil) {
        return true;
    }
    return false;
}


keyType Dictionary::currentKey() const {
    if (!hasCurrent()) {
        throw std::logic_error("Dictionary: currentKey: current is not defined right now, BAD!");
    }
    return current->key;
}


valType& Dictionary::currentVal() const {
    if (!hasCurrent()) {
        throw std::logic_error("Dictionary: currentVal: current is not defined right now, BAD!");
    }
    return current->val;
}


////////////////////////////////////////// changing bits and pieces in the dict ////////////////////////////////////////////

void Dictionary::clear() {
    postOrderDelete(root);
    root = nil;
    current = nil;
}


void Dictionary::setValue(keyType k, valType v) {
    Node *y = nil;
    Node *x = root;
    // pre existing case
    if (search(root, k) != nil) {
        Node *T = search(root, k);
        T->val = v;
        return;
    }
    while (x != nil) {
        y = x;
        if (k < x->key) {
            x = x->left;
        }
        else {
            x = x->right;
        }
    }
        // we have found where the leaf needs to go that this point
    if (y == nil) {
        root = new Node(k, v);
        root->parent = nil; 
        num_pairs += 1;
        return;
    }
    if (k < y->key) {
        y->left = new Node(k, v);
        y->left->parent = y;
    }
    else {
        y->right = new Node(k, v);
        y->right->parent = y;
    }
    num_pairs += 1;
}



void Dictionary::transplant(Node* U, Node* V) {
    if (U->parent == nil) {
        root = V;
    } else if (U == U->parent->left) {
        U->parent->left = V;
    } else {
        U->parent->right = V;
    }
    if (V != nil) {
        V->parent = U->parent;
    }
}


void Dictionary::remove(keyType k) {
    if (!contains(k)) {
        throw std::logic_error("Dictionary: remove(): they key does not exist in the dictionary");
    }
    Node *N = search(root, k);
    // current case
    if (N == current) {
        current = nil;
    }
    // right child assention
    if (N->left == nil) {
        transplant(N, N->right);
    }
    // left child assention
    else if (N->right == nil) {
        transplant(N, N->left);
    }
    // 2 child case, the parent leaf trap
    else {
        Node *y = findNext(N);
        if (y->parent != N) {
            transplant(y, y->right);
            y->right = N->right;
            y->right->parent = y;
        }
        transplant(N, y);
        y->left = N->left;
        y->left->parent = y;
    }
    N->left = nullptr;
    N->right = nullptr;
    N->parent = nullptr;
    delete N;
    num_pairs -= 1;
}


/////////////////////////////////////////////////// moving through the dictionary ///////////////////////////////////////////////////////


void Dictionary::begin() {
    current = findMin(root);
}


void Dictionary::end() {
    current = findMax(root);
}


void Dictionary::next() {
    if (!hasCurrent()) {
        throw std::logic_error("Dictionary: next: you cant move next on nil, BAD!");
    }
    current = findNext(current);
}


void Dictionary::prev() {
    if (!hasCurrent()) {
        throw std::logic_error("Dictionary: prev: you cant move prev on nil, BAD!");
    }
    current = findPrev(current);
}

////////////////////////////////////////////// String stuff ////////////////////////////////////////////////////////////////

std::string Dictionary::to_string() const {
    std::string s = "";
    inOrderString(s, root);
    return s;
}


std::string Dictionary::pre_string() const {
    std::string s = "";
    preOrderString(s, root);
    return s;
}


bool Dictionary::equals(const Dictionary& D) const {
    if (num_pairs != D.num_pairs) {
        return false;
    }
    Dictionary A = *this;
    Dictionary B = D;
    if (A.to_string().compare(B.to_string()) != 0) {
        return false;
    } 
    return true;
}


/////////////////////////////////////////// Overloaded operators ///////////////////////////////////////////////////////////

std::ostream& operator<<( std::ostream& stream, Dictionary& D ) {
    return stream << D.Dictionary::to_string();
}

bool operator==( const Dictionary& A, const Dictionary& B ) {
    return A.equals(B);
}

Dictionary& Dictionary::operator=( const Dictionary& D ) { // might need some fixing in the end
    if (this != &D) {
        Dictionary newt = D;

        std::swap(nil, newt.nil);
        std::swap(root, newt.root);
        std::swap(current, newt.current);
        std::swap(num_pairs, newt.num_pairs);
    }
    return *this;
}