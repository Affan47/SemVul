describe_monster_exp(int r_idx, const monster_lore *l_ptr)
{
	const monster_race *r_ptr = &r_info[r_idx];
	bitflag f[RF_SIZE];

	const char *p, *q;

	long i, j;

	char buf[20] = "";


	monster_flags_known(r_ptr, l_ptr, f);


	if (rf_has(f, RF_UNIQUE))
		text_out("Killing");
	else
		text_out("A kill of");

	text_out(" this creature");


	i = (long)r_ptr->mexp * r_ptr->level / p_ptr->lev;


	j = ((((long)r_ptr->mexp * r_ptr->level % p_ptr->lev) *
		  (long)1000 / p_ptr->lev + 5) / 10);


	strnfmt(buf, sizeof(buf), "%ld", (long)i);
	if (j) my_strcat(buf, format(".%02ld", (long)j), sizeof(buf));


	text_out(" is worth ");
	text_out_c(TERM_BLUE, format("%s point%s", buf, PLURAL((i == 1) && (j == 0))));


	p = "th";
	i = p_ptr->lev % 10;
	if ((p_ptr->lev / 10) == 1) ;
	else if (i == 1) p = "st";
	else if (i == 2) p = "nd";
	else if (i == 3) p = "rd";


	q = "";
	i = p_ptr->lev;
	if ((i == 8) || (i == 11) || (i == 18)) q = "n";


	text_out(" for a%s %lu%s level character.  ", q, (long)i, p);
}
