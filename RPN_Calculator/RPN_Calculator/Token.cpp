#include "Token.h"

Token::Token() {
	memset(token, 0, sizeof(token));
	this->length = 0;
}

void Token::readToken() {
	this->token[0] = '\0';
	this->length = 0;

	int c = getchar();

	int index = 0;
	while (c != ' ' && c != '\n') {
		this->token[index] = c;
		this->length++;
		index++;
		c = getchar();
	}
	this->token[index] = '\0';

}

void Token::printToken() {
	printf("%s ", this->token);
}

void Token::extendTokenByNumber(int number) {
	char buffer[20];
	sprintf(buffer, "%d", number);

	for (int i = 0; i < strlen(buffer); i++) {
		this->token[this->length] = buffer[i];
		this->length++;
	}
	this->token[this->length] = '\0';
}

bool Token::isANumber() {
	return this->token[0] >= '0' && this->token[0] <= '9';
}

bool operator==(Token token, const char* other) {
	return !strcmp(token.token, other);
}

bool operator!=(Token token, const char* other) {
	int check = strcmp(token.token, other);
	return check != 0;
}

Token& Token::operator=(Token other) {
	strcpy(this->token, other.token);
	this->length = other.length;
	return *this;
}

