#pragma once
#include <fstream>
#include "In.h"
#include "Parm.h"
#include "Error.h"

namespace Log
{
	struct LOG	//протокол
	{
		wchar_t logfile[PARM_MAX_SIZE];	//имя фала протокола
		std::ofstream * stream;		//выходной поток протокола 
	};

	static const LOG INTLOG = { L"", NULL };//структура для начальной инициализ. LOG
	LOG getlog(wchar_t logfile[]);			// сформировать структуру LOG
	void WriteLine(LOG log, char* c, ...);	//вывести в протокол конкатенацию строк
	void WriteLine(LOG log, wchar_t* c, ...);//вывести в протокол конкатенацию строк
	void WriteLog(LOG log);					//вывести в протокол заголовок 
	void WriteParm(LOG log, Parm::PARM parm);// информацию о входных параметрах 
	void WriteIn(LOG log, In::IN in);// информацию о входном потоке
	void WriteError(LOG log, Error::ERROR error);//информацию об ошибке
	void Close(LOG log);//закрыть протокол 
};