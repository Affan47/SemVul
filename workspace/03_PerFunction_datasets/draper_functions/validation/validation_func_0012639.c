_eio_eet_read_direct_job(void *data, Ecore_Thread *thread)
{
   Eio_Eet_Read *er = data;

   er->result = (void*) eet_read_direct(er->ef, er->name, &er->size);
   if (!er->result) eio_file_thread_error(&er->common, thread);
}
