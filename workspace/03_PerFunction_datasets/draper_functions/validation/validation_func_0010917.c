handle_rpc_aux(GUI_RPC_CONN& grc) {
    int retval = 0;
    grc.mfin.init_buf_read(grc.request_msg);
    if (grc.xp.get_tag()) return ERR_XML_PARSE;
    if (grc.xp.get_tag()) return ERR_XML_PARSE;
    for (unsigned int i=0; i<sizeof(gui_rpcs)/sizeof(GUI_RPC); i++) {
        GUI_RPC& gr = gui_rpcs[i];
        if (!grc.xp.match_tag(gr.req_tag) && !grc.xp.match_tag(gr.alt_req_tag)) {
            continue;
        }
        if (gr.auth_required && grc.auth_needed) {
            auth_failure(grc.mfout);
            if (grc.sent_unauthorized) {
                retval = ERR_AUTHENTICATOR;
            }
            grc.sent_unauthorized = true;
            return retval;
        }
        if (gr.enable_network)  {
            gstate.gui_rpcs.time_of_last_rpc_needing_network = gstate.now;
        }
        (*gr.handler)(grc);
        return 0;;
    }
    grc.mfout.printf("<error>unrecognized op: %s</error>\n", grc.xp.parsed_tag);
    return 0;
}
