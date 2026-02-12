exit_command()
{

    if (equals(c_token+1,"gnuplot"))
	gp_exit(EXIT_SUCCESS);

    if (equals(c_token+1,"status")) {
	int status;
	c_token += 2;
	status = int_expression();
	gp_exit(status);
    }


    if (equals(c_token+1,"error")) {
	c_token += 2;
	int_error(NO_CARET, try_to_get_string());
    }


    command_exit_requested = 1;
}
