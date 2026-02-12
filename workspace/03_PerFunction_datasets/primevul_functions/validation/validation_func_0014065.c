tcp_analyze_sequence_number(packet_info *pinfo, guint32 seq, guint32 ack, guint32 seglen, guint16 flags, guint32 window, struct tcp_analysis *tcpd)
{
    tcp_unacked_t *ual=NULL;
    tcp_unacked_t *prevual=NULL;
    guint32 nextseq;
    int ackcount;

#if 0
    printf("\nanalyze_sequence numbers   frame:%u\n",pinfo->num);
    printf("FWD list lastflags:0x%04x base_seq:%u: nextseq:%u lastack:%u\n",tcpd->fwd->lastsegmentflags,tcpd->fwd->base_seq,tcpd->fwd->tcp_analyze_seq_info->nextseq,tcpd->rev->tcp_analyze_seq_info->lastack);
    for(ual=tcpd->fwd->tcp_analyze_seq_info->segments; ual; ual=ual->next)
            printf("Frame:%d Seq:%u Nextseq:%u\n",ual->frame,ual->seq,ual->nextseq);
    printf("REV list lastflags:0x%04x base_seq:%u nextseq:%u lastack:%u\n",tcpd->rev->lastsegmentflags,tcpd->rev->base_seq,tcpd->rev->tcp_analyze_seq_info->nextseq,tcpd->fwd->tcp_analyze_seq_info->lastack);
    for(ual=tcpd->rev->tcp_analyze_seq_info->segments; ual; ual=ual->next)
            printf("Frame:%d Seq:%u Nextseq:%u\n",ual->frame,ual->seq,ual->nextseq);
#endif

    if (!tcpd) {
        return;
    }


    if( !(tcpd->fwd->static_flags & TCP_S_BASE_SEQ_SET)) {
        if(flags & TH_SYN) {
            tcpd->fwd->base_seq = seq;
            tcpd->fwd->static_flags |= (flags & TH_ACK) ? TCP_S_SAW_SYNACK : TCP_S_SAW_SYN;
        }
        else {
            tcpd->fwd->base_seq = seq-1;
        }
        tcpd->fwd->static_flags |= TCP_S_BASE_SEQ_SET;
    }


    if( !(tcpd->rev->static_flags & TCP_S_BASE_SEQ_SET) && (flags & TH_ACK) ) {
        tcpd->rev->base_seq = ack-1;
        tcpd->rev->static_flags |= TCP_S_BASE_SEQ_SET;
    }

    if( flags & TH_ACK ) {
        tcpd->rev->valid_bif = 1;
    }


    if( seglen==1
    &&  seq==tcpd->fwd->tcp_analyze_seq_info->nextseq
    &&  tcpd->rev->window==0 ) {
        if(!tcpd->ta) {
            tcp_analyze_get_acked_struct(pinfo->num, seq, ack, TRUE, tcpd);
        }
        tcpd->ta->flags|=TCP_A_ZERO_WINDOW_PROBE;
        goto finished_fwd;
    }


    if( window==0
    && (flags&(TH_RST|TH_FIN|TH_SYN))==0 ) {
        if(!tcpd->ta) {
            tcp_analyze_get_acked_struct(pinfo->num, seq, ack, TRUE, tcpd);
        }
        tcpd->ta->flags|=TCP_A_ZERO_WINDOW;
    }


    if( tcpd->fwd->tcp_analyze_seq_info->nextseq
    &&  GT_SEQ(seq, tcpd->fwd->tcp_analyze_seq_info->nextseq)
    &&  (flags&(TH_RST))==0 ) {
        if(!tcpd->ta) {
            tcp_analyze_get_acked_struct(pinfo->num, seq, ack, TRUE, tcpd);
        }
        tcpd->ta->flags|=TCP_A_LOST_PACKET;


        tcpd->fwd->valid_bif = 0;
    }


    if( (seglen==0||seglen==1)
    &&  seq==(tcpd->fwd->tcp_analyze_seq_info->nextseq-1)
    &&  (flags&(TH_SYN|TH_FIN|TH_RST))==0 ) {
        if(!tcpd->ta) {
            tcp_analyze_get_acked_struct(pinfo->num, seq, ack, TRUE, tcpd);
        }
        tcpd->ta->flags|=TCP_A_KEEP_ALIVE;
    }


    if( seglen==0
    &&  window
    &&  window!=tcpd->fwd->window
    &&  seq==tcpd->fwd->tcp_analyze_seq_info->nextseq
    &&  ack==tcpd->fwd->tcp_analyze_seq_info->lastack
    &&  (flags&(TH_SYN|TH_FIN|TH_RST))==0 ) {
        if(!tcpd->ta) {
            tcp_analyze_get_acked_struct(pinfo->num, seq, ack, TRUE, tcpd);
        }
        tcpd->ta->flags|=TCP_A_WINDOW_UPDATE;
    }


    if( seglen>0
    &&  tcpd->rev->win_scale!=-1
    &&  (seq+seglen)==(tcpd->rev->tcp_analyze_seq_info->lastack+(tcpd->rev->window<<(tcpd->rev->win_scale==-2?0:tcpd->rev->win_scale)))
    &&  (flags&(TH_SYN|TH_FIN|TH_RST))==0 ) {
        if(!tcpd->ta) {
            tcp_analyze_get_acked_struct(pinfo->num, seq, ack, TRUE, tcpd);
        }
        tcpd->ta->flags|=TCP_A_WINDOW_FULL;
    }


    if( seglen==0
    &&  window
    &&  window==tcpd->fwd->window
    &&  seq==tcpd->fwd->tcp_analyze_seq_info->nextseq
    &&  ack==tcpd->fwd->tcp_analyze_seq_info->lastack
    && (tcpd->rev->lastsegmentflags&TCP_A_KEEP_ALIVE)
    &&  (flags&(TH_SYN|TH_FIN|TH_RST))==0 ) {
        if(!tcpd->ta) {
            tcp_analyze_get_acked_struct(pinfo->num, seq, ack, TRUE, tcpd);
        }
        tcpd->ta->flags|=TCP_A_KEEP_ALIVE_ACK;
        goto finished_fwd;
    }


    if( seglen==0
    &&  window==0
    &&  window==tcpd->fwd->window
    &&  seq==tcpd->fwd->tcp_analyze_seq_info->nextseq
    &&  ack==tcpd->fwd->tcp_analyze_seq_info->lastack
    && (tcpd->rev->lastsegmentflags&TCP_A_ZERO_WINDOW_PROBE)
    &&  (flags&(TH_SYN|TH_FIN|TH_RST))==0 ) {
        if(!tcpd->ta) {
            tcp_analyze_get_acked_struct(pinfo->num, seq, ack, TRUE, tcpd);
        }
        tcpd->ta->flags|=TCP_A_ZERO_WINDOW_PROBE_ACK;
        goto finished_fwd;
    }


    if( seglen==0
    &&  window
    &&  window==tcpd->fwd->window
    &&  seq==tcpd->fwd->tcp_analyze_seq_info->nextseq
    &&  ack==tcpd->fwd->tcp_analyze_seq_info->lastack
    &&  (flags&(TH_SYN|TH_FIN|TH_RST))==0 ) {
        tcpd->fwd->tcp_analyze_seq_info->dupacknum++;
        if(!tcpd->ta) {
            tcp_analyze_get_acked_struct(pinfo->num, seq, ack, TRUE, tcpd);
        }
        tcpd->ta->flags|=TCP_A_DUPLICATE_ACK;
        tcpd->ta->dupack_num=tcpd->fwd->tcp_analyze_seq_info->dupacknum;
        tcpd->ta->dupack_frame=tcpd->fwd->tcp_analyze_seq_info->lastnondupack;
    }


finished_fwd:

    if( ack != tcpd->fwd->tcp_analyze_seq_info->lastack ) {
        tcpd->fwd->tcp_analyze_seq_info->lastnondupack=pinfo->num;
        tcpd->fwd->tcp_analyze_seq_info->dupacknum=0;
    }


    if( tcpd->rev->tcp_analyze_seq_info->maxseqtobeacked
    &&  GT_SEQ(ack, tcpd->rev->tcp_analyze_seq_info->maxseqtobeacked )
    &&  (flags&(TH_ACK))!=0 ) {
        if(!tcpd->ta) {
            tcp_analyze_get_acked_struct(pinfo->num, seq, ack, TRUE, tcpd);
        }
        tcpd->ta->flags|=TCP_A_ACK_LOST_PACKET;


        tcpd->rev->tcp_analyze_seq_info->maxseqtobeacked=tcpd->rev->tcp_analyze_seq_info->nextseq;
    }


    if (seglen>0 || flags&(TH_SYN|TH_FIN)) {
        gboolean seq_not_advanced = tcpd->fwd->tcp_analyze_seq_info->nextseq
                && (LT_SEQ(seq, tcpd->fwd->tcp_analyze_seq_info->nextseq));

        guint64 t;
        guint64 ooo_thres;

        if(tcpd->ta && (tcpd->ta->flags&TCP_A_KEEP_ALIVE) ) {
            goto finished_checking_retransmission_type;
        }


        if (seglen > 1 && tcpd->fwd->tcp_analyze_seq_info->nextseq - 1 == seq) {
            seq_not_advanced = FALSE;
        }


        t=(pinfo->abs_ts.secs-tcpd->rev->tcp_analyze_seq_info->lastacktime.secs)*1000000000;
        t=t+(pinfo->abs_ts.nsecs)-tcpd->rev->tcp_analyze_seq_info->lastacktime.nsecs;
        if( seq_not_advanced
        &&  tcpd->rev->tcp_analyze_seq_info->dupacknum>=2
        &&  tcpd->rev->tcp_analyze_seq_info->lastack==seq
        &&  t<20000000 ) {
            if(!tcpd->ta) {
                tcp_analyze_get_acked_struct(pinfo->num, seq, ack, TRUE, tcpd);
            }
            tcpd->ta->flags|=TCP_A_FAST_RETRANSMISSION;
            goto finished_checking_retransmission_type;
        }


        t=(pinfo->abs_ts.secs-tcpd->fwd->tcp_analyze_seq_info->nextseqtime.secs)*1000000000;
        t=t+(pinfo->abs_ts.nsecs)-tcpd->fwd->tcp_analyze_seq_info->nextseqtime.nsecs;
        if (tcpd->ts_first_rtt.nsecs == 0 && tcpd->ts_first_rtt.secs == 0) {
            ooo_thres = 3000000;
        } else {
            ooo_thres = tcpd->ts_first_rtt.nsecs + tcpd->ts_first_rtt.secs*1000000000;
        }

        if( seq_not_advanced
        && t < ooo_thres
        && tcpd->fwd->tcp_analyze_seq_info->nextseq != seq + seglen ) {
            if(!tcpd->ta) {
                tcp_analyze_get_acked_struct(pinfo->num, seq, ack, TRUE, tcpd);
            }
            tcpd->ta->flags|=TCP_A_OUT_OF_ORDER;
            goto finished_checking_retransmission_type;
        }


        if ( seglen > 0
        && tcpd->rev->tcp_analyze_seq_info->lastack
        && LE_SEQ(seq + seglen, tcpd->rev->tcp_analyze_seq_info->lastack) ) {
            if(!tcpd->ta){
                tcp_analyze_get_acked_struct(pinfo->num, seq, ack, TRUE, tcpd);
            }
            tcpd->ta->flags|=TCP_A_SPURIOUS_RETRANSMISSION;
            goto finished_checking_retransmission_type;
        }

        if (seq_not_advanced) {

            if(!tcpd->ta) {
                tcp_analyze_get_acked_struct(pinfo->num, seq, ack, TRUE, tcpd);
            }
            tcpd->ta->flags|=TCP_A_RETRANSMISSION;
            nstime_delta(&tcpd->ta->rto_ts, &pinfo->abs_ts, &tcpd->fwd->tcp_analyze_seq_info->nextseqtime);
            tcpd->ta->rto_frame=tcpd->fwd->tcp_analyze_seq_info->nextseqframe;
        }
    }

finished_checking_retransmission_type:

    nextseq = seq+seglen;
    if ((seglen || flags&(TH_SYN|TH_FIN)) && tcpd->fwd->tcp_analyze_seq_info->segment_count < TCP_MAX_UNACKED_SEGMENTS) {


        ual = wmem_new(wmem_file_scope(), tcp_unacked_t);
        ual->next=tcpd->fwd->tcp_analyze_seq_info->segments;
        tcpd->fwd->tcp_analyze_seq_info->segments=ual;
        tcpd->fwd->tcp_analyze_seq_info->segment_count++;
        ual->frame=pinfo->num;
        ual->seq=seq;
        ual->ts=pinfo->abs_ts;


        if( (flags&(TH_SYN|TH_FIN)) ) {
            nextseq+=1;
        }
        ual->nextseq=nextseq;
    }


    if(GT_SEQ(nextseq, tcpd->fwd->tcp_analyze_seq_info->nextseq) || !tcpd->fwd->tcp_analyze_seq_info->nextseq) {
        if( !tcpd->ta || !(tcpd->ta->flags&TCP_A_ZERO_WINDOW_PROBE) ) {
            tcpd->fwd->tcp_analyze_seq_info->nextseq=nextseq;
            tcpd->fwd->tcp_analyze_seq_info->nextseqframe=pinfo->num;
            tcpd->fwd->tcp_analyze_seq_info->nextseqtime.secs=pinfo->abs_ts.secs;
            tcpd->fwd->tcp_analyze_seq_info->nextseqtime.nsecs=pinfo->abs_ts.nsecs;
        }
    }


    if(EQ_SEQ(seq, tcpd->fwd->tcp_analyze_seq_info->maxseqtobeacked) || !tcpd->fwd->tcp_analyze_seq_info->maxseqtobeacked) {
        if( !tcpd->ta || !(tcpd->ta->flags&TCP_A_ZERO_WINDOW_PROBE) ) {
            tcpd->fwd->tcp_analyze_seq_info->maxseqtobeacked=tcpd->fwd->tcp_analyze_seq_info->nextseq;
        }
    }


    tcpd->fwd->window=window;
    tcpd->fwd->tcp_analyze_seq_info->lastack=ack;
    tcpd->fwd->tcp_analyze_seq_info->lastacktime.secs=pinfo->abs_ts.secs;
    tcpd->fwd->tcp_analyze_seq_info->lastacktime.nsecs=pinfo->abs_ts.nsecs;


    if(tcpd->ta) {
        tcpd->fwd->lastsegmentflags=tcpd->ta->flags;
    } else {
        tcpd->fwd->lastsegmentflags=0;
    }


    ackcount=0;
    prevual = NULL;
    ual = tcpd->rev->tcp_analyze_seq_info->segments;
    while(ual) {
        tcp_unacked_t *tmpual;


        if(ack==ual->nextseq) {
            tcp_analyze_get_acked_struct(pinfo->num, seq, ack, TRUE, tcpd);
            tcpd->ta->frame_acked=ual->frame;
            nstime_delta(&tcpd->ta->ts, &pinfo->abs_ts, &ual->ts);
        }

        else if (GT_SEQ(ack, ual->seq) && LE_SEQ(ack, ual->nextseq)) {
            ual->seq = ack;
            continue;
        }

        else if (GT_SEQ(ual->nextseq,ack)) {
            prevual = ual;
            ual = ual->next;
            continue;
        }


        ackcount++;
        tmpual=ual->next;

        if (tcpd->rev->scps_capable) {

          if ((ual->nextseq - ual->seq) > tcpd->fwd->maxsizeacked) {
            tcpd->fwd->maxsizeacked = (ual->nextseq - ual->seq);
          }
        }

        if (!prevual) {
            tcpd->rev->tcp_analyze_seq_info->segments = tmpual;
        }
        else{
            prevual->next = tmpual;
        }
        wmem_free(wmem_file_scope(), ual);
        ual = tmpual;
        tcpd->rev->tcp_analyze_seq_info->segment_count--;
    }


    ual=tcpd->fwd->tcp_analyze_seq_info->segments;
    if (tcp_track_bytes_in_flight && seglen!=0 && ual && tcpd->fwd->valid_bif) {
        guint32 first_seq, last_seq, in_flight;

        first_seq = ual->seq - tcpd->fwd->base_seq;
        last_seq = ual->nextseq - tcpd->fwd->base_seq;
        while (ual) {
            if ((ual->nextseq-tcpd->fwd->base_seq)>last_seq) {
                last_seq = ual->nextseq-tcpd->fwd->base_seq;
            }
            if ((ual->seq-tcpd->fwd->base_seq)<first_seq) {
                first_seq = ual->seq-tcpd->fwd->base_seq;
            }
            ual = ual->next;
        }
        in_flight = last_seq-first_seq;

        if (in_flight>0 && in_flight<2000000000) {
            if(!tcpd->ta) {
                tcp_analyze_get_acked_struct(pinfo->num, seq, ack, TRUE, tcpd);
            }
            tcpd->ta->bytes_in_flight = in_flight;
        }

        if((flags & TH_PUSH) && !tcpd->fwd->push_set_last) {
          tcpd->fwd->push_bytes_sent += seglen;
          tcpd->fwd->push_set_last = TRUE;
        } else if ((flags & TH_PUSH) && tcpd->fwd->push_set_last) {
          tcpd->fwd->push_bytes_sent = seglen;
          tcpd->fwd->push_set_last = TRUE;
        } else if (tcpd->fwd->push_set_last) {
          tcpd->fwd->push_bytes_sent = seglen;
          tcpd->fwd->push_set_last = FALSE;
        } else {
          tcpd->fwd->push_bytes_sent += seglen;
        }
        if(!tcpd->ta) {
          tcp_analyze_get_acked_struct(pinfo->fd->num, seq, ack, TRUE, tcpd);
        }
        tcpd->ta->push_bytes_sent = tcpd->fwd->push_bytes_sent;
    }

}
