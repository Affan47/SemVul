S_measure_struct(pTHX_ tempsym_t* symptr)
{
    I32 total = 0;

    PERL_ARGS_ASSERT_MEASURE_STRUCT;

    while (next_symbol(symptr)) {
	I32 len;
	int size;

        switch (symptr->howlen) {
	  case e_star:
   	    Perl_croak(aTHX_ "Within []-length '*' not allowed in %s",
                        _action( symptr ) );
            break;
	  default:

	    len = symptr->length;
	    break;
        }

	size = packprops[TYPE_NO_ENDIANNESS(symptr->code)] & PACK_SIZE_MASK;
	if (!size) {
            int star;

	    switch(TYPE_NO_ENDIANNESS(symptr->code)) {
	    default:
		Perl_croak(aTHX_ "Invalid type '%c' in %s",
			   (int)TYPE_NO_MODIFIERS(symptr->code),
                           _action( symptr ) );
#ifdef PERL_PACK_CAN_SHRIEKSIGN
	    case '.' | TYPE_IS_SHRIEKING:
	    case '@' | TYPE_IS_SHRIEKING:
#endif
	    case '@':
	    case '.':
	    case '/':
	    case 'U':
	    case 'w':
	    case 'u':
		Perl_croak(aTHX_ "Within []-length '%c' not allowed in %s",
			   (int) TYPE_NO_MODIFIERS(symptr->code),
                           _action( symptr ) );
	    case '%':
		size = 0;
		break;
	    case '(':
	    {
		tempsym_t savsym = *symptr;
		symptr->patptr = savsym.grpbeg;
		symptr->patend = savsym.grpend;


		size = measure_struct(symptr);
		*symptr = savsym;
		break;
	    }
	    case 'X' | TYPE_IS_SHRIEKING:


		if (!len)
		    len = 1;
		len = total % len;

	    case 'X':
		size = -1;
		if (total < len)
                    Perl_croak(aTHX_ "'X' outside of string in %s", _action( symptr ) );
		break;
	    case 'x' | TYPE_IS_SHRIEKING:
		if (!len)
		    len = 1;
		star = total % len;
		if (star)
		    len = len - star;
		else
		    len = 0;

	    case 'x':
	    case 'A':
	    case 'Z':
	    case 'a':
		size = 1;
		break;
	    case 'B':
	    case 'b':
		len = (len + 7)/8;
		size = 1;
		break;
	    case 'H':
	    case 'h':
		len = (len + 1)/2;
		size = 1;
		break;

	    case 'P':
		len = 1;
		size = sizeof(char*);
		break;
	    }
	}
	total += len * size;
    }
    return total;
}
