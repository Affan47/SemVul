log_fsa_input(fsa_data_t * stored_msg)
{
    crm_trace("Processing queued input %d", stored_msg->id);
    if (stored_msg->fsa_cause == C_CCM_CALLBACK) {
        crm_trace("FSA processing CCM callback from %s", stored_msg->origin);

    } else if (stored_msg->fsa_cause == C_LRM_OP_CALLBACK) {
        crm_trace("FSA processing LRM callback from %s", stored_msg->origin);

    } else if (stored_msg->data == NULL) {
        crm_trace("FSA processing input from %s", stored_msg->origin);

    } else {
        ha_msg_input_t *ha_input = fsa_typed_data_adv(stored_msg, fsa_dt_ha_msg, __FUNCTION__);

        crm_trace("FSA processing XML message from %s", stored_msg->origin);
        crm_log_xml_trace(ha_input->xml, "FSA message data");
    }
}
