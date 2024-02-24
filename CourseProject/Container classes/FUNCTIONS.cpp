#include "FUNCTIONS.h"
void fill_map_cont(QMap<int, QString>& map, const QString& filename)
{
	QFile file(filename);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		throw FileException(11, "������ ��� �������� �����", filename); //��������� ���������
	QTextStream in(&file);
	in.setCodec(QTextCodec::codecForName("UTF-8"));
	while (!in.atEnd())                 //���� �� ����� �����
	{
		int id;
		QString str;
		in >> id;                       //������� ID ������
		str = in.readLine().trimmed();  //������� ������
		map.insert(id, str);            //�������� � ���������
	}
	file.close();
}
void checkLogin(QString login)
{
	if (login.isEmpty())
		throw InputException(16, "����� �� ����� ���� ������");
	if (login.length() > 10)
		throw InputException(6, "����� ������ �������� �� �� ����� 10 ��������");
}
void checkPassword(QString password)
{
	if (password.isEmpty())
		throw InputException(17, "������ �� ����� ���� ������");
	if (password.length() > 4)
		throw InputException(7, "������ ������ �������� �� �� ����� 4 ��������");
}
void checkName(QString name)
{
	if (name.isEmpty())
		throw InputException(18, "��� �� ����� ���� ������");
	QStringList words = name.split(" ");    //��������� ��� �� �����
	if (words.size() != 3)                   //���� ���� �� 3
		throw InputException(12, "������� ������ ���");
	QRegExp rx("[�-��-߸�]+");              //������ ��������� ��� ��������(������ ������� �����)
	for (const QString& word : words)        //������ �� ������
	{
		if (!rx.exactMatch(word))
			throw InputException(13, "��� ������ ��������� ������ ������� �����");
	}
}
void checkDate(QString date)
{
	if (date.isEmpty())
		throw InputException(19, "���� �� ����� ���� ������");
	QRegExp rx("^\\d{2}\\.\\d{2}\\.\\d{4}$");    //������ ��������� ��� ��������(������ ����)
	if (!rx.exactMatch(date))
		throw InputException(14, "���� ������ ���� � ������� DD.MM.YYYY");
}
void checkTime(QString time)
{
	if (time.isEmpty())
		throw InputException(20, "����� �� ����� ���� ������");
	QRegExp rx("^\\d{2}:\\d{2}$");     //������ ��������� ��� ��������(������ �������)
	if (!rx.exactMatch(time))
		throw InputException(18, "����� ������ ���� � ������� hh::mm");
}
void checkContacts(QString contacts)
{
	if (contacts.isEmpty())
		throw InputException(21, "����� �������� �� ����� ���� ������");
	QRegExp rx("^\\+\\d{12}$");     //������ ��������� ��� ��������(������ ������ ��������)
	if (!rx.exactMatch(contacts))
		throw InputException(15, "����� �������� ������ ���������� � '+' � ��������� 12 ����");
}
void checkAdress(QString adress)
{
	if (adress.isEmpty())
		throw InputException(22, "����� �� ����� ���� ������");
	QRegExp rx("^[�-��-߸�\\s]+ \\d{1,3}-\\d{1,3}$");   //������ ��������� ��� ��������(������ ������)
	if (!rx.exactMatch(adress))
		throw InputException(5, "����� ������ ���� � �������: �������� ����� �� ������� �����, ������, ���������-�������������");
}
