krb5_authenticator_internalize(krb5_context kcontext, krb5_pointer *argp, krb5_octet **buffer, size_t *lenremain)
{
    krb5_error_code     kret;
    krb5_authenticator  *authenticator;
    krb5_int32          ibuf;
    krb5_octet          *bp;
    size_t              remain;
    int                 i;
    krb5_int32          nadata;
    size_t              len;

    bp = *buffer;
    remain = *lenremain;
    kret = EINVAL;

    if (krb5_ser_unpack_int32(&ibuf, &bp, &remain))
        ibuf = 0;
    if (ibuf == KV5M_AUTHENTICATOR) {
        kret = ENOMEM;


        if ((remain >= (3*sizeof(krb5_int32))) &&
            (authenticator = (krb5_authenticator *)
             calloc(1, sizeof(krb5_authenticator)))) {


            (void) krb5_ser_unpack_int32(&ibuf, &bp, &remain);
            authenticator->ctime = (krb5_timestamp) ibuf;


            (void) krb5_ser_unpack_int32(&ibuf, &bp, &remain);
            authenticator->cusec = ibuf;


            (void) krb5_ser_unpack_int32(&ibuf, &bp, &remain);
            authenticator->seq_number = ibuf;

            kret = 0;


            kret = krb5_internalize_opaque(kcontext,
                                           KV5M_PRINCIPAL,
                                           (krb5_pointer *)
                                           &authenticator->client,
                                           &bp,
                                           &remain);
            if (kret == EINVAL)
                kret = 0;


            if (!kret) {
                kret = krb5_internalize_opaque(kcontext,
                                               KV5M_CHECKSUM,
                                               (krb5_pointer *)
                                               &authenticator->checksum,
                                               &bp,
                                               &remain);
                if (kret == EINVAL)
                    kret = 0;
            }


            if (!kret) {
                kret = krb5_internalize_opaque(kcontext,
                                               KV5M_KEYBLOCK,
                                               (krb5_pointer *)
                                               &authenticator->subkey,
                                               &bp,
                                               &remain);
                if (kret == EINVAL)
                    kret = 0;
            }


            if (!(kret = krb5_ser_unpack_int32(&ibuf, &bp, &remain))) {
                nadata = ibuf;
                len = (size_t) (nadata + 1);


                if ((authenticator->authorization_data = (krb5_authdata **)
                     calloc(len, sizeof(krb5_authdata *)))) {
                    for (i=0; !kret && (i<nadata); i++) {
                        kret = krb5_internalize_opaque(kcontext,
                                                       KV5M_AUTHDATA,
                                                       (krb5_pointer *)
                                                       &authenticator->
                                                       authorization_data[i],
                                                       &bp,
                                                       &remain);
                    }


                    if (!kret) {
                        kret = krb5_ser_unpack_int32(&ibuf, &bp, &remain);
                        if (!kret && (ibuf == KV5M_AUTHENTICATOR))
                            authenticator->magic = KV5M_AUTHENTICATOR;
                        else
                            kret = EINVAL;
                    }
                }
            }
            if (!kret) {
                *buffer = bp;
                *lenremain = remain;
                *argp = (krb5_pointer) authenticator;
            }
            else
                krb5_free_authenticator(kcontext, authenticator);
        }
    }
    return(kret);
}
