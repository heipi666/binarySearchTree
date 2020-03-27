#include <iostream>
#include <stdlib.h>
#include <ctime>

template <typename Key, typename Value>
class Bst {
private:
    struct Node {
        Key key;
        Value value;
        Node* left;
        Node* right;
        Node(Key key, Value value) {
            this->key = key;
            this->value = value;
            this->left = this->right = NULL;
        }
        
    };
    int count;
    Node* root;
    
public:
    Bst() {
        root = NULL;
        count = 0;
    }
    ~Bst() {
        //释放整个树，采取后序遍历的方法，因为需要先释放叶子节点
        destory(root);
    }
    int size() {
        return count;
    }
    bool isEmpty() {
        return !count;
    }

    void insert(Key key, Value value) {
        root = insert(root, key, value);
    }

    bool contian(Key key) {
        return contian(root, key);
    }
    //如果返回值写成Value
    // 会出现查找不存在时，无法判断返回值和未查到的区别
    Value *search(Key key) {
        return search(root, key);
    }

    void preOrder() {
        preOrder(root);
    }
    void inOrder() {
        inOrder(root);
    }
    void postOrder() {
        postOrder(root);
    }

private:
    //向以node为根的节点插入（key，value）的数据。
    //返回插入新的节点后的二叉树的根
    Node* insert(Node* node, Key key, Value value) {

        if (node == NULL) {
            count++;
            return new Node(key, value);
        }

        if (key == node->key) {
            node->value = value;
        }
        else if (key > node->key) {
            node->right = insert(node->right, key, value);
        }
        else {
            node->left = insert(node->left, key, value);
        }
        return node;
    }
    
    bool contain(Node* node, Key key) {
        //如果节点为空，直接返回false
        if (node == NULL) {
            return false;
        }
        if (key == node->key) {
            return true;
        }
        else if (key < node->key) {
            return contain(node->left, key);
        }
        else {  //  key > node->key
            return contain(node->right, key);
        }

    }
    Value *search(Node* node, Key key) {
        if (node == NULL) {
            return NULL;
        }
        if (key == node->key) {
            return &node->value;
        }
        else if (key < node->key) {
            return search(node->left, key);
        }
        else {
            return search(node->right, key);
        }
    }

    void preOrder(Node* node) {
        if (node == NULL) {
            return;
        }
        std::cout << node->key << std::endl;
        preOrder(node->left);
        preOrder(node->right);
        
    }

    //采用中序遍历打印的结果的key是有序的
    void inOrder(Node* node) {
        if (node == NULL) {
            return;
        }
        inOrder(node->left);
        std::cout << node->key << std::endl;
        inOrder(node->right);
    }

    //后序遍历
    void postOrder(Node* node) {
        if (node != NULL) {
            postOrder(node->left);
            postOrder(node->right);
            std::cout << node->key << std::endl;
        }
    }

    void destory(Node* node) {
        if (node != NULL) {
            destory(node->left);
            destory(node->right);
            delete node;
            count--;
        }
    }

};

int main01(int argc, char const* argv[])
{
    Bst<int, int> bst;
    srand((unsigned int)time(NULL));
    for (int i = 0; i < 100; i++) {
        bst.insert(rand() % 100,i);
    }
    std::cout << "bst isEmpty" << bst.isEmpty() << std::endl;
    std::cout << "bst size" << bst.size() << std::endl;
    std::cout << "search 55:" << *bst.search(9) << std::endl;
    
    std::cout << "preOrder:" << std::endl;
    bst.preOrder();
    std::cout << "inOrder:" << std::endl;
    bst.inOrder();
    std::cout << "postOrder:" << std::endl;
    bst.postOrder();

    return 0;
}
