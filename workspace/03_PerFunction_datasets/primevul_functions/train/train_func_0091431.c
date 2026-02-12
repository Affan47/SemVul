irc_nick_set_host (struct t_irc_nick *nick, const char *host)
{
    if (!nick)
        return;


    if ((!nick->host && !host)
        || (nick->host && host && strcmp (nick->host, host) == 0))
    {
        return;
    }


    if (nick->host)
        free (nick->host);
    nick->host = (host) ? strdup (host) : NULL;
}
