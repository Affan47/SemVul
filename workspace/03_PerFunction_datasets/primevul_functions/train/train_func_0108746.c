add_authorization_data(krb5_enc_tkt_part *enc_tkt_part, krb5_authdata **ad)
{
    krb5_authdata **newad;
    int oldones, newones;
    int i;

    if (enc_tkt_part == NULL || ad == NULL)
        return EINVAL;

    for (newones = 0; ad[newones] != NULL; newones++);
    if (newones == 0)
        return 0;

    if (enc_tkt_part->authorization_data == NULL)
        oldones = 0;
    else
        for (oldones = 0;
             enc_tkt_part->authorization_data[oldones] != NULL; oldones++);

    newad = malloc((oldones + newones + 1) * sizeof(krb5_authdata *));
    if (newad == NULL)
        return ENOMEM;


    for (i = 0; i < oldones; i++)
        newad[i] = enc_tkt_part->authorization_data[i];


    for (i = 0; i < newones; i++)
        newad[oldones+i] = ad[i];


    newad[oldones+i] = NULL;


    if (enc_tkt_part->authorization_data != NULL)
        free(enc_tkt_part->authorization_data);


    enc_tkt_part->authorization_data = newad;

    return 0;
}
