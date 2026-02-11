command_completion (char *text,int start,int end)
{
    char **matches = NULL;
    int i;


    if (possible_commandp(text,start,end))
	matches = siod_command_generator(text+start,end-start);
    else if (possible_variablep(text,start,end))
	matches = siod_variable_generator(text+start,end-start);

    if (matches && matches[0] && matches[1])
    {

	for (i=0; matches[i] != NULL; i++);
	qsort(matches,i,sizeof(char **),qsort_str_compare);
    }

    return matches;
}
