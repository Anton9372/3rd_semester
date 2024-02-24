//����� ����� ��� ������ ���������� �������� � ������
#ifndef STACK_H
#define STACK_
#include"stackelem.h"
template <class T>
class Stack
{
	StackElem<T>* top;   //��������� �� ������� �����
public:
	Stack();                                   //�����������
	Stack(Stack<T>& other);
	~Stack();                                  //����������
	void push(StackElem<T>* newElem);          //���������� � ����
	StackElem<T>* pop();                       //�������� �� �����
	bool isEmpty();
	void deleteStack(StackElem<T>* current);   //�������� �����
};
//����������
template <typename T>
Stack<T>::Stack()
{
	this->top = nullptr;
}
template <typename T>
Stack<T>::Stack(Stack<T>& other)
{
	if (other.top == nullptr)
		top = nullptr;
	else
	{
		top = new StackElem<T>(*other.top);
		StackElem<T>* temp = other.top->next;
		while (temp != nullptr)
		{
			StackElem<T>* newElem = new StackElem<T>(*temp);
			push(newElem);
			temp = temp->next;
		}
	}
}
//����������
template <typename T>
Stack<T>::~Stack()
{
	deleteStack(this->top);
}
//���������� � ����
template <typename T>
void Stack<T>::push(StackElem<T>* newElem)
{
	//���� ���� ����, �� ����� ������� ���������� ��������
	if (!top)
		top = newElem;
	else
	{
		//����� ����� ������� ���������� ��������, � ���������� ������� ���������� ��� ��������� ���������
		newElem->next = top;
		top = newElem;
	}
}
//�������� �� �����
template <typename T>
StackElem<T>* Stack<T>::pop()
{
	//���� ���� ����, �� ���������� nullptr
	if (!(this->top))
		return nullptr;
	else
	{
		//����� ��������� ��������� �� ������� ����� � ���������� ������� �� ��������� �������
		StackElem<T>* temp = this->top;
		this->top = this->top->next;
		//���������� ��������� �� ��������� �������
		return temp;
	}
}
template <typename T>
bool Stack<T>::isEmpty()
{
	return this->top == nullptr;
}
//�������� �����
template <typename T>
void Stack<T>::deleteStack(StackElem<T>* current)
{
	//���� ������� ������� �� nullptr, �� ���������� ������� ��������� ������� � ����� ������� �������
	if (current != nullptr)
	{
		deleteStack(current->next);
		delete current;
	}
}
#endif // STACK_H
