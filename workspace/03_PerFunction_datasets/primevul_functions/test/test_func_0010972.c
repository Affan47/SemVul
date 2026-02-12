write_tabs(int *tab_list)
{
    int stop;

    while ((stop = *tab_list++) > 0 && stop <= max_cols) {
	fputs((stop == 1) ? "*" : "\t*", stdout);
    };

    if (stop < max_cols)
	fputs("\t+", stdout);
    putchar('\n');
}
