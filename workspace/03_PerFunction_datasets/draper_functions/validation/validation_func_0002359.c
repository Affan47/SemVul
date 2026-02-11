send_error(context, fd, err_code, err_text)
    krb5_context context;
    int fd;
    krb5_error_code     err_code;
    char        *err_text;
{
    krb5_error      error;
    const char      *text;
    krb5_data       outbuf;
    char            buf[1024];

    memset(&error, 0, sizeof(error));
    krb5_us_timeofday(context, &error.stime, &error.susec);
    error.server = server;
    error.client = client;

    if (err_text)
        text = err_text;
    else
        text = error_message(err_code);

    error.error = err_code - ERROR_TABLE_BASE_krb5;
    if (error.error > 127) {
        error.error = KRB_ERR_GENERIC;
        if (err_text) {
            snprintf(buf, sizeof(buf), "%s %s",
                     error_message(err_code), err_text);
            text = buf;
        }
    }
    error.text.length = strlen(text) + 1;
    error.text.data = strdup(text);
    if (error.text.data) {
        if (!krb5_mk_error(context, &error, &outbuf)) {
            (void) krb5_write_message(context, (void *)&fd,&outbuf);
            krb5_free_data_contents(context, &outbuf);
        }
        free(error.text.data);
    }
}
