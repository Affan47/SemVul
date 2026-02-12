compare_part(const char *part, const char *full)
{
    const char *next_part;
    const char *next_full;
    unsigned used_full = 0;
    unsigned used_delay = 0;

    while (*part != 0) {
	if (*part != *full) {
	    used_full = 0;
	    break;
	}


	if (used_delay != 0) {
	    used_full += used_delay;
	    used_delay = 0;
	}
	if (*part == '$' && *full == '$') {
	    next_part = skip_delay(part);
	    next_full = skip_delay(full);
	    if (next_part != part && next_full != full) {
		used_delay += (unsigned) (next_full - full);
		full = next_full;
		part = next_part;
		continue;
	    }
	}
	++used_full;
	++part;
	++full;
    }
    return used_full;
}
