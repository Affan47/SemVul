static void Log_call(LogObject *self, const char *s, int l)
{


    if (self->r) {
        Py_BEGIN_ALLOW_THREADS
        ap_log_rerror(APLOG_MARK, WSGI_LOG_LEVEL(self->level),
                      self->r, "%s", s);
        Py_END_ALLOW_THREADS
    }
    else {
        Py_BEGIN_ALLOW_THREADS
        ap_log_error(APLOG_MARK, WSGI_LOG_LEVEL(self->level),
                     wsgi_server, "%s", s);
        Py_END_ALLOW_THREADS
    }
}
