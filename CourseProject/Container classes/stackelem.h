//элемент стэка для отмены последнего действия в дереве
#ifndef STACKELEM_H
#define STACKELEM_H
#include "node.h"
template <class T>
class StackElem
{
public:
	//поля
	Node<T>* node;           //сохранненый узел
	char operation;          //операция
	StackElem<T>* next;      //следущий элемент
	//методы
	StackElem(Node<T>* node, char operation);   //конструктор с параметрами для отмены действия добавить/удалить узел
	StackElem(StackElem<T>& other);
	~StackElem();                               //деструктор
};
//конструктор с параметрами для отмены действия добавить/удалить узел
template <typename T>
StackElem<T>::StackElem(Node<T>* node, char operation)
{
	if (operation == 'r')
		this->node = new Node<T>(node);
	else
		this->node = node;
	this->operation = operation;
	this->next = nullptr;
}
template <typename T>
StackElem<T>::StackElem(StackElem<T>& other)
{
	operation = other.operation;
	if (operation == 'r')
		this->node = new Node<T>(other.node);
	else
		this->node = other.node;
	this->next = nullptr;
}
//деструктор
template <typename T>
StackElem<T>::~StackElem()
{
	if (operation == 'r')
		delete node;
}
#endif // STACKELEM_H
