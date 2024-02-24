#include "shedulewindow.h"
#include "ui_shedulewindow.h"
sheduleWindow::sheduleWindow(Doctor& doctor, Tree<Appointment>& appointments, QWidget* parent) : doctor(doctor), appointments(appointments), QDialog(parent), ui(new Ui::sheduleWindow)
{
	ui->setupUi(this);
	setWindowTitle("���������� ����������");
	resize(850, 650);
	ui->date1Edit->setText("��.��.����");
	ui->time1Edit->setText("��:MM");
	ui->time2Edit->setText("��:MM");
}
sheduleWindow::~sheduleWindow()
{
	delete ui;
}
void sheduleWindow::on_saveButton_clicked()
{
	//������� ��������� ������
	QString n = ui->daysNumEdit->text();
	QString d1 = ui->date1Edit->text();
	QString t1 = ui->time1Edit->text();
	QString t2 = ui->time2Edit->text();
	QString r = ui->rangeEdit->text();
	//��������� ��������� ������
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
	//������� ����
	int num = n.toInt();
	if (num < 5)
	{
		QMessageBox::critical(this, "�������� ������ �������", "����� ������ ���� �� ������ 5 �����");
		return;
	}
	QDate date1 = QDate::fromString(d1, "dd.MM.yyyy");
	QTime time1 = QTime::fromString(t1, "hh:mm");
	QTime time2 = QTime::fromString(t2, "hh:mm");
	int range = r.toInt();
	for (int i = 0; i < num; ++i)   //���� �� ����
	{
		QDate date = date1.addDays(i);  //��������� ����
		QTime time = time1;
		while (time <= time2)            //���� �� ������� ������
		{
			QDateTime dateTime(date, time); //������� ������
			Appointment app(doctor.getId(), 0, doctor.getServiceId(), dateTime);    //������� ������
			appointments.push(app);         //�������� ������
			time = time.addSecs(range * 60);  //�������� �����
		}
	}
	this->close();
	emit exit(appointments);    //����� �� ����
}
