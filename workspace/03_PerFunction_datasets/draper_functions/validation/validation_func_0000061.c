s3_hex_encode(const GByteArray *to_enc)  {
    guint i;
    gchar *ret = NULL, table[] = "0123456789abcdef";
    if (!to_enc) return NULL;

    ret = g_new(gchar, to_enc->len*2 + 1);
    for (i = 0; i < to_enc->len; i++) {

        ret[i*2] = table[to_enc->data[i] >> 4];

        ret[i*2 + 1] = table[to_enc->data[i] & 0xf];
    }
    ret[to_enc->len*2] = '\0';

    return ret;
}
