//класс стэка для отмены последнего действия в дереве
#ifndef STACK_H
#define STACK_
#include"stackelem.h"
template <class T>
class Stack
{
	StackElem<T>* top;   //указатель на вершину стэка
public:
	Stack();                                   //конструктор
	Stack(Stack<T>& other);
	~Stack();                                  //деструктор
	void push(StackElem<T>* newElem);          //добавление в стэк
	StackElem<T>* pop();                       //удаление из стэка
	bool isEmpty();
	void deleteStack(StackElem<T>* current);   //удаление стэка
};
//конструкто
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
//деструктор
template <typename T>
Stack<T>::~Stack()
{
	deleteStack(this->top);
}
//добавление в стэк
template <typename T>
void Stack<T>::push(StackElem<T>* newElem)
{
	//если стек пуст, то новый элемент становится вершиной
	if (!top)
		top = newElem;
	else
	{
		//иначе новый элемент становится вершиной, а предыдущая вершина становится его следующим элементом
		newElem->next = top;
		top = newElem;
	}
}
//удаление из стэка
template <typename T>
StackElem<T>* Stack<T>::pop()
{
	//если стек пуст, то возвращаем nullptr
	if (!(this->top))
		return nullptr;
	else
	{
		//иначе сохраняем указатель на вершину стека и перемещаем вершину на следующий элемент
		StackElem<T>* temp = this->top;
		this->top = this->top->next;
		//возвращаем указатель на удаленный элемент
		return temp;
	}
}
template <typename T>
bool Stack<T>::isEmpty()
{
	return this->top == nullptr;
}
//удаление стэка
template <typename T>
void Stack<T>::deleteStack(StackElem<T>* current)
{
	//если текущий элемент не nullptr, то рекурсивно удаляем следующий элемент и затем текущий элемент
	if (current != nullptr)
	{
		deleteStack(current->next);
		delete current;
	}
}
#endif // STACK_H
