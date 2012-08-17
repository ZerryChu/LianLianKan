//
//  Tree.h
//  lianliankan
//
//  Created by Gun Li on 8/17/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef lianliankan_Tree_h
#define lianliankan_Tree_h


#pragma mark - Node

template <class T> class Tree;  //树类的前导定义

template <class T>
class Node {                    //节点类
    friend class Tree<T>;       //定义树类为友元类
private:
    Node<T> *firstChild;        //第一个孩子节点
    Node<T> *nextSibling;       //下一个兄弟节点
    
public:
    T NodeData;                 //数据元素
    
    //构造函数
    Node(T value, Node<T> *fc = NULL, Node<T> *ns = NULL):NodeData(value),firstChild(fc),nextSibling(ns){};
    virtual ~Node(){};
    //getter
    Node<T>* &FirstChild(void){return firstChild;}
    Node<T>* &NextSibling(void){return nextSibling;}
};

#pragma mark - Tree

template <class T>
class Tree {
private:
    Node<T> *rootNode;
    Node<T> *currentNode;
    
    //在树root中查找节点s的双亲节点
    Node<T> *SearchParent(Node<T>* &root,Node<T>* &s);
public:
    //构造与析构
    Tree();
    virtual ~Tree();
    
    //第一类操作：寻找满足某种特定关系的节点
    int Current(Node<T>* &t);//使当前节点指向节点t
    int Root(void);           //是跟节点为当前节点
    int Parent(void);           //使当前节点的双亲节点为当前节点
    int FirstChild(void);       //是当前节点的第一个孩子节点为当前节点
    int NextSubling(void);      //是当前节点的兄弟节点为当前节点
    
    //第二类操作：插入 || 删除节点
    void InsertChild(T value);  //把value插入到当前节点的最后一个孩子节点
    void DeleteSubtree(Node<T>* &t);    //删除以t为跟节点的子树
    int DeleteFirstChild(void);        //删除当前节点的第一个孩子节点
    int DeleteNextSubling(void);        //删除当前节点的下一个兄弟节点
    
    //第三类操作：各种遍历
    void PreOrderTree(Node<T>* &t);     //前序遍历根节点为t的树
    void PostOrderTree(Node<T>* &t);    //后序遍历
    void LevelOrderTree(Node<T>* &t);   //层序遍历
    void DisplayTree();         //显示数据元素
};

#include <iostream>

using namespace std;

template <class T>
Tree<T>::Tree()
{
    rootNode = NULL; 
    currentNode = NULL;
}

template <class T>
Tree<T>::~Tree<T>()
{
    DeleteSubtree(rootNode);
}

template <class T>
void Tree<T>::DeleteSubtree(Node<T> *&t)        //删除
{
    if (t == NULL) return;
    
    Node<T> *q = t->firstChild, *p = NULL;
    while (q != NULL) {
        p = q->nextSibling;
        DeleteSubtree(q);
        q = p;
    }
    cout<<"\n删除的元素->"<<t->NodeData<<endl;
    delete t;
}

//第一类操作

template <class T>
int Tree<T>::Current(Node<T> *&t)               //是当前节点为t
{
    if (t == NULL) return 0;
    currentNode = t;
    return 1;
}

template <class T>
int Tree<T>::Root()
{
    if (rootNode == NULL) {
        currentNode = NULL;
        return 0;
    }
    return Current(rootNode);
}

template <class T>
int Tree<T>::FirstChild()
{
    if (currentNode != NULL && currentNode->firstChild != NULL) {
        return Current(currentNode->firstChild);
    }
    else return 0;
}

template <class T>
int Tree<T>::NextSubling()
{
    if (currentNode != NULL && currentNode->nextSubling != NULL) {
        return Current(currentNode->nextSubling);
    }
    else return 0;
}

template <class T>
int Tree<T>::Parent()
{
    if (currentNode == NULL) {
        currentNode = rootNode;
        return 0;
    }
    Node<T> *p = SearchParent(rootNode, currentNode);
    if (p == NULL) {
        return 0;
    } else {
        return Current(p);
    }
}

template <class T>
Node<T>* Tree<T>::SearchParent(Node<T> *&rootTemp, Node<T> *&s)
{
    if (rootNode == NULL) return NULL;
    if (rootTemp->FirstChild() == s || rootTemp->NextSubling() == s) { //rootTemp->NextSubling() == s这样返回的是s的兄弟节点而非双亲节点吧？
        return rootTemp;
    }
    
    Node<T> *p;
    if ((p = SearchParent(rootTemp->FirstChild(), s)) != NULL) {
        return p;
    }
    if ((p = SearchParent(rootTemp->NextSubling(), s)) != NULL) {
        return p;
    }
    return NULL;
}

//第二类操作
template <class T>
void Tree<T>::InsertChild(T value)          //插入
{
    Node<T> *newNode = new Node<T>(value);
    
    if (rootNode == NULL) {
        rootNode = currentNode = newNode;
        return;
    }
    
    if (currentNode->firstChild == NULL) {
        currentNode->FirstChild() = newNode;
    } else {
        Node<T> *p = currentNode->firstChild;
        while (p->nextSibling != NULL) {
            p = p->nextSibling;
        }
        p->nextSibling = newNode;
    }
    Current(newNode);
}

template <class T>
int Tree<T>::DeleteFirstChild()
{
    Node<T> *temp = currentNode->firstChild;
    if (temp == NULL) {
        return 0;
    }
    currentNode->firstChild = temp->nextSubling;
    DeleteSubtree(temp);
    return 1;
}

template <class T>
int Tree<T>::DeleteNextSubling()
{
    Node<T> *p = currentNode->nextSubling;
    if (p == NULL) {
        return 0;
    }
    currentNode->nextSubling = p->nextSubling;
    DeleteSubtree(p);
    return 1;
}


//第三类操作：各种遍历
template <class T>
void Tree<T>::PreOrderTree(Node<T>* &t)     //前序遍历根节点为t的树
{
    if (t == NULL) {
        return;
    }
    cout<<t->NodeData<<" ";
    if (t->firstChild != NULL) {
        PreOrderTree(t->firstChild);
    }
    if (t->nextSibling != NULL) {
        PreOrderTree(t->nextSibling);
    }
}

template <class T>
void Tree<T>::PostOrderTree(Node<T>* &t)    //后序遍历
{
    if (t == NULL) {
        return;
    }
    if (t->firstChild != NULL) {
        PostOrderTree(t->firstChild);
    }
    
    cout<<t->NodeData<<" ";
    
    if (t->nextSibling != NULL) {
        PostOrderTree(t->nextSibling);
    }
}

template <class T>
void Tree<T>::LevelOrderTree(Node<T>* &t)   //层序遍历
{}

template <class T>
void Tree<T>::DisplayTree()         //显示数据元素
{
    cout<<"\n前序遍历显示节点：\n";
    PreOrderTree(rootNode);
    
    cout<<"\n后序遍历显示节点：\n";
    PostOrderTree(rootNode);
}



#endif
