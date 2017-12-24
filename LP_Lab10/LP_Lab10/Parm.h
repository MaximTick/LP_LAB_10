#pragma once
#define PARM_IN L"-in:"	//ключ для файла исходного кода
#define PARM_OUT L"-out:"	//ключ для файла объектного кода
#define PARM_LOG L"-log:"	// для фала журнала
#define PARM_MAX_SIZE 300	//максимальная длина строки параметра 
#define PARM_OUT_DEFAULT_EXT L".out"	//расширение фала об. кода по умолчанию
#define PARM_LOG_DEFAULT_EXT L".log"	//расширение файла протокола по умолчанию

namespace Parm	//обработка входных параметров
{
	struct PARM	//входные параметры
	{
		wchar_t in[PARM_MAX_SIZE];	//in: имя файла исходного коды
		wchar_t out[PARM_MAX_SIZE];		  //имя объектного кода
		wchar_t log[PARM_MAX_SIZE];		//имя фала протокола
	};

	PARM getparm(int argc, _TCHAR* argv[]);
}