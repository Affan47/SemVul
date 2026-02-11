_eio_eet_open_job(void *data, Ecore_Thread *thread)
{
   Eio_Eet_Open *eet = data;

   eet->result = eet_open(eet->filename, eet->mode);
   if (!eet->result) eio_file_thread_error(&eet->common, thread);
}
