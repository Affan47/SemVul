clear_bot()
{


	if (oldbot)
		lower_left();
	else
		line_left();

	if (attrmode == AT_NORMAL)
		clear_eol_bot();
	else
	{
		int saved_attrmode = attrmode;

		at_exit();
		clear_eol_bot();
		at_enter(saved_attrmode);
	}
}
