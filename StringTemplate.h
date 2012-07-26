#pragma once
#include <array>
#include <algorithm>
#include "StringTemplateHelper.h"

template <unsigned long TLength, char... TChars>
class StringTemplate
{
public:
	static_assert(TLength == sizeof...(TChars), "String length mismatch.");
	
	enum { Length = TLength };
	typedef std::array<char, Length> ArrayType;
	
	static const char* Get()
	{
		return mData.data();
	}

private:
	static ArrayType CreateArray()
	{
		ArrayType value;
		StringTemplateHelper<TChars...>::SetNextChar(value.begin());
		return value;
	}
	
private:
	static ArrayType mData;
};

template <unsigned long TLength, char... TChars>
typename StringTemplate<TLength, TChars...>::ArrayType StringTemplate<TLength, TChars...>::mData = StringTemplate<TLength, TChars...>::CreateArray();

#define STRING_TEMPLATE_0(s) s[0]
#define STRING_TEMPLATE_1(s) STRING_TEMPLATE_0(s), s[1]
#define STRING_TEMPLATE_2(s) STRING_TEMPLATE_1(s), s[2]
#define STRING_TEMPLATE_3(s) STRING_TEMPLATE_2(s), s[3]
#define STRING_TEMPLATE_4(s) STRING_TEMPLATE_3(s), s[4]
#define STRING_TEMPLATE_5(s) STRING_TEMPLATE_4(s), s[5]
#define STRING_TEMPLATE_6(s) STRING_TEMPLATE_5(s), s[6]
#define STRING_TEMPLATE_7(s) STRING_TEMPLATE_6(s), s[7]
#define STRING_TEMPLATE_8(s) STRING_TEMPLATE_7(s), s[8]
#define STRING_TEMPLATE_9(s) STRING_TEMPLATE_8(s), s[9]
#define STRING_TEMPLATE_10(s) STRING_TEMPLATE_9(s), s[10]
#define STRING_TEMPLATE_11(s) STRING_TEMPLATE_10(s), s[11]
#define STRING_TEMPLATE_12(s) STRING_TEMPLATE_11(s), s[12]
#define STRING_TEMPLATE_13(s) STRING_TEMPLATE_12(s), s[13]
#define STRING_TEMPLATE_14(s) STRING_TEMPLATE_13(s), s[14]
#define STRING_TEMPLATE_15(s) STRING_TEMPLATE_14(s), s[15]
#define STRING_TEMPLATE_16(s) STRING_TEMPLATE_15(s), s[16]
#define STRING_TEMPLATE_17(s) STRING_TEMPLATE_16(s), s[17]
#define STRING_TEMPLATE_18(s) STRING_TEMPLATE_17(s), s[18]
#define STRING_TEMPLATE_19(s) STRING_TEMPLATE_18(s), s[19]
#define STRING_TEMPLATE_20(s) STRING_TEMPLATE_19(s), s[20]
#define STRING_TEMPLATE_21(s) STRING_TEMPLATE_20(s), s[21]
#define STRING_TEMPLATE_22(s) STRING_TEMPLATE_21(s), s[22]
#define STRING_TEMPLATE_23(s) STRING_TEMPLATE_22(s), s[23]
#define STRING_TEMPLATE_24(s) STRING_TEMPLATE_23(s), s[24]
#define STRING_TEMPLATE_25(s) STRING_TEMPLATE_24(s), s[25]
#define STRING_TEMPLATE_26(s) STRING_TEMPLATE_25(s), s[26]
#define STRING_TEMPLATE_27(s) STRING_TEMPLATE_26(s), s[27]
#define STRING_TEMPLATE_28(s) STRING_TEMPLATE_27(s), s[28]
#define STRING_TEMPLATE_29(s) STRING_TEMPLATE_28(s), s[29]
#define STRING_TEMPLATE_30(s) STRING_TEMPLATE_29(s), s[30]
#define STRING_TEMPLATE_31(s) STRING_TEMPLATE_30(s), s[31]
#define STRING_TEMPLATE_32(s) STRING_TEMPLATE_31(s), s[32]
#define STRING_TEMPLATE_33(s) STRING_TEMPLATE_32(s), s[33]
#define STRING_TEMPLATE_34(s) STRING_TEMPLATE_33(s), s[34]
#define STRING_TEMPLATE_35(s) STRING_TEMPLATE_34(s), s[35]
#define STRING_TEMPLATE_36(s) STRING_TEMPLATE_35(s), s[36]
#define STRING_TEMPLATE_37(s) STRING_TEMPLATE_36(s), s[37]
#define STRING_TEMPLATE_38(s) STRING_TEMPLATE_37(s), s[38]
#define STRING_TEMPLATE_39(s) STRING_TEMPLATE_38(s), s[39]
#define STRING_TEMPLATE_40(s) STRING_TEMPLATE_39(s), s[40]
#define STRING_TEMPLATE_41(s) STRING_TEMPLATE_40(s), s[41]
#define STRING_TEMPLATE_42(s) STRING_TEMPLATE_41(s), s[42]
#define STRING_TEMPLATE_43(s) STRING_TEMPLATE_42(s), s[43]
#define STRING_TEMPLATE_44(s) STRING_TEMPLATE_43(s), s[44]
#define STRING_TEMPLATE_45(s) STRING_TEMPLATE_44(s), s[45]
#define STRING_TEMPLATE_46(s) STRING_TEMPLATE_45(s), s[46]
#define STRING_TEMPLATE_47(s) STRING_TEMPLATE_46(s), s[47]
#define STRING_TEMPLATE_48(s) STRING_TEMPLATE_47(s), s[48]
#define STRING_TEMPLATE_49(s) STRING_TEMPLATE_48(s), s[49]
#define STRING_TEMPLATE_50(s) STRING_TEMPLATE_49(s), s[50]
#define STRING_TEMPLATE_51(s) STRING_TEMPLATE_50(s), s[51]
#define STRING_TEMPLATE_52(s) STRING_TEMPLATE_51(s), s[52]
#define STRING_TEMPLATE_53(s) STRING_TEMPLATE_52(s), s[53]
#define STRING_TEMPLATE_54(s) STRING_TEMPLATE_53(s), s[54]
#define STRING_TEMPLATE_55(s) STRING_TEMPLATE_54(s), s[55]
#define STRING_TEMPLATE_56(s) STRING_TEMPLATE_55(s), s[56]
#define STRING_TEMPLATE_57(s) STRING_TEMPLATE_56(s), s[57]
#define STRING_TEMPLATE_58(s) STRING_TEMPLATE_57(s), s[58]
#define STRING_TEMPLATE_59(s) STRING_TEMPLATE_58(s), s[59]
#define STRING_TEMPLATE_60(s) STRING_TEMPLATE_59(s), s[60]
#define STRING_TEMPLATE_61(s) STRING_TEMPLATE_60(s), s[61]
#define STRING_TEMPLATE_62(s) STRING_TEMPLATE_61(s), s[62]
#define STRING_TEMPLATE_63(s) STRING_TEMPLATE_62(s), s[63]
#define STRING_TEMPLATE_64(s) STRING_TEMPLATE_63(s), s[64]
#define STRING_TEMPLATE_65(s) STRING_TEMPLATE_64(s), s[65]
#define STRING_TEMPLATE_66(s) STRING_TEMPLATE_65(s), s[66]
#define STRING_TEMPLATE_67(s) STRING_TEMPLATE_66(s), s[67]
#define STRING_TEMPLATE_68(s) STRING_TEMPLATE_67(s), s[68]
#define STRING_TEMPLATE_69(s) STRING_TEMPLATE_68(s), s[69]
#define STRING_TEMPLATE_70(s) STRING_TEMPLATE_69(s), s[70]
#define STRING_TEMPLATE_71(s) STRING_TEMPLATE_70(s), s[71]
#define STRING_TEMPLATE_72(s) STRING_TEMPLATE_71(s), s[72]
#define STRING_TEMPLATE_73(s) STRING_TEMPLATE_72(s), s[73]
#define STRING_TEMPLATE_74(s) STRING_TEMPLATE_73(s), s[74]
#define STRING_TEMPLATE_75(s) STRING_TEMPLATE_74(s), s[75]
#define STRING_TEMPLATE_76(s) STRING_TEMPLATE_75(s), s[76]
#define STRING_TEMPLATE_77(s) STRING_TEMPLATE_76(s), s[77]
#define STRING_TEMPLATE_78(s) STRING_TEMPLATE_77(s), s[78]
#define STRING_TEMPLATE_79(s) STRING_TEMPLATE_78(s), s[79]
#define STRING_TEMPLATE_80(s) STRING_TEMPLATE_79(s), s[80]
#define STRING_TEMPLATE_81(s) STRING_TEMPLATE_80(s), s[81]
#define STRING_TEMPLATE_82(s) STRING_TEMPLATE_81(s), s[82]
#define STRING_TEMPLATE_83(s) STRING_TEMPLATE_82(s), s[83]
#define STRING_TEMPLATE_84(s) STRING_TEMPLATE_83(s), s[84]
#define STRING_TEMPLATE_85(s) STRING_TEMPLATE_84(s), s[85]
#define STRING_TEMPLATE_86(s) STRING_TEMPLATE_85(s), s[86]
#define STRING_TEMPLATE_87(s) STRING_TEMPLATE_86(s), s[87]
#define STRING_TEMPLATE_88(s) STRING_TEMPLATE_87(s), s[88]
#define STRING_TEMPLATE_89(s) STRING_TEMPLATE_88(s), s[89]
#define STRING_TEMPLATE_90(s) STRING_TEMPLATE_89(s), s[90]
#define STRING_TEMPLATE_91(s) STRING_TEMPLATE_90(s), s[91]
#define STRING_TEMPLATE_92(s) STRING_TEMPLATE_91(s), s[92]
#define STRING_TEMPLATE_93(s) STRING_TEMPLATE_92(s), s[93]
#define STRING_TEMPLATE_94(s) STRING_TEMPLATE_93(s), s[94]
#define STRING_TEMPLATE_95(s) STRING_TEMPLATE_94(s), s[95]
#define STRING_TEMPLATE_96(s) STRING_TEMPLATE_95(s), s[96]
#define STRING_TEMPLATE_97(s) STRING_TEMPLATE_96(s), s[97]
#define STRING_TEMPLATE_98(s) STRING_TEMPLATE_97(s), s[98]
#define STRING_TEMPLATE_99(s) STRING_TEMPLATE_98(s), s[99]
#define STRING_TEMPLATE(s, count) StringTemplate<sizeof(s) / sizeof(s[0]), STRING_TEMPLATE_##count(s)>
#define _ST(s, count) STRING_TEMPLATE(s, count)