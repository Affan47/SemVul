static void Log_file(LogObject *self, const char *s, int l)
{


    char errstr[MAX_STRING_LEN];

    int plen = 0;
    int slen = 0;

#if AP_SERVER_MAJORVERSION_NUMBER < 2
    FILE *logf;
#else
    apr_file_t *logf = NULL;
#endif

    if (self->r)
        logf = self->r->server->error_log;
    else
        logf = wsgi_server->error_log;

#if AP_SERVER_MAJORVERSION_NUMBER < 2
    plen = ap_snprintf(errstr, sizeof(errstr), "[%s] ", ap_get_time());
#else
    errstr[0] = '[';
    ap_recent_ctime(errstr + 1, apr_time_now());
    errstr[1 + APR_CTIME_LEN - 1] = ']';
    errstr[1 + APR_CTIME_LEN    ] = ' ';
    plen = 1 + APR_CTIME_LEN + 1;
#endif

    if (self->target) {
        int len;

        errstr[plen++] = '[';

        len = strlen(self->target);
        memcpy(errstr+plen, self->target, len);

        plen += len;

        errstr[plen++] = ']';
        errstr[plen++] = ' ';
    }

    slen = MAX_STRING_LEN - plen - 1;

    Py_BEGIN_ALLOW_THREADS


    while (1) {
        if (l > slen) {
            memcpy(errstr+plen, s, slen);
            errstr[plen+slen] = '\n';
#if AP_SERVER_MAJORVERSION_NUMBER < 2
            fwrite(errstr, plen+slen+1, 1, logf);
            fflush(logf);
#else
            apr_file_write_full(logf, errstr, plen+slen+1, NULL);
            apr_file_flush(logf);
#endif
            s += slen;
            l -= slen;
        }
        else {
            memcpy(errstr+plen, s, l);
            errstr[plen+l] = '\n';
#if AP_SERVER_MAJORVERSION_NUMBER < 2
            fwrite(errstr, plen+l+1, 1, logf);
            fflush(logf);
#else
            apr_file_write_full(logf, errstr, plen+l+1, NULL);
            apr_file_flush(logf);
#endif
            break;
        }
    }

    Py_END_ALLOW_THREADS
}
