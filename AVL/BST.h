#include <iostream>
#include <algorithm>  //用于取最值

class UnderflowException { };
class IllegalArgumentException { };
class ArrayIndexOutOfBoundsException { };
class IteratorOutOfBoundsException { };
class IteratorMismatchException { };
class IteratorUninitializedException { };

template <typename Comparable>
class BinarySearchTree
{
public:
    BinarySearchTree() : root{ nullptr } {} //默认构造函数
    BinarySearchTree(const BinarySearchTree &rhs) : root{ clone(rhs.root) } {} //拷贝构造函数（深拷贝）
    BinarySearchTree(BinarySearchTree &&rhs) noexcept : root{ rhs.root } { //移动构造函数
        rhs.root = nullptr;
    }
    ~BinarySearchTree() { //析构函数
        makeEmpty();
    }

    const Comparable &findMin() const {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMin(root)->element;
    }

    const Comparable &findMax() const {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMax(root)->element;
    }

    bool contains(const Comparable &x) const { //检查树是否包含指定元素
        return contains(x, root);
    }

    bool isEmpty() const {
        return root == nullptr;
    }

    void printTree(std::ostream &out = std::cout) const {
        if (isEmpty()) {
            out << "Empty tree" << std::endl;
        } else {
            printTree(root, out);
        }
    }

    void makeEmpty() {
        makeEmpty(root);
    }

    void insert(const Comparable &x) {  //插入一个常量引用元素到树中(左值引用)
        insert(x, root);
    }

    void insert(Comparable &&x) {  //插入一个右值引用元素到树中
        insert(std::move(x), root);
    }

    void remove(const Comparable &x) {
        remove(x, root);
    }

    BinarySearchTree &operator=(const BinarySearchTree &rhs) {
        if (this != &rhs) {
            BinarySearchTree temp(rhs);
            std::swap(root, temp.root);
        }
        return *this;
    }

    BinarySearchTree &operator=(BinarySearchTree &&rhs) noexcept {
        std::swap(root, rhs.root);
        return *this;
    }

protected:
    struct BinaryNode
    {
        Comparable element;
        BinaryNode *left;
        BinaryNode *right;
        int height = 0;  //新增加高度height

        BinaryNode(const Comparable &theElement, BinaryNode *lt, BinaryNode *rt)
            : element{ theElement }, left{ lt }, right{ rt } {}

        BinaryNode(Comparable &&theElement, BinaryNode *lt, BinaryNode *rt)
            : element{ std::move(theElement) }, left{ lt }, right{ rt } {}
    };


    int height(BinaryNode *node){
        return node == nullptr ? 0 : node->height; //空节点的高度为0
    }

    void updateHeight(BinaryNode *node){
        node->height = 1 + std::max(height(node->left), height(node->right));
    }

    /* 获取平衡因子 */
    int balanceFactor(BinaryNode *node) {
        if (node == nullptr) // 空节点平衡因子为 0
            return 0;
        return height(node->left) - height(node->right); // 节点平衡因子 = 左子树高度 - 右子树高度
    }

    /* 右旋操作 */
    BinaryNode *rightRotate(BinaryNode *node) {
        // 设定 child 为 node 的左子节点，grandChild 为左子节点的右子节点
        BinaryNode *child = node->left;
        BinaryNode *grandChild = child->right;
        // 将 node 向右旋转，更新后以 node 的左子树（child）为原点
        child->right = node;
        node->left = grandChild;
        // 更新节点高度
        updateHeight(node);
        updateHeight(child);
        // 返回旋转后子树的根节点
        return child;
    }


    /* 左旋操作 */
    BinaryNode *leftRotate(BinaryNode *node) {
        // 设定 child 为 node 的右子节点，grandChild 为右子节点的左子节点
        BinaryNode *child = node->right;
        BinaryNode *grandChild = child->left;
        // 将 node 向左旋转，更新后以 node 的右子树（child）为原点
        child->left = node;
        node->right = grandChild;
        // 更新节点高度
        updateHeight(node);
        updateHeight(child);
        // 返回旋转后子树的根节点
        return child;
    }


    /* 执行旋转操作，使该子树重新恢复平衡 */
    BinaryNode *rotate(BinaryNode *node) {
        if (node == nullptr ) return nullptr;
        // 获取节点 node 的平衡因子
        int _balanceFactor = balanceFactor(node);
        // 左偏
        if (_balanceFactor > 1) {
            if (balanceFactor(node->left) >= 0) {
                // 右旋
                return rightRotate(node);
            } else {
                // 先左旋后右旋
                node->left = leftRotate(node->left);
                return rightRotate(node);
            }
        }
        // 右偏
        if (_balanceFactor < -1) {
            if (balanceFactor(node->right) <= 0) {
                // 左旋
                return leftRotate(node);
            } else {
                // 先右旋后左旋
                node->right = rightRotate(node->right);
                return leftRotate(node);
            }
        }
        return node;
    }

    BinaryNode *root;

    BinaryNode *findMin(BinaryNode *t) const {
        if (t == nullptr) {
            return nullptr;
        }
        if (t->left == nullptr) {
            return t;
        }
        return findMin(t->left);
    }

    BinaryNode *findMax(BinaryNode *t) const {
        if (t != nullptr) {
            while (t->right != nullptr) {
                t = t->right;
            }
        }
        return t;
    }

    bool contains(const Comparable &x, BinaryNode *t) const {
        if (t == nullptr) {
            return false;
        }
        if (x < t->element) {
            return contains(x, t->left);
        } 
        else if (x > t->element) {
            return contains(x, t->right);
        } 
        else {
            return true;
        }
    }

    void printTree(BinaryNode *t, std::ostream &out) const {
        if (t != nullptr) {
            printTree(t->left, out);
            out << t->element << std::endl;
            printTree(t->right, out);
        }
    }

    void makeEmpty(BinaryNode * &t) {
        if (t != nullptr) {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
            t = nullptr;
        }
    }

void insert(const Comparable &x, BinaryNode * &t) {
        if (t == nullptr) {
            t = new BinaryNode{x, nullptr, nullptr};
        } else if (x < t->element) {
            insert(x, t->left);
        } else if (x > t->element) {
            insert(x, t->right);
        } else {
        } 
        rotate(t);
    }

    void insert(Comparable &&x, BinaryNode * &t) {
        if (t == nullptr) {
            t = new BinaryNode{std::move(x), nullptr, nullptr};
        } else if (x < t->element) {
            insert(std::move(x), t->left);
        } else if (x > t->element) {
            insert(std::move(x), t->right);
        } else {
        } 
        rotate(t);
    }


    void remove(const Comparable &x, BinaryNode *&t) {
        if (t == nullptr) {
            return;  
        }
        if (x < t->element) {
            remove(x, t->left);
        } else if (x > t->element) {
            remove(x, t->right);
        } else if (t->left != nullptr && t->right != nullptr) {  
            BinaryNode *s = detachMin(t->right);
            s->left = t->left;
            s->right = t->right;
            t = s;
        } else {
            BinaryNode *oldNode = t;
            t = (t->left != nullptr) ? t->left : t->right;  
            delete oldNode;  
        } 
        rotate(t);
    }


    BinaryNode *detachMin(BinaryNode *&t) {
        if (t == nullptr) {
            return nullptr; // 子树为空
        } else if (t->left != nullptr) {
            return detachMin(t->left); // 递归查找最小节点
        } else {
            // 找到最小节点
            BinaryNode *minNode = t;
            t = t->right; // 从树中移除最小节点
            return minNode; // 返回最小节点
        }
    }

    BinaryNode *clone(BinaryNode *t) const {
        if (t == nullptr) {
            return nullptr;
        }
        return new BinaryNode{t->element, clone(t->left), clone(t->right)};
    }
};
