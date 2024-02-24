#include "appointmentwindow.h"
#include "ui_appointmentwindow.h"
AppointmentWindow::AppointmentWindow(int id, Tree<User>& users, QMap<int, Doctor>& doctors, Tree<Appointment>& appointments,
	QMap<int, QString>& services, QWidget* parent) : id(id), users(users), doctors(doctors), appointments(appointments), services(services), QDialog(parent),
	ui(new Ui::AppointmentWindow)
{
	ui->setupUi(this);
	setWindowTitle("Записи на прием к врачу");
	resize(2000, 1000);                                                        //установить начальную ширину окна
	fillAppList(id, users, doctors, appointments, services);                   //заполнить список записей к врачам
	flag = 0;
	//установить шрифты
	ui->appList->setFont(QFontDatabase::systemFont(QFontDatabase::FixedFont));
	ui->docList->setFont(QFontDatabase::systemFont(QFontDatabase::FixedFont));
	ui->timeList->setFont(QFontDatabase::systemFont(QFontDatabase::FixedFont));
	//перестроить контейнер с данными о пользователях по параметру ФИО
	Algorithm<User>::restructing(users, 4);
	for (auto it = users.begin(), ite = users.end(); it != ite; ++it) //проход по дереву
	{
		if ((*it).getRole() == 'd')                                   //если доктор
		{
			//добавить в список
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
	ui->appList->clear();   //очистить список
	map.clear();            //очистить контейнер текущих записей
	Algorithm<User>::restructing(users, 1); //перестроить дерево по параметру ID пользователя
	int num = 1;    //порядковый номер записи
	for (auto it = appointments.begin(), ite = appointments.end(); it != ite; ++it)    //пройти по контейнеру
	{
		if ((*it).getPatientId() == id)  //если ID пациента совпало
		{
			map.insert(num, *it);   //добавить в контейнер
			//получить данные из контейнеров и добавить в список
			QString pos = QString::number(num);
			QString serv = services[(*it).getServiceId()];
			serv = serv.leftJustified(20, ' ');
			QString date = (*it).getTime().toString("dd.MM.yyyy hh:mm");
			User obj((*it).getDoctorId());
			auto doc = Algorithm<User>::search(users, obj);
			QString docName = doc->getName();
			docName = docName.leftJustified(36, ' ');
			QString cab = QString::number(doctors[(*it).getDoctorId()].getCabinet());
			QString info = pos + " " + docName + " " + serv + " " + date + " Кабинет " + cab;
			ui->appList->addItem(info);
			num++;
		}
	}
}
void AppointmentWindow::on_deleteAppButton_clicked()
{
	QListWidgetItem* item = ui->appList->currentItem(); //сохранить текущий элемент
	if (item)
	{
		QString info = item->text();        //получить тект
		QStringList parts = info.split(" ");//разбить на слова
		int num = parts[0].toInt();
		Appointment obj = map[num];         //получить объект записи
		//найти запись
		Appointment del = Algorithm<Appointment>::findNode(appointments.getRoot(), obj,
			appointments.getConstructionMode())->getData();
		//удалить запись
		appointments.pop(del);
		//установить что запись свободна
		del.setPatientId(0);
		appointments.push(del); //добавить запись
		delete item;    //удалить из списка
		flag++;
	}
}
void AppointmentWindow::on_exitButton_clicked()
{
	this->close();
	emit exit(appointments);    //выйти из окна
}
void AppointmentWindow::on_cancelButton_clicked()
{
	if (flag <= 0)
	{
		QMessageBox::warning(this, "damn", "Невозможно выполнить отмену");
		return;
	}
	//отменить добавление свободной записи и удаления занятой
	Algorithm<Appointment>::cancel(appointments);
	Algorithm<Appointment>::cancel(appointments);
	//обновить список записей
	fillAppList(id, users, doctors, appointments, services);
	flag--;
}
void AppointmentWindow::on_choiceButton_clicked()
{
	ui->timeList->clear();  //очистить список с временем
	QListWidgetItem* item = ui->docList->currentItem(); //сохранить текущий элемент списка с врачами
	if (item)
	{
		QString info = item->text();            //получить текст
		QStringList parts = info.split(" ");    //разбить на слова
		QString name = parts[0] + " " + parts[1] + " " + parts[2];
		int id = 0;
		User obj(0, 'd', "", "", name); //создать временный объект
		Algorithm<User>::restructing(users, 4);     //перестроить дерево по параметру ФИО пациента
		std::optional<User> opt = Algorithm<User>::search(users, obj);  //найти доктора с такими данными
		if (opt.has_value())
			id = opt->getId();  //обновить ID доктора
		for (auto it = appointments.begin(), ite = appointments.end(); it != ite; ++it) //пройти по контейнеру
		{
			if ((*it).getDoctorId() == id)       //если ID совпало
			{
				if ((*it).getPatientId() == 0)   //если запись свободна
				{
					//добавить время записи в список
					QString time = (*it).getTime().toString("dd.MM.yyyy hh:mm");
					ui->timeList->addItem(time);
				}
			}
		}
	}
}
void AppointmentWindow::on_appButton_clicked()
{
	//сохранить выбранные элементы
	QListWidgetItem* docItem = ui->docList->currentItem();
	QListWidgetItem* timeItem = ui->timeList->currentItem();
	if (docItem && timeItem)
	{
		//получить данные
		QString docInfo = docItem->text();
		QString timeInfo = timeItem->text();
		//разбить на слова
		QStringList docParts = docInfo.split(" ");
		QStringList timeParts = timeInfo.split(" ");
		QString name = docParts[0] + " " + docParts[1] + " " + docParts[2];
		int id = 0; //ID доктора
		User obj(0, 'd', "", "", name);     //создать временный объект
		Algorithm<User>::restructing(users, 4); //перестроить дерево по параметру ФИО пользователя
		std::optional<User> opt = Algorithm<User>::search(users, obj);  //создать временный объект
		if (opt.has_value())
			id = opt->getId();  //обновить ID доктора
		for (auto it = appointments.begin(), ite = appointments.end(); it != ite; ++it) //пройти по контейнеру
		{
			//если ID доктора и время совпали
			if ((*it).getTime().toString("dd.MM.yyyy hh:mm") == timeParts[0] + " " + timeParts[1] && (*it).getDoctorId() == id)
			{
				//устанавливаем ID пациента
				(*it).setPatientId(this->id);
				//удаляем из списка запись
				ui->timeList->takeItem(ui->timeList->row(timeItem));
				//обновить список с текущими записями
				fillAppList(this->id, users, doctors, appointments, services);
			}
		}
	}
}
