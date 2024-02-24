#include "Message.h"
Message::Message(int patientId, int doctorId, QString message) : Record(patientId, doctorId), message(message)
{

}
Message::~Message()
{

}
QString Message::getMessage()const
{
	return message;
}
void Message::setMessage(QString message)
{
	this->message = message;
}
QTextStream& operator<<(QTextStream& out, const Message& obj)
{
	out.setFieldAlignment(QTextStream::AlignLeft);
	out.setFieldWidth(3);
	out << obj.getPatientId();
	out.setFieldWidth(3);
	out << obj.getDoctorId();
	out << obj.message;
	out.setFieldWidth(0);  // —бросить ширину пол€
	return out;
}
QTextStream& operator>>(QTextStream& in, Message& obj)
{
	in >> obj.patientId >> obj.doctorId;
	obj.message = in.readLine().trimmed();
	return in;
}
