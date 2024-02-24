#include "exception.h"
//опеределение базового класса исключений
Exception::Exception(int code, QString message, QString type) : code(code), message(message), type(type)
{

}
Exception::~Exception()
{

}
void Exception::what()const
{
	qDebug() << "Error code:" << code << ":" << type << "," << message;
}
//определение класса иключения при вводе данных пользователем
InputException::InputException(int code, QString message, QString type) : Exception(code, message, type)
{

}
InputException::~InputException()
{

}
int InputException::getCode()const
{
	return code;
}
QString InputException::getType()const
{
	return type;
}
QString InputException::getMessage()const
{
	return message;
}
//определение класса исключения при работе с файлами
FileException::FileException(int code, QString message, QString fileName, QString type) : Exception(code, message, type), fileName(fileName)
{

}
FileException::~FileException()
{

}
void FileException::whatFile()const
{
	what();
	qDebug() << " in file: " << fileName << '\n';
}
//определение класса исключения при работе с программой
AlgException::AlgException(int code, QString message, QString funcName, QString type) : Exception(code, message, type), funcName(funcName)
{

}
AlgException::~AlgException()
{

}
void AlgException::whatAlg()const
{
	what();
	qDebug() << "in function: " << funcName << '\n';
}
