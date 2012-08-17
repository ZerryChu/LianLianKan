#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <queue>
using namespace std;

struct Info
{
	int xIndex;
	int yLevel;
};

template <class T>
class treeNode
{
private:
	treeNode<T> *leftChild;
	treeNode<T> *rightChild;
public:
	T data;                //数据元素
    
	//构造与析构
	treeNode():leftChild(NULL),rightChild(NULL){}
	treeNode(T item, treeNode<T> *left = NULL, treeNode<T> *right = NULL):data(item),leftChild(left),rightChild(right){}
	~treeNode(){}
	//结点操作成员函数
	treeNode<T>* &Left(void)      //指针引用可以做左值！！！！！！！！！！！！
	{
		return leftChild;
	}
	treeNode<T>* &Right(void)
	{
		return rightChild;
	}
};
///////////////////////////////////////////////////
//////////////////二叉树类/////////////////////////
///////////////////////////////////////////////////
template <class T>
class BiTree
{
private:
	treeNode<T> *root;                     //根结点指针
	treeNode<T> *current;                  //当前结点指针
public:
	BiTree():root(NULL),current(NULL){};
	~BiTree(){};
	//返回属性
	treeNode<T> *getRootNode();
	treeNode<T> *getCurrentNode();
	int NodeNum();                            
	int NodeNum(treeNode<T>* &t);          //返回结点数
	int depth(treeNode<T>* &t);            //计算深度
	int treeDeepin();                      //返回深度
	T getCurrentData();                    //返回当前结点数据元素
	int Current(treeNode<T>* &t);          //使当前结点为t所指结点
	treeNode<T> *searchNode(treeNode<T>* &myroot,T key);     //搜索数据元素key的结点
	int currentByData(T key);              //设置key数据元素结点为当前结点
	int Root();                            //使当前结点为根结点
	int Parent();                          //使当前结点为其双亲结点
	int Brather();                         //使当前结点为其兄弟结点
	treeNode<T> *searchParent(treeNode<T>* &myroot, treeNode<T>* &s);  //搜索myroot树结点s的双亲结点
	int empty();
	//删除、插入、修改
	int setCurrentNode(T key);             //修改current值
	void makeTree(const T &item, BiTree<T> &left, BiTree<T> &right);   //建立数据元素为item的左树left右树为rignt的二叉树
	void deleteTree(treeNode<T>* &t);      //删除t为根结点的子树
	//遍历
	void myPrintf(T item);                 //打印item
	void preLevelOrder(treeNode<T>* &t);   //层序遍历
	void preDLROrder(treeNode<T>* &t);     //前序
	void preLDROrder(treeNode<T>* &t);     //中序
	void preLRDOrder(treeNode<T>* &t);     //后序遍历
	void displayTree();                    //显示数据元素
	void destroyTree();                    //销毁树(删除树的所有结点)
	void destroySubTree(T item);           //删除以数据元素为item的结点为根结点de子树
	void zeroTree(treeNode<T>* &t);        //清空树?(把数据元素都清零)
	void setAllZero();                     //清空树?(把数据元素都清零)
	void insertTree(BiTree<T> &t);      //插入t为根结点的树到本树,,前序遍历,优先插入到只有一个子结点的结点,否则插入到本树的第一个叶子结点
	treeNode<T> *nodeInsertPlace();  //前序遍历，返回遍历到的第一个只有一个子结点的结点，否则返回第一个叶子结点
	treeNode<T> *sigleSonNode(treeNode<T>* &t);     //返回第一个只有一个子结点的结点,前序遍历
	treeNode<T> *leaveNode(treeNode<T>* &t);        //返回第一个叶子结点,前序遍历
	void printVTree();               //竖向打印树
};
//***********************************************
//BiTree函数定义
//***********************************************
template <class T>
void BiTree<T>::makeTree(const T &item, BiTree<T> &left, BiTree<T> &right)
{//建立数据元素为item的左树left右树为rignt的二叉树
	root = new treeNode<T>(item, left.root, right.root);
}

template <class T>
int BiTree<T>::Current(treeNode<T>* &t)
{//使当前结点为t所指结点
	if (t == NULL) return 0;
	current = t;
	return 1;
}

template <class T>
treeNode<T> *BiTree<T>::searchNode(treeNode<T>* &myroot,T key)
{//搜索数据元素key的结点并设置为当前结点
	if (myroot == NULL) return NULL;
	if(myroot->data == key)return myroot;
	treeNode<T> *p;
	if((p = searchNode(myroot->Left(),key)))
		if(p->data == key)return p;
	if((p = searchNode(myroot->Right(),key)))
		if(p->data == key)return p;
	return NULL;
}

template <class T>
int BiTree<T>::Root()
{//使当前结点为根结点
	if (root == NULL)
	{
		current = NULL;
		return 0;
	}
	return Current(root);
}

template <class T>
treeNode<T> *BiTree<T>::searchParent(treeNode<T>* &myroot, treeNode<T>* &s)
{//搜索myroot树结点s的双亲结点
	if(myroot == NULL) return NULL;
	if (myroot->Left() == s || myroot->Right() == s)
	{
		return myroot;
	}
	treeNode<T> *p;
	if((p = searchParent(myroot->Left(),s)) != NULL)return p;
	if((p = searchParent(myroot->Right(),s)) != NULL)return p;
	return NULL;
}

template <class T>
int BiTree<T>::Parent()
{//使当前结点为其双亲结点
	if (current == NULL)
	{
		current = root;
		return 0;
	}
	treeNode<T> *p = searchParent(root,current);
	if (p == NULL) return 0;
	else return Current(p);
}

template <class T>
int BiTree<T>::Brather()
{
	if(current == root)return 0;
	if (current != NULL)
	{
		treeNode<T> *p = searchParent(root,current);
		if (p->Right() != NULL && p->Left() == current)
		{
			current = p->Right();
			return 1;
		}
		if (p->Left() != NULL && p->Right() == current)
		{
			current = p->Left();
			return 1;
		}
	}
	else return 0;
}

template <class T>
void BiTree<T>::myPrintf(T item)
{
    cout<<item;
}

template <class T>
void BiTree<T>::preDLROrder(treeNode<T>* &t)
{//前序遍历
	if (t != NULL)
	{
		myPrintf(t->data);
		preDLROrder(t->Left());
		preDLROrder(t->Right());
	}
}

template <class T>
void BiTree<T>::preLDROrder(treeNode<T>* &t)
{//中序遍历s
	if (t != NULL)
	{
		preLDROrder(t->Left());
		myPrintf(t->data);
		preLDROrder(t->Right());
	}
}

template <class T>
void BiTree<T>::preLRDOrder(treeNode<T>* &t)
{//后序遍历
	if (t != NULL)
	{
		preLRDOrder(t->Left());
		preLRDOrder(t->Right());
		myPrintf(t->data);
	}
}

template <class T>
void BiTree<T>::preLevelOrder(treeNode<T>* &t)
{//层序
	if (t == NULL)return;
	queue<treeNode<T>*> q;
	treeNode<T> *p;
	q.push(t);
	while (!q.empty())
	{
		p = q.front();
        cout<<p->data; 
		q.pop();
		if(p->Left() != NULL)q.push(p->Left());
		if(p->Right() != NULL)q.push(p->Right());
	}
}

template <class T>
treeNode<T> *BiTree<T>::getRootNode()
{//返回根结点
	return root;
}

template <class T>
treeNode<T> *BiTree<T>::getCurrentNode()
{
	return current;
}

template <class T>
int BiTree<T>::setCurrentNode(T key)
{//修改current
	current->data = key;
	return 0;
}

template <class T>
void BiTree<T>::displayTree()
{//显示树
	cout<<"前序遍历:";
	preDLROrder(root);
	cout<<endl<<"中序遍历:";
	preLDROrder(root);
	cout<<endl<<"后续遍历:";
	preLRDOrder(root);
	cout<<endl<<"层序遍历:";
	preLevelOrder(root);
}

template <class T>
int BiTree<T>::currentByData(T key)
{
	current = searchNode(root,key);
	return 0;
}

template <class T>
int BiTree<T>::empty()
{//空返回0
	return (root == NULL)? 1:0;
}

template <class T>
T BiTree<T>::getCurrentData()
{
	return current->data;
}

template <class T>
int BiTree<T>::NodeNum(treeNode<T>* &t)
{//返回结点数
	int num = 0;
	if (t != NULL)
	{
		num ++;
		num = num + NodeNum(t->Left());
		num = num + NodeNum(t->Right());
	}
	return num;
}

template <class T>
int BiTree<T>::depth(treeNode<T>* &t)
{//计算树深度
	int dLeft,dRight,dVal;
	if (t == NULL)return -1;
	else
	{
		dLeft = depth(t->Left());
		dRight = depth(t->Right());
		dVal = 1 + ((dLeft > dRight)? dLeft:dRight);
	}
	return dVal;
}

template <class T>
int BiTree<T>::treeDeepin()
{//返回树深度
	//if (root == NULL)return -1;
	//double mynum = (double)NodeNum(root);
	//cout<<mynum<<endl;
	//double f = log10(mynum+1.0)/log10(2.0);
	//int deep = floor(f);
	//return deep;
	return depth(root);
}

template <class T>
void BiTree<T>::deleteTree(treeNode<T>* &t)
{//删除子树
	if (t != NULL)
	{
		deleteTree(t->Left());
		deleteTree(t->Right());
		delete t;
		t = NULL;
	}
}

template <class T>
void BiTree<T>::destroyTree()
{//销毁树
	deleteTree(root);
}

template<class T>
void BiTree<T>::destroySubTree(T item)
{//删除以数据元素为item的根结点的子树
	treeNode<T> * p = searchNode(root,item);
	if (p == root)
	{
		destroyTree();
	    return;
	}
	treeNode<T> *parent = searchParent(root,p);
	if(parent->Left() == p)parent->Left() = NULL;
	if(parent->Right() == p)parent->Right() = NULL;
	if(p != NULL)
	{
		deleteTree(p);
	}
	else cout<<"cant find the subtree whith's data is "<<item;
}

template <class T>
void BiTree<T>::zeroTree(treeNode<T>* &t)
{//清空树?(把数据元素都清零)
	if (t != NULL)
	{
		t->data = (T)0;//测试时T为char,0被换成了空格貌似
		zeroTree(t->Left());
		zeroTree(t->Right());
	}
}

template <class T>
void BiTree<T>::setAllZero()
{
	zeroTree(root);
}

template <class T>
treeNode<T> *BiTree<T>::sigleSonNode(treeNode<T>* &t)
{//返回独生子结点的双亲结点
	if (t != NULL)
	{
		if((t->Left() == NULL || t->Right() == NULL) && (!(t->Left() == NULL && t->Right() == NULL)))
			return t;
		treeNode<T> *p;
		if ((p = sigleSonNode(t->Left())) != NULL)return p;
		if ((p = sigleSonNode(t->Right())) != NULL)return p;
	}
	return NULL;
}

template <class T>
treeNode<T> *BiTree<T>::leaveNode(treeNode<T>* &t)
{//返回第一个叶子结点
	if (t != NULL)
	{
		if(t->Left() == NULL && t->Right() == NULL)
			return t;
		treeNode<T> *p;
		if ((p = leaveNode(t->Left())) != NULL)return p;
		if ((p = leaveNode(t->Right())) != NULL)return p;
	}
	return NULL;
}

template <class T>
treeNode<T> *BiTree<T>::nodeInsertPlace()
{//返回被插入处的结点
	treeNode<T> *p = NULL;
	if ((p = sigleSonNode(root)) == NULL)
		p = leaveNode(root);
	return p;
}

template <class T>
void BiTree<T>::insertTree(BiTree<T> &t)
{//插入子树
	treeNode<T> *p = nodeInsertPlace();
	if (p != NULL)
	{
		if (p->Left() == NULL && p->Right() != NULL)
		{//只有右孩子,子树将插入为左孩子
			p->Left() = t.getRootNode();
		}
		else if (p->Left() != NULL && p->Right() == NULL)
		{//只有左孩子,子树将插入为右孩子
			p->Right() = t.getRootNode();
		}
		else if (p->Left() == NULL && p->Right() == NULL)
		{//叶子结点,子树将插入为左孩子
			p->Left() = t.getRootNode();
		}
	}
}

template <class T>
void BiTree<T>::printVTree()
{
	int screenWidth = 64;                  //屏幕宽度
	int dataWidth = 2;                     //孩子结点偏移量s
	queue<treeNode<T>*> Q;
	queue<Info> QI;
	treeNode<T> *p = NULL;
	Info s,s1,s2;
	int offset, level = -1, i;
	
	if(root != NULL)Q.push(root);
	s.xIndex = screenWidth/dataWidth;     //计算结点x , y坐标
	s.yLevel = 0;
	QI.push(s);                            //根结点坐标入队列
	while(!Q.empty() && !QI.empty())
	{
		s2 = s;
		p = Q.front();
		Q.pop();
		s = QI.front();
		QI.pop();
		//走过空格
		if (s.yLevel != level)             //该节点第一次显示
		{
			cout<<"\n第"<<s.yLevel<<"层";
			level = s.yLevel;
			for (i = 0; i < s.xIndex-1; i ++)cout<<" ";
		}
		else for (i = 0; i < s.xIndex-s2.xIndex; i ++)cout<<" ";
		cout<<p->data;
		if (p->Left() != NULL)
		{
			Q.push(p->Left());
			s1.yLevel = s.yLevel + 1;        //y坐标为双亲结点y+1
			//计算第i层节点偏移量
			offset = screenWidth/pow((float)dataWidth,(float)(s1.yLevel+1));
			//计算第i层左孩子结点的x 坐标;s.xIndex为双亲结点的x坐标
			s1.xIndex = s.xIndex - offset;
			QI.push(s1);
		}
		if (p->Right() != NULL)
		{
			Q.push(p->Right());
			s1.yLevel = s.yLevel + 1;
			offset = screenWidth/pow((float)dataWidth,(float)(s1.yLevel+1));
			s1.xIndex = s.xIndex + offset;
			QI.push(s1);
		}
	}
}

template <class T>
int BiTree<T>::NodeNum()
{
	return NodeNum(root);
}