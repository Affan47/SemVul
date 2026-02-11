put_double(blxcontext_t *ctx, double data, unsigned char **bufptr) {
    if((is_big_endian() && ctx->endian == LITTLEENDIAN) ||
       (!is_big_endian() && ctx->endian == BIGENDIAN))
	data = doubleSWAP(data);
    memcpy(*bufptr, &data, sizeof(double));
    *bufptr+=sizeof(double);
}
