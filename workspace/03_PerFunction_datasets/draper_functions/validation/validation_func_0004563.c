OpenSSLTrace(SSL *ssl, int where, int rc)
{
    NsOpenSSLConn *sslconn         = (NsOpenSSLConn *) SSL_get_app_data(ssl);
    char          *alertTypePrefix = NULL;
    char          *alertType       = NULL;
    char          *alertDescPrefix = NULL;
    char          *alertDesc       = NULL;
    struct Tcl_Time previoustime;
    unsigned long  seconds;
    unsigned long  microseconds;

    if (where & SSL_CB_ALERT) {
        alertTypePrefix = "; alert type = ";
        alertType = (char *) SSL_alert_type_string_long(rc);
        alertDescPrefix = "; alert desc = ";
        alertDesc = (char *) SSL_alert_desc_string_long(rc);
    } else {
        alertTypePrefix = alertType = "";
        alertDescPrefix = alertDesc = "";
    }


    previoustime = sslconn->timer;


    Tcl_GetTime(&sslconn->timer);


    seconds = sslconn->timer.sec - previoustime.sec;


    microseconds = sslconn->timer.usec - previoustime.usec;


    microseconds = microseconds + (seconds * 1000000);

    Ns_Log(Notice, "%s (%s): trace (%p): %8ld secs: %s%s%s%s%s",
            MODULE, sslconn->server,
            sslconn,
            microseconds,
            SSL_state_string_long(ssl),
            alertTypePrefix, alertType, alertDescPrefix, alertDesc
    );
}
