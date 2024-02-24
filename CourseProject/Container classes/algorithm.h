//класс алгоритма для работы с контейнером бинарное дерево
#ifndef ALGORITHM_H
#define ALGORITHM_H
#include "tree.h"
#include "mas.h"
#include "exception.h"
#include <optional>
template<class T>
class Algorithm
{
public:
	static void restructing(Tree<T>& tree, int mode);           //перестройка дерева по новому параметру
	static void toMas(Node<T>* current, Mas<T>* mas);           //перевод дерева в одномерный массив
	static void cancel(Tree<T>& tree);                          //отмена последней операции над деревом
	static Node<T>* findNode(Node<T>* root, T& data, int mode); //найти узел в дереве с текущими данными
	static std::optional<T> search(Tree<T>& tree, T data);      //найти данные в дереве (поиск по одному параметру)
};
template <typename T>
void Algorithm<T>::restructing(Tree<T>& tree, int mode)
{
	if (tree.isEmpty())
		throw AlgException(222, "Пустой контейнер", __func__);
	Mas<T>* mas = new Mas<T>(tree.getCount(tree.root)); //создать массив
	toMas(tree.getRoot(), mas);                         //перевести в массив
	mas->sort(mode);                                    //сортировать
	tree.deleteTree(tree.getRoot());                    //удалить текущее дерево
	tree.root = nullptr;
	tree.constructionMode = mode;
	mas->toTree(&tree);                                  //создать новое дерево
}
//перевод дерева в массив
template <typename T>
void Algorithm<T>::toMas(Node<T>* current, Mas<T>* mas)
{
	if (current != nullptr)
	{
		toMas(current->left, mas);	//перевести левое поддерево в массив
		mas->insert(current);		//вставить узел в массив
		toMas(current->right, mas); //перевести правое поддерево в массив
	}
}
template <class T>
void Algorithm<T>::cancel(Tree<T>& tree)
{
	if (tree.isEmpty())
		throw AlgException(222, "Пустой контейнер", __func__);
	if (!tree.stack->isEmpty())
	{
		StackElem<T>* stackElem = tree.stack->pop();    //верхний элемент стэка
		if (stackElem->operation == 'a')                 //если отменить добавление
			tree.popDefault(stackElem->node);           //удалить
		if (stackElem->operation == 'r')                 //если отменить удаление
			tree.pushDefault(stackElem->node);          //добавить
	}
}
template <typename T>
Node<T>* Algorithm<T>::findNode(Node<T>* root, T& data, int mode)
{
	if (root == nullptr || root->data == data)      //если узла нет или данные совпали
		return root;
	if (root->data.compare(data, mode))             //сравнить
		return findNode(root->right, data, mode);   //перейти к правому поддереву
	else
		return findNode(root->left, data, mode);    //перейти к левому поддереву
}
template <class T>
std::optional<T> Algorithm<T>::search(Tree<T>& tree, T data)
{
	Node<T>* current = tree.root;                                   //временный указатель
	while (current != nullptr)
	{
		if (current->data.isEqual(data, tree.constructionMode))     //если данные совпали
			return current->data;                                   //вернуть данные
		else if (current->data.compare(data, tree.constructionMode))//сравнить
			current = current->right;                               //перейти к правому поддереву
		else
			current = current->left;                                //перейти к левому поддереву
	}
	return std::nullopt;                                            //если данные не найдены вернуть пустой элемент
}
#endif // ALGORITHM_H
