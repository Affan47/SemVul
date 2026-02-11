PyInit_syslog(void)
{
    PyObject *m;


    m = PyModule_Create(&syslogmodule);
    if (m == NULL)
        return NULL;


    PyModule_AddIntConstant(m, "LOG_EMERG",       LOG_EMERG);
    PyModule_AddIntConstant(m, "LOG_ALERT",       LOG_ALERT);
    PyModule_AddIntConstant(m, "LOG_CRIT",        LOG_CRIT);
    PyModule_AddIntConstant(m, "LOG_ERR",         LOG_ERR);
    PyModule_AddIntConstant(m, "LOG_WARNING", LOG_WARNING);
    PyModule_AddIntConstant(m, "LOG_NOTICE",  LOG_NOTICE);
    PyModule_AddIntConstant(m, "LOG_INFO",        LOG_INFO);
    PyModule_AddIntConstant(m, "LOG_DEBUG",       LOG_DEBUG);


    PyModule_AddIntConstant(m, "LOG_PID",         LOG_PID);
    PyModule_AddIntConstant(m, "LOG_CONS",        LOG_CONS);
    PyModule_AddIntConstant(m, "LOG_NDELAY",  LOG_NDELAY);
#ifdef LOG_ODELAY
    PyModule_AddIntConstant(m, "LOG_ODELAY",  LOG_ODELAY);
#endif
#ifdef LOG_NOWAIT
    PyModule_AddIntConstant(m, "LOG_NOWAIT",  LOG_NOWAIT);
#endif
#ifdef LOG_PERROR
    PyModule_AddIntConstant(m, "LOG_PERROR",  LOG_PERROR);
#endif


    PyModule_AddIntConstant(m, "LOG_KERN",        LOG_KERN);
    PyModule_AddIntConstant(m, "LOG_USER",        LOG_USER);
    PyModule_AddIntConstant(m, "LOG_MAIL",        LOG_MAIL);
    PyModule_AddIntConstant(m, "LOG_DAEMON",  LOG_DAEMON);
    PyModule_AddIntConstant(m, "LOG_AUTH",        LOG_AUTH);
    PyModule_AddIntConstant(m, "LOG_LPR",         LOG_LPR);
    PyModule_AddIntConstant(m, "LOG_LOCAL0",  LOG_LOCAL0);
    PyModule_AddIntConstant(m, "LOG_LOCAL1",  LOG_LOCAL1);
    PyModule_AddIntConstant(m, "LOG_LOCAL2",  LOG_LOCAL2);
    PyModule_AddIntConstant(m, "LOG_LOCAL3",  LOG_LOCAL3);
    PyModule_AddIntConstant(m, "LOG_LOCAL4",  LOG_LOCAL4);
    PyModule_AddIntConstant(m, "LOG_LOCAL5",  LOG_LOCAL5);
    PyModule_AddIntConstant(m, "LOG_LOCAL6",  LOG_LOCAL6);
    PyModule_AddIntConstant(m, "LOG_LOCAL7",  LOG_LOCAL7);

#ifndef LOG_SYSLOG
#define LOG_SYSLOG              LOG_DAEMON
#endif
#ifndef LOG_NEWS
#define LOG_NEWS                LOG_MAIL
#endif
#ifndef LOG_UUCP
#define LOG_UUCP                LOG_MAIL
#endif
#ifndef LOG_CRON
#define LOG_CRON                LOG_DAEMON
#endif

    PyModule_AddIntConstant(m, "LOG_SYSLOG",  LOG_SYSLOG);
    PyModule_AddIntConstant(m, "LOG_CRON",        LOG_CRON);
    PyModule_AddIntConstant(m, "LOG_UUCP",        LOG_UUCP);
    PyModule_AddIntConstant(m, "LOG_NEWS",        LOG_NEWS);

#ifdef LOG_AUTHPRIV
    PyModule_AddIntConstant(m, "LOG_AUTHPRIV",    LOG_AUTHPRIV);
#endif

    return m;
}
