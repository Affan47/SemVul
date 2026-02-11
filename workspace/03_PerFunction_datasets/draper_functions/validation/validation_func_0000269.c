igeti4 (hstring, keyword, ival)

char *hstring;

char *keyword;


int *ival;
{
char *value;
double dval;
int minint;


	value = igetc (hstring,keyword);


	if (value != NULL) {
	    minint = -INT_MAX - 1;
	    strcpy (val, value);
	    dval = atof (val);
	    if (dval+0.001 > INT_MAX)
		*ival = INT_MAX;
	    else if (dval >= 0)
		*ival = (int) (dval + 0.001);
	    else if (dval-0.001 < minint)
		*ival = minint;
	    else
		*ival = (int) (dval - 0.001);
	    return (1);
	    }
	else {
	    return (0);
	    }
}
