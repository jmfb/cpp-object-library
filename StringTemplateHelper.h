#pragma once

template <char... TChars>
class StringTemplateHelper
{
};

template <char TChar, char... TRest>
class StringTemplateHelper<TChar, TRest...>
{
public:
	template <typename TIter>
	static void SetNextChar(TIter iter)
	{
		*iter = TChar;
		StringTemplateHelper<TRest...>::SetNextChar(iter + 1);
	}
};

template <>
class StringTemplateHelper<>
{
public:
	template <typename TIter>
	static void SetNextChar(TIter iter)
	{
		//nothing
	}
};
