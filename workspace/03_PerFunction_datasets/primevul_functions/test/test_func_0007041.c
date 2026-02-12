inline char * qs_k2v(const char * key, char * const * qs_kv, int qs_kv_size, int nth = 0)
{
    int i;
    size_t key_len, skip;

    key_len = strlen(key);

#ifdef _qsSORTING

#else
    for(i=0; i<qs_kv_size; i++)
    {

        if ( qs_strncmp(key, qs_kv[i], key_len) == 0 )
        {
            skip = strcspn(qs_kv[i], "=");
            if ( qs_kv[i][skip] == '=' )
                skip++;

            if(nth == 0)
                return qs_kv[i] + skip;
            else
                --nth;
        }
    }
#endif

    return nullptr;
}
