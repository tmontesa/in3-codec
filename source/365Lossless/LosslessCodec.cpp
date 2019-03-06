#include "LosslessCodec.h"

namespace LosslessCodec {
	std::string hex2bin(std::string in) {
		std::map<char, std::string> d;
		d['0'] = "0000";
		d['1'] = "0001";
		d['2'] = "0010";
		d['3'] = "0011";
		d['4'] = "0100";
		d['5'] = "0101";
		d['6'] = "0110";
		d['7'] = "0111";
		d['8'] = "1000";
		d['9'] = "1001";
		d['a'] = "1010";
		d['b'] = "1011";
		d['c'] = "1100";
		d['d'] = "1101";
		d['e'] = "1110";
		d['f'] = "1111";

		std::string o;
		for (int c = 0; c < in.length(); c++) {
			o += d[in[c]];
		}

		return o;
	}

	std::string bin2hex(std::string in) {
		std::map<std::string, char> d;
		d["0000"] = '0';
		d["0001"] = '1';
		d["0010"] = '2';
		d["0011"] = '3';
		d["0100"] = '4';
		d["0101"] = '5';
		d["0110"] = '6';
		d["0111"] = '7';
		d["1000"] = '8';
		d["1001"] = '9';
		d["1010"] = 'a';
		d["1011"] = 'b';
		d["1100"] = 'c';
		d["1101"] = 'd';
		d["1110"] = 'e';
		d["1111"] = 'f';

		std::string o;
		for (int c = 0; c < in.length(); c += 4) {
			o += d[in.substr(c, 4)];
			}

		return o;
	}

	std::string padstr(std::string i, char c, unsigned int n) {
		std::string o;
		for (int x = 0; x < n - i.length(); x++) {
			o += c;
		}
		return o + i;
	}

	std::string Encoder(std::string input, int width, int height) {
		std::queue<unsigned int> code;
		std::string output = "";
			
		input = std::bitset<16>(width).to_string() + std::bitset<16>(height).to_string() + input;

		std::map<std::string, unsigned int> dictionary;
		std::map<unsigned int, std::string> dictionary_reverse;
		std::string selection, pointer;
		unsigned int s, p;
		unsigned int z;

		s = 0;
		p = 0;
		


		// ADD STRINGS TO INITIAL DICTIONARY

		std::string b;
		for (unsigned int j = 0; j < pow(2, MULTIPLIER); j++) {
			b = std::bitset<MULTIPLIER>(j).to_string();
			dictionary_reverse[j] = b;
			dictionary[b] = j;
		}



		// LZW ENCODING

		selection = input.substr(s, MULTIPLIER);

		while (p < input.length()) {
			p += MULTIPLIER;
			pointer = input.substr(p, MULTIPLIER);

			if (dictionary.find(selection + pointer) != dictionary.end()) {
				selection += pointer;
			}
			else {
				z = dictionary.size();
				code.push(dictionary[selection]);

				if (z <= pow(2, MAXCODELENGTH)) {
					dictionary_reverse[z] = selection + pointer;
					dictionary[selection + pointer] = z;
				}
				selection = pointer;
				s = p;
			}
		}
		code.push(dictionary[selection]);



		// ITERATING THROUGH CODE

		while (!code.empty()) {
			output += std::bitset<MAXCODELENGTH>(code.front()).to_string();
			code.pop();
		}

		return output;
	}




	std::string Decoder(std::string input) {
		std::string output = "";

		std::map<int, std::string> decoder;

		std::string d;
		for (int l = 0; l < pow(2, MULTIPLIER); l++) {
			d = std::bitset<MULTIPLIER>(l).to_string();
			decoder[l] = d;
		}

		std::string prev;
		std::string curr;
		std::string entry;
		int pos;

		prev = "";
		curr = "";
		pos = 0;

		while (pos < int(input.length())) {

			curr = input.substr(pos, MAXCODELENGTH);

			if (decoder.find(std::stoi(curr, nullptr, 2)) == decoder.end()) {
				entry = prev + prev.substr(0, MULTIPLIER);
			}
			else {
				entry = decoder[std::stoi(curr, nullptr, 2)];
			}

			output += entry;

			if (!prev.empty()) {
				decoder[decoder.size()] = prev + entry.substr(0, MULTIPLIER);
			}

			prev = entry;
			pos += MAXCODELENGTH;
		}


		return output;
	}
}
