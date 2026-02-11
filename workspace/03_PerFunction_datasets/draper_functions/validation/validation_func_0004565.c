thread_writer_fct(void *args)
{
    struct s_headinfo headinfo;
    struct s_blockinfo blkinfo;
    carchwriter *ai=NULL;
    s64 blknum;
    int type;


    inc_secthreads();

    if ((ai=(carchwriter *)args)==NULL)
    {   errprintf("ai is NULL\n");
        goto thread_writer_fct_error;
    }
    if (archwriter_volpath(ai)!=0)
    {   msgprintf(MSG_STACK, "archwriter_volpath() failed\n");
        goto thread_writer_fct_error;
    }
    if (archwriter_create(ai)!=0)
    {   msgprintf(MSG_STACK, "archwriter_create(%s) failed\n", ai->basepath);
        goto thread_writer_fct_error;
    }
    if (archwriter_write_volheader(ai)!=0)
    {   msgprintf(MSG_STACK, "cannot write volume header: archwriter_write_volheader() failed\n");
        goto thread_writer_fct_error;
    }

    while (queue_get_end_of_queue(&g_queue)==false)
    {
        if ((blknum=queue_dequeue_first(&g_queue, &type, &headinfo, &blkinfo))<0 && blknum!=FSAERR_ENDOFFILE)
        {   msgprintf(MSG_STACK, "queue_dequeue_first()=%ld=%s failed\n", (long)blknum, error_int_to_string(blknum));
            goto thread_writer_fct_error;
        }
        else if (blknum>0)
        {
            switch (type)
            {
                case QITEM_TYPE_BLOCK:
                    if (archwriter_dowrite_block(ai, &blkinfo)!=0)
                    {   msgprintf(MSG_STACK, "archive_dowrite_block() failed\n");
                        goto thread_writer_fct_error;
                    }
                    free(blkinfo.blkdata);
                    break;
                case QITEM_TYPE_HEADER:
                    if (archwriter_dowrite_header(ai, &headinfo)!=0)
                    {   msgprintf(MSG_STACK, "archive_write_header() failed\n");
                        goto thread_writer_fct_error;
                    }
                    dico_destroy(headinfo.dico);
                    break;
                default:
                    errprintf("unexpected item type from queue: type=%d\n", type);
                    break;
            }
        }
    }


    if (archwriter_write_volfooter(ai, true)!=0)
    {   msgprintf(MSG_STACK, "cannot write volume footer: archio_write_volfooter() failed\n");
        goto thread_writer_fct_error;
    }
    archwriter_close(ai);
    msgprintf(MSG_DEBUG1, "THREAD-WRITER: exit success\n");
    dec_secthreads();
    return NULL;

thread_writer_fct_error:
    msgprintf(MSG_DEBUG1, "THREAD-WRITER: exit remove\n");
    set_stopfillqueue();
    while (queue_get_end_of_queue(&g_queue)==false)
        queue_destroy_first_item(&g_queue);
    archwriter_close(ai);
    dec_secthreads();
    return NULL;
}
