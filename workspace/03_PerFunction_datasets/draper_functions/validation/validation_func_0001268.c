unpack_wdp_datagram_real(WAPEvent *datagram)
{
    WTP_PDU *pdu;
    WAPEvent *event;
    Octstr *data;

    gw_assert(datagram->type == T_DUnitdata_Ind);

    data = datagram->u.T_DUnitdata_Ind.user_data;

    if (truncated_datagram(datagram)) {
        warning(0, "WTP: got a truncated datagram, ignoring");
        return NULL;
    }

    pdu = wtp_pdu_unpack(data);


    if (pdu == NULL) {
        error(0, "WTP: cannot unpack pdu, dropping packet.");
        return NULL;
    }

    event = NULL;

    switch (pdu->type) {

    case Invoke:
        event = unpack_invoke(pdu, datagram->u.T_DUnitdata_Ind.addr_tuple);

        if (!wtp_event_is_for_responder(event)){
            debug("wap.wtp", 0, "WTP: Invoke when initiator. Message was");
            wap_event_destroy(event);
            event = pack_error(datagram);
        }
        break;

    case Segmented_invoke:
        event = unpack_segmented_invoke(pdu, datagram->u.T_DUnitdata_Ind.addr_tuple);
        break;

    case Result:
        event = unpack_result(pdu, datagram->u.T_DUnitdata_Ind.addr_tuple);

        if (wtp_event_is_for_responder(event)){
            debug("wap.wtp", 0, "WTP: Result when responder. Message was");
            wap_event_destroy(event);
            event = pack_error(datagram);
        }
        break;

    case Ack:
	    event = unpack_ack(pdu, datagram->u.T_DUnitdata_Ind.addr_tuple);
        break;

    case Negative_ack:
        event = unpack_negative_ack(pdu, datagram->u.T_DUnitdata_Ind.addr_tuple);
        break;

	case Abort:
	    event = unpack_abort(pdu, datagram->u.T_DUnitdata_Ind.addr_tuple);
        break;

	default:
	    event = pack_error(datagram);
	    debug("wap.wtp", 0, "WTP: Unhandled PDU type. Message was");
            wap_event_dump(datagram);
	    return event;
	}

    wtp_pdu_destroy(pdu);

    wap_event_assert(event);
    return event;
}
