#include "Parameta.h"

Parameta::Parameta(void)
{
	pos = { 0.0f,0.0f,0.0f };
	rot = { 0.0f,0.0f,0.0f };
	scl = { 1.0f,1.0f,1.0f };
}

Parameta::Parameta(VECTOR ipos, VECTOR irot, VECTOR iscl, bool iisLoop,bool iisStop)
{
	pos = ipos;
	rot = irot;
	scl = iscl;
	isLoop = iisLoop;
	isStop = iisStop;
}

Parameta::~Parameta()
{
	
}
