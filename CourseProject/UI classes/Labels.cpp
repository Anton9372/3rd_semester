#include "labels.h"
#include <QVBoxLayout>
ViewDoctorsLabel::ViewDoctorsLabel(Tree<User>& users, QMap<int, Doctor>& doctors, QMap<int, QString>& services, QWidget* parent)
	: QWidget(parent)
{
	setWindowTitle("Просмотр докторов");
	//создать временное дерево и перестроить его по параметру ФИО пользователя
	Tree<User> tree;
	tree.copyTree(users);
	Algorithm<User>::restructing(tree, 4);
	QGridLayout* grid = new QGridLayout();
	//создать шапку
	QLabel* nameHeader = new QLabel("ФИО", this);
	QLabel* contactsHeader = new QLabel("Контакты", this);
	QLabel* experienceHeader = new QLabel("Опыт работы(лет)", this);
	QLabel* serviceHeader = new QLabel("Предоставляемая услуга", this);
	grid->addWidget(nameHeader, 0, 0);
	grid->addWidget(contactsHeader, 0, 1);
	grid->addWidget(experienceHeader, 0, 2);
	grid->addWidget(serviceHeader, 0, 3);
	int row = 1;    //ряд
	for (auto it = tree.begin(), ite = tree.end(); it != ite; ++it)    //пройти по контейнеру
	{
		if ((*it).getRole() == 'd')      //если пользователь - врач
		{
			//добавить его
			QLabel* nameLabel = new QLabel((*it).getName(), this);
			QLabel* contactsLabel = new QLabel((*it).getContacts(), this);
			QString exp = QString::number(doctors.value((*it).getId()).getExperience());
			QLabel* experienceLabel = new QLabel(exp, this);
			QString service = services[doctors.value((*it).getId()).getServiceId()];
			QLabel* serviceLabel = new QLabel(service, this);
			nameLabel->setFont(QFont("Purisa", 10));
			contactsLabel->setFont(QFont("Purisa", 10));
			experienceLabel->setFont(QFont("Purisa", 10));
			serviceLabel->setFont(QFont("Purisa", 10));
			grid->addWidget(nameLabel, row, 0);
			grid->addWidget(contactsLabel, row, 1);
			grid->addWidget(experienceLabel, row, 2);
			grid->addWidget(serviceLabel, row, 3);
			row++;
		}
	}
	setLayout(grid);
}
ViewDoctorsLabel::~ViewDoctorsLabel()
{
}
ViewServicesLabel::ViewServicesLabel(QMap<int, QString>& services, QWidget* parent)
	: QWidget(parent)
{
	setWindowTitle("Просмотр услуг");
	QGridLayout* grid = new QGridLayout();
	int row = 0;
	for (int i = 1; i <= services.size(); ++i)   //пройти по услугам
	{
		//добавить услугу
		QLabel* serviceLabel = new QLabel(services.value(i), this);
		serviceLabel->setFont(QFont("Purisa", 10));
		grid->addWidget(serviceLabel, row, 0);
		row++;
	}
	setLayout(grid);
}
ViewServicesLabel::~ViewServicesLabel()
{
}
ViewMessagesLabel::ViewMessagesLabel(int id, Tree<User>& users, Tree<Message>& messages, QWidget* parent) : id(id), QWidget(parent)
{
	setWindowTitle("Просмотр входящих сообщений");
	//создать временное дерево и перестроить его по параметру ID пользователя
	Tree<User> tree;
	tree.copyTree(users);
	Algorithm<User>::restructing(tree, 1);
	QGridLayout* grid = new QGridLayout();
	int row = 0;    //ряд
	for (auto it = messages.begin(), ite = messages.end(); it != ite; ++it)    //пройти по контейнеру
	{
		if ((*it).getPatientId() == id)  //если ID пацеента совпало
		{
			User obj((*it).getDoctorId());  //временный объект доктора
			auto doc = Algorithm<User>::search(tree, obj);     //найти врача
			//добавить данные врача и сообщение
			QString docName = doc->getName();
			QString mess = (*it).getMessage();
			QLabel* nameLabel = new QLabel(docName, this);
			QLabel* messLabel = new QLabel(mess, this);
			nameLabel->setFont(QFont("Purisa", 10));
			messLabel->setFont(QFont("Purisa", 10));
			grid->addWidget(nameLabel, row, 0);
			grid->addWidget(messLabel, row, 1);
			row++;
		}
	}
	setLayout(grid);
}
ViewMessagesLabel::~ViewMessagesLabel()
{
}
ViewMedCardLabel::ViewMedCardLabel(int id, Tree<User>& users, Tree<Diagnosis>& diagnoses, Tree<Analysis>& analyses, QMap<int, QString>& services, QWidget* parent)
	: id(id), QWidget(parent)
{
	setWindowTitle("Просмотр медицинской карточки");
	//создать временное дерево и перестроить его по параметру ID пользователя
	Tree<User> tree;
	tree.copyTree(users);
	Algorithm<User>::restructing(tree, 1);
	QGridLayout* grid = new QGridLayout();
	int row = 0;    //ряд
	//добавить шапку
	QLabel* nameHeader1 = new QLabel("Услуги", this);
	grid->addWidget(nameHeader1, row, 0);
	row++;
	for (auto it = diagnoses.begin(), ite = diagnoses.end(); it != ite; ++it)  //пройти по контейнеру
	{
		if ((*it).getPatientId() == id)  //если ID пациента совпало
		{
			User obj((*it).getDoctorId());  //временный объект доктора
			auto doc = Algorithm<User>::search(tree, obj);  //найти данные доктора
			//добавить данные доктора, дату, предоставленную услугу и результат
			QString docName = doc->getName();
			QString date = (*it).getDate();
			QString serv = services[(*it).getServiceId()];
			QString diag = (*it).getDiagnosis();
			QLabel* nameLabel = new QLabel(docName, this);
			QLabel* dateLabel = new QLabel(date, this);
			QLabel* servLabel = new QLabel(serv, this);
			QLabel* diagLabel = new QLabel(diag, this);
			nameLabel->setFont(QFont("Purisa", 10));
			dateLabel->setFont(QFont("Purisa", 10));
			servLabel->setFont(QFont("Purisa", 10));
			diagLabel->setFont(QFont("Purisa", 10));
			grid->addWidget(nameLabel, row, 0);
			grid->addWidget(dateLabel, row, 1);
			grid->addWidget(servLabel, row, 2);
			grid->addWidget(diagLabel, row, 3);
			row++;
		}
	}
	//доьавить шапку
	QLabel* nameHeader2 = new QLabel("Анализы", this);
	grid->addWidget(nameHeader2, row, 0);
	row++;
	for (auto it = analyses.begin(), ite = analyses.end(); it != ite; ++it)    //цикл по контейнеру
	{
		if ((*it).getPatientId() == id)  //если ID пациента совпало
		{
			User obj((*it).getDoctorId());  //временный объект доктора
			auto doc = Algorithm<User>::search(tree, obj);  //найти данные доктора
			//добавить данные доктора, дату, тип анализа и результат
			QString docName = doc->getName();
			QString date = (*it).getDate();
			QString type = (*it).getType();
			QString res = (*it).getResults();
			QLabel* nameLabel = new QLabel(docName, this);
			QLabel* dateLabel = new QLabel(date, this);
			QLabel* typeLabel = new QLabel(type, this);
			QLabel* resLabel = new QLabel(res, this);
			nameLabel->setFont(QFont("Purisa", 10));
			dateLabel->setFont(QFont("Purisa", 10));
			typeLabel->setFont(QFont("Purisa", 10));
			resLabel->setFont(QFont("Purisa", 10));
			grid->addWidget(nameLabel, row, 0);
			grid->addWidget(dateLabel, row, 1);
			grid->addWidget(typeLabel, row, 2);
			grid->addWidget(resLabel, row, 3);
			row++;
		}
	}
	setLayout(grid);
}
ViewMedCardLabel::~ViewMedCardLabel()
{
}
ViewScheduleLabel::ViewScheduleLabel(int id, Tree<User>& users, QMap<int, QString>& services, Tree<Appointment>& appointments, QWidget* parent)
{
	setWindowTitle("Просмотр записей");
	//создать временное дерево и перестроить его по параметру ID пользователя
	Tree<User> tree;
	tree.copyTree(users);
	Algorithm<User>::restructing(tree, 1);
	QGridLayout* grid = new QGridLayout();
	//создать шапку
	QLabel* nameHeader = new QLabel("ФИО Пациента", this);
	QLabel* servHeader = new QLabel("Услуга", this);
	QLabel* dateHeader = new QLabel("Дата", this);
	grid->addWidget(nameHeader, 0, 0);
	grid->addWidget(servHeader, 0, 1);
	grid->addWidget(dateHeader, 0, 2);
	int row = 1;    //ряд
	for (auto it = appointments.begin(), ite = appointments.end(); it != ite; ++it)    //пройти по контейнеру
	{
		if ((*it).getDoctorId() == id)
		{
			User obj((*it).getPatientId());         //временный объект пациента
			std::optional<User> pat = Algorithm<User>::search(tree, obj);   //найти данные пациента
			if (pat.has_value())
			{
				//добавить данные пациента, услугу и время
				QString patName = pat->getName();
				QString serv = services[(*it).getServiceId()];
				QString date = (*it).getTime().toString("dd.MM.yyyy hh:mm");
				QLabel* nameLabel = new QLabel(patName, this);
				QLabel* servLabel = new QLabel(serv, this);
				QLabel* dateLabel = new QLabel(date, this);
				nameLabel->setFont(QFont("Purisa", 10));
				servLabel->setFont(QFont("Purisa", 10));
				dateLabel->setFont(QFont("Purisa", 10));
				grid->addWidget(nameLabel, row, 0);
				grid->addWidget(servLabel, row, 1);
				grid->addWidget(dateLabel, row, 2);
				row++;
			}
		}
	}
	setLayout(grid);
}
ViewScheduleLabel::~ViewScheduleLabel()
{
}
ViewPatientsLabel::ViewPatientsLabel(Tree<User>& users, QMap<int, Patient>& patients, QWidget* parent) : QWidget(parent)
{
	setWindowTitle("Просмотр пациентов");
	//создать временное дерево и перестроить его по параметру ФИО пользователя
	Tree<User> tree;
	tree.copyTree(users);
	Algorithm<User>::restructing(tree, 4);
	QGridLayout* grid = new QGridLayout();
	//добавить шапку
	QLabel* nameHeader = new QLabel("ФИО", this);
	QLabel* contactsHeader = new QLabel("Контакты", this);
	QLabel* dateHeader = new QLabel("Дата рождения", this);
	QLabel* adressHeader = new QLabel("Адрес", this);
	grid->addWidget(nameHeader, 0, 0);
	grid->addWidget(contactsHeader, 0, 1);
	grid->addWidget(dateHeader, 0, 2);
	grid->addWidget(adressHeader, 0, 3);
	int row = 1;        //ряд
	for (auto it = tree.begin(), ite = tree.end(); it != ite; ++it)        //пройти по пользователям
	{
		if ((*it).getRole() == 'p')  //если пользователь - пациент
		{
			//добавить его данные
			QLabel* nameLabel = new QLabel((*it).getName(), this);
			QLabel* contactsLabel = new QLabel((*it).getContacts(), this);
			QString date = patients[(*it).getId()].getDateOfBirth();
			QLabel* dateLabel = new QLabel(date, this);
			QString adress = patients[(*it).getId()].getAdress();
			QLabel* adressLabel = new QLabel(adress, this);
			nameLabel->setFont(QFont("Purisa", 10));
			contactsLabel->setFont(QFont("Purisa", 10));
			dateLabel->setFont(QFont("Purisa", 10));
			adressLabel->setFont(QFont("Purisa", 10));
			grid->addWidget(nameLabel, row, 0);
			grid->addWidget(contactsLabel, row, 1);
			grid->addWidget(dateLabel, row, 2);
			grid->addWidget(adressLabel, row, 3);
			row++;
		}
	}
	setLayout(grid);
}
ViewPatientsLabel::~ViewPatientsLabel()
{
}
