null_dashtype(int type, t_dashtype *custom_dash_pattern)
{
    (void) custom_dash_pattern;


    if (type <= 0)
	type = LT_SOLID;
    term->linetype(type);
}
