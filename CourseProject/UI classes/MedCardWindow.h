//класс окна для записи в медицинскую карточку пациента
#ifndef MEDCARDWINDOW_H
#define MEDCARDWINDOW_H
#include <QDialog>
#include <QMap>
#include <QMessageBox>
#include <QFontDatabase>
#include "tree.h"
#include "Analysis.h"
#include "Diagnosis.h"
#include "Message.h"
#include "Doctor.h"
#include "Patient.h"
#include "labels.h"
#include "FUNCTIONS.h"
#include "exception.h"
#include "algorithm.h"
namespace Ui {
	class MedCardWindow;
}
class MedCardWindow : public QDialog
{
	Q_OBJECT
signals:
	void exit(Tree<Message>& messages, Tree<Diagnosis>& diagnoses, Tree<Analysis>& analyses);   //выход из окна
public:
	MedCardWindow(Doctor& doctor, Tree<User>& users, QMap<int, Doctor>& doctors, QMap<int, Patient>& patients, Tree<Message>& messages, Tree<Diagnosis>& diagnoses, Tree<Analysis>& analyses, QMap<int, QString>& services, QWidget* parent = nullptr);
	~MedCardWindow();
private slots:
	void on_exitButton_clicked();
	void on_findButton_clicked();
	void on_choiceButton_clicked();
	void on_viewMedCardButton_clicked();
	void on_viewPatientsButton_clicked();
	void on_sendButton_clicked();
	void on_diagSaveButton_clicked();
	void on_analSaveButton_clicked();
	void on_cancelMess_clicked();
	void on_cancelDiag_clicked();
	void on_cancelAnal_clicked();
private:
	Doctor doctor;      //доктор
	Patient patient;    //пациент
	//контейнеры с данными
	Tree<User> users;
	QMap<int, Doctor> doctors;
	QMap<int, Patient> patients;
	Tree<Message> messages;
	Tree<Diagnosis> diagnoses;
	Tree<Analysis> analyses;
	QMap<int, QString> services;
	//флаги для отмены действий
	int messFl;
	int otherFl;
	Ui::MedCardWindow* ui;  //окно
};
#endif // MEDCARDWINDOW_H
