base64(int encode, char *in, int len) {
    BIO *bio, *b64;
    char *out;

    b64=BIO_new(BIO_f_base64());
    BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
    bio=BIO_new(BIO_s_mem());
    if(encode)
        bio=BIO_push(b64, bio);
    BIO_write(bio, in, len);
    (void)BIO_flush(bio);
    if(encode) {
        bio=BIO_pop(bio);
        BIO_free(b64);
    } else {
        bio=BIO_push(b64, bio);
    }
    len=BIO_pending(bio);


    out=str_alloc(len<32?32:len+1);
    if(!out) {
        s_log(LOG_ERR, "Fatal memory allocation error");
        die(2);
    }
    BIO_read(bio, out, len);
    BIO_free_all(bio);
    return out;
}
