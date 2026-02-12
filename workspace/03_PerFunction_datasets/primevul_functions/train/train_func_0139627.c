static void rcc_fun(REgg *egg, const char *str) {
	char *ptr, *ptr2;
	REggEmit *e = egg->remit;
	str = skipspaces (str);
	if (CTX) {
		ptr = strchr (str, '=');
		if (ptr) {
			*ptr++ = '\0';
			free (egg->lang.dstvar);
			egg->lang.dstvar = strdup (skipspaces (str));
			ptr2 = (char *) skipspaces (ptr);
			if (*ptr2) {
				rcc_set_callname (egg, skipspaces (ptr));
			}
		} else {
			str = skipspaces (str);
			rcc_set_callname (egg, skipspaces (str));
			egg->remit->comment (egg, "rcc_fun %d (%s)",
				CTX, egg->lang.callname);
		}
	} else {
		ptr = strchr (str, '@');
		if (ptr) {
			*ptr++ = '\0';
			egg->lang.mode = NORMAL;
			if (strstr (ptr, "env")) {

				free (egg->lang.setenviron);
				egg->lang.setenviron = strdup (skipspaces (str));
				egg->lang.slurp = 0;
			} else if (strstr (ptr, "fastcall")) {

			} else if (strstr (ptr, "syscall")) {
				if (*str) {
					egg->lang.mode = SYSCALL;
					egg->lang.dstvar = strdup (skipspaces (str));
				} else {
					egg->lang.mode = INLINE;
					free (egg->lang.syscallbody);
					egg->lang.syscallbody = malloc (4096);
					egg->lang.dstval = egg->lang.syscallbody;
					R_FREE (egg->lang.dstvar);
					egg->lang.ndstval = 0;
					*egg->lang.syscallbody = '\0';
				}
			} else if (strstr (ptr, "include")) {
				egg->lang.mode = INCLUDE;
				free (egg->lang.includefile);
				egg->lang.includefile = strdup (skipspaces (str));


			} else if (strstr (ptr, "alias")) {
				egg->lang.mode = ALIAS;
				ptr2 = egg->lang.dstvar = strdup (skipspaces (str));
				while (*ptr2 && !is_space (*ptr2)) {
					ptr2++;
				}
				*ptr2 = '\x00';

			} else if (strstr (ptr, "data")) {
				egg->lang.mode = DATA;
				egg->lang.ndstval = 0;
				egg->lang.dstvar = strdup (skipspaces (str));
				egg->lang.dstval = malloc (4096);
			} else if (strstr (ptr, "naked")) {
				egg->lang.mode = NAKED;


				r_egg_printf (egg, "%s:\n", str);
			} else if (strstr (ptr, "inline")) {
				egg->lang.mode = INLINE;
				free (egg->lang.dstvar);
				egg->lang.dstvar = strdup (skipspaces (str));
				egg->lang.dstval = malloc (4096);
				egg->lang.ndstval = 0;
			} else {

				if (*ptr) {
					r_egg_printf (egg, "\n.%s %s\n", ptr, str);
				}
				r_egg_printf (egg, "%s:\n", str);
			}
		} else {

			if (CTX > 0) {

				eprintf ("LABEL %d\n", CTX);
				r_egg_printf (egg, "\n%s:\n", str);
			} else {
				if (!strcmp (str, "goto")) {
					egg->lang.mode = GOTO;
				} else {

					e->call (egg, str, 0);
				}
			}
		}
	}
}
