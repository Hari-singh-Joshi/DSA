#include <iostream>
#include<climits>
#include<vector>
#include<set>
#include<unordered_map>
#include<map>
#include<string>
#include<algorithm>
using namespace std;
class BinaryNode{
    public:
    int data,height;
    BinaryNode *left,*right;
    BinaryNode(int data){
        this->data=data;
        this->height=1;
        left=right=NULL;
    }
};
class AVL{
    public:
    BinaryNode *root;
    AVL(){
        root=NULL;
    }
    void preorder(BinaryNode *node){
        if(node==NULL){
            return;
        }
        cout<<node->data<<" ";
        preorder(node->left);
        preorder(node->right);
    }
    void postorder(BinaryNode *node){
        if(node==NULL){
            return;
        }
        
        postorder(node->left);
        postorder(node->right);
        cout<<node->data<<" ";
    }
    int getheight(BinaryNode* node){
        if(node==nullptr){
            return 0;

        }
        else{
            return node->height;
        }
    }
    int getBalanceFactor(BinaryNode* node){
        if(node==nullptr){
            return 0;
        }
        else{
            return getheight(node->left)-getheight(node->right);
        }
    }
    BinaryNode* rotateRight(BinaryNode* node){
        BinaryNode* nr=node->left;
        node->left=nr->right;
        nr->right=node;
        node->height=1+max(getheight(node->left),getheight(node->right));
        nr->height=1+max(getheight(nr->left),getheight(nr->right));
        return nr;
    }
     BinaryNode* rotateLeft(BinaryNode* node){
        BinaryNode* nr=node->right;
        node->right=nr->left;
        nr->left=node;
        node->height=1+max(getheight(node->left),getheight(node->right));
        nr->height=1+max(getheight(nr->left),getheight(nr->right));
        return nr;
    }
    BinaryNode* insertNode(BinaryNode* node, int data) {
    // Step 1: Perform the normal BST insert
    if (node == nullptr) {
        return new BinaryNode(data);
    } 
    if (data < node->data) {
        node->left = insertNode(node->left, data);
    } 
    else if (data > node->data) {
        node->right = insertNode(node->right, data);
    } 
    else {
        // Duplicate data is not allowed in the AVL tree
        return node; 
    }

    // Step 2: Update the height of this ancestor node
    node->height = 1 + max(getheight(node->left), getheight(node->right));

    // Step 3: Get the balance factor of this ancestor node
    int balance = getBalanceFactor(node);

    // Step 4: If this node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && data < node->left->data) {
        return rotateRight(node);
    }
    // Right Right Case
    if (balance < -1 && data > node->right->data) {
        return rotateLeft(node);
    }
    // Left Right Case
    if (balance > 1 && data > node->left->data) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    // Right Left Case
    if (balance < -1 && data < node->right->data) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    // Return the (unchanged) node pointer
    return node;
}

    void insert(int data){
        root=insertNode(root,data);
    }
};

int main(){

    AVL ob;
    ob.insert(30);
    ob.insert(25);
    ob.insert(35);
    
    
    ob.insert(20);
    ob.insert(15);
    ob.insert(5);
    ob.insert(10);
    ob.insert(50);
    ob.insert(60);
    ob.insert(70);
    ob.insert(65);
    ob.preorder(ob.root);
 

    return 0;
}