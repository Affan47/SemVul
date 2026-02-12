hkmap(int c)
{
    if (p_hkmapp)
    {
	enum {hALEF=0, BET, GIMEL, DALET, HEI, VAV, ZAIN, HET, TET, IUD,
	    KAFsofit, hKAF, LAMED, MEMsofit, MEM, NUNsofit, NUN, SAMEH, AIN,
	    PEIsofit, PEI, ZADIsofit, ZADI, KOF, RESH, hSHIN, TAV};
	static char_u map[26] =
	    {(char_u)hALEF, (char_u)BET  , (char_u)hKAF    ,
	     (char_u)DALET, (char_u)-1   , (char_u)PEIsofit,
	     (char_u)GIMEL, (char_u)HEI  , (char_u)IUD     ,
	     (char_u)HET  , (char_u)KOF  , (char_u)LAMED   ,
	     (char_u)MEM  , (char_u)NUN  , (char_u)SAMEH   ,
	     (char_u)PEI  , (char_u)-1   , (char_u)RESH    ,
	     (char_u)ZAIN , (char_u)TAV  , (char_u)TET     ,
	     (char_u)VAV  , (char_u)hSHIN, (char_u)-1      ,
	     (char_u)AIN  , (char_u)ZADI };

	if (c == 'N' || c == 'M' || c == 'P' || c == 'C' || c == 'Z')
	    return (int)(map[CharOrd(c)] - 1 + p_aleph);

	else if (c == 'x')
	    return 'X';
	else if (c == 'q')
	    return '\'';
	else if (c == 246)
	    return ' ';
	else if (c == 228)
	    return ' ';
	else if (c == 252)
	    return ' ';
#ifdef EBCDIC
	else if (islower(c))
#else

	else if (c >= 'a' && c <= 'z')
#endif
	    return (int)(map[CharOrdLow(c)] + p_aleph);
	else
	    return c;
    }
    else
    {
	switch (c)
	{
	    case '`':	return ';';
	    case '/':	return '.';
	    case '\'':	return ',';
	    case 'q':	return '/';
	    case 'w':	return '\'';

	    case ',':	c = '{'; break;
	    case '.':	c = 'v'; break;
	    case ';':	c = 't'; break;
	    default: {
			 static char str[] = "zqbcxlsjphmkwonu ydafe rig";

#ifdef EBCDIC

			 if (!islower(c))
#else
			 if (c < 'a' || c > 'z')
#endif
			     return c;
			 c = str[CharOrdLow(c)];
			 break;
		     }
	}

	return (int)(CharOrdLow(c) + p_aleph);
    }
}
}
