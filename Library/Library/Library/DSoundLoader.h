#ifndef DSOUNDLOADER_H
#define DSOUNDLOADER_H
#include <dsound.h>
#include "Singleton.h"

namespace Lib
{
	class DSoundLoader
	{
		friend Singleton<DSoundLoader>;
	public:
		LPDIRECTSOUNDBUFFER8 LoadWave(LPCTSTR _pFileName);

	private:
		DSoundLoader();
		~DSoundLoader();
	};
}


#endif
