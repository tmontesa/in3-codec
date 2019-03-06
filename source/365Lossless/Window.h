#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Window.h"

#include <QFileDialog>
#include <QDebug>



class Window : public QMainWindow
{
	Q_OBJECT

public:
	Window(QWidget *parent = Q_NULLPTR);

public slots:
	void GetFile();
	void GetIN3Stream(QString);
	void SaveIN3Stream();

signals:
	void SendFilename(QString);
	void SendFilestream(QString, QString);

private:
	Ui::WindowClass ui;

	QString filename;
	QString filestream;
	QString in3stream;

	int IsIN3();
};
