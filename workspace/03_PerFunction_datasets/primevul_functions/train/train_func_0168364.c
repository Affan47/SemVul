int ssh_get_random(void *where, int len, int strong)
{
#ifdef HAVE_OPENSSL_RAND_PRIV_BYTES
    if (strong) {

        return !!RAND_priv_bytes(where, len);
    }
#else
    (void)strong;
#endif


    return !!RAND_bytes(where, len);
}
