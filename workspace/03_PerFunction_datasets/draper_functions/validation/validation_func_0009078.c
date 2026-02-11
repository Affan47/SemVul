clear_index_cache_for_thread(MAILSTREAM *stream, PINETHRD_S *thrd, MSGNO_S *msgmap)
{
    unsigned long msgno;

    if(!thrd || !stream || thrd->rawno < 1L || thrd->rawno > stream->nmsgs)
      return;

    msgno = mn_raw2m(msgmap, thrd->rawno);

    clear_index_cache_ent(stream, msgno, 0);

    if(thrd->next)
      clear_index_cache_for_thread(stream, fetch_thread(stream, thrd->next),
				   msgmap);

    if(thrd->branch)
      clear_index_cache_for_thread(stream, fetch_thread(stream, thrd->branch),
				   msgmap);
}
