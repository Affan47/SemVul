initoptions_finish()
{
#ifndef MAC
	char *opts = getenv("NETHACKOPTIONS");
	if (!opts) opts = getenv("HACKOPTIONS");
	if (opts) {
		if (*opts == '/' || *opts == '\\' || *opts == '@') {
			if (*opts == '@') opts++;

			if (strlen(opts) < BUFSZ/2)
			    read_config_file(opts, SET_IN_FILE);
		} else {
			read_config_file((char *)0, SET_IN_FILE);


			parseoptions(opts, TRUE, FALSE);
		}
	} else
#endif
		read_config_file((char *)0, SET_IN_FILE);

	(void)fruitadd(pl_fruit);


	obj_descr[SLIME_MOLD].oc_name = "fruit";

	return;
}
