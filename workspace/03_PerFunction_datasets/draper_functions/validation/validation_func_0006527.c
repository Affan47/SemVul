server_setup(krb5_context *context, int argc, char **argv)
{
    int port = common_setup(context, &argc, argv, server_usage);
    krb5_error_code ret;

    if(argv[argc] != NULL)
	server_usage(1, args, num_args);
    if (keytab_str != NULL) {
        ret = krb5_kt_resolve (*context, keytab_str, &keytab);
        if (ret)
            krb5_err (*context, 1, ret, "krb5_kt_resolve");
    } else {
        ret = krb5_kt_default (*context, &keytab);
        if (ret)
            krb5_err (*context, 1, ret, "krb5_kt_default");
    }
    return port;
}
