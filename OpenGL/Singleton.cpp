#include "Singleton.h"

Singleton * Singleton::m_Instance = 0;

Singleton::Singleton(void)
{
}


Singleton::~Singleton(void)
{
}


Singleton* Singleton::GetInstance(void)
{
	if(m_Instance == 0)
		m_Instance = new Singleton();
	
	return m_Instance;
}
