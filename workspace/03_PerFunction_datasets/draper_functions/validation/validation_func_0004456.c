opal_progress_unregister(opal_progress_callback_t cb)
{
    size_t i;
    int ret = OPAL_ERR_NOT_FOUND;

#if OPAL_ENABLE_MULTI_THREADS
    opal_atomic_lock(&progress_lock);
#endif

    for (i = 0 ; i < callbacks_len ; ++i) {
        if (cb == callbacks[i]) {
            callbacks[i] = &fake_cb;
            ret = OPAL_SUCCESS;
            break;
        }
    }


    if (OPAL_SUCCESS == ret) {
        if (callbacks_len > 1 ) {

            for ( ; i < callbacks_len - 1 ; ++i) {
                callbacks[i] = callbacks[i + 1];
            }
        }
        callbacks[callbacks_len - 1] = &fake_cb;
        callbacks_len--;
    }

#if OPAL_ENABLE_MULTI_THREADS
    opal_atomic_unlock(&progress_lock);
#endif

    return ret;
}
