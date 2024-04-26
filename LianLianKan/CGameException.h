#pragma once
#include <exception>
#include <string>
class CGameException :public std::exception
{
public:
	CGameException(const std::string &what_arg);
	virtual const char* what(void) const noexcept override;
private:
	std::string m_what_arg;
};

