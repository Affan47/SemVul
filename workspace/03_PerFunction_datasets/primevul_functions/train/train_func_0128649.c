initialize(void)
{


    rndpool = secure_alloc ? xmalloc_secure_clear(POOLSIZE+BLOCKLEN)
			   : xmalloc_clear(POOLSIZE+BLOCKLEN);
    keypool = secure_alloc ? xmalloc_secure_clear(POOLSIZE+BLOCKLEN)
			   : xmalloc_clear(POOLSIZE+BLOCKLEN);
    is_initialized = 1;
}
