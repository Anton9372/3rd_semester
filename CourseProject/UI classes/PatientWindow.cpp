#include "patientwindow.h"
#include "ui_patientwindow.h"
PatientWindow::PatientWindow(User& user, Tree<User>& users, QMap<int, Patient>& patients, QMap<int, Doctor>& doctors, QMap<int, QString>& services, Tree<Message>& messages, Tree<Diagnosis>& diagnoses, Tree<Analysis>& analyses, Tree<Appointment>& appointments, QWidget* parent) :
	users(users), patients(patients), doctors(doctors), services(services), messages(messages), diagnoses(diagnoses), analyses(analyses), appointments(appointments), QDialog(parent), ui(new Ui::PatientWindow), patient(user.getId(), user.getRole(), user.getLogin(), user.getPassword(), user.getName(), user.getContacts())
{
	ui->setupUi(this);
	setWindowTitle("Главное меню");
	resize(850, 650);
	//установить данные для пациента
	Patient obj = patients.value(user.getId());
	patient.setAdress(obj.getAdress());
	patient.setDateOfBirth(obj.getDateOfBirth());
}
PatientWindow::~PatientWindow()
{
	delete ui;
}
void PatientWindow::updatePatient(const Patient& patient)
{
	//удалить старные данные
	users.pop(this->patient);
	patients.remove(this->patient.getId());
	this->patient = patient;    //обновить данные
	//добавить новые данные
	users.push(patient);
	patients.insert(patient.getId(), patient);
}
void PatientWindow::updateApps(Tree<Appointment>& apps)
{
	appointments.copyTree(apps);    //обновить контейнер с записями к врачам
}
void PatientWindow::on_viewMedCardButton_clicked()
{
	//создать список с медицинской карточкой
	label4 = new ViewMedCardLabel(patient.getId(), users, diagnoses, analyses, services);
	label4->show();
}
void PatientWindow::on_appointmentButton_clicked()
{
	//создать окно записи к врачам
	ui_appointment = new AppointmentWindow(patient.getId(), users, doctors, appointments, services);
	//связать выход из окна записи с показом текущего и обновлением данных
	connect(ui_appointment, &AppointmentWindow::exit, this, &PatientWindow::show);
	connect(ui_appointment, &AppointmentWindow::exit, this, &PatientWindow::updateApps);
	this->close();
	ui_appointment->show();
}
void PatientWindow::on_viewDoctorsButton_clicked()
{
	//создать списко с врачами
	label1 = new ViewDoctorsLabel(users, doctors, services);
	label1->show();
}
void PatientWindow::on_viewServicesButton_clicked()
{
	//создать список с услугами
	label2 = new ViewServicesLabel(services);
	label2->show();
}
void PatientWindow::on_changeInfoButton_clicked()
{
	//создать окно изменения личной информации
	ui_changeInfo = new PatientChangeInfoWindow(patient);
	//связать выход из окна изменения с показом текущего и обновлением данных
	connect(ui_changeInfo, &PatientChangeInfoWindow::save, this, &PatientWindow::updatePatient);
	connect(ui_changeInfo, &PatientChangeInfoWindow::save, this, &PatientWindow::show);
	this->close();
	ui_changeInfo->show();
}
void PatientWindow::on_viewMessagesButton_clicked()
{
	//создать список с входящими сообщениями
	label3 = new ViewMessagesLabel(patient.getId(), users, messages);
	label3->show();
}
void PatientWindow::on_exitButton_clicked()
{
	FileStream fs;  //файловый поток
	Algorithm<User>::restructing(users, 1); //перестроить дерево по полю ID пользователя
	//запись данных в файлы
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
	emit exit(users);   //выход из окна
}
