make_resume_reply_pdu(WSPMachine *m, List *headers)
{
    WSP_PDU *pdu;
    Octstr *os;

    pdu = wsp_pdu_create(Reply);


    pdu->u.Reply.status = wsp_convert_http_status_to_wsp_status(HTTP_OK);
    if (headers == NULL) {
        headers = http_create_empty_headers();
        pdu->u.Reply.headers = wsp_headers_pack(headers, 1, m->encoding_version);
        http_destroy_headers(headers);
    } else {
        pdu->u.Reply.headers = wsp_headers_pack(headers, 1, m->encoding_version);
    }
    pdu->u.Reply.data = octstr_create("");

    os = wsp_pdu_pack(pdu);
    wsp_pdu_destroy(pdu);

    return os;
}
