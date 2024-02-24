//������� ����� ��� ������ ���������� �������� � ������
#ifndef STACKELEM_H
#define STACKELEM_H
#include "node.h"
template <class T>
class StackElem
{
public:
	//����
	Node<T>* node;           //����������� ����
	char operation;          //��������
	StackElem<T>* next;      //�������� �������
	//������
	StackElem(Node<T>* node, char operation);   //����������� � ����������� ��� ������ �������� ��������/������� ����
	StackElem(StackElem<T>& other);
	~StackElem();                               //����������
};
//����������� � ����������� ��� ������ �������� ��������/������� ����
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
//����������
template <typename T>
StackElem<T>::~StackElem()
{
	if (operation == 'r')
		delete node;
}
#endif // STACKELEM_H
