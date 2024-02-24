//����� ���� ��������� ������
#ifndef NODE_H
#define NODE_H
//��������������� ���������� ������������� �������
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
	T data;                         //���� ������
	Node<T>* left;                  //��������� �� ������ �������
	Node<T>* right;                 //��������� �� ������� �������
	friend class Tree<T>;           //����� ������
	friend class TreeIterator<T>;   //����� ���������
	friend class FileStream;        //����� ��������� ������
	friend class Algorithm<T>;      //����� ���������
public:
	Node();							//����������� �� ���������
	Node(T data);                   //����������� � ����������
	Node(Node<T>* node);            //����������� �����������
	~Node();                        //����������
	T getData();
};
//����������� �� ���������
template <typename T>
Node<T>::Node()
{
	data = T();
	left = nullptr;
	right = nullptr;
}
//����������� � ����������
template <typename T>
Node<T>::Node(T data)
{
	this->data = data;
	left = nullptr;
	right = nullptr;
}
//����������� �����������
template <typename T>
Node<T>::Node(Node<T>* node)
{
	data = node->data;
	left = nullptr;
	right = nullptr;
}
//����������
template <typename T>
Node<T>::~Node()
{

}
//�������� ������
template <typename T>
T Node<T>::getData()
{
	return this->data;
}

#endif
