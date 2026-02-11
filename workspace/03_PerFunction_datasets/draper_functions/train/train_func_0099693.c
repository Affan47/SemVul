encrypt_token(struct client *client, int32_t hContext, int32_t flags,
	   krb5_data *in, krb5_data *out)
{
    int32_t val;
    put32(client, eEncrypt);
    put32(client, hContext);
    put32(client, flags);
    put32(client, 0);
    putdata(client, *in);
    ret32(client, val);
    retdata(client, *out);
    return val;
}
