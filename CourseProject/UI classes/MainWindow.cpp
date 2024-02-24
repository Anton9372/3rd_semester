#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget* parent) : users(2), QMainWindow(parent), ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	setWindowTitle("����� ����������");
	resize(850, 650);   //���������� ��������� ������ ����
	FileStream fs;      //������� �������� �����
	//������� ������ �� ������ � ����������
	try
	{
		fs.open("C:\\Qt\\projects\\textFiles\\user_demo.txt", 1);
		fs.read(users);
		fs.close();
		fill_map_cont<Doctor>(doctors, "C:\\Qt\\projects\\textFiles\\doctor_demo.txt");
		fill_map_cont(services, "C:\\Qt\\projects\\textFiles\\service.txt");
	}
	catch (FileException& e)
	{
		QMessageBox::critical(this, "�������������� ������", "������ ������ � �������");
		e.whatFile();
		QCoreApplication::exit(1);
	}
}
MainWindow::~MainWindow()
{
	delete ui;
}
void MainWindow::updateConts(Tree<User>& users)
{
	this->users.copyTree(users);    //�������� ���������
}
void MainWindow::on_loginButton_clicked()
{
	ui_auth = new AuthWindow(users, doctors, services);                     //������� ���� �����������
	//������� ������ ������ �� ���� ����������� � ����������� ����������
	connect(ui_auth, &AuthWindow::exit, this, &MainWindow::updateConts);
	//������� ������ ������ �� ���� ����������� � ������� ���������� ����
	connect(ui_auth, &AuthWindow::exit, this, &MainWindow::show);
	this->close();                                                          //������� ��������� ����
	ui_auth->show();                                                        //�������� ���� �����������
}
void MainWindow::on_viewDoctorsButton_clicked()
{
	label1 = new ViewDoctorsLabel(users, doctors, services);    //������� ������ ������
	label1->show();                                             //�������� ������ ������
}
void MainWindow::on_viewServicesButton_clicked()
{
	label2 = new ViewServicesLabel(services);                   //������� ������ �����
	label2->show();                                             //��������
}
