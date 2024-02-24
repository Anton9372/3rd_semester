//����� ��������� ��� ������ � ����������� �������� ������
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
	static void restructing(Tree<T>& tree, int mode);           //����������� ������ �� ������ ���������
	static void toMas(Node<T>* current, Mas<T>* mas);           //������� ������ � ���������� ������
	static void cancel(Tree<T>& tree);                          //������ ��������� �������� ��� �������
	static Node<T>* findNode(Node<T>* root, T& data, int mode); //����� ���� � ������ � �������� �������
	static std::optional<T> search(Tree<T>& tree, T data);      //����� ������ � ������ (����� �� ������ ���������)
};
template <typename T>
void Algorithm<T>::restructing(Tree<T>& tree, int mode)
{
	if (tree.isEmpty())
		throw AlgException(222, "������ ���������", __func__);
	Mas<T>* mas = new Mas<T>(tree.getCount(tree.root)); //������� ������
	toMas(tree.getRoot(), mas);                         //��������� � ������
	mas->sort(mode);                                    //�����������
	tree.deleteTree(tree.getRoot());                    //������� ������� ������
	tree.root = nullptr;
	tree.constructionMode = mode;
	mas->toTree(&tree);                                  //������� ����� ������
}
//������� ������ � ������
template <typename T>
void Algorithm<T>::toMas(Node<T>* current, Mas<T>* mas)
{
	if (current != nullptr)
	{
		toMas(current->left, mas);	//��������� ����� ��������� � ������
		mas->insert(current);		//�������� ���� � ������
		toMas(current->right, mas); //��������� ������ ��������� � ������
	}
}
template <class T>
void Algorithm<T>::cancel(Tree<T>& tree)
{
	if (tree.isEmpty())
		throw AlgException(222, "������ ���������", __func__);
	if (!tree.stack->isEmpty())
	{
		StackElem<T>* stackElem = tree.stack->pop();    //������� ������� �����
		if (stackElem->operation == 'a')                 //���� �������� ����������
			tree.popDefault(stackElem->node);           //�������
		if (stackElem->operation == 'r')                 //���� �������� ��������
			tree.pushDefault(stackElem->node);          //��������
	}
}
template <typename T>
Node<T>* Algorithm<T>::findNode(Node<T>* root, T& data, int mode)
{
	if (root == nullptr || root->data == data)      //���� ���� ��� ��� ������ �������
		return root;
	if (root->data.compare(data, mode))             //��������
		return findNode(root->right, data, mode);   //������� � ������� ���������
	else
		return findNode(root->left, data, mode);    //������� � ������ ���������
}
template <class T>
std::optional<T> Algorithm<T>::search(Tree<T>& tree, T data)
{
	Node<T>* current = tree.root;                                   //��������� ���������
	while (current != nullptr)
	{
		if (current->data.isEqual(data, tree.constructionMode))     //���� ������ �������
			return current->data;                                   //������� ������
		else if (current->data.compare(data, tree.constructionMode))//��������
			current = current->right;                               //������� � ������� ���������
		else
			current = current->left;                                //������� � ������ ���������
	}
	return std::nullopt;                                            //���� ������ �� ������� ������� ������ �������
}
#endif // ALGORITHM_H
