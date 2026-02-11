randplay(AWALE * a)
{
    short int i;
    AWALE *tmp = NULL;

    do {
	i = 6 + g_random_int() % 6;
    } while (a->board[i] == 0 && !(tmp = moveAwale(i, a)));

    g_free(tmp);
    return (i);
}
