int wc_RsaSetNonBlock(RsaKey* key, RsaNb* nb)
{
    if (key == NULL)
        return BAD_FUNC_ARG;

    if (nb) {
        XMEMSET(nb, 0, sizeof(RsaNb));
    }


    key->nb = nb;

    return 0;
}
