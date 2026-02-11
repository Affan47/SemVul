sfmemcap_dupmem( MEMCAP * mc, void * src, unsigned long n )
{
    void * data = (char *)sfmemcap_alloc( mc, n );
    if(data == NULL)
    {
        return  0;
    }

    memcpy( data, src, n );

    return data;
}
