help_heuristic(
    char_u	*matched_string,
    int		offset,
    int		wrong_case)
{
    int		num_letters;
    char_u	*p;

    num_letters = 0;
    for (p = matched_string; *p; p++)
	if (ASCII_ISALNUM(*p))
	    num_letters++;


    if (ASCII_ISALNUM(matched_string[offset]) && offset > 0
				 && ASCII_ISALNUM(matched_string[offset - 1]))
	offset += 10000;
    else if (offset > 2)
	offset *= 200;
    if (wrong_case)
	offset += 5000;


    if (matched_string[0] == '+' && matched_string[1] != NUL)
	offset += 100;
    return (int)(100 * num_letters + STRLEN(matched_string) + offset);
}
