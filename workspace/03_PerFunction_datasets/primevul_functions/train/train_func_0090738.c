fruitadd(str)
char *str;
{
	register int i;
	register struct fruit *f;
	int highest_fruit_id = 0;
	char buf[PL_FSIZ], altname[PL_FSIZ];
	boolean user_specified = (str == pl_fruit);


	if (user_specified) {
		boolean found = FALSE, numeric = FALSE;


		nmcpy(pl_fruit, makesingular(str), PL_FSIZ);


		for (i = bases[FOOD_CLASS]; objects[i].oc_class == FOOD_CLASS;
						i++) {
			if (!strcmp(OBJ_NAME(objects[i]), pl_fruit)) {
				found = TRUE;
				break;
			}
		}
		{
		    char *c;

		    c = pl_fruit;

		    for(c = pl_fruit; *c >= '0' && *c <= '9'; c++)
			;
		    if (isspace(*c) || *c == 0) numeric = TRUE;
		}
		if (found || numeric ||
		    !strncmp(str, "cursed ", 7) ||
		    !strncmp(str, "uncursed ", 9) ||
		    !strncmp(str, "blessed ", 8) ||
		    !strncmp(str, "partly eaten ", 13) ||
		    (!strncmp(str, "tin of ", 7) &&
			(!strcmp(str+7, "spinach") ||
			 name_to_mon(str+7) >= LOW_PM)) ||
		    !strcmp(str, "empty tin") ||
		    ((!strncmp(eos(str)-7," corpse",7) ||
			    !strncmp(eos(str)-4, " egg",4)) &&
			name_to_mon(str) >= LOW_PM))
			{
				Strcpy(buf, pl_fruit);
				Strcpy(pl_fruit, "candied ");
				nmcpy(pl_fruit+8, buf, PL_FSIZ-8);
		}
		*altname = '\0';
	} else {

		copynchars(altname, str, PL_FSIZ-1);
		sanitize_name(altname);
	}
	for(f=ffruit; f; f = f->nextf) {
		if(f->fid > highest_fruit_id) highest_fruit_id = f->fid;
		if (!strncmp(str, f->fname, PL_FSIZ-1) ||
			    (*altname && !strcmp(altname, f->fname)))
			goto nonew;
	}


	if (highest_fruit_id >= 127) return rnd(127);

	f = newfruit();
	copynchars(f->fname, *altname ? altname : str, PL_FSIZ-1);
	f->fid = ++highest_fruit_id;


	f->nextf = ffruit;
	ffruit = f;
 nonew:
	if (user_specified) context.current_fruit = f->fid;
	return f->fid;
}
