ipmi_pef_list_policies(struct ipmi_intf * intf)
{


	struct ipmi_rs * rsp;
	struct ipmi_rq req;
	struct pef_cfgparm_policy_table_entry * ptbl, * ptmp;
	uint32_t i;
	uint8_t wrk, ch, medium, tbl_size;

	tbl_size = ipmi_pef_get_policy_table(intf, &ptbl);
	if (!tbl_size)
		return;
	memset(&req, 0, sizeof(req));
	req.msg.netfn = IPMI_NETFN_APP;
	req.msg.cmd = IPMI_CMD_GET_CHANNEL_INFO;
	req.msg.data = &ch;
	req.msg.data_len = sizeof(ch);
	for (ptmp=ptbl, i=1; i<=tbl_size; i++, ptmp++) {
		if ((ptmp->entry.policy & PEF_POLICY_ENABLED) == PEF_POLICY_ENABLED) {
			if (i > 1)
				printf("\n");
			first_field = 1;
			ipmi_pef_print_dec("Alert policy table entry",
						(ptmp->data1 & PEF_POLICY_TABLE_ID_MASK));
			ipmi_pef_print_dec("Policy set",
						(ptmp->entry.policy & PEF_POLICY_ID_MASK) >> PEF_POLICY_ID_SHIFT);
			ipmi_pef_print_str("Policy entry rule",
						ipmi_pef_bit_desc(&pef_b2s_policies, (ptmp->entry.policy & PEF_POLICY_FLAGS_MASK)));

			if (ptmp->entry.alert_string_key & PEF_POLICY_EVENT_SPECIFIC) {
				ipmi_pef_print_str("Event-specific", "true");

			}
			wrk = ptmp->entry.chan_dest;


			ch = (wrk & PEF_POLICY_CHANNEL_MASK) >> PEF_POLICY_CHANNEL_SHIFT;
			rsp = ipmi_pef_msg_exchange(intf, &req, "Channel info");
			if (!rsp || rsp->data[0] != ch) {
				lprintf(LOG_ERR, " **Error retrieving %s",
					"Channel info");
				continue;
			}
			medium = rsp->data[1];
			ipmi_pef_print_dec("Channel number", ch);
			ipmi_pef_print_str("Channel medium",
						ipmi_pef_bit_desc(&pef_b2s_ch_medium, medium));


			wrk &= PEF_POLICY_DESTINATION_MASK;
			switch (medium) {
				case PEF_CH_MEDIUM_TYPE_LAN:
					ipmi_pef_print_lan_dest(intf, ch, wrk);
					break;
				case PEF_CH_MEDIUM_TYPE_SERIAL:
					ipmi_pef_print_serial_dest(intf, ch, wrk);
					break;
				default:
					ipmi_pef_print_dest(intf, ch, wrk);
					break;
			}
		}
	}
	free(ptbl);
}
