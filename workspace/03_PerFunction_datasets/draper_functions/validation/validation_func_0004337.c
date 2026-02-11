_cl_date_get_bazi_lunar (LunarDate *date)
{
	int m, flag;
	LunarDatePrivate *priv;

	priv = LUNAR_DATE_GET_PRIVATE (date);

	if (priv->solar->month==1)
	{
		flag = _cmp_date(priv->solar->month, priv->solar->day,
				1, fest[priv->solar->year - first_solar_date.year - 1][11]);
		if (flag<0)
			priv->lunar2->month = 11;
		else if (flag>0)
			priv->lunar2->month = 12;
		priv->lunar2->year = priv->solar->year - 1;
		return(flag==0);
	}
	for (m=2; m<=12; m++)
	{
		flag = _cmp_date(priv->solar->month, priv->solar->day,
				m, fest[priv->solar->year - first_solar_date.year][m-2]);
		if (flag==0) m++;
		if (flag<=0) break;
	}
	priv->lunar2->month = (m-2) % 12;
	priv->lunar2->year = priv->solar->year;
	if ((priv->lunar2->month)==0)
	{
		priv->lunar2->year = priv->solar->year - 1;
		priv->lunar2->month = 12;
	}
	return(flag==0);
}
