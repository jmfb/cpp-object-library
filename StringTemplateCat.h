#pragma once
#include "StringTemplate.h"

template <typename... TStringTemplates>
class StringTemplateCat
{
};

template <unsigned long TLength, char... TChars, typename... TStringTemplates>
class StringTemplateCat<StringTemplate<TLength, TChars...>, TStringTemplates...>
{
public:
	typedef typename StringTemplateCat<
		StringTemplate<TLength, TChars...>,
		typename StringTemplateCat<TStringTemplates...>::Type
	>::Type Type;
};

template <unsigned long TFirstLength, char TFirstChar, char... TFirstChars, unsigned long TSecondLength, char... TSecondChars>
class StringTemplateCat<StringTemplate<TFirstLength, TFirstChar, TFirstChars...>, StringTemplate<TSecondLength, TSecondChars...>>
{
public:
	typedef typename StringTemplateCat<
		StringTemplate<2, TFirstChar, '\0'>,
		typename StringTemplateCat<
			StringTemplate<TFirstLength - 1, TFirstChars...>,
			StringTemplate<TSecondLength, TSecondChars...>
		>::Type
	>::Type Type;
};

template <char TPrefix, unsigned long TLength, char... TChars>
class StringTemplateCat<StringTemplate<2, TPrefix, '\0'>, StringTemplate<TLength, TChars...>>
{
public:
	typedef StringTemplate<TLength + 1, TPrefix, TChars...> Type;
};

template <unsigned long TLength, char... TChars>
class StringTemplateCat<StringTemplate<1, '\0'>, StringTemplate<TLength, TChars...>>
{
public:
	typedef StringTemplate<TLength, TChars...> Type;
};

template <unsigned long TLength, char... TChars>
class StringTemplateCat<StringTemplate<TLength, TChars...>>
{
public:
	typedef StringTemplate<TLength, TChars...> Type;
};
