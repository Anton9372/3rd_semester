//����� ���������� ���� ���������
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QMap>
#include "labels.h"
#include "authwindow.h"
#include "tree.h"
#include "User.h"
#include "FUNCTIONS.h"
#include "filestream.h"
#include "exception.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	explicit MainWindow(QWidget* parent = nullptr);
	~MainWindow();
	void updateConts(Tree<User>& users);            //����� ���������� ���������� � ��������������
private slots:
	void on_loginButton_clicked();
	void on_viewDoctorsButton_clicked();
	void on_viewServicesButton_clicked();
private:
	Tree<User> users;               //��������� � ������� �������������
	QMap<int, Doctor> doctors;      //��������� � ������� ������
	QMap<int, QString> services;    //��������� � ������� ���������
	Ui::MainWindow* ui;             //������� ����
	AuthWindow* ui_auth;            //���� �����������
	ViewDoctorsLabel* label1;       //������ ��������
	ViewServicesLabel* label2;      //������ ��������������� �����
};
#endif // MAINWINDOW_H
