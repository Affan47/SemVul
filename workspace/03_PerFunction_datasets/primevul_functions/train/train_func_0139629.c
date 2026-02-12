R_API void r_egg_lang_init(REgg *egg) {
	egg->lang.varsize = 'l';

	egg->lang.docall = 1;
	egg->lang.line = 1;
	egg->lang.file = "stdin";
	egg->lang.oc = '\n';
	egg->lang.mode = NORMAL;
}
