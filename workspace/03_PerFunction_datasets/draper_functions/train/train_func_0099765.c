hud_num_make_mono(char *num_str)
{
	int len, i, sc;
	len = strlen(num_str);

	sc = Lcl_special_chars;
	for ( i = 0; i < len; i++ ) {
		if ( num_str[i] == '1' ) {
			num_str[i] = (char)(sc + 1);
		}
	}
}
