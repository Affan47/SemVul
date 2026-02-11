NET_SV_NumReadyPlayers(void)
{
    int result = 0;
    int i;

    for (i = 0; i < MAXNETNODES; ++i)
    {
        if (ClientConnected(&clients[i])
         && !clients[i].drone && clients[i].ready)
        {
            ++result;
        }
    }

    return result;
}
