make_ecpoint_string(const EC_GROUP *g,
                                      const EC_POINT *p)
{
    ssh_string s;
    size_t len;

    len = EC_POINT_point2oct(g,
                             p,
                             POINT_CONVERSION_UNCOMPRESSED,
                             NULL,
                             0,
                             NULL);
    if (len == 0) {
        return NULL;
    }

    s = ssh_string_new(len);
    if (s == NULL) {
        return NULL;
    }

    len = EC_POINT_point2oct(g,
                             p,
                             POINT_CONVERSION_UNCOMPRESSED,
                             ssh_string_data(s),
                             ssh_string_len(s),
                             NULL);
    if (len != ssh_string_len(s)) {
        ssh_string_free(s);
        return NULL;
    }

    return s;
}
