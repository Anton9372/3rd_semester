//����� ���������� �������� ������
#ifndef TREE_H
#define TREE_H
#include "stack.h"
#include "node.h"
#include "mas.h"
#include "exception.h"
//��������������� ���������� �������
template<class T>
class StackElem;
template<class T>
class Stack;
template<class T>
class TreeIterator;
template<class T>
class Algorithm;
template <class T>
class Tree
{
	Node<T>* root;             //������ ������
	int constructionMode;      //�������� ���������� ������
	Stack<T>* stack;           //��������� �� ���� ��� ������ ���������� ��������
	friend class Algorithm<T>; //����� ���������
public:
	Tree(int mode = 0);                                             //�����������
	Tree(Tree<T>& other);                                           //����������� �����������
	~Tree();                                                        //����������
private:
	Node<T>* getHeir(Node<T> deleted);                              //����� ���������� ��� ��������
public:
	Node<T>* getRoot()const;                                        //�������� �������
	int getCount(Node<T>* node);                                    //�������� ���������� �����
	int getConstructionMode();                                      //�������� �������� ���������� ������
	bool isEmpty();                                                 //�������� �� ������ ������
	void push(T data);                                              //������� ���� � ������ ������
	void pop(T data);                                               //�������� ���� � ������ ������
	void deleteTree(Node<T>* current);                              //�������� ������
	void pushDefault(Node<T>* newNode);                             //������� ����
	void popDefault(Node<T>* deleted);                              //�������� ����
	Node<T>* copyNodes(Node<T>* node);                              //����������� ����������� ���� ����� ������
	void copyTree(Tree<T>& other);                                  //����������� ������
	TreeIterator<T> begin();                                        //������ ������
	TreeIterator<T> end();                                          //����� ������
	TreeIterator<T> last();                                         //��������� ������� ������
};
template <typename T>
Tree<T>::Tree(int mode)
{
	root = nullptr;
	constructionMode = mode;
	stack = new Stack<T>();
}
template <typename T>
Tree<T>::Tree(Tree<T>& other)
{
	constructionMode = other.getConstructionMode();
	root = copyNodes(other.getRoot());
	stack = new Stack<T>(*other.stack);
}
template <typename T>
Tree<T>::~Tree()
{
	deleteTree(root);
	delete stack;
}
template <typename T>
Node<T>* Tree<T>::getHeir(Node<T> deleted)
{
	Node<T>* heir = deleted.right;    //��������� � ������� �������
	while (heir->left != nullptr)     //���� ���� ����� ������� ����������
		heir = heir->left;            //���������� ���� �� ����� �����
	return heir;                      //������� ����������
}
template <typename T>
Node<T>* Tree<T>::getRoot()const
{
	return root;
}
template <typename T>
int Tree<T>::getCount(Node<T>* node)
{
	if (node == nullptr)
		return 0;
	else
		return 1 + getCount(node->left) + getCount(node->right);
}
template <typename T>
int Tree<T>::getConstructionMode()
{
	return constructionMode;
}
template<typename T>
bool Tree<T>::isEmpty()
{
	return root == nullptr;
}
template <typename T>
void Tree<T>::push(T data)
{
	Node<T>* newNode = new Node<T>(data);
	pushDefault(newNode);
	StackElem<T>* stackElem = new StackElem<T>(newNode, 'a');   //������� ������, ������� �������� ���������� � ����������� ��������
	stack->push(stackElem);									    //����� ���� ������ � ����
}
template <typename T>
void Tree<T>::pop(T data)
{
	if (isEmpty())
		throw AlgException(222, "������ ���������", __func__);
	Node<T>* deleted = Algorithm<T>::findNode(root, data, constructionMode);
	StackElem<T>* stackElem = new StackElem<T>(deleted, 'r');   //������� ������, ������� �������� ���������� � ����������� ��������
	stack->push(stackElem);										//����� ���� ������ � ����
	popDefault(deleted);
}
template <typename T>
void Tree<T>::deleteTree(Node<T>* current)
{
	if (current != nullptr)			//���� ������� ���� �� ������
	{
		deleteTree(current->left);	//������� ����� ���������, ������� � ������ ������� �������� ����
		deleteTree(current->right); //������� ������ ���������, ������� � ������� ������� �������� ����
		delete current;				//������� ������� ����
	}
}
template <typename T>
void Tree<T>::pushDefault(Node<T>* newNode)
{
	Node<T>* current = root;
	Node<T>* parent = nullptr;
	while (current != nullptr)								//���� �� ��������� ����� ������
	{
		parent = current;									//��������� ������� ����
		if (current->data.compare(newNode->data, constructionMode))	//���� ������ �������� ���� ������ ������ ������ ���� �� ��������� ���������� ������
			current = current->right;						//��������� � ������ ������� �������� ����
		else												//���� ������ �������� ���� ������ ��� ����� ������ ������ ���� �� ��������� ���������� ������
			current = current->left;						//��������� � ������� ������� �������� ����
	}
	if (parent == nullptr)									//���� ������������ ���� ������, �� ���� ������ ������
		root = newNode;										//������ ������ - ����� ����
	else if (parent->data.compare(newNode->data, constructionMode))	//���� ������ ������������� ���� ������ ������ ������ ���� �� ��������� ���������� ������
		parent->right = newNode;							//����� ������� ������������� ���� - ����� ����
	else													//���� ������ ������������� ���� ������ ��� ����� ������ ������ ���� �� ��������� ���������� ������
		parent->left = newNode;								//������ ������� ������������� ���� - ����� ����
}
template <typename T>
void Tree<T>::popDefault(Node<T>* deleted)
{
	if (isEmpty())
		throw AlgException(222, "������ ���������", __func__);
	Node<T>* current = root;											//������� ���� - ������ ������
	Node<T>* parent = nullptr;											//������������ ���� - ������
	while (current != nullptr && current != deleted)					//���� �� ��������� ����� ������ ��� �� ������ ������� ���� ��� ��������
	{
		parent = current;												//������������ ���� - ������� ����
		if (current->data.compare(deleted->data, constructionMode))				//���� ������ �������� ���� ������ ������ ���������� ���� �� ��������� ���������� ������
			current = current->right;									//��������� � ������ ������� �������� ����
		else															//���� ������ �������� ���� ������ ��� ����� ������ ���������� ���� �� ��������� ���������� ������
			current = current->left;									//��������� � ������� ������� �������� ����
	}
	if (current == nullptr)												//���� ������� ���� �� ������
		throw AlgException(333, "���� �� ������", __func__);
	if (current->left == nullptr || current->right == nullptr)			//���� ��������� ���� ����� �� ����� ������ �������
	{
		Node<T>* temp;
		if (current->left != nullptr) {
			temp = current->left;
		}
		else {
			temp = current->right;
		} //��������� ��������� �� ������������� ������� ��� ������ ���������, ���� �������� ���
		if (parent == nullptr)											//���� ������������ ���� ������, �� ���� ��������� ���� - ������ ������
			root = temp;												//������ ������ - ������������ ������� ��� ������ ���������
		else if (parent->left == current)								//���� ��������� ���� - ����� ������� ������������� ����
			parent->left = temp;										//����� ������� ������������� ���� - ������������ ������� ��� ������ ���������
		else															//���� ��������� ���� - ������ ������� ������������� ����
			parent->right = temp;										//������ ������� ������������� ���� - ������������ ������� ��� ������ ���������
		delete current;													//������� ������� ����
	}
	else																//���� ��������� ���� ����� ���� ��������
	{
		Node<T>* heir = getHeir(*current);								//������� ���������� ��� ��������
		T heirData = heir->data;										//��������� ������ ����������
		popDefault(heir);												//������� ���������� �� ������ ����������
		current->data = heirData;										//�������� ������ ���������� � ������� ����
	}
}
template<typename T>
Node<T>* Tree<T>::copyNodes(Node<T>* node)
{
	if (!node)
		return nullptr;
	Node<T>* newNode = new Node<T>(*node);
	newNode->left = copyNodes(node->left);
	newNode->right = copyNodes(node->right);
	return newNode;
}
template<typename T>
void Tree<T>::copyTree(Tree<T>& other)
{
	if (root)
		deleteTree(root);
	constructionMode = other.getConstructionMode();
	root = copyNodes(other.getRoot());
}
template <typename T>
TreeIterator<T> Tree<T>::begin()
{
	return TreeIterator<T>(root, 1);
}
template <typename T>
TreeIterator<T> Tree<T>::end()
{
	return TreeIterator<T>(nullptr);
}
template<typename T>
TreeIterator<T> Tree<T>::last()
{
	return TreeIterator<T>(root, 0);
}
#endif // TREE_H
