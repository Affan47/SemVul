i_new_line_options(int create)
{
    int i;
    char val[1000];
    char temp[1000];

    G_debug(4, "i_new_line_options(), create = %d", create);

    if (create) {
	Tcl_Eval(Toolbox, "new_line_options 1");


	sprintf(val, "$GWidget(cat_mode) configure -values [list");
	for (i = 0; i < CAT_MODE_COUNT; i++) {
	    sprintf(temp, " \"%s\"", CatModeLab[i]);
	    strcat(val, temp);
	}
	strcat(val, "]");

	G_debug(2, "Cat modes: %s", val);
	Tcl_Eval(Toolbox, val);

	sprintf(val, "$GWidget(cat_mode) setvalue @%d",
		var_geti(VAR_CAT_MODE));
	G_debug(2, "Cat mode: %s", val);
	Tcl_Eval(Toolbox, val);
    }
    else {
	Tcl_Eval(Toolbox, "new_line_options 0");
    }

    sprintf(val, "%d", var_geti(VAR_FIELD));
    Tcl_SetVar(Toolbox, "field", val, TCL_GLOBAL_ONLY);
    i_set_cat_mode();
}
