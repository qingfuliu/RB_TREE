#include"R_BTree.h"
#include<iostream>
int main(){
    R_BTree<int> Tree;
    Tree.insert(10);
     std::cout<<Tree.toString()<<std::endl;
    Tree.insert(70);
     std::cout<<Tree.toString()<<std::endl;
    Tree.insert(32);
       std::cout<<Tree.toString()<<std::endl;
    Tree.insert(34);
    Tree.insert(13);
    Tree.insert(56);
    Tree.insert(32);
    Tree.insert(21);
    Tree.insert(36);
    Tree.insert(24);
    std::cout<<Tree.toString()<<std::endl;
    // Tree.delete_node(24);
    // Tree.delete_node(13);
    // std::cout<<Tree.toString()<<std::endl;
    return 0;
}
