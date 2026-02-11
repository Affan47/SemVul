krb5_dbe_compute_salt(krb5_context context, const krb5_key_data *key,
                      krb5_const_principal princ, krb5_int16 *salttype_out,
                      krb5_data **salt_out)
{
    krb5_error_code retval;
    krb5_int16 stype;
    krb5_data *salt, sdata;

    stype = (key->key_data_ver < 2) ? KRB5_KDB_SALTTYPE_NORMAL :
        key->key_data_type[1];
    *salttype_out = stype;
    *salt_out = NULL;


    switch (stype) {
    case KRB5_KDB_SALTTYPE_NORMAL:
        retval = krb5_principal2salt(context, princ, &sdata);
        if (retval)
            return retval;
        break;
    case KRB5_KDB_SALTTYPE_V4:
        sdata = empty_data();
        break;
    case KRB5_KDB_SALTTYPE_NOREALM:
        retval = krb5_principal2salt_norealm(context, princ, &sdata);
        if (retval)
            return retval;
        break;
    case KRB5_KDB_SALTTYPE_AFS3:
    case KRB5_KDB_SALTTYPE_ONLYREALM:
        return krb5_copy_data(context, &princ->realm, salt_out);
    case KRB5_KDB_SALTTYPE_SPECIAL:
        sdata = make_data(key->key_data_contents[1], key->key_data_length[1]);
        return krb5_copy_data(context, &sdata, salt_out);
    default:
        return KRB5_KDB_BAD_SALTTYPE;
    }


    salt = malloc(sizeof(*salt));
    if (salt == NULL) {
        free(sdata.data);
        return ENOMEM;
    }
    *salt = sdata;
    *salt_out = salt;
    return 0;
}
