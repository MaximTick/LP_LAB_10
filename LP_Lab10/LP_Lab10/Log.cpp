#include "stdafx.h"
#include "Log.h"
#include "Error.h"
#include <fstream>
#include <stdio.h>  
#include <stdarg.h>
#include <time.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/timeb.h>
#include <string.h>
#include "Parm.h"
#include <iostream>

namespace Log
{
	LOG getlog(wchar_t logfile[])	//функция создания потока вывода
	{
		LOG a;
		wcscpy_s(a.logfile, logfile);		//копируем содержимое logfile в a.logfile
		a.stream = new std::ofstream(logfile, std::ofstream::out);	//создание потока вывода
		if (a.stream->fail()) {
			throw ERROR_THROW(112);
		}
		return a;
	}

	void WriteLine(LOG log, char*c, ...)
	{
		char** pc = &c;
		int len = 0;
		while (*pc != "")
		{
			len += strlen(*pc);
			pc++;
		}
		char *str = new char[len + 1];
		str[0] = 0;
		pc = &c;
		while (*pc != "")
		{
			strcat(str, *pc);
			pc++;
		}
		log.stream->write(str, len);
		delete[] str;
	}

	void WriteLine(LOG log, wchar_t*c, ...)//ф-ия для конкатенации строк
	{
		wchar_t** pc = &c;
		int len = 0;	//длина строки 0
		while (*pc != L"") //пока не дойдет до пустоты (вычисляем длину строки, передвигаем указатель)
		{
			len += wcslen(*pc);
			pc++;
		}
		wchar_t *str = new wchar_t[len + 1];  //создание 2-х массивов
		char* strl = new char[len + 1];
		str[0] = 0; //инициализация динам массива
		pc = &c; // возвращаем указатель в начало строки 
		while (*pc != L"")
		{
			wcscat(str, *pc); //конкатенация строк(str-нулевая строка; )
			pc++;
		}
		wcstombs(strl, str, len + 2);//эта ф-ия переводит один тип данных в другой
		log.stream->write(strl, len);//вывод полученного результа
		delete[] str;
	}
	void WriteLog(LOG log)	//шаблон для получения временных данных от системы

	{
		time_t curTime;
		tm timeStruct;
		time(&curTime);

		char strTime[1024];
		localtime_s(&timeStruct, &curTime);

		strftime(strTime, 1024, "%d.%m.%Y %H:%M:%S", &timeStruct);
		*log.stream << "---- Протокол ------ " << strTime << " -------------" << std::endl;
	}

	void WriteParm(LOG log, Parm::PARM parm)//ф-ия для вывода параметров в консоль
	{
		*log.stream << "---- Параметры ------" << std::endl;

		char temp[PARM_MAX_SIZE + 1];	//создание массива размером []
		wcstombs(temp, PARM_LOG, wcslen(PARM_LOG) + 1); //конвертирует строку широких символов, на которую
														//указывает параметр in, в многобайтовый эквивалент
		*log.stream << temp << " ";	//вывод в консоль
		wcstombs(temp, parm.log, wcslen(parm.log) + 1);
		*log.stream << temp << std::endl;

		wcstombs(temp, PARM_OUT, wcslen(PARM_OUT) + 1);
		*log.stream << temp << " ";
		wcstombs(temp, parm.out, wcslen(parm.out) + 1);
		*log.stream << temp << std::endl;

		wcstombs(temp, PARM_IN, wcslen(PARM_IN) + 1);
		*log.stream << temp << " ";
		wcstombs(temp, parm.in, wcslen(parm.in) + 1);
		*log.stream << temp << std::endl;
	}

	void WriteIn(LOG log, In::IN in)// ф-ия записи в файл журнала
	{
		*log.stream << "---- Исходные данные ------" << std::endl;
		*log.stream << "Количество символов: " << in.size << std::endl;
		*log.stream << "Проигнорировано    : " << in.ignor << std::endl;
		*log.stream << "Количество строк   : " << in.lines + 1 << std::endl;
	}

	void WriteError(LOG log, Error::ERROR error)//ф-ия для оповещания ошибок
	{
		*log.stream << "Ошибка " << error.id << ": " << error.message << ", строка " << error.inext.line << ",позиция " << error.inext.col << std::endl;
	}

	void Close(LOG log)
	{
		log.stream->close();//закрыте журнала
		delete log.stream;
		log.stream = NULL;
	}
}