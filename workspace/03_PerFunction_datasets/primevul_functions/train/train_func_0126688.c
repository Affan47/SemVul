smtp_log_tls_fail(uschar * errstr)
{
uschar * conn_info = smtp_get_connection_info();

if (Ustrncmp(conn_info, US"SMTP ", 5) == 0) conn_info += 5;


log_write(0, LOG_MAIN, "TLS error on %s %s", conn_info, errstr);
return FALSE;
}
