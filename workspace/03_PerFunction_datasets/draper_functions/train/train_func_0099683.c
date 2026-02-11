dhcp6_print(const u_char *cp, u_int length)
{
	struct dhcp6 *dh6;
	struct dhcp6_relay *dh6relay;
	const u_char *ep;
	u_char *extp;
	const char *name;

	printf("dhcp6");

	ep = (u_char *)snapend;
	if (cp + length < ep)
		ep = cp + length;

	dh6 = (struct dhcp6 *)cp;
	dh6relay = (struct dhcp6_relay *)cp;
	TCHECK(dh6->dh6_xid);
	switch (dh6->dh6_msgtype) {
	case DH6_SOLICIT:
		name = "solicit";
		break;
	case DH6_ADVERTISE:
		name = "advertise";
		break;
	case DH6_REQUEST:
		name = "request";
		break;
	case DH6_CONFIRM:
		name = "confirm";
		break;
	case DH6_RENEW:
		name = "renew";
		break;
	case DH6_REBIND:
		name = "rebind";
		break;
	case DH6_REPLY:
		name = "reply";
		break;
	case DH6_RELEASE:
		name = "release";
		break;
	case DH6_DECLINE:
		name = "decline";
		break;
	case DH6_RECONFIGURE:
		name = "reconfigure";
		break;
	case DH6_INFORM_REQ:
		name= "inf-req";
		break;
	case DH6_RELAY_FORW:
		name= "relay-fwd";
		break;
	case DH6_RELAY_REPLY:
		name= "relay-reply";
		break;
	default:
		name = NULL;
		break;
	}

	if (!vflag) {
		if (name)
			printf(" %s", name);
		else if (dh6->dh6_msgtype != DH6_RELAY_FORW &&
		    dh6->dh6_msgtype != DH6_RELAY_REPLY) {
			printf(" msgtype-%u", dh6->dh6_msgtype);
		}
		return;
	}


	if (name)
		printf(" %s (", name);
	else
		printf(" msgtype-%u (", dh6->dh6_msgtype);
	if (dh6->dh6_msgtype != DH6_RELAY_FORW &&
	    dh6->dh6_msgtype != DH6_RELAY_REPLY) {
		printf("xid=%x", EXTRACT_32BITS(&dh6->dh6_xid) & DH6_XIDMASK);
		extp = (u_char *)(dh6 + 1);
		dhcp6opt_print(extp, ep);
	} else {
		struct in6_addr addr6;

		TCHECK(dh6relay->dh6relay_peeraddr);

		memcpy(&addr6, dh6relay->dh6relay_linkaddr, sizeof (addr6));
		printf("linkaddr=%s", ip6addr_string(&addr6));

		memcpy(&addr6, dh6relay->dh6relay_peeraddr, sizeof (addr6));
		printf(" peeraddr=%s", ip6addr_string(&addr6));

		dhcp6opt_print((u_char *)(dh6relay + 1), ep);
	}

	printf(")");
	return;

trunc:
	printf("[|dhcp6]");
}
