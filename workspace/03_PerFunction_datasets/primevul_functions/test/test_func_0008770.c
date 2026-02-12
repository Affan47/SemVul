static const char *screen_units_str(void)
{

	const char *units_str[] = {N_("mil"), N_("mm"), N_("in")};

	return _(units_str[screen.unit]);
}
