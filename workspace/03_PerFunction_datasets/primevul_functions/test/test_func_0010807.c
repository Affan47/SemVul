exit_code(int token, int value)
{
    int result = 99;

    switch (token) {
    case BOOLEAN:
	result = !value;
	break;
    case NUMBER:
	result = 0;
	break;
    case STRING:
	result = value;
	break;
    }
    return result;
}
