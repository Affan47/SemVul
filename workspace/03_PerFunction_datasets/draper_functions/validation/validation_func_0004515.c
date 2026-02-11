print_rule(const struct fw_rule *fr, void *arg)
{
	struct protoent *pr;
	char proto[16], sport[16], dport[16], typecode[16];

	if (fr->fw_proto == 0)
		proto[0] = '\0';
	else if ((pr = getprotobynumber(fr->fw_proto)) == NULL)
		snprintf(proto, sizeof(proto), "%d ", fr->fw_proto);
	else
		snprintf(proto, sizeof(proto), "%s ", pr->p_name);

	sport[0] = dport[0] = typecode[0] = '\0';

	switch (fr->fw_proto) {
	case IP_PROTO_ICMP:
		if (fr->fw_sport[1] && fr->fw_dport[1])
			snprintf(typecode, sizeof(typecode), " %d/%d",
			    fr->fw_sport[0], fr->fw_dport[0]);
		else if (fr->fw_sport[1])
			snprintf(typecode, sizeof(typecode), " %d",
			    fr->fw_sport[0]);
		break;
	case IP_PROTO_TCP:
	case IP_PROTO_UDP:
		if (fr->fw_sport[0] == fr->fw_sport[1]) {
			snprintf(sport, sizeof(sport), ":%d", fr->fw_sport[0]);
		} else
			snprintf(sport, sizeof(sport), ":%d-%d",
			    fr->fw_sport[0], fr->fw_sport[1]);

		if (fr->fw_dport[0] == fr->fw_dport[1]) {
			snprintf(dport, sizeof(dport), ":%d", fr->fw_dport[0]);
		} else
			snprintf(dport, sizeof(dport), ":%d-%d",
			    fr->fw_dport[0], fr->fw_dport[1]);
		break;
	}
	printf("%s %s %s %s%s%s %s%s%s\n",
	    fr->fw_op == FW_OP_ALLOW ? "allow" : "block",
	    fr->fw_dir == FW_DIR_IN ? "in" : "out",
	    *fr->fw_device ? fr->fw_device : "any",
	    proto,
	    fr->fw_src.addr_type ? addr_ntoa(&fr->fw_src) : "",
	    sport,
	    fr->fw_dst.addr_type ? addr_ntoa(&fr->fw_dst) : "",
	    dport,
	    typecode);

	return (0);
}
