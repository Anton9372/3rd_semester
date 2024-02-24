#include "FUNCTIONS.h"
void fill_map_cont(QMap<int, QString>& map, const QString& filename)
{
	QFile file(filename);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		throw FileException(11, "Ошибка при открытии файла", filename); //выбросить иключение
	QTextStream in(&file);
	in.setCodec(QTextCodec::codecForName("UTF-8"));
	while (!in.atEnd())                 //пока не конец файла
	{
		int id;
		QString str;
		in >> id;                       //считать ID услуги
		str = in.readLine().trimmed();  //считать услугу
		map.insert(id, str);            //вставить в контейнер
	}
	file.close();
}
void checkLogin(QString login)
{
	if (login.isEmpty())
		throw InputException(16, "Логин не может быть пустым");
	if (login.length() > 10)
		throw InputException(6, "Логин должен состоять из не более 10 символов");
}
void checkPassword(QString password)
{
	if (password.isEmpty())
		throw InputException(17, "Пароль не может быть пустым");
	if (password.length() > 4)
		throw InputException(7, "Пароль должен состоять из не более 4 символов");
}
void checkName(QString name)
{
	if (name.isEmpty())
		throw InputException(18, "Имя не может быть пустым");
	QStringList words = name.split(" ");    //разделить ФИО на слова
	if (words.size() != 3)                   //если слов не 3
		throw InputException(12, "Введите полное имя");
	QRegExp rx("[а-яА-ЯёЁ]+");              //задать параметры для проверки(только русские буквы)
	for (const QString& word : words)        //пройти по словам
	{
		if (!rx.exactMatch(word))
			throw InputException(13, "ФИО должно содержать только русские буквы");
	}
}
void checkDate(QString date)
{
	if (date.isEmpty())
		throw InputException(19, "Дата не может быть пустой");
	QRegExp rx("^\\d{2}\\.\\d{2}\\.\\d{4}$");    //задать параметры для проверки(формат даты)
	if (!rx.exactMatch(date))
		throw InputException(14, "Дата должна быть в формате DD.MM.YYYY");
}
void checkTime(QString time)
{
	if (time.isEmpty())
		throw InputException(20, "Время не может быть пустым");
	QRegExp rx("^\\d{2}:\\d{2}$");     //задать параметры для проверки(формат времени)
	if (!rx.exactMatch(time))
		throw InputException(18, "Время должно быть в формате hh::mm");
}
void checkContacts(QString contacts)
{
	if (contacts.isEmpty())
		throw InputException(21, "Номер телефона не может быть пустым");
	QRegExp rx("^\\+\\d{12}$");     //задать параметры для проверки(формат номера телефона)
	if (!rx.exactMatch(contacts))
		throw InputException(15, "Номер телефона должен начинаться с '+' и содержать 12 цифр");
}
void checkAdress(QString adress)
{
	if (adress.isEmpty())
		throw InputException(22, "Адрес не может быть пустым");
	QRegExp rx("^[а-яА-ЯёЁ\\s]+ \\d{1,3}-\\d{1,3}$");   //задать параметры для проверки(формат адреса)
	if (!rx.exactMatch(adress))
		throw InputException(5, "Адрес должен быть в формате: Название улицы на русском языке, пробел, номерДома-номерКвартиры");
}
