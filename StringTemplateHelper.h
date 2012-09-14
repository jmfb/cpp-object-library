#pragma once

template <char... TChars>
class StringTemplateHelper
{
public:
	static const bool valid = false;
};

template <char TChar, char... TRest>
class StringTemplateHelper<TChar, TRest...>
{
public:
	static const bool valid = TChar != '\0' && StringTemplateHelper<TRest...>::valid;
};

template <char TChar>
class StringTemplateHelper<TChar>
{
public:
	static const bool valid = TChar == '\0';
};
