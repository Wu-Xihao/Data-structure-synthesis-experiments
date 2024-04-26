#include "pch.h"
#include "CGameException.h"
#include<iostream>
#include<string>


CGameException::CGameException(const std::string& what_arg) :
	m_what_arg(what_arg)
{
}

const char* CGameException::what(void) const noexcept
{
	auto text = "¥ÌŒÛ–≈œ¢£∫" + m_what_arg;
	return text.c_str();
}
