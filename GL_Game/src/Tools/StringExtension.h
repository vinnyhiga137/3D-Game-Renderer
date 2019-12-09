#pragma once

#include <iostream>
#include <string>

namespace StringExtension {

	static char* join(const char* first, const char* second) {

		int firstLen = strlen(first);
		int secondLen = strlen(second);

		char* data = (char*) malloc(sizeof(char) * (firstLen + secondLen));

		memcpy(data, first, firstLen);
		memcpy(data + firstLen, second, secondLen + 1);

		return data;
	}

}