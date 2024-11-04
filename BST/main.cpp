#include <iostream>
#include "BinarySearchTree.h"  

int main() {
    BinarySearchTree<int> bst;

    // 插入一些元素构造样本组
    bst.insert(10);
    bst.insert(5);
    bst.insert(15);
    bst.insert(3);
    bst.insert(7);
    bst.insert(12);
    bst.insert(18);
    bst.insert(20);

    // 打印初始树结构
    std::cout << "Initial Tree:" << std::endl;
    bst.printTree();

    // 测试remove函数的功能
    bst.remove(7);  //测试删除叶子节点
    std::cout << "Tree after removing 7:" << std::endl;
    bst.printTree();

    bst.remove(5);  //测试删除只有左子节点的节点
    std::cout << "Tree after removing 5:" << std::endl;
    bst.printTree();

    bst.remove(20);  //测试删除只有右子节点的节点
    std::cout << "Tree after removing 20:" << std::endl;
    bst.printTree();

    bst.remove(10);  //测试删除根节点，同时也是有两个子节点的节点
    std::cout << "Tree after removing 10:" << std::endl;
    bst.printTree();

    bst.makeEmpty();  //清空树
    return 0;
}