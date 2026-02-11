slapi_counter_destroy(Slapi_Counter **counter)
{
    if ((counter != NULL) && (*counter != NULL)) {
#ifndef ATOMIC_64BIT_OPERATIONS
        slapi_destroy_mutex((*counter)->lock);
#endif
        slapi_ch_free((void **)counter);
    }
}
