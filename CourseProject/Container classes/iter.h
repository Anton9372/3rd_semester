//класс итератора бинарного дерева
#ifndef TREEITERATOR_H
#define TREEITERATOR_H
#include "node.h"
#include <Qstack>
template <class T>
class TreeIterator
{
	Node<T>* current;			//текущий узел
	QStack<Node<T>*>stack;
public:
	TreeIterator(Node<T>* root, bool mode = 1);    //конструктор
	//mode = 1: итератор на начало дерева(левый конец)
	//mode = 2: итератор на конец дерева(правый конец)
	~TreeIterator();                               //деструктор
	bool operator==(const TreeIterator<T>& other); //оператор сравнения
	bool operator!=(const TreeIterator<T>& other); //оператор сравнения
	T& operator*(); 							   //оператор разадресации
	TreeIterator<T>& operator++();                 //инкремет
	TreeIterator<T>& operator--();                 //декремент
	TreeIterator<T> operator++(int);
	TreeIterator<T> operator--(int);
};
template <typename T>
TreeIterator<T>::TreeIterator(Node<T>* root, bool mode) : current(root)
{
	if (root)
	{
		stack.push(nullptr);
		if (mode == 1)
		{
			while (current->left != nullptr)
			{
				stack.push(current);
				current = current->left;
			}
		}
		if (mode == 0)
		{
			while (current->right != nullptr)
			{
				stack.push(current);
				current = current->right;
			}
		}
	}
}
//деструктор
template <typename T>
TreeIterator<T>::~TreeIterator()
{
	stack.clear();
}
//оператор сравнения
template <typename T>
bool TreeIterator<T>::operator==(const TreeIterator<T>& other)
{
	return current == other.current;
}
//оператор сравнения
template <typename T>
bool TreeIterator<T>::operator!=(const TreeIterator<T>& other)
{
	return current != other.current;
}
//оператор разадресации
template <typename T>
T& TreeIterator<T>::operator*()
{
	return current->data;
}
//инкремет
template <typename T>
TreeIterator<T>& TreeIterator<T>::operator++()
{
	if (current->right != nullptr)
	{
		current = current->right;
		while (current->left != nullptr)
		{
			stack.push(current);
			current = current->left;
		}
	}
	else
	{
		current = stack.top();
		stack.pop();
	}
	return *this;
}
//декремент
template <typename T>
TreeIterator<T>& TreeIterator<T>::operator--()
{
	if (current->left != nullptr)
	{
		current = current->left;
		while (current->right != nullptr)
		{
			stack.push(current);
			current = current->right;
		}
	}
	else
	{
		current = stack.top();
		stack.pop();
	}
	return *this;
}
template <typename T>
TreeIterator<T> TreeIterator<T>::operator++(int)
{
	TreeIterator<T> temp = *this;
	++(*this);
	return temp;
}
template <typename T>
TreeIterator<T> TreeIterator<T>::operator--(int)
{
	TreeIterator<T> temp = *this;
	--(*this);
	return temp;
}
#endif
