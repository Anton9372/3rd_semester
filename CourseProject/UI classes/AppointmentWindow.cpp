#include "appointmentwindow.h"
#include "ui_appointmentwindow.h"
AppointmentWindow::AppointmentWindow(int id, Tree<User>& users, QMap<int, Doctor>& doctors, Tree<Appointment>& appointments,
	QMap<int, QString>& services, QWidget* parent) : id(id), users(users), doctors(doctors), appointments(appointments), services(services), QDialog(parent),
	ui(new Ui::AppointmentWindow)
{
	ui->setupUi(this);
	setWindowTitle("������ �� ����� � �����");
	resize(2000, 1000);                                                        //���������� ��������� ������ ����
	fillAppList(id, users, doctors, appointments, services);                   //��������� ������ ������� � ������
	flag = 0;
	//���������� ������
	ui->appList->setFont(QFontDatabase::systemFont(QFontDatabase::FixedFont));
	ui->docList->setFont(QFontDatabase::systemFont(QFontDatabase::FixedFont));
	ui->timeList->setFont(QFontDatabase::systemFont(QFontDatabase::FixedFont));
	//����������� ��������� � ������� � ������������� �� ��������� ���
	Algorithm<User>::restructing(users, 4);
	for (auto it = users.begin(), ite = users.end(); it != ite; ++it) //������ �� ������
	{
		if ((*it).getRole() == 'd')                                   //���� ������
		{
			//�������� � ������
			QString docName = (*it).getName();
			docName = docName.leftJustified(36, ' ');
			int serv = doctors[(*it).getId()].getServiceId();
			QString service = services[serv];
			QString info = docName + service;
			ui->docList->addItem(info);
		}
	}
}
AppointmentWindow::~AppointmentWindow()
{
	delete ui;
}
void AppointmentWindow::fillAppList(int id, Tree<User>& users, QMap<int, Doctor>& doctors, Tree<Appointment>& appointments, QMap<int, QString>& services)
{
	ui->appList->clear();   //�������� ������
	map.clear();            //�������� ��������� ������� �������
	Algorithm<User>::restructing(users, 1); //����������� ������ �� ��������� ID ������������
	int num = 1;    //���������� ����� ������
	for (auto it = appointments.begin(), ite = appointments.end(); it != ite; ++it)    //������ �� ����������
	{
		if ((*it).getPatientId() == id)  //���� ID �������� �������
		{
			map.insert(num, *it);   //�������� � ���������
			//�������� ������ �� ����������� � �������� � ������
			QString pos = QString::number(num);
			QString serv = services[(*it).getServiceId()];
			serv = serv.leftJustified(20, ' ');
			QString date = (*it).getTime().toString("dd.MM.yyyy hh:mm");
			User obj((*it).getDoctorId());
			auto doc = Algorithm<User>::search(users, obj);
			QString docName = doc->getName();
			docName = docName.leftJustified(36, ' ');
			QString cab = QString::number(doctors[(*it).getDoctorId()].getCabinet());
			QString info = pos + " " + docName + " " + serv + " " + date + " ������� " + cab;
			ui->appList->addItem(info);
			num++;
		}
	}
}
void AppointmentWindow::on_deleteAppButton_clicked()
{
	QListWidgetItem* item = ui->appList->currentItem(); //��������� ������� �������
	if (item)
	{
		QString info = item->text();        //�������� ����
		QStringList parts = info.split(" ");//������� �� �����
		int num = parts[0].toInt();
		Appointment obj = map[num];         //�������� ������ ������
		//����� ������
		Appointment del = Algorithm<Appointment>::findNode(appointments.getRoot(), obj,
			appointments.getConstructionMode())->getData();
		//������� ������
		appointments.pop(del);
		//���������� ��� ������ ��������
		del.setPatientId(0);
		appointments.push(del); //�������� ������
		delete item;    //������� �� ������
		flag++;
	}
}
void AppointmentWindow::on_exitButton_clicked()
{
	this->close();
	emit exit(appointments);    //����� �� ����
}
void AppointmentWindow::on_cancelButton_clicked()
{
	if (flag <= 0)
	{
		QMessageBox::warning(this, "damn", "���������� ��������� ������");
		return;
	}
	//�������� ���������� ��������� ������ � �������� �������
	Algorithm<Appointment>::cancel(appointments);
	Algorithm<Appointment>::cancel(appointments);
	//�������� ������ �������
	fillAppList(id, users, doctors, appointments, services);
	flag--;
}
void AppointmentWindow::on_choiceButton_clicked()
{
	ui->timeList->clear();  //�������� ������ � ��������
	QListWidgetItem* item = ui->docList->currentItem(); //��������� ������� ������� ������ � �������
	if (item)
	{
		QString info = item->text();            //�������� �����
		QStringList parts = info.split(" ");    //������� �� �����
		QString name = parts[0] + " " + parts[1] + " " + parts[2];
		int id = 0;
		User obj(0, 'd', "", "", name); //������� ��������� ������
		Algorithm<User>::restructing(users, 4);     //����������� ������ �� ��������� ��� ��������
		std::optional<User> opt = Algorithm<User>::search(users, obj);  //����� ������� � ������ �������
		if (opt.has_value())
			id = opt->getId();  //�������� ID �������
		for (auto it = appointments.begin(), ite = appointments.end(); it != ite; ++it) //������ �� ����������
		{
			if ((*it).getDoctorId() == id)       //���� ID �������
			{
				if ((*it).getPatientId() == 0)   //���� ������ ��������
				{
					//�������� ����� ������ � ������
					QString time = (*it).getTime().toString("dd.MM.yyyy hh:mm");
					ui->timeList->addItem(time);
				}
			}
		}
	}
}
void AppointmentWindow::on_appButton_clicked()
{
	//��������� ��������� ��������
	QListWidgetItem* docItem = ui->docList->currentItem();
	QListWidgetItem* timeItem = ui->timeList->currentItem();
	if (docItem && timeItem)
	{
		//�������� ������
		QString docInfo = docItem->text();
		QString timeInfo = timeItem->text();
		//������� �� �����
		QStringList docParts = docInfo.split(" ");
		QStringList timeParts = timeInfo.split(" ");
		QString name = docParts[0] + " " + docParts[1] + " " + docParts[2];
		int id = 0; //ID �������
		User obj(0, 'd', "", "", name);     //������� ��������� ������
		Algorithm<User>::restructing(users, 4); //����������� ������ �� ��������� ��� ������������
		std::optional<User> opt = Algorithm<User>::search(users, obj);  //������� ��������� ������
		if (opt.has_value())
			id = opt->getId();  //�������� ID �������
		for (auto it = appointments.begin(), ite = appointments.end(); it != ite; ++it) //������ �� ����������
		{
			//���� ID ������� � ����� �������
			if ((*it).getTime().toString("dd.MM.yyyy hh:mm") == timeParts[0] + " " + timeParts[1] && (*it).getDoctorId() == id)
			{
				//������������� ID ��������
				(*it).setPatientId(this->id);
				//������� �� ������ ������
				ui->timeList->takeItem(ui->timeList->row(timeItem));
				//�������� ������ � �������� ��������
				fillAppList(this->id, users, doctors, appointments, services);
			}
		}
	}
}
