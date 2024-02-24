#include "filestream.h"
FileStream::FileStream() : infile(&file), outfile(&file)
{
	infile.setCodec(QTextCodec::codecForName("UTF-8"));
	outfile.setCodec(QTextCodec::codecForName("UTF-8"));
}
FileStream::~FileStream()
{

}
void FileStream::open(const char* fileName, int mode)
{
	file.setFileName(fileName);
	if (mode == 1)
		file.open(QIODevice::ReadOnly | QIODevice::Text);
	else if (mode == 2)
		file.open(QIODevice::WriteOnly | QIODevice::Text);
	else if (mode == 3)
		file.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Truncate);
}
bool FileStream::isOpen()const
{
	return file.isOpen();
}
bool FileStream::end()const
{
	return infile.atEnd();
}
void FileStream::close()
{
	if (file.isOpen())
		file.close();
}
void FileStream::deleteLastNewLine()
{
	if (!file.isOpen())
		throw FileException(444, "Файл не открыт", file.fileName());
	outfile.flush();
	file.resize(file.size() - 2);
}
