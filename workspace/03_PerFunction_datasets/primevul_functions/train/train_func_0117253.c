static void wsgi_hook_init(server_rec *s, apr_pool_t *p)
{
    char package[128];


    sprintf(package, "mod_wsgi/%s", MOD_WSGI_VERSION_STRING);

    ap_add_version_component(package);


    if (!Py_IsInitialized()) {
        char buffer[256];
        const char *token = NULL;
        const char *version = NULL;

        version = Py_GetVersion();

        token = version;
        while (*token && *token != ' ')
            token++;

        strcpy(buffer, "Python/");
        strncat(buffer, version, token - version);

        ap_add_version_component(buffer);
    }


    wsgi_server = s;


    wsgi_parent_pid = getpid();


    wsgi_multiprocess = 1;
    wsgi_multithread = 0;


    wsgi_server_config = ap_get_module_config(s->module_config, &wsgi_module);


    wsgi_python_version();


    if (!wsgi_python_after_fork)
        wsgi_python_init(p);
}
