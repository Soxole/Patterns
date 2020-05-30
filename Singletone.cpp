#include "Singletone.h"

SingleTone *SingleTone::p_inst = nullptr;
SingleToneDestroyer SingleTone::destroyer;

SingleTone &SingleTone::getInst()
{
	if (!p_inst)
	{
		p_inst = new SingleTone();
		destroyer.initialize(p_inst);
	}
	return *p_inst;
}


