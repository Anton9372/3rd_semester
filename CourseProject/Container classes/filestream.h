//����� ��������� ������ ��� ������ � �����������
#ifndef FILESTREAM_H
#define FILESTREAM_H
#include <QTextStream>
#include <QFile>
#include <QTextCodec>
#include "tree.h"
#include "exception.h"
class FileStream
{
	QFile file;
	QTextStream infile;
	QTextStream outfile;
public:
	FileStream();
	~FileStream();
	void open(const char* fileName, int mode);
	bool isOpen()const;
	bool end()const;
	void close();
	template <typename T>
	void read(Tree<T>& tree);
	template <typename T>
	void writeNode(Node<T>& node);
	template <typename T>
	void write(Node<T>* root);
	void deleteLastNewLine();
};
template <typename T>
void FileStream::read(Tree<T>& tree)
{
	if (!file.isOpen())
		throw FileException(1, "���� �� ������", file.fileName());
	T obj;
	while (!infile.atEnd())
	{
		infile >> obj;
		if (infile.status() != QTextStream::Ok)
			throw InputException(2, "������ ������ �� �����", "������ �����");
		tree.push(obj);
	}
}
template <typename T>
void FileStream::writeNode(Node<T>& node)
{
	if (!file.isOpen())
		throw FileException(1, "���� �� ������", file.fileName());
	outfile << node.data << '\n';
	if (outfile.status() != QTextStream::Ok)
		throw FileException(3, "������ ������ � ����", file.fileName());
}
template <typename T>
void FileStream::write(Node<T>* root)
{
	if (!root)
		return;
	write(root->left);
	writeNode(*root);
	write(root->right);
}
#endif // FILESTREAM_H
