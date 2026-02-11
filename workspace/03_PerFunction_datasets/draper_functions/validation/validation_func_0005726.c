gli_delete_stream(stream_t *str)
{
  stream_t *prev, *next;

  if (gli_unregister_obj)
    (*gli_unregister_obj)(str, gidisp_Class_Stream, str->disprock);

  str->type = -1;
  str->readcount = 0;
  str->writecount = 0;
  str->win = NULL;
  str->buf = NULL;
  str->bufptr = NULL;
  str->bufend = NULL;
  str->bufeof = NULL;
  str->buflen = 0;

  prev = str->prev;
  next = str->next;
  str->prev = NULL;
  str->next = NULL;

  if (prev)
    prev->next = next;
  else
    gli_streamlist = next;
  if (next)
    next->prev = prev;

  free(str);
}
