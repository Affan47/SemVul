vfc_splash(char *vf_file_name)
{
	if (did_not_splash) {


		char *strbfr = malloc(strlen(vf_file_name) + 65);
		sprintf(strbfr,
			"Reading additional FCodes from file:  %s\n",
			vf_file_name);
		printremark(strbfr);
		free(strbfr);
		did_not_splash = FALSE;
	}
}
