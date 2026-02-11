PopupChooseword (void (*ok_func) (), void (*cancel_func) (), struct chooseword_info *info)
{
	if (!g_pReciteWord->chooseword)
	{
		g_pReciteWord->chooseword = new CChooseword;
	}
	g_pReciteWord->chooseword->show (ok_func, cancel_func, info);
}
