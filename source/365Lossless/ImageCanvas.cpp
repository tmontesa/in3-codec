#include "ImageCanvas.h"

ImageCanvas::ImageCanvas(QWidget *parent)
	: QWidget(parent)
{
	filestream = "";
	mode = 0;
	width, height = 0;
}

ImageCanvas::~ImageCanvas()
{
}

void ImageCanvas::GetFilestream(QString fs, QString m) {
	qDebug() << "Getting filestream...";

	filestream = fs.toStdString();
	mode = stoi(m.toStdString());

	if (mode == 1) {
		qDebug() << "Set to mode 1 (BMP).";
		dataoffset = LittleHextoInt(filestream.substr(10 * 2, 4 * 2)) * 2;
		imagestream = filestream.substr(dataoffset);
		GetDimensions();
	} else {
		qDebug() << "Set to mode 2 (IN3).";
		imagestream = filestream;
	} 

	this->update();
	return;
}

void ImageCanvas::GetDimensions() {
	qDebug() << "Getting dimensions...";
	width = LittleHextoInt(filestream.substr(18 * 2, 4 * 2));
	height = LittleHextoInt(filestream.substr(22 * 2, 4 * 2));
}



void ImageCanvas::paintEvent(QPaintEvent* event) {
	QPainter painter(this);
	int r, g, b  = 0;

	if (mode == 1) {
		QImage image(width * 2, height, QImage::Format_RGB32);
		std::string compressed_imagestream;

		// DRAW ORIGINAL
		qDebug() << "Drawing original BMP...";
		for (int x = 0; x < width; x++) {
			for (int y = 0; y < height; y++) {
				// g, r, b
				b = HextoInt(imagestream.substr((6 * ((height * y) + x)) + 0, 2));
				g = HextoInt(imagestream.substr((6 * ((height * y) + x)) + 2, 2));
				r = HextoInt(imagestream.substr((6 * ((height * y) + x)) + 4, 2));
				image.setPixel(x, height - 1 - y, qRgb(r, g, b));
			}
		}
		painter.drawImage(QPoint(0, 0), image);
		qDebug() << "Done: Uncompressed RGB.";


		// COMPRESS & DECOMPRESS
		qDebug() << "Coverting hex data to binary...";
		compressed_imagestream = LosslessCodec::hex2bin(imagestream);
		qDebug() << "ENCODING binary data...";
		compressed_imagestream = LosslessCodec::Encoder(compressed_imagestream, width, height);
		emit SendIN3Stream(QString::fromStdString(LosslessCodec::bin2hex(compressed_imagestream)));

		qDebug() << "Calculating compression ratio...";
		double filesize = imagestream.length() * 4;
		double compressed_filesize = compressed_imagestream.length();
		double ratio = (compressed_filesize / filesize) * 100;
		emit SendCompressionRatio(QString::fromStdString("Ratio: " + std::to_string(ratio) + "%"));
		
		qDebug() << "DECODING binary data...";
		compressed_imagestream = LosslessCodec::Decoder(compressed_imagestream);
		
		
		qDebug() << "Coverting binary data to hex...";
		compressed_imagestream = LosslessCodec::bin2hex(compressed_imagestream);
		

		// DRAW COMPRESSED
		qDebug() << "Drawing compressed IN3...";
		compressed_imagestream = compressed_imagestream.substr(8);
		for (int x = 0; x < width; x++) {
			for (int y = 0; y < height; y++) {
				// g, r, b
				b = HextoInt(compressed_imagestream.substr((6 * ((height * y) + x)) + 0, 2));
				g = HextoInt(compressed_imagestream.substr((6 * ((height * y) + x)) + 2, 2));
				r = HextoInt(compressed_imagestream.substr((6 * ((height * y) + x)) + 4, 2));
				image.setPixel(width + x, height - 1 - y, qRgb(r, g, b));
			}
		}
		
		backup = image;
		painter.drawImage(QPoint(0, 0), image);
		qDebug() << "Done: Compressed RGB.";
		qDebug() << "Saved backup (for redraw).";
		mode = 3;
		qDebug() << "Set to mode 3 (Redrawing).";
	} else if (mode == 2) {
		std::string compressed_imagestream;

		qDebug() << "Converting hex data to binary...";
		compressed_imagestream = LosslessCodec::hex2bin(imagestream);

		qDebug() << "DECODING IN3 data...";
		compressed_imagestream = LosslessCodec::Decoder(compressed_imagestream);
		compressed_imagestream = LosslessCodec::bin2hex(compressed_imagestream);

		qDebug() << "DECODING IN3 data...";
		width = HextoInt(compressed_imagestream.substr(0, 4));
		height = HextoInt(compressed_imagestream.substr(4, 4));

		qDebug() << "Getting dimensions...";
		qDebug() << width;
		qDebug() << height;

		emit SendCompressionRatio(QString::fromStdString("Ratio: N/A"));

		QImage image(width, height, QImage::Format_RGB32);

		compressed_imagestream = compressed_imagestream.substr(8);

		qDebug() << "Drawing compressed IN3...";
		for (int x = 0; x < width; x++) {
			for (int y = 0; y < height; y++) {

				// b, g, r
				b = HextoInt(compressed_imagestream.substr((6 * ((height * y) + x)) + 0, 2));
				g = HextoInt(compressed_imagestream.substr((6 * ((height * y) + x)) + 2, 2));
				r = HextoInt(compressed_imagestream.substr((6 * ((height * y) + x)) + 4, 2));
				image.setPixel(x, height - 1 - y, qRgb(r, g, b));
			}
		}
		backup = image;
		painter.drawImage(QPoint(0, 0), image);
		qDebug() << "Done: Compressed RGB.";
		qDebug() << "Saved backup (for redraw).";
		mode = 3;
		qDebug() << "Set to mode 3 (Redrawing).";
	} else if (mode == 3) {
		painter.drawImage(QPoint(0, 0), backup);
	}
		
}

// PRIVATE

std::string ImageCanvas::LittleEndiantoBigEndian(std::string little) {
	std::string big;
	for (int i = little.length() - 1; i > 0; i -= 2) {
		big.append(little.substr(i - 1, 2));
	}
	return big;
}

int ImageCanvas::LittleHextoInt(std::string s) {
	return std::stoi(LittleEndiantoBigEndian(s), nullptr, 16);
}

int ImageCanvas::HextoInt(std::string s) {
	return std::stoi(s, nullptr, 16);
}