session_request_query(dns_session_t *session, dns_sock_buf_t *sbuf)
{
    int rcode;
    dns_msg_question_t *q;

    q = &session->sess_question;

    if (!DNS_TYPE_QMETA(q->mq_type) || q->mq_type == DNS_TYPE_ALL)
        rcode = session_request_query_normal(session, sbuf);
    else {
        switch (q->mq_type) {
        case DNS_TYPE_AXFR:
            rcode = session_request_query_axfr(session, sbuf);
            break;
        default:
            rcode = DNS_RCODE_NOTIMP;
            break;
        }
    }

    return rcode;
}
