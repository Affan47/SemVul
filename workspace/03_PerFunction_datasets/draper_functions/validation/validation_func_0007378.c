krb5_encrypt(krb5_context context, krb5_const_pointer inptr,
             krb5_pointer outptr, size_t size, krb5_encrypt_block *eblock,
             krb5_pointer ivec)
{
    krb5_data inputd, ivecd;
    krb5_enc_data outputd;
    size_t blocksize, outlen;
    krb5_error_code ret;

    if (ivec) {
        ret = krb5_c_block_size(context, eblock->key->enctype, &blocksize);
        if (ret)
            return ret;

        ivecd = make_data(ivec, blocksize);
    }


    inputd = make_data((void *) inptr, size);


    ret = krb5_c_encrypt_length(context, eblock->key->enctype, size, &outlen);
    if (ret)
        return ret;

    outputd.ciphertext = make_data(outptr, outlen);

    return krb5_c_encrypt(context, eblock->key, 0, ivec ? &ivecd : 0,
                          &inputd, &outputd);
}
