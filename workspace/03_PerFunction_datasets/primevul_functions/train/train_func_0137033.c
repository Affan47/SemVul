inline bool IsSpecialFileName(const char* pName)
{


    char ch = (pName[0] & ~0x20);
    switch (ch)
    {
	case 'A':
	    if (((pName[1] & ~0x20) == 'U')
		&& ((pName[2] & ~0x20) == 'X')
		&& !pName[3])
		    return true;
	    break;
	case 'C':
	    ch = (pName[1] & ~0x20);
	    switch (ch)
	    {
		case 'L':
		    if (((pName[2] & ~0x20) == 'O')
			&& ((pName[3] & ~0x20) == 'C')
			&& ((pName[4] & ~0x20) == 'K')
			&& (pName[5] == '$')
			&& !pName[6])
			    return true;
		    break;
		case 'O':
		    if ((pName[2] & ~0x20) == 'M') {
			if ((pName[3] >= '1') && (pName[3] <= '9')
			    && !pName[4])
			    return true;
		    }
		    else if ((pName[2] & ~0x20) == 'N') {
			if (!pName[3])
			    return true;
			else if ((pName[3] & ~0x20) == 'I') {
			    if (((pName[4] & ~0x20) == 'N')
				&& (pName[5] == '$')
				&& !pName[6])
			    return true;
			}
			else if ((pName[3] & ~0x20) == 'O') {
			    if (((pName[4] & ~0x20) == 'U')
				&& ((pName[5] & ~0x20) == 'T')
				&& (pName[6] == '$')
				&& !pName[7])
			    return true;
			}
		    }
		    break;
	    }
	    break;
	case 'L':
	    if (((pName[1] & ~0x20) == 'U')
		&& ((pName[2] & ~0x20) == 'X')
		&& (pName[3] >= '1') && (pName[3] <= '9')
		&& !pName[4])
		    return true;
	    break;
	case 'N':
	    if (((pName[1] & ~0x20) == 'U')
		&& ((pName[2] & ~0x20) == 'L')
		&& !pName[3])
		    return true;
	    break;
	case 'P':
	    if (((pName[1] & ~0x20) == 'R')
		&& ((pName[2] & ~0x20) == 'N')
		&& !pName[3])
		    return true;
	    break;
    }
    return false;
}
