//������ ����������
#ifndef EXCEPTION_H
#define EXCEPTION_H
#include <QString>
#include <QDebug>
//������� ����� ����������
class Exception
{
protected:
	int code;           //��� ������
	QString message;    //��������� �� ������
	QString type;       //��� ������
public:
	Exception(int code, QString message, QString type);
	~Exception();
	void what()const;       //����� � ������� ����������
};
//����� ��������� ��� ����� ������ �������������
class InputException : public Exception
{
public:
	InputException(int code, QString message, QString type = "������ �����");
	~InputException();
	int getCode()const;
	QString getType()const;
	QString getMessage()const;
};
//����� ���������� ��� ������ � �������
class FileException : public Exception
{
	QString fileName;   //��� �����
public:
	FileException(int code, QString message, QString fileName, QString type = "File Error");
	~FileException();
	void whatFile()const;   //����� � ������� ����������
};
//����� ���������� ��� ������ � ����������
class AlgException : public Exception
{
	QString funcName;   //��� ������� � ������� ��������� ������
public:
	AlgException(int code, QString message, QString funcName, QString type = "Algorythm Error");
	~AlgException();
	void whatAlg()const;   //����� � ������� ����������
};
#endif // EXCEPTION_H
