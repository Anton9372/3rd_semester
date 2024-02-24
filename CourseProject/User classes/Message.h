//класс личного сообщения врача пациенту
#ifndef MESSAGE_H
#define MESSAGE_H
#include "Record.h"
#include <QString>
class Message : public Record
{
	QString message;    //сообщение
public:
	Message(int patientId = 0, int doctorId = 0, QString message = "");
	virtual ~Message();
	QString getMessage()const;
	void setMessage(QString message);
	friend QTextStream& operator<<(QTextStream& out, const Message& obj);
	friend QTextStream& operator>>(QTextStream& in, Message& obj);
};
#endif // MESSAGE_H
