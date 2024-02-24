//класс узла бинарного дерева
#ifndef NODE_H
#define NODE_H
//предварительное объявление дружественных классов
template<typename T>
class Tree;
template<typename T>
class TreeIterator;
class FileStream;
template <class T>
class Algorithm;
template <class T>
class Node
{
	T data;                         //поле данных
	Node<T>* left;                  //указатель на левого потомка
	Node<T>* right;                 //указатель на правого потомка
	friend class Tree<T>;           //класс дерева
	friend class TreeIterator<T>;   //класс итератора
	friend class FileStream;        //класс файлового потока
	friend class Algorithm<T>;      //класс алгоритма
public:
	Node();							//конструктор по умолчанию
	Node(T data);                   //конструктор с параметром
	Node(Node<T>* node);            //конструктор копирования
	~Node();                        //деструктор
	T getData();
};
//конструктор по умолчанию
template <typename T>
Node<T>::Node()
{
	data = T();
	left = nullptr;
	right = nullptr;
}
//конструктор с параметром
template <typename T>
Node<T>::Node(T data)
{
	this->data = data;
	left = nullptr;
	right = nullptr;
}
//конструктор копирования
template <typename T>
Node<T>::Node(Node<T>* node)
{
	data = node->data;
	left = nullptr;
	right = nullptr;
}
//деструктор
template <typename T>
Node<T>::~Node()
{

}
//получить данные
template <typename T>
T Node<T>::getData()
{
	return this->data;
}

#endif
