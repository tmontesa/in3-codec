#include <QDebug>
#include <QString>
#include <queue>
#include <map>
#include <bitset>

namespace LosslessCodec {
	const int MULTIPLIER = 8;
	const int MAXCODELENGTH = 16;

	std::string hex2bin(std::string);
	std::string bin2hex(std::string);
	std::string padstr(std::string, char, unsigned int);
	std::string Encoder(std::string, int, int);
	std::string Decoder(std::string);
}
