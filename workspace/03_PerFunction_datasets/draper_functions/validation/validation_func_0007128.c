mca_pml_bfo_completion_sendreq_has_error(mca_pml_bfo_send_request_t* sendreq,
					      int status,
					      mca_btl_base_module_t* btl,
					      int type,
					      char *description)
{
    opal_output_verbose(30, mca_pml_bfo_output,
                        "%s: completion: sendreq has error, outstanding events=%d, "
                        "PML=%d, RQS=%d, src_req=%p, dst_req=%p, status=%d, peer=%d",
                        description,
                        sendreq->req_events, (uint16_t)sendreq->req_send.req_base.req_sequence,
                        sendreq->req_restartseq, (void *)sendreq,
                        sendreq->req_recv.pval,
                        status, sendreq->req_send.req_base.req_peer);
    if (0 == sendreq->req_events) {
        mca_pml_bfo_send_request_rndvrestartnotify(sendreq, false,
                                                   type, status, btl);
    }
}
