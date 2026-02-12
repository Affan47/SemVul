othercase(charset,ch)
CHARSET_INFO *charset;
int ch;
{


	assert(my_isalpha(charset,ch));
	if (my_isupper(charset,ch))
	{
		return(charset->to_lower ? my_tolower(charset,ch) :
		                          ch - 'A' + 'a');
	}
	else if (my_islower(charset,ch))
	{
		return(charset->to_upper ? my_toupper(charset,ch) :
		                          ch - 'a' + 'A');
	}
	else
		return(ch);
}
