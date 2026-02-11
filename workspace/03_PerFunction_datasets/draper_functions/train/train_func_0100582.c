skip_iv(gs_type1_state *pcis)
{
    int skip = pcis->pfont->data.lenIV;
    ip_state_t *ipsp = &pcis->ipstack[pcis->ips_count - 1];
    const byte *cip = ipsp->cs_data.bits.data;
    crypt_state state = crypt_charstring_seed;

    for (; skip > 0; ++cip, --skip)
        decrypt_skip_next(*cip, state);
    ipsp->ip = cip;
    ipsp->dstate = state;
}
