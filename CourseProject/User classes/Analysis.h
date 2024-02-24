//класс медицинского анализа
#ifndef ANALYSIS_H
#define ANALYSIS_H
#include "MedRecord.h"
class Analysis : public MedRecord
{
	QString type;       //тип анализа
	QString results;    //результаты
public:
	Analysis(int patientId = 0, int doctorId = 0, QString date = "", QString type = "", QString results = "");
	~Analysis();
	QString getType()const;
	void setType(QString type);
	QString getResults()const;
	void setResults(QString results);
	friend QTextStream& operator<<(QTextStream& out, const Analysis& obj);
	friend QTextStream& operator>>(QTextStream& in, Analysis& obj);
};
#endif // ANALYSIS_H
