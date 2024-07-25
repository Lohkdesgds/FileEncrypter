#include <string_to_random.h>

uint64_t string_to_key(const std::string& source)
{
	uint64_t calcd = 0;

	for (const auto& i : source) {
		calcd *= 99194853094755497LLU; // random large prime out there.
		calcd += static_cast<uint64_t>(i);
	}

	return calcd;
}