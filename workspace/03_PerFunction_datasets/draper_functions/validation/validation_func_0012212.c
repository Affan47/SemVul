pop_xdele(POP *p)
{
    MsgInfoList     *   mp;

    int msg_min, msg_max;
    int i;


    msg_min = atoi(p->pop_parm[1]);
    if(p->parm_count == 1)
	msg_max = msg_min;
    else
	msg_max = atoi(p->pop_parm[2]);

    if (msg_min < 1)
        return (pop_msg (p,POP_FAILURE,"Message %d does not exist.",msg_min));
    if(msg_max > p->msg_count)
        return (pop_msg (p,POP_FAILURE,"Message %d does not exist.",msg_max));
    for(i = msg_min; i <= msg_max; i++) {


	mp = &(p->mlp[i - 1]);


	if (mp->flags & DEL_FLAG)
	    continue;

	mp->flags |= DEL_FLAG;

#ifdef DEBUG
	if(p->debug)
	    pop_log(p, POP_DEBUG,
		    "Deleting message %u at offset %ld of length %ld\n",
		    mp->number, mp->offset, mp->length);
#endif


	p->msgs_deleted++;
	p->bytes_deleted += mp->length;
    }


    if (p->last_msg < msg_max) p->last_msg = msg_max;

    return (pop_msg (p,POP_SUCCESS,"Messages %d-%d has been deleted.",
		     msg_min, msg_max));

}
