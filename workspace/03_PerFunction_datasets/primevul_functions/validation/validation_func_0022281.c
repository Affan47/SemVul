undefine_command()
{
    char key[MAX_ID_LEN+1];
    TBOOLEAN wildcard;

    c_token++;

    while (!END_OF_COMMAND) {

	copy_str(key, c_token, MAX_ID_LEN);


	wildcard = equals(c_token+1,"*");
	if (wildcard)
	    c_token++;


	else if (*key == '$')
	    copy_str(&key[1], ++c_token, MAX_ID_LEN-1);


	else if (!isletter(c_token))
	    int_error(c_token, "Not a variable name");


	if (equals(c_token+1, "[") || equals(c_token+1, "("))
	    int_error(c_token, "Cannot undefine function or array element");


	if (strncmp(key, "GPVAL_", 6) && strncmp(key, "MOUSE_", 6))
	    del_udv_by_name( key, wildcard );

	c_token++;
    }
}
