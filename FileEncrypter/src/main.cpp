// CMakeTestWSL.cpp : Defines the entry point for the application.
//
#include <iostream>
#include <string>
#include <fstream>
#include <memory>
#include <string_to_random.h>

bool work_on_file(Lunaris::form_64& f, const char* src, const bool enc);

int main(int argc, char* argv[])
{
	if (argc == 1) {
		std::cout << "Please drop file(s) into the app to start a encryption/decryption session." << std::endl;
		return 1;
	}

	std::string enc_pw{};
	char enc_opt{};

	std::cout << " ======= Lohk's Extremely Simple  Form64 Encoder/Decoder Application =======" << std::endl;
	std::cout << " = Do not use this to encrypt real important data, only for test purposes! =" << std::endl;
	std::cout << " ===========================================================================" << std::endl << std::endl;
	std::cout << "[E]ncrypt a file or [D]ecrypt? (type only the wanted character): ";

	std::cin >> enc_opt;
	std::cin.get();

	std::cout << "Please give the passphrase for your encryption: ";

	std::getline(std::cin, enc_pw);

	const auto enc_number = string_to_key(enc_pw);

	std::cout << "Got '" << enc_pw << "' -> '" << enc_number << "'" << std::endl;

	Lunaris::form_64 fun(enc_number);

	switch (enc_opt) {
	case 'e':
	case 'E':
	{
		for (int p = 1; p < argc; ++p) {
			std::cout << "Encoding '" << argv[p] << "' to '" << argv[p] << ".enc'..." << std::endl;
			if (!work_on_file(fun, argv[p], true)) {
				std::cout << "Failed on '" << argv[p] << "'." << std::endl;
			}
		}
	}
		break;
	case 'd':
	case 'D':
	{
		for (int p = 1; p < argc; ++p) {
			std::cout << "Encoding '" << argv[p] << "' to '" << argv[p] << ".dec'..." << std::endl;
			if (!work_on_file(fun, argv[p], false)) {
				std::cout << "Failed on '" << argv[p] << "'." << std::endl;
			}
		}
	}
		break;
	default:
		std::cout << "I said either 'D' or 'E'. You typed '" << enc_opt << "'. Skipped." << std::endl;
		break;
	}

	return 0;
}

bool work_on_file(Lunaris::form_64& f, const char* src, const bool enc)
{
	constexpr size_t mem_use = 1ULL << 20;

	std::fstream fin(src, std::ios::in | std::ios::binary);
	std::fstream fou(src + std::string(enc ? ".enc" : ".dec"), std::ios::out | std::ios::binary);

	if (!fin || !fou) {
		std::cout << "Cannot open files for '" << src << "'." << std::endl;
		return false;
	}

	const auto do_work = [&f, &enc](char* targ, size_t len) {
		if (enc) f.encode_in((uint8_t*)targ, len);
		else     f.decode_in((uint8_t*)targ, len);
	};

	auto buf = std::unique_ptr<char[]>(new char[mem_use]);

	while (!fin.eof()) {
		fin.read(buf.get(), mem_use);
		const auto rd = fin.gcount();
		if (rd == 0) break;
		do_work(buf.get(), rd);
		fou.write(buf.get(), rd);
	}

	return true;
}
