#ifndef _TREE_H_

    #include <iostream>
    #include <string>
    #include <vector>

    using namespace std;

    class Tree {

    private:
            Tree  * left_ptr;
            Tree  * right_ptr;
            vector<string> value;

    public:
            Tree();
            Tree(string);

            Tree * getLeftTree();
            Tree * getRightTree();
            string getValue(int);
            vector<string> getValue();

            void setLeftTree(Tree * leftTree);
            void setRightTree(Tree * rightTree);
            void setValue(string);

            void add(string);

            bool find(string);

    };




#endif