#include "shedulewindow.h"
#include "ui_shedulewindow.h"
sheduleWindow::sheduleWindow(Doctor& doctor, Tree<Appointment>& appointments, QWidget* parent) : doctor(doctor), appointments(appointments), QDialog(parent), ui(new Ui::sheduleWindow)
{
	ui->setupUi(this);
	setWindowTitle("Установить расписание");
	resize(850, 650);
	ui->date1Edit->setText("ДД.ММ.ГГГГ");
	ui->time1Edit->setText("ЧЧ:MM");
	ui->time2Edit->setText("ЧЧ:MM");
}
sheduleWindow::~sheduleWindow()
{
	delete ui;
}
void sheduleWindow::on_saveButton_clicked()
{
	//считать введенные данные
	QString n = ui->daysNumEdit->text();
	QString d1 = ui->date1Edit->text();
	QString t1 = ui->time1Edit->text();
	QString t2 = ui->time2Edit->text();
	QString r = ui->rangeEdit->text();
	//проверить введенные данные
	try
	{
		checkDate(d1);
		checkTime(t1);
		checkTime(t2);
	}
	catch (InputException& e)
	{
		QMessageBox::critical(this, e.getType(), e.getMessage());
		return;
	}
	//првести типы
	int num = n.toInt();
	if (num < 5)
	{
		QMessageBox::critical(this, "Неверный формат времени", "Время должно быть не меньше 5 минут");
		return;
	}
	QDate date1 = QDate::fromString(d1, "dd.MM.yyyy");
	QTime time1 = QTime::fromString(t1, "hh:mm");
	QTime time2 = QTime::fromString(t2, "hh:mm");
	int range = r.toInt();
	for (int i = 0; i < num; ++i)   //цикл по дням
	{
		QDate date = date1.addDays(i);  //увеличить дату
		QTime time = time1;
		while (time <= time2)            //цикл по времени работы
		{
			QDateTime dateTime(date, time); //создать объект
			Appointment app(doctor.getId(), 0, doctor.getServiceId(), dateTime);    //создать объект
			appointments.push(app);         //добавить объект
			time = time.addSecs(range * 60);  //добавить время
		}
	}
	this->close();
	emit exit(appointments);    //выйти из окна
}
