#pragma once
#define IN_MAX_LEN_TEXT 1024*1024	//максимальный размер исходного кода
#define IN_CODE_ENDL '\n'			//символ конца строки
//таблица проверки вхоодной информации
#define IN_CODE_TABLE {\
	IN::F, IN::T, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::T, IN::F, IN::F, IN::I, IN::F, IN::F, \
	IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, \
	IN::T, IN::T, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, \
	IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, \
	IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::T, IN::F, IN::F, IN::F, IN::F, IN::T, IN::F, IN::F, \
	IN::F, IN::F, IN::F, IN::F, IN::T, IN::F, IN::F, IN::T, IN::I, '!', IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, \
	IN::F, IN::T, IN::F, IN::T, IN::T, IN::T, IN::F, IN::F, IN::T, IN::T, IN::F, IN::T, IN::T, IN::T, IN::T, IN::T, \
	IN::F, IN::F, IN::T, IN::F, IN::F, IN::F, IN::T, IN::F, IN::T, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, \
	\
	IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, \
	IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, \
	IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, \
	IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, \
	IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, \
	IN::F, IN::F, IN::T, IN::F, IN::F, IN::T, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, \
	IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::T, IN::F, IN::F, IN::T, IN::F, IN::F, IN::T, IN::F, \
	IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::T, IN::F, IN::T, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F \
} //

namespace In
{
	struct IN			//исходные данные
	{
		enum { T = 1024, F = 2048, I = 4096 }; //I-игнорировать, иначе заменить
		int size;	//размер исходного кода
		int lines;	//кол строк
		int ignor;	// кол проигнорированных строк
		unsigned char* text;	//исходный код (Windows-1251)
		int code[256];	// таблица проверки: T, F, I, новое значение
	};
	IN getin(wchar_t infile[]);	//ввести и проверить входной поток 
};