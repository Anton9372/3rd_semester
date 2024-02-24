#include "doctorwindow.h"
#include "ui_doctorwindow.h"
DoctorWindow::DoctorWindow(User& user, Tree<User>& users, QMap<int, Patient>& patients, QMap<int, Doctor>& doctors, QMap<int, QString>& services,
	Tree<Message>& messages, Tree<Diagnosis>& diagnoses, Tree<Analysis>& analyses, Tree<Appointment>& appointments, QWidget* parent) :
	users(users), patients(patients), doctors(doctors), services(services), messages(messages), diagnoses(diagnoses), analyses(analyses),
	appointments(appointments), QDialog(parent), ui(new Ui::DoctorWindow),
	doctor(user.getId(), user.getRole(), user.getLogin(), user.getPassword(), user.getName(), user.getContacts())
{
	ui->setupUi(this);
	setWindowTitle("Главное меню");
	resize(850, 650);
	//записать в текущий объект Doctor данные
	Doctor obj = doctors.value(user.getId());
	doctor.setExperience(obj.getExperience());
	doctor.setCabinet(obj.getCabinet());
	doctor.setServiceId(obj.getServiceId());
}
DoctorWindow::~DoctorWindow()
{
	delete ui;
}
void DoctorWindow::updateApps(Tree<Appointment>& apps)
{
	appointments.copyTree(apps);    //обновить контейнер с данными о расписании
}

void DoctorWindow::updateConts(Tree<Message>& messages, Tree<Diagnosis>& diagnoses, Tree<Analysis>& analyses)
{
	//обновить контейнеры с данными о медицинской карточке
	this->messages.copyTree(messages);
	this->diagnoses.copyTree(diagnoses);
	this->analyses.copyTree(analyses);
}
void DoctorWindow::updateDoctor(const Doctor& doctor)
{
	//удалить из контейра старные данные
	users.pop(this->doctor);
	doctors.remove(this->doctor.getId());
	//обновить текущий обьект Doctor
	this->doctor = doctor;
	//добавить новые данные в контейнеры
	users.push(doctor);
	doctors.insert(doctor.getId(), doctor);
}
void DoctorWindow::on_changeInfoButton_clicked()
{
	ui_changeInfo = new DoctorChangeInfoWindow(doctor); //создать окно изменения личных данных
	//свзязать выход из окна изменения с показом текущего окна и обновления данных
	connect(ui_changeInfo, &DoctorChangeInfoWindow::save, this, &DoctorWindow::updateDoctor);
	connect(ui_changeInfo, &DoctorChangeInfoWindow::save, this, &DoctorWindow::show);
	this->close();
	ui_changeInfo->show();
}
void DoctorWindow::on_exitButton_clicked()
{
	FileStream fs;      //создать файловый поток
	Algorithm<User>::restructing(users, 1);     //перестроить дерево по ID пользователя
	//записать данные из контейнеров в файлы
	try
	{
		fs.open("C:\\Qt\\projects\\textFiles\\user_demo.txt", 2);
		fs.write(users.getRoot());
		fs.deleteLastNewLine();
		fs.close();
		fs.open("C:\\Qt\\projects\\textFiles\\message_demo.txt", 2);
		fs.write(messages.getRoot());
		fs.deleteLastNewLine();
		fs.close();
		fs.open("C:\\Qt\\projects\\textFiles\\analysis_demo.txt", 2);
		fs.write(analyses.getRoot());
		fs.deleteLastNewLine();
		fs.close();
		fs.open("C:\\Qt\\projects\\textFiles\\diagnosis_demo.txt", 2);
		fs.write(diagnoses.getRoot());
		fs.deleteLastNewLine();
		fs.close();
		fs.open("C:\\Qt\\projects\\textFiles\\appointment_demo.txt", 2);
		fs.write(appointments.getRoot());
		fs.deleteLastNewLine();
		fs.close();
		write_file_map_cont(patients, "C:\\Qt\\projects\\textFiles\\patient_demo.txt");
		write_file_map_cont(doctors, "C:\\Qt\\projects\\textFiles\\doctor_demo.txt");
	}
	catch (FileException& e)
	{
		QMessageBox::critical(this, "Непредвиденная ошибка", "Данные не сохранились");
		e.whatFile();
		QCoreApplication::exit(1);
	}
	this->close();
	emit exit(users);
}
void DoctorWindow::on_addRecordButton_clicked()
{
	//создать окно записи в карточку пациента
	ui_medCard = new MedCardWindow(this->doctor, users, doctors, patients, messages, diagnoses, analyses, services);
	//связать выход из окна записи с показом текущего окна и обновлением контейнеров с данными
	connect(ui_medCard, &MedCardWindow::exit, this, &DoctorWindow::show);
	connect(ui_medCard, &MedCardWindow::exit, this, &DoctorWindow::updateConts);
	this->close();
	ui_medCard->show();
}
void DoctorWindow::on_checkSchedButton_clicked()
{
	//создать список с расписанием врача
	label = new ViewScheduleLabel(doctor.getId(), users, services, appointments);
	label->show();
}
void DoctorWindow::on_changeSchedButton_clicked()
{
	ui_shedule = new sheduleWindow(this->doctor, appointments); //создать окно с добавлением расписания
	//связать выход из окна расписания с показом текущего окна и обновлением контейнеров с данными
	connect(ui_shedule, &sheduleWindow::exit, this, &DoctorWindow::show);
	connect(ui_shedule, &sheduleWindow::exit, this, &DoctorWindow::updateApps);
	this->close();
	ui_shedule->show();
}
