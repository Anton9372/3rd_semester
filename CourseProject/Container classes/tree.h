//класс контейнера бинарное дерево
#ifndef TREE_H
#define TREE_H
#include "stack.h"
#include "node.h"
#include "mas.h"
#include "exception.h"
//предварительное объявление классов
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
	Node<T>* root;             //корень дерева
	int constructionMode;      //параметр построения дерева
	Stack<T>* stack;           //указатель на стэк для отмены последнего действия
	friend class Algorithm<T>; //класс алгоритма
public:
	Tree(int mode = 0);                                             //конструктор
	Tree(Tree<T>& other);                                           //конструктор копирования
	~Tree();                                                        //деструктор
private:
	Node<T>* getHeir(Node<T> deleted);                              //поиск наследника для удаления
public:
	Node<T>* getRoot()const;                                        //получить вершину
	int getCount(Node<T>* node);                                    //получить количество узлов
	int getConstructionMode();                                      //получить параметр построения дерева
	bool isEmpty();                                                 //проверка на пустое дерево
	void push(T data);                                              //вставка узла с учетом отмены
	void pop(T data);                                               //удаление узла с учетом отмены
	void deleteTree(Node<T>* current);                              //удаление дерева
	void pushDefault(Node<T>* newNode);                             //вставка узла
	void popDefault(Node<T>* deleted);                              //удаление узла
	Node<T>* copyNodes(Node<T>* node);                              //рекурсивное копирование всех узлов дерева
	void copyTree(Tree<T>& other);                                  //копирование дерева
	TreeIterator<T> begin();                                        //начало дерева
	TreeIterator<T> end();                                          //конец дерева
	TreeIterator<T> last();                                         //последний элемент дерева
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
	Node<T>* heir = deleted.right;    //переходим к правому потомку
	while (heir->left != nullptr)     //пока есть левые потомки наследника
		heir = heir->left;            //спускаемся вниз по левой ветке
	return heir;                      //возврат наследника
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
	StackElem<T>* stackElem = new StackElem<T>(newNode, 'a');   //создаем объект, который содержит информацию о выполненном действии
	stack->push(stackElem);									    //ложим этот объект в стек
}
template <typename T>
void Tree<T>::pop(T data)
{
	if (isEmpty())
		throw AlgException(222, "Пустой контейнер", __func__);
	Node<T>* deleted = Algorithm<T>::findNode(root, data, constructionMode);
	StackElem<T>* stackElem = new StackElem<T>(deleted, 'r');   //создаем объект, который содержит информацию о выполненном действии
	stack->push(stackElem);										//ложим этот объект в стек
	popDefault(deleted);
}
template <typename T>
void Tree<T>::deleteTree(Node<T>* current)
{
	if (current != nullptr)			//если текущий узел не пустой
	{
		deleteTree(current->left);	//удаляем левое поддерево, начиная с левого потомка текущего узла
		deleteTree(current->right); //удаляем правое поддерево, начиная с правого потомка текущего узла
		delete current;				//удаляем текущий узел
	}
}
template <typename T>
void Tree<T>::pushDefault(Node<T>* newNode)
{
	Node<T>* current = root;
	Node<T>* parent = nullptr;
	while (current != nullptr)								//пока не достигнут конец дерева
	{
		parent = current;									//сохраняем текущий узел
		if (current->data.compare(newNode->data, constructionMode))	//если данные текущего узла больше данных нового узла по параметру построения дерева
			current = current->right;						//переходим к левому потомку текущего узла
		else												//если данные текущего узла меньше или равны данным нового узла по параметру построения дерева
			current = current->left;						//переходим к правому потомку текущего узла
	}
	if (parent == nullptr)									//если родительский узел пустой, то есть дерево пустое
		root = newNode;										//корень дерева - новый узел
	else if (parent->data.compare(newNode->data, constructionMode))	//если данные родительского узла больше данных нового узла по параметру построения дерева
		parent->right = newNode;							//левый потомок родительского узла - новый узел
	else													//если данные родительского узла меньше или равны данным нового узла по параметру построения дерева
		parent->left = newNode;								//правый потомок родительского узла - новый узел
}
template <typename T>
void Tree<T>::popDefault(Node<T>* deleted)
{
	if (isEmpty())
		throw AlgException(222, "Пустой контейнер", __func__);
	Node<T>* current = root;											//текущий узел - корень дерева
	Node<T>* parent = nullptr;											//родительский узел - пустой
	while (current != nullptr && current != deleted)					//пока не достигнут конец дерева или не найден искомый узел для удаления
	{
		parent = current;												//родительский узел - текущий узел
		if (current->data.compare(deleted->data, constructionMode))				//если данные текущего узла больше данных удаляемого узла по параметру построения дерева
			current = current->right;									//переходим к левому потомку текущего узла
		else															//если данные текущего узла меньше или равны данным удаляемого узла по параметру построения дерева
			current = current->left;									//переходим к правому потомку текущего узла
	}
	if (current == nullptr)												//если искомый узел не найден
		throw AlgException(333, "Узел не найден", __func__);
	if (current->left == nullptr || current->right == nullptr)			//если удаляемый узел имеет не более одного потомка
	{
		Node<T>* temp;
		if (current->left != nullptr) {
			temp = current->left;
		}
		else {
			temp = current->right;
		} //временный указатель на единственного потомка или пустой указатель, если потомков нет
		if (parent == nullptr)											//если родительский узел пустой, то есть удаляемый узел - корень дерева
			root = temp;												//корень дерева - единственный потомок или пустой указатель
		else if (parent->left == current)								//если удаляемый узел - левый потомок родительского узла
			parent->left = temp;										//левый потомок родительского узла - единственный потомок или пустой указатель
		else															//если удаляемый узел - правый потомок родительского узла
			parent->right = temp;										//правый потомок родительского узла - единственный потомок или пустой указатель
		delete current;													//удаляем текущий узел
	}
	else																//если удаляемый узел имеет двух потомков
	{
		Node<T>* heir = getHeir(*current);								//находим наследника для удаления
		T heirData = heir->data;										//сохраняем данные наследника
		popDefault(heir);												//удаляем наследника из дерева рекурсивно
		current->data = heirData;										//копируем данные наследника в текущий узел
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
