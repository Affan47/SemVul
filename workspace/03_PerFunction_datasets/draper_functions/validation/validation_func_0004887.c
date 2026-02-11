yywrap()
{
	fclose(inc[inc_p].fp);
	inc_p--;
	list_on = list_on_next = TRUE;
	if(inc_p > 1)
		list_on = list_on_next = FALSE;
	if(inc_p) {
		yyin = inc[inc_p].fp;
		return 0;
	} else {
		return 1;
	}
}
