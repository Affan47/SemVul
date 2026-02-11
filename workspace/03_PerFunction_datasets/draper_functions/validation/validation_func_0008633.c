find_unused()
{
    int i;
    int newsize;

    for(i = 0; i < file_table_size; i++)
	if(file_table[i] == NULL)
	    return i;

    newsize = file_table_size + 16;
    file_table = av_realloc(file_table, sizeof(*file_table) * newsize);
    for(i = file_table_size; i < newsize; i++)
	file_table[i] = NULL;

    i = file_table_size;
    file_table_size = newsize;

    return i;
}
