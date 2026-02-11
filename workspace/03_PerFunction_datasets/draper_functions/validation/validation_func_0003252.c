get1(char *c)
{
    if (read1(c) != 0)
	return 1;
    if (*c != COMMAND_ESC)
	return 0;
    if (read1(c) != 0)
	return 1;
    if (*c) {
	current_command = *c;
	return -1;
    }
    *c = COMMAND_ESC;
    return 0;
}
