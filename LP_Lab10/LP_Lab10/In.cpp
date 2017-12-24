#include "stdafx.h"
#include "In.h"
#include "Error.h"
#include <fstream>
#include <iostream>
#include <string.h>

namespace In
{
	IN getin(wchar_t infile[])//ф-ия для считывания из файла 
	{
		IN in;
		in.lines = 0;
		in.ignor = 0;
		in.size = 0;//количество символов 
		int constCode[256] = IN_CODE_TABLE;
		for (int i = 0; i < 256; i++)
			in.code[i] = constCode[i];// переносим из массива в структуру посивольно 
		std::ifstream ifs;	//ifs это переменная типа фаловый поток чтения
		ifs.open(infile, std::ifstream::in);//infine имя входного файла 
		if (ifs.fail()) {
			throw ERROR_THROW(110);
		}
		char c = ifs.get();//методом ifs.get() посимвольно заносим символы в переменную с
		int curLine = 0;//линия в которой находятся символы
		int posSymb = 0;// след. символ
		while (ifs.good()) {
			posSymb++;
			if (c == IN_CODE_ENDL) // IN_CODE_ENDL символ концаа строки
			{
				in.lines++;//кол-во линий увеличивается 
				curLine++;// переход на след. линию 
				posSymb = 0;
				in.size++;
			}
			else if (in.code[c] == IN::F) {	//если с фолс вылазит ошибка
				throw ERROR_THROW_IN(111, curLine, posSymb);
			}
			else if (in.code[c] == IN::I) {
				in.ignor++;// ко-во проигнорированных символов увеличивается 
			}
			else if (in.code[c] == IN::T) {
				in.size++;
			}

			c = ifs.get();
		}
		ifs.close();


		in.text = new unsigned char[in.size];//вывод исправленного текста в консольное 
		ifs.open(infile, std::ifstream::in);// открываем для записи
		c = ifs.get();//посимвольное считывание 
		posSymb = 0;
		while (ifs.good()) {
			if (c == IN_CODE_ENDL) {
				in.text[posSymb] = IN_CODE_ENDL;
				posSymb++;
			}
			else if (in.code[c] == IN::I) {

			}
			else if (in.code[c] == IN::T) {
				in.text[posSymb] = c;
				posSymb++;//переход к след символу
			}
			else if (in.code[c] >= 0 && in.code[c] < 256) {// проверка принадлежности таблице 
				in.text[posSymb] = in.code[c];//след сивол== считанному символу с
				posSymb++;
			}
			c = ifs.get();
		}
		in.text[posSymb] = 0;
		ifs.close();

		return in;
	}
}