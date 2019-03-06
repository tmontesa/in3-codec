#pragma once

#include <stdlib.h>
#include <QWidget>
#include <QPainter>
#include <QDebug>
#include "LosslessCodec.h"

class ImageCanvas : public QWidget
{
	Q_OBJECT


public:
	ImageCanvas(QWidget *parent);
	~ImageCanvas();

public slots:
	void GetFilestream(QString, QString);
	

signals:
	void SendCompressionRatio(QString);
	void SendIN3Stream(QString);

protected:
	void GetDimensions();
	void paintEvent(QPaintEvent* event);

private:
	std::string filestream;
	std::string imagestream;
	int mode;
	int width;
	int height;
	int dataoffset;

	QImage backup;

	std::string LittleEndiantoBigEndian(std::string little);
	int LittleHextoInt(std::string s);
	int HextoInt(std::string s);
	
};
