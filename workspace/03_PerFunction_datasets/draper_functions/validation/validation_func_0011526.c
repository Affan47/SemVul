getnet(int c, unsigned char **p_r, unsigned char *plen_r, int *af_r,
          gnc_t gnc, void *closure)
{
    char *t;
    unsigned char *ip;
    unsigned char addr[16];
    unsigned char plen;
    int af, rc;

    c = getword(c, &t, gnc, closure);
    if(c < -1)
        return c;
    rc = parse_net(t, addr, &plen, &af);
    if(rc < 0) {
        free(t);
        return -2;
    }
    free(t);
    ip = malloc(16);
    if(ip == NULL)
        return -2;
    memcpy(ip, addr, 16);
    *p_r = ip;
    *plen_r = plen;
    if(af_r) *af_r = af;
    return c;
}
