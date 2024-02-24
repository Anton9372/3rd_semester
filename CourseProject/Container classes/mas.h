//����� ������� ��� ����������� ������
#ifndef MAS_H
#define MAS_H
template <typename T>
class Node;
template<typename T>
class Tree;
template <class T>
class Mas
{
	Node<T>** mas;   //������ ����� ������
	int size;        //������ �������
	friend class Tree<T>;
public:
	Mas(int size);                                   //����������� � ����������
	~Mas();                                          //����������
	void insert(Node<T>* newNode);                   //������� ���� � ������
	void toTree(Tree<T>* tree);                      //������� ������� � ������
	void toTree(Tree<T>*, int left, int right);      //������� ������� � ������
	void sort(int mode);							 //���������� ������� �� ���� ����
	void quickSort(int left, int right, int mode);   //������� ����������
	void swap(int i, int j);                         //����� �����
};
//�����������
template <typename T>
Mas<T>::Mas(int size)
{
	this->size = size;
	this->mas = new Node<T>*[size];     //�������� ������ ��� �������
	for (int i = 0; i < size; i++)
		mas[i] = nullptr;
}
//����������
template <typename T>
Mas<T>::~Mas()
{
	for (int i = 0; i < size; i++)
		delete mas[i];
	delete[]mas;
}
//������� ���� � ������
template <typename T>
void Mas<T>::insert(Node<T>* newNode)
{
	Node<T>* node = new Node<T>(newNode);
	for (int i = 0; i < size; i++)          //�������� �� �������
	{
		if (mas[i] == nullptr)              //���� ����� ��������� �����
		{
			mas[i] = node;                  //��������� ����
			break;                          //������� �� �����
		}
	}
}
//������� ������� � ������
template <typename T>
void Mas<T>::toTree(Tree<T>* tree)
{
	toTree(tree, 0, size - 1);
}
//������� ������� � ������
template <typename T>
void Mas<T>::toTree(Tree<T>* tree, int left, int right)
{
	if (left <= right)
	{
		int mid = (left + right) / 2;
		tree->pushDefault(mas[mid]);
		toTree(tree, left, mid - 1);
		toTree(tree, mid + 1, right);
	}
}
//���������� ������� �� ���� ����
template <typename T>
void Mas<T>::sort(int mode)
{
	quickSort(0, size - 1, mode);
}
//������� ����������
template <typename T>
void Mas<T>::quickSort(int left, int right, int mode)
{
	int i = left;
	int j = right;
	Node<T>* mid = mas[(left + right) / 2];
	while (i <= j)
	{
		while (mas[i]->getData().compare(mid->getData(), mode))
			i++;
		while (mid->getData().compare(mas[j]->getData(), mode))
			j--;
		if (i <= j)
		{
			swap(i, j);
			i++;
			j--;
		}
	}
	if (left < j)
		quickSort(left, j, mode);
	if (i < right)
		quickSort(i, right, mode);
}
//����� �����
template <typename T>
void Mas<T>::swap(int i, int j)
{
	Node<T>* temp = mas[i];         //��������� ��������� �� i-� ���� �� ��������� ����������
	mas[i] = mas[j];                //����������� i-�� ���� ��������� �� j-� ����
	mas[j] = temp;                  //����������� j-�� ���� ��������� �� ��������� ����������
}
#endif // MAS_H
