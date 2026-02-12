static void wsgi_hook_child_init(server_rec *s, apr_pool_t *p)
{
    if (wsgi_python_required) {


        if (wsgi_python_after_fork)
            wsgi_python_init(p);


        wsgi_python_child_init(p);
    }
}
