#include<stdio.h>
struct Node
{
    int key;
    struct Node* left;
    struct Node* right;
    int height;
};
int max(int a,int b){
    if(a>=b) return a;
    else return b;
}
int getHeight(struct Node* n)
{
    if(n==NULL) return 0;
    return n->height;
}
struct Node* createNode(int key){
    struct Node* node=(struct Node*)malloc(sizeof(struct Node));
    node->key=key;
    node->left=NULL;
    node->right=NULL;
    node->height=1; //height for null is zero
    return node;
}
int getBF(struct Node* n){
    if(n==NULL) return 0;
    return (getHeight(n->left)-getHeight(n->right));
}
struct Node* rightRotate(struct Node *y){
    struct Node *x=y->left;
    struct Node *t2=x->right;
    x->right=y;
    y->left=t2;
    y->height=max(getHeight(y->right),getHeight(y->left))+1;
    x->height=max(getHeight(x->right),getHeight(x->left))+1;
    return x;
}
struct Node* leftRotate(struct Node *y){
    struct Node *x=y->right;
    struct Node *t2=x->left;
    x->left=y;
    y->right=t2;
    y->height=max(getHeight(y->right),getHeight(y->left))+1;
    x->height=max(getHeight(x->right),getHeight(x->left))+1;
    return x;
}
struct Node* insert(struct Node* node,int key){
    if(node==NULL) return(createNode(key));
    if(key<node->key) node->left=insert(node->left,key);
    else if(key>node->key) node->right=insert(node->right,key);
    node->height=1+max(getHeight(node->left),getHeight(node->right));
    int bf=getBF(node);
    //case1: LEFT LEFT CASE
    if(bf>1&&key<node->left->key){
        return rightRotate(node);
    }
    //case2: RIGHT RIGHT CASE
    if(bf<-1&&key>node->right->key){
        return leftRotate(node);
    }
    //case3: LEFT RIGHT CASE
    if(bf>1&&key>node->left->key){
        node->left=leftRotate(node->left);
        return rightRotate(node);
    }
    //case4: RIGHT LEFT CASE
    if(bf<-1&&key<node->right->key){
        node->right=rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}
void preorder(struct Node* root){
    if(root==NULL) return;
    printf("%d ",root->key);
    preorder(root->left);
    preorder(root->right);
}
void main(){
    struct Node* root=NULL;
    root=insert(root,1);
    root=insert(root,2);
    root=insert(root,4);
    root=insert(root,5);
    root=insert(root,6);
    root=insert(root,3);
    preorder(root);
}
