_sasl_get_plugin(const char *file,
		     const sasl_callback_t *verifyfile_cb,
		     void **libraryptr)
{
#ifdef DO_DLOPEN
    int r = 0;
    int flag;
    void *library;
    lib_list_t *newhead;

    r = ((sasl_verifyfile_t *)(verifyfile_cb->proc))
		    (verifyfile_cb->context, file, SASL_VRFY_PLUGIN);
    if (r != SASL_OK) return r;

#ifdef RTLD_NOW
    flag = RTLD_NOW;
#else
    flag = 0;
#endif

    newhead = sasl_ALLOC(sizeof(lib_list_t));
    if(!newhead) return SASL_NOMEM;

    if (!(library = dlopen(file, flag))) {
	_sasl_log(NULL, SASL_LOG_ERR,
		  "unable to dlopen %s: %s", file, dlerror());
	sasl_FREE(newhead);
	return SASL_FAIL;
    }

    newhead->library = library;
    newhead->next = lib_list_head;
    lib_list_head = newhead;

    *libraryptr = library;
    return SASL_OK;
#else
    return SASL_FAIL;
#endif
}
