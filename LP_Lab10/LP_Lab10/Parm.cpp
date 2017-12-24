#include "stdafx.h"
#include "Parm.h"
#include "Error.h"
#include<iostream>
#include <string.h>

namespace Parm
{
	PARM getparm(int argc, _TCHAR* argv[])//обработка параметров 
	{
		PARM p;
		wcscpy_s(p.in, L"");//копируем пустоту в параметр in
		wcscpy_s(p.out, L"");
		wcscpy_s(p.log, L"");
		if (argc == 1)//кол-во параметров in
		{
			throw ERROR_THROW(100);
		}
		for (int i = 1; i < argc; i++)
		{
			if (wcslen(argv[i]) >= PARM_MAX_SIZE)//если длина указателя больше максимальной длины- ошибка
			{
				throw ERROR_THROW(104);
			}
			if (wcsstr(argv[i], PARM_IN) == argv[i]) //проверка вхождения PARM_IN в указатель argv
			{
				wcscpy_s(p.in, argv[i] + wcslen(PARM_IN));// копируем указатель + длина PARM_IN в параметр in структуры p
			}
			else if (wcsstr(argv[i], PARM_OUT) == argv[i]) {
				wcscpy_s(p.out, argv[i] + wcslen(PARM_OUT));
			}
			else if (wcsstr(argv[i], PARM_LOG) == argv[i]) {
				wcscpy_s(p.log, argv[i] + wcslen(PARM_LOG));
			}
		}
		if (wcslen(p.in) == 0) {
			throw ERROR_THROW(100);
		}
		if (wcslen(p.out) == 0) {
			if (wcslen(p.in) + wcslen(PARM_OUT_DEFAULT_EXT) >= PARM_MAX_SIZE) {
				throw ERROR_THROW(104);
			}
			wcscpy_s(p.out, p.in);
			wcsncat_s(p.out, PARM_OUT_DEFAULT_EXT, 4);//объеденяем второй аргумент с первым начиная с 4 символа
		}
		if (wcslen(p.log) == 0) {
			if (wcslen(p.in) + wcslen(PARM_LOG_DEFAULT_EXT) >= PARM_MAX_SIZE) {
				throw ERROR_THROW(104);
			}
			wcscpy_s(p.log, p.in);
			wcsncat_s(p.log, PARM_LOG_DEFAULT_EXT, 4);
		}
		return p;
	}
}
