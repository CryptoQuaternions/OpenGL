#pragma once
class Singleton
{
public:
	Singleton(void);
	~Singleton(void);
	Singleton * GetInstance(void);

private:
	static Singleton * m_Instance;
};

