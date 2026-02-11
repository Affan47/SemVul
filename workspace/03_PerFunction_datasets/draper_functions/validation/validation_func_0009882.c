jid_cmpx(jid a, jid b, int parts)
{
    if(a == NULL || b == NULL)
        return -1;

    if(parts & JID_RESOURCE && _jid_nullstrcmp(a->resource, b->resource) != 0) return -1;
    if(parts & JID_USER && _jid_nullstrcasecmp(a->user, b->user) != 0) return -1;
    if(parts & JID_SERVER && _jid_nullstrcmp(a->server, b->server) != 0) return -1;

    return 0;
}
