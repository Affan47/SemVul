htol(char *s, int flags, int *errptr)
{
    	long i, j;
	ulong n;

    	if (s == NULL) {
		if (!(flags & QUIET))
			error(INFO, "received NULL string\n");
		goto htol_error;
	}

    	if (STRNEQ(s, "0x") || STRNEQ(s, "0X"))
		s += 2;

    	if (strlen(s) > MAX_HEXADDR_STRLEN) {
		if (!(flags & QUIET))
			error(INFO,
			    "input string too large: \"%s\" (%d vs %d)\n",
				s, strlen(s), MAX_HEXADDR_STRLEN);
		goto htol_error;
	}

    	for (n = i = 0; s[i] != 0; i++) {
	        switch (s[i])
	        {
	            case 'a':
	            case 'b':
	            case 'c':
	            case 'd':
	            case 'e':
	            case 'f':
	                j = (s[i] - 'a') + 10;
	                break;
	            case 'A':
	            case 'B':
	            case 'C':
	            case 'D':
	            case 'E':
	            case 'F':
	                j = (s[i] - 'A') + 10;
	                break;
	            case '1':
	            case '2':
	            case '3':
	            case '4':
	            case '5':
	            case '6':
	            case '7':
	            case '8':
	            case '9':
	            case '0':
	                j = s[i] - '0';
	                break;
		    case 'x':
		    case 'X':
		    case 'h':
			continue;
	            default:
			if (!(flags & QUIET))
				error(INFO, "invalid input: \"%s\"\n", s);
			goto htol_error;
	        }
	        n = (16 * n) + j;
    	}

    	return(n);

htol_error:
	switch (flags & (FAULT_ON_ERROR|RETURN_ON_ERROR))
	{
	case FAULT_ON_ERROR:
		RESTART();

	case RETURN_ON_ERROR:
		if (errptr)
			*errptr = TRUE;
		break;
	}

	return BADADDR;
}
