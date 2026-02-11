krb5int_thread_support_fini (void)
{
    if (! INITIALIZER_RAN (krb5int_thread_support_init))
        return;

#ifdef SHOW_INITFINI_FUNCS
    printf("krb5int_thread_support_fini\n");
#endif

#ifndef ENABLE_THREADS


#elif defined(_WIN32)


    TlsFree(tls_idx);
    DeleteCriticalSection(&key_lock);

#else

    if (! INITIALIZER_RAN(krb5int_thread_support_init))
        return;
    if (K5_PTHREADS_LOADED)
        pthread_key_delete(key);

    k5_mutex_destroy(&key_lock);

#endif

    krb5int_fini_fac();
}
