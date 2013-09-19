#ifndef _NODE_CPP_

    #include "tree.h"

    Tree::Tree() {
        left_ptr    = NULL;
        right_ptr   = NULL;
    };

    Tree::Tree(string str) {
        left_ptr    = NULL;
        right_ptr   = NULL;
        value.push_back(str);
    }

    Tree * Tree::getLeftTree () {
        return left_ptr;
    };

    Tree * Tree::getRightTree () {
        return right_ptr;
    };

    void Tree::setLeftTree (Tree * _leftTree) {
        left_ptr = _leftTree;
    };

    void Tree::setRightTree (Tree * _rightTree) {
        right_ptr = _rightTree;
    };

    string Tree::getValue (int index) {
        return value[index];
    };

    vector<string> Tree::getValue() {
        return value;
    };

    void Tree::setValue (string _value) {
        value.push_back(_value);
    };

    void Tree::add(string new_value) {
        if(value.empty()) {
            value.push_back(new_value);
            return;
        }

        Tree * current = this;

        while(true) {
            if(new_value[0] > current->getValue(0)[0]) {
                if (current->getRightTree() == NULL) {
                    current->setRightTree( new Tree(new_value));
                    break;
                } else {
                    current = current->getRightTree();
                }
            } else if(new_value[0] < current->getValue(0)[0]) {
                if(current->getLeftTree() == NULL) {
                    current->setLeftTree( new Tree(new_value));
                    break;
                } else {
                    current = current->getLeftTree();
                }
            } else {
                current->setValue(new_value);
                break;
            }
        }
    };

    bool Tree::find(string str) {

        Tree * current = this;

        while(true) {
            if(str[0] < current->getValue(0)[0]) {
                if(current->getLeftTree() != NULL) {
                    current = current->getLeftTree();
                    continue;
                } else {
                    return false;
                }
            } else if(str[0] > current->getValue(0)[0]) {
                if( current->getRightTree() != NULL) {
                    current = current->getRightTree();
                    continue;
                }else {
                    return false;
                }
            } else {
                int collisions = 0;
                for(int i = 0; i < current->getValue().size(); i++) {
                    if(str == current->getValue()[i]) {
                        cout << "Number of iteration on collision: " << collisions << "\n";
                        return true;
                    }
                    collisions++;
                }
                return false;
            }
        }
    }







#endif