_rtl92c_query_rxpwrpercentage(char antpower)
{
	if ((antpower <= -100) || (antpower >= 20))
		return 0;
	else if (antpower >= 0)
		return 100;
	else
		return 100 + antpower;
}
