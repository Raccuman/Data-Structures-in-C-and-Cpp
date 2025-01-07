/***
* Catherine Bronte
* cebronte 1969208
* 2024 Fall CSE101 PA8
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

////////////////////////////////////// new stuff ///////////////////////////////////////////////////////////////

void Dictionary::LeftRotate(Node* N) {
    Node *y = N->right; 
    N->right = y->left; 
    if (y->left != nil) {
        y->left->parent = N;
    }     

    y->parent = N->parent; 
    if (N->parent == nil) {
        root = y;
    } else if (N == N->parent->left) {
        N->parent->left = y;
    } else {
        N->parent->right = y;
    }
    
    y->left = N;
    N->parent = y;
}


void Dictionary::RightRotate(Node* N) {
    Node *y = N->left; 
    N->left = y->right; 
    if (y->right != nil) {
        y->right->parent = N;
    }     

    y->parent = N->parent; 
    if (N->parent == nil) {
        root = y;
    } else if (N == N->parent->right) {
        N->parent->right = y;
    } else {
        N->parent->left = y;
    }

    y->right = N;
    N->parent = y;
}


void Dictionary::RB_InsertFixUp(Node* N) {
    Node *y;
    while (N->parent->color == 1) {
        if (N->parent == N->parent->parent->left) {
            y = N->parent->parent->right;
            if (y->color == 1) {
                N->parent->color = 0;
                y->color = 0;
                N->parent->parent->color = 1;
                N = N->parent->parent;
            } else {
                if (N == N->parent->right) {
                    N = N->parent;
                    LeftRotate(N);
                }
                N->parent->color = 0;
                N->parent->parent->color = 1;
                RightRotate(N->parent->parent);
            }
        } else {
            y = N->parent->parent->left;
            if (y->color == 1) {
                N->parent->color = 0;
                y->color = 0;
                N->parent->parent->color = 1;
                N = N->parent->parent;
            } else {
                if (N == N->parent->left) {
                    N = N->parent;
                    RightRotate(N);
                }
                N->parent->color = 0;
                N->parent->parent->color = 1;
                LeftRotate(N->parent->parent);
            }
        }
    }
    root->color = 0;
}


void Dictionary::RB_Transplant(Node* u, Node* v) {
    if (u->parent == nil) {
        root = v;
    } else if ( u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    v->parent = u->parent;
}


void Dictionary::RB_DeleteFixUp(Node* N) {
    while (N != root && N->color == 0) {
        Node *w;
        if (N == N->parent->left) {
            w = N->parent->right;
            if (w->color == 1) {
                w->color = 0;
                N->parent->color = 1;
                LeftRotate(N->parent);
                w = N->parent->right;
            }
            if (w->left->color == 0 && w->right->color == 0) {
                w->color = 1;
                N = N->parent;
            } else {
                if (w->right->color == 0) {
                    w->left->color = 0;
                    w->color = 1;
                    RightRotate(w);
                    w = N->parent->right;
                }
                w->color = N->parent->color;
                N->parent->color = 0;
                w->right->color = 0;
                LeftRotate(N->parent);
                N = root;
            }
        } else {
            w = N->parent->left;
            if (w->color == 1) {
                w->color = 0;
                N->parent->color = 1;
                RightRotate(N->parent);
                w = N->parent->left;
            }
            if (w->right->color == 0 && w->left->color == 0) {
                w->color = 1;
                N = N->parent;
            } else {
                if (w->left->color == 0) {
                    w->right->color = 0;
                    w->color = 1;
                    LeftRotate(w);
                    w = N->parent->left;
                }
                w->color = N->parent->color;
                N->parent->color = 0;
                w->left->color = 0;
                RightRotate(N->parent);
                N = root;
            }
        }
    }
    N->color = 0;
}


void Dictionary::RB_Delete(Node* N) {
    Node *y = N;
    Node *x;
    int C = y->color;
    if (N->left == nil) {
        x = N->right;
        RB_Transplant(N, N->right);
    } else if (N->right == nil) {
        x = N->left;
        RB_Transplant(N, N->left);
    } else {
        y = findMin(N->right);
        C = y->color;
        x = y->right;
        if (y->parent == N) {
            x->parent = y;
            
        } else {
            RB_Transplant(y, y->right);
            y->right = N->right;
            y->right->parent = y;
        }
        RB_Transplant(N, y);
        y->left = N->left;
        y->left->parent = y;
        y->color = N->color;
        
    }
    if (C == 0) {
        RB_DeleteFixUp(x);
    }
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
        s.append(R->key);
        if (R->color == 1) {
            s.append(" (RED)");
        }
        s.append("\n");

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


void Dictionary::postOrderDelete(Node* R) {
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
    nil = new Node("nil", -1); // the nill node
    root = nil; // gets defined later
    current = nil; // the current node, the cursor system
    nil->color = 0;
    num_pairs = 0; 
}

// its like dictionary but you gave it some stuff to start with, it copies over the dict
Dictionary::Dictionary(const Dictionary& D) {
    nil = new Node("nil", -1); // the nill node
    root = nil; // gets defined later
    current = nil; // the current node, the cursor system
    num_pairs = 0; 
    nil->color = 0;
    (*this).preOrderCopy(D.root, D.nil);
}


Dictionary::~Dictionary() {
    clear();
    delete nil;
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
    Node *n = new Node(k, v);
    while (x != nil) {
        y = x;
        int cp = n->key.compare(x->key);
        if (cp == 0) {
            x->val = v;
            delete n;
            return;
        }
        if (cp < 0) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    n->parent = y;
    if (y == nil) {
        root = n;
    } else if (n->key.compare(y->key) < 0) {
        y->left = n;
    } else {
        y->right = n;
    }
    n->left = nil;
    n->right = nil;
    n->color = 1;
    RB_InsertFixUp(n);
    num_pairs += 1;
}


void Dictionary::remove(keyType k) { // this guy will need the new transplant
    if (contains(k) == false) {
        throw std::logic_error("Dictionary Error: remove(), K is not in the dictionary");
    }
    
    Node *N = search(root, k);
    if (N == current) {
        current = nil;
    }    
    RB_Delete(N);
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