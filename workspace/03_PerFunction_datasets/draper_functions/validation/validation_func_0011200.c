krb5_k_decrypt(krb5_context context, krb5_key key,
               krb5_keyusage usage, const krb5_data *cipher_state,
               const krb5_enc_data *input, krb5_data *output)
{
    const struct krb5_keytypes *ktp;
    krb5_crypto_iov iov[4];
    krb5_error_code ret;
    unsigned int header_len, trailer_len, plain_len;
    char *scratch = NULL;

    ktp = find_enctype(key->keyblock.enctype);
    if (ktp == NULL)
        return KRB5_BAD_ENCTYPE;

    if (input->enctype != ENCTYPE_UNKNOWN && ktp->etype != input->enctype)
        return KRB5_BAD_ENCTYPE;


    header_len = ktp->crypto_length(ktp, KRB5_CRYPTO_TYPE_HEADER);
    trailer_len = ktp->crypto_length(ktp, KRB5_CRYPTO_TYPE_TRAILER);
    if (input->ciphertext.length < header_len + trailer_len)
        return KRB5_BAD_MSIZE;
    plain_len = input->ciphertext.length - header_len - trailer_len;
    if (output->length < plain_len)
        return KRB5_BAD_MSIZE;

    scratch = k5alloc(header_len + trailer_len, &ret);
    if (scratch == NULL)
        return ret;

    iov[0].flags = KRB5_CRYPTO_TYPE_HEADER;
    iov[0].data = make_data(scratch, header_len);
    memcpy(iov[0].data.data, input->ciphertext.data, header_len);

    iov[1].flags = KRB5_CRYPTO_TYPE_DATA;
    iov[1].data = make_data(output->data, plain_len);
    memcpy(iov[1].data.data, input->ciphertext.data + header_len, plain_len);


    iov[2].flags = KRB5_CRYPTO_TYPE_PADDING;
    iov[2].data = empty_data();

    iov[3].flags = KRB5_CRYPTO_TYPE_TRAILER;
    iov[3].data = make_data(scratch + header_len, trailer_len);
    memcpy(iov[3].data.data, input->ciphertext.data + header_len + plain_len,
           trailer_len);

    ret = ktp->decrypt(ktp, key, usage, cipher_state, iov, 4);
    if (ret != 0)
        zap(output->data, plain_len);
    else
        output->length = plain_len;
    zapfree(scratch, header_len + trailer_len);
    return ret;
}
