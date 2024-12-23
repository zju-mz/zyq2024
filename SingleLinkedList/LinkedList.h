#include <initializer_list>
#include <iostream>

template <typename T>
class SingleLinkedList
{
private:
    class Node
    {
    private:
        T data;
        Node *next = nullptr;
        Node(T _val){data = _val;}

        friend class SingleLinkedList<T>;
    };
    Node* head = nullptr;
    int size = 0;
    Node* currentPos = nullptr;
    void _emptyList();
    void _copy(const SingleLinkedList<T> &_l);
public:
    /// 返回当前位置的值
    T getCurrentVal() const;
    /// 设置当前位置的值
    void setCurrentVal(const T &_val);
    /// 如果链表为空，返回 true；否则返回 false
    bool isEmpty() const;

    int getSize() const;
    void emptyList();
    bool find (const T &_val);
    SingleLinkedList(){};
    ~SingleLinkedList(); 
    SingleLinkedList(std::initializer_list<T> _l);
    void printList() const;
    SingleLinkedList(const SingleLinkedList<T> &_l);
    SingleLinkedList<T>& operator=(const SingleLinkedList<T> &_l);

    /// 在 currentPos 后面插入一个元素，数据为 _val
    void insert(T _val); 
    /// 如果找到，返回 ture, currentPos 停留在第一个 _val 的位置。
    /// 否则返回 false, currentPos 不动。
    bool find(const T &_val) const;  
    /// 删除 currentPos 后面的元素
    void remove();    
    void removecurrent(); //修改remove函数                                   
};

template<typename T>
bool SingleLinkedList<T>::find(const T &_val)
{
    Node *p = head;
    while (p != nullptr)
    {
        if (p->data == _val)
        {
            currentPos = p;
            return true;
        }
        p = p->next;    
    }
    return false;
}

template<typename T>
int SingleLinkedList<T>::getSize() const
{
    return size;
}

template <typename T>
SingleLinkedList<T>::SingleLinkedList(std::initializer_list<T> _l)
{
    for (auto i = _l.begin(); i != _l.end(); ++i)
    {
        Node* newNode = new Node(*i);
        if (head == nullptr)
        {
            head = newNode;
            currentPos = head;
        }
        else
        {
            currentPos->next = newNode;
            currentPos = newNode;
        }
        ++size;
    }
}

template <typename T>
void SingleLinkedList<T>::_emptyList()
{
    Node* p = head;
    while (p != nullptr)
    {
        Node* t = p;
        p = p->next; 
        delete t;
    }
}

template <typename T>
void SingleLinkedList<T>::printList() const
{
    Node* p = head;
    while (p != nullptr)
    {
        std::cout << p->data << "\t";
        p = p->next;
    }
    std::cout << std::endl;    
}

template <typename T>
SingleLinkedList<T>::~SingleLinkedList()
{
    _emptyList();
};

template<typename T>
SingleLinkedList<T>::SingleLinkedList(const SingleLinkedList<T> &_l)
{
    _copy(_l);
}

template<typename T>
void SingleLinkedList<T>::emptyList()
{
    _emptyList();
    head = nullptr;
    currentPos = nullptr;
    size = 0;
}

template<typename T>
SingleLinkedList<T>& SingleLinkedList<T>::operator=(const SingleLinkedList<T> &_l)
{
    if (this == &_l)
        return *this;
    emptyList();
    _copy(_l);
    return *this;
}

template <typename T>
void SingleLinkedList<T>::_copy(const SingleLinkedList<T> &_l)
{
    Node *p = _l.head;
    while (p != nullptr)
    {
        Node* newNode = new Node(p->data);
        if (head == nullptr)
        {
            head = newNode;
            currentPos = head;
        }
        else
        {
            currentPos->next = newNode;
            currentPos = newNode;
        }
        ++size;
        p = p->next;
    }
}

//作业
//1.T getCurrentVal() const:返回当前位置的值，若当前位置为空，则报错"Empty current position! Can't get value!"并停止退出；
template <typename T>
T SingleLinkedList<T>::getCurrentVal() const
{
    if (currentPos == nullptr)
    {
        throw std::runtime_error("Empty current position! Can't get value!");
    }
    return currentPos->data;
}

//2.void setCurrentVal(const T &_val):设置当前位置的值,若当前位置为空，则报错"Empty current position! Can't setvalue!"并停止退出；
template <typename T>
void SingleLinkedList<T>::setCurrentVal(const T &_val)
{
    if (currentPos == nullptr)
    {
        throw std::runtime_error("Empty current position! Can't setvalue!");
    }
    currentPos->data = _val;
}

//3.bool isEmpty() const:判断链表是否为空
template <typename T>
bool SingleLinkedList<T>::isEmpty() const
{
    if (head == nullptr){
        return true;
    }
    else{
        return false;
    }
}

//4.void insert(T _val):若为空链表则插入一个元素；若非空，则在当前位置后插入一个元素，值为_val；
template <typename T>
void SingleLinkedList<T>::insert(T _val)
{
    Node *newNode = new Node(_val);
    if (isEmpty()){
        head = newNode;
        newNode->next = nullptr;
        currentPos = head;
    }
    else{
        //修正：对于非空链表且当前位置为空的问题，我的处理是将新元素插在列表头部
        if (currentPos == nullptr){
            newNode->next = head;
            head = newNode;
            currentPos = newNode;
        }
        else{
            newNode->next = currentPos->next;
            currentPos->next = newNode;
            currentPos = newNode;
        }
    }
    ++size;
}

//5.void remove():若当前位置为空则不进行操作；若链表仅有一个元素则删除此元素成为空链表；
//若链表有超过一个元素且当前位置不为最后一个，则删除后一个元素.
template <typename T>
void SingleLinkedList<T>::remove()
{
    if (currentPos == nullptr){
        return;
    }
    if (size == 1){
        delete head;
        head = nullptr;
        currentPos = nullptr;
    }
    else{
        Node *p = currentPos->next;
        currentPos->next = p -> next;
        delete p;
    }
    size--;
}

//remove函数的修正:空链表不进行操作；若链表仅有一个元素则删除此元素成为空链表；
//若链表有超过一个元素且当前位置不为空，则删除当前位置的元素.
template <typename T>
void SingleLinkedList<T>::removecurrent()
{
    if (size == 0){
        return;
    }
    if (size == 1){
        delete head;
        head = nullptr;
        currentPos = nullptr;
    }
    else{
        if (currentPos != nullptr){
            if (currentPos == head){
                Node *temp = head;
                head = head->next;
                delete temp;
                currentPos = head;
            }
            else{
                Node *pre = head;
                while (pre!=nullptr && pre->next != currentPos){
                    pre = pre->next;
                }
                if (pre != nullptr){
                    pre->next = currentPos->next;
                    delete currentPos;
                    currentPos = pre->next;
                }
            }
        }
    }
    size--;
}
