//классы исключений
#ifndef EXCEPTION_H
#define EXCEPTION_H
#include <QString>
#include <QDebug>
//базовый класс исключения
class Exception
{
protected:
	int code;           //код ошибки
	QString message;    //сообщение об ошибке
	QString type;       //тип ошибки
public:
	Exception(int code, QString message, QString type);
	~Exception();
	void what()const;       //вывод в консоль исключения
};
//класс иключения при вводе данных пользователем
class InputException : public Exception
{
public:
	InputException(int code, QString message, QString type = "Ошибка ввода");
	~InputException();
	int getCode()const;
	QString getType()const;
	QString getMessage()const;
};
//класс исключения при работе с файлами
class FileException : public Exception
{
	QString fileName;   //имя файла
public:
	FileException(int code, QString message, QString fileName, QString type = "File Error");
	~FileException();
	void whatFile()const;   //вывод в консоль исключения
};
//класс исключения при работе с программой
class AlgException : public Exception
{
	QString funcName;   //имя функции в которой произошла ошибка
public:
	AlgException(int code, QString message, QString funcName, QString type = "Algorythm Error");
	~AlgException();
	void whatAlg()const;   //вывод в консоль исключения
};
#endif // EXCEPTION_H
