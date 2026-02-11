get_directive(char *string)
{
    int index = -1;
    register int x;

    for(x=0; x < MAXTEMPLATE; x++)  {
        if(!strncmp(string, templates[x].name,
                    strlen(templates[x].name))) {
            index = x;
            break;
        }
    }
    return index;
}
