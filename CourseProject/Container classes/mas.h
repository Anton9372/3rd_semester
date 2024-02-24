//класс массива для перестройки дерева
#ifndef MAS_H
#define MAS_H
template <typename T>
class Node;
template<typename T>
class Tree;
template <class T>
class Mas
{
	Node<T>** mas;   //массив узлов дерева
	int size;        //размер массива
	friend class Tree<T>;
public:
	Mas(int size);                                   //конструктор с параметром
	~Mas();                                          //деструктор
	void insert(Node<T>* newNode);                   //вставка узла в массив
	void toTree(Tree<T>* tree);                      //перевод массива в дерево
	void toTree(Tree<T>*, int left, int right);      //перевод массива в дерево
	void sort(int mode);							 //сортировка массива по полю узла
	void quickSort(int left, int right, int mode);   //быстрая сортировка
	void swap(int i, int j);                         //обмен узлов
};
//конструктор
template <typename T>
Mas<T>::Mas(int size)
{
	this->size = size;
	this->mas = new Node<T>*[size];     //выделяем память для массива
	for (int i = 0; i < size; i++)
		mas[i] = nullptr;
}
//деструктор
template <typename T>
Mas<T>::~Mas()
{
	for (int i = 0; i < size; i++)
		delete mas[i];
	delete[]mas;
}
//вставка узла в массив
template <typename T>
void Mas<T>::insert(Node<T>* newNode)
{
	Node<T>* node = new Node<T>(newNode);
	for (int i = 0; i < size; i++)          //проходим по массиву
	{
		if (mas[i] == nullptr)              //если нашли свободное место
		{
			mas[i] = node;                  //вставляем узел
			break;                          //выходим из цикла
		}
	}
}
//перевод массива в дерево
template <typename T>
void Mas<T>::toTree(Tree<T>* tree)
{
	toTree(tree, 0, size - 1);
}
//перевод массива в дерево
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
//сортировка массива по полю узла
template <typename T>
void Mas<T>::sort(int mode)
{
	quickSort(0, size - 1, mode);
}
//быстрая сортировка
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
//обмен узлов
template <typename T>
void Mas<T>::swap(int i, int j)
{
	Node<T>* temp = mas[i];         //сохраняем указатель на i-й узел во временную переменную
	mas[i] = mas[j];                //присваиваем i-му узлу указатель на j-й узел
	mas[j] = temp;                  //присваиваем j-му узлу указатель на временную переменную
}
#endif // MAS_H
