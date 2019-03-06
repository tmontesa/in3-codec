#include "Window.h"

Window::Window(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	qDebug() << "IN3 Lossless Compressor";
	qDebug() << "CMPT 365 - Summer 2018";
	qDebug() << "Timothy Montesa";
}

void Window::GetFile() {
	filename = QFileDialog::getOpenFileName(this, tr("Open File"),
		"/home", tr("Images (*.bmp *.in3)"));

	qDebug() << "Opening file...";
	QFile file(filename);
	if (!file.exists()) return;
	file.open(QIODevice::ReadOnly);

	qDebug() << "Reading file...";
	filestream = file.readAll().toHex();
	emit SendFilename(filename);
	if (IsIN3()) {
		qDebug() << "File is IN3.";
		emit SendFilestream(filestream, QString::number(2));
	} else {
		qDebug() << "File is BMP.";
		emit SendFilestream(filestream, QString::number(1));
	}

	file.close();
	return;
}

void Window::GetIN3Stream(QString i) {
	qDebug() << "Obtained IN3 stream.";
	in3stream = i;
}

void Window::SaveIN3Stream() {
	if (in3stream == NULL) return;
	
	QByteArray in3 = QByteArray::fromHex(in3stream.toUtf8());

	qDebug() << "Preparing to save file...";
	QString dir = QFileDialog::getSaveFileName(this, "Save file", ".in3", ".in3");

	QFile file(dir);
	file.open(QIODevice::WriteOnly);
	file.write(in3);
	file.close();

	qDebug() << "File saved.";
	return;
}

int Window::IsIN3() {
	return filename.toStdString().substr(filename.length() - 3) == "in3";
}