#include <iostream>  
#include "List.h" // 包含 List 类的头文件  


//输出函数-->测试迭代器
void printList(const List<int>& myList) {  
    for (auto it = myList.begin(); it != myList.end(); ++it) {  
        std::cout << *it << " ";  
    }  
    std::cout << std::endl;  
}  
  
int main() {  
    // 测试创建和初始化  
    List<int> list1; // 创建一个空列表  
    List<int> list2 = {1, 2, 3, 4}; // 创建一个带有初始值的列表  
  
    // 输出list2  
    std::cout << "list2: " ;
    printList(list2);
  
    // 测试大小和空  
    std::cout << "the size of list2: " << list2.size() << std::endl;  
    std::cout << "Is list1 empty?" << (list1.empty() ? "yes" : "no") << std::endl;  
  
    // 测试插入 
    list1.push_back(5);  //在尾部插入 5
    list1.push_front(0);   //在第一个元素前插入 0
    list1.insert(++list1.begin(), 2); // 在特定位置插入，即在第一个元素后出入 2 ,同时检查++

    //输出list1检查结果: 0 2 5
    std::cout << "list1: " ;
    printList(list1); 

    //测试删除
    list1.erase(--(--list1.end()));  //删除倒数第二个元素,同时检查--
    printList(list1); 
    list1.pop_back();  //删除最后一个元素
    printList(list1); 
    list1.pop_front();  //删除首元素
    printList(list1);   
  
    // 测试访问首尾元素  
    std::cout << "The first element of list2: " << list2.front() << std::endl;  
    std::cout << "The last element of list2: " << list2.back() << std::endl;  
  
    // 测试复制和移动语义  
    List<int> list3 = list2; // 测试复制构造函数  
    std::cout << "list2: " ;
    printList(list3); 
    List<int> list4(std::move(list3)); // 测试移动构造函数  
    std::cout << "list4: " ;
    printList(list4); 
    list1 = list2; // 测试复制赋值运算符  
    std::cout << "list1: " ;
    printList(list1); 
    list1.pop_front(); //修改list1，用于下一语句区别原来的list2
    list2 = std::move(list1); // 测试移动赋值运算符 
    std::cout << "list2: " ;
    printList(list2); 
     
  
    // 测试清空函数  
    list2.clear();  
    std::cout << "After clearing, is list2 empty?" << (list2.empty() ? "yes" : "no") << std::endl;  
  
    return 0;  
}  