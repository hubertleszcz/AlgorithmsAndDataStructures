#pragma once

enum Priority {
	PLUS = 1,
	MINUS = 1,
	MULTIPLICATION = 2,
	DIVISION = 2,

	NEGATION = 3,
	IF = 3,
	MIN = 3,
	MAX = 3,

	LEFT_PARENTHESIS = 99,
	RIGHT_PARENTHESIS = 99,
};