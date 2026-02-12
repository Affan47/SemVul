int fr_dhcp_encode(RADIUS_PACKET *packet, RADIUS_PACKET *original)
{
	int i, num_vps;
	uint8_t *p;
	VALUE_PAIR *vp;
	uint32_t lvalue, mms;
	size_t dhcp_size, length;
	dhcp_packet_t *dhcp;
	char buffer[1024];

	if (packet->data) return 0;

	packet->data = malloc(MAX_PACKET_SIZE);
	if (!packet->data) return -1;

	packet->data_len = MAX_PACKET_SIZE;

	if (packet->code == 0) packet->code = PW_DHCP_NAK;


	if (original) {
		packet->dst_ipaddr.af = AF_INET;
		packet->src_ipaddr.af = AF_INET;

		packet->dst_port = original->src_port;
		packet->src_port = original->dst_port;


		dhcp = (dhcp_packet_t *) original->data;

		if (dhcp->giaddr != htonl(INADDR_ANY)) {
			packet->dst_ipaddr.ipaddr.ip4addr.s_addr = dhcp->giaddr;

			if (dhcp->giaddr != htonl(INADDR_LOOPBACK)) {
				packet->dst_port = original->dst_port;
			} else {
				packet->dst_port = original->src_port;
			}

		} else if (packet->code == PW_DHCP_NAK) {
			packet->dst_ipaddr.ipaddr.ip4addr.s_addr = htonl(INADDR_BROADCAST);

		} else if (dhcp->ciaddr != htonl(INADDR_ANY)) {
			packet->dst_ipaddr.ipaddr.ip4addr.s_addr = dhcp->ciaddr;

		} else if ((dhcp->flags & 0x8000) != 0) {
			packet->dst_ipaddr.ipaddr.ip4addr.s_addr = htonl(INADDR_BROADCAST);

		} else if (packet->dst_ipaddr.ipaddr.ip4addr.s_addr == htonl(INADDR_ANY)) {
			packet->dst_ipaddr.ipaddr.ip4addr.s_addr = htonl(INADDR_BROADCAST);

		} else if (dhcp->yiaddr != htonl(INADDR_ANY)) {
			packet->dst_ipaddr.ipaddr.ip4addr.s_addr = dhcp->yiaddr;

		} else {

		}


		if (packet->src_ipaddr.ipaddr.ip4addr.s_addr == htonl(INADDR_BROADCAST)) {
			packet->src_ipaddr.ipaddr.ip4addr.s_addr = htonl(INADDR_ANY);
		}
	} else {
		memset(packet->data, 0, packet->data_len);
	}

	if (fr_debug_flag > 1) {
		char type_buf[64];
		const char *name = type_buf;
		char src_ip_buf[256], dst_ip_buf[256];

		if ((packet->code >= PW_DHCP_DISCOVER) &&
		    (packet->code <= PW_DHCP_INFORM)) {
			name = dhcp_message_types[packet->code - PW_DHCP_OFFSET];
		} else {
			snprintf(type_buf, sizeof(type_buf), "%d",
				 packet->code - PW_DHCP_OFFSET);
		}

		DEBUG("Sending %s of id %08x from %s:%d to %s:%d",
		       name, (unsigned int) packet->id,
		       inet_ntop(packet->src_ipaddr.af,
				 &packet->src_ipaddr.ipaddr,
				 src_ip_buf, sizeof(src_ip_buf)),
		       packet->src_port,
		       inet_ntop(packet->dst_ipaddr.af,
				 &packet->dst_ipaddr.ipaddr,
				 dst_ip_buf, sizeof(dst_ip_buf)),
		       packet->dst_port);
	}

	p = packet->data;

	mms = DEFAULT_PACKET_SIZE;

	if (original) {


		vp = pairfind(original->vps, DHCP2ATTR(57));
		if (vp && (vp->vp_integer > mms)) {
			mms = vp->vp_integer;

			if (mms > MAX_PACKET_SIZE) mms = MAX_PACKET_SIZE;
		}
	}


	vp = pairfind(packet->vps, DHCP2ATTR(90));
	if (vp) {
		if (vp->length < 2) {
			memset(vp->vp_octets + vp->length, 0,
			       2 - vp->length);
			vp->length = 2;
		}

		if (vp->length < 3) {
			struct timeval tv;

			gettimeofday(&tv, NULL);
			vp->vp_octets[2] = 0;
			timeval2ntp(&tv, vp->vp_octets + 3);
			vp->length = 3 + 8;
		}


		if (vp->vp_octets[0] == 0) {
			VALUE_PAIR *pass;
			vp->vp_octets[1] = 0;

			pass = pairfind(packet->vps, PW_CLEARTEXT_PASSWORD);
			if (pass) {
				length = pass->length;
				if ((length + 11) > sizeof(vp->vp_octets)) {
					length -= ((length + 11) - sizeof(vp->vp_octets));
				}
				memcpy(vp->vp_octets + 11, pass->vp_strvalue,
				       length);
				vp->length = length + 11;
			} else {
				vp->length = 11 + 8;
				memset(vp->vp_octets + 11, 0, 8);
				vp->length = 11 + 8;
			}
		} else {
			fr_strerror_printf("DHCP-Authentication %d unsupported",
				vp->vp_octets[0]);
		}
	}

	if (!original) {
		*p++ = 1;
	} else {
		*p++ = 2;
	}
	*p++ = 1;
	*p++ = 6;
	*p++ = 0;

	if (original) {
		memcpy(p, original->data + 4, 4);
	} else {
		lvalue = fr_rand();
		memcpy(p, &lvalue, 4);
	}
	p += 4;

	memset(p, 0, 2);
	p += 2;

	if (original) {
		memcpy(p, original->data + 10, 6);
	}


	vp = pairfind(packet->vps, DHCP2ATTR(262));
	if (vp) {
		p[0] |= (vp->vp_integer & 0xff00) >> 8;
		p[1] |= (vp->vp_integer & 0xff);
	}

	p += 6;


	vp = pairfind(packet->vps, DHCP2ATTR(264));
	if (vp) {
		lvalue = vp->vp_ipaddr;
	} else {
		lvalue = htonl(INADDR_ANY);
	}
	memcpy(p, &lvalue, 4);
	p += 4;

	vp = pairfind(packet->vps, DHCP2ATTR(265));
	if (!vp) vp = pairfind(packet->vps, DHCP2ATTR(54));
	if (vp) {
		lvalue = vp->vp_ipaddr;
	} else {
		lvalue = htonl(INADDR_ANY);
	}
	memcpy(p, &lvalue, 4);
	p += 4;

	if (original) {
		memcpy(p, original->data + 24, 4);
	} else {
		vp = pairfind(packet->vps, DHCP2ATTR(266));
		if (vp) {
			lvalue = vp->vp_ipaddr;
		} else {
			lvalue = htonl(INADDR_NONE);
		}
		memcpy(p, &lvalue, 4);
	}
	p += 4;

	if (original) {
		memcpy(p, original->data + 28, DHCP_CHADDR_LEN);
	} else {
		vp = pairfind(packet->vps, DHCP2ATTR(267));
		if (vp) {
			if (vp->length > DHCP_CHADDR_LEN) {
				memcpy(p, vp->vp_octets, DHCP_CHADDR_LEN);
			} else {
				memcpy(p, vp->vp_octets, vp->length);
			}
		}
	}
	p += DHCP_CHADDR_LEN;

	memset(p, 0, 192);
	p += 192;

	lvalue = htonl(DHCP_OPTION_MAGIC_NUMBER);
	memcpy(p, &lvalue, 4);
	p += 4;


	if (fr_debug_flag > 1) {
		uint8_t *pp = p;

		p = packet->data;

		for (i = 0; i < 14; i++) {
			vp = pairmake(dhcp_header_names[i], NULL, T_OP_EQ);
			if (!vp) {
				fr_strerror_printf("Parse error %s", fr_strerror());
				return -1;
			}

			switch (vp->type) {
			case PW_TYPE_BYTE:
				vp->vp_integer = p[0];
				vp->length = 1;
				break;

			case PW_TYPE_SHORT:
				vp->vp_integer = (p[0] << 8) | p[1];
				vp->length = 2;
				break;

			case PW_TYPE_INTEGER:
				memcpy(&vp->vp_integer, p, 4);
				vp->vp_integer = ntohl(vp->vp_integer);
				vp->length = 4;
				break;

			case PW_TYPE_IPADDR:
				memcpy(&vp->vp_ipaddr, p, 4);
				vp->length = 4;
				break;

			case PW_TYPE_STRING:
				memcpy(vp->vp_strvalue, p, dhcp_header_sizes[i]);
				vp->vp_strvalue[dhcp_header_sizes[i]] = '\0';
				vp->length = strlen(vp->vp_strvalue);
				break;

			case PW_TYPE_OCTETS:
				memcpy(vp->vp_octets, p, packet->data[2]);
				vp->length = packet->data[2];
				break;

			case PW_TYPE_ETHERNET:
				memcpy(vp->vp_ether, p, sizeof(vp->vp_ether));
				vp->length = sizeof(vp->vp_ether);
				break;

			default:
				fr_strerror_printf("Internal sanity check failed %d %d", vp->type, __LINE__);
				pairfree(&vp);
				break;
			}

			p += dhcp_header_sizes[i];

			vp_prints(buffer, sizeof(buffer), vp);
			fr_strerror_printf("\t%s", buffer);
			pairfree(&vp);
		}


		p = pp;
	}


	num_vps = 0;
	for (vp = packet->vps; vp != NULL; vp = vp->next) {
		num_vps++;
	}
	if (num_vps > 1) {
		VALUE_PAIR **array, **last;

		array = malloc(num_vps * sizeof(VALUE_PAIR *));

		i = 0;
		for (vp = packet->vps; vp != NULL; vp = vp->next) {
			array[i++] = vp;
		}


		qsort(array, (size_t) num_vps, sizeof(VALUE_PAIR *),
		      attr_cmp);

		last = &packet->vps;
		for (i = 0; i < num_vps; i++) {
			*last = array[i];
			array[i]->next = NULL;
			last = &(array[i]->next);
		}
		free(array);
	}

	p[0] = 0x35;
	p[1] = 1;
	p[2] = packet->code - PW_DHCP_OFFSET;
	p += 3;


	vp = packet->vps;
	while (vp) {
		int num_entries = 1;

		VALUE_PAIR *same;
		uint8_t *plength, *pattr;

		if (!IS_DHCP_ATTR(vp)) goto next;
		if (vp->attribute == DHCP2ATTR(53)) goto next;
		if (((vp->attribute & 0xffff) > 255) &&
		    (DHCP_BASE_ATTR(vp->attribute) != PW_DHCP_OPTION_82)) goto next;

		length = vp->length;

		for (same = vp->next; same != NULL; same = same->next) {
			if (same->attribute != vp->attribute) break;
			num_entries++;
		}


		if ((vp->type == PW_TYPE_ETHERNET) &&
		    (vp->length == 6) &&
		    (num_entries == 1)) {
			vp->type = PW_TYPE_OCTETS;
			memmove(vp->vp_octets + 1, vp->vp_octets, 6);
			vp->vp_octets[0] = 1;
		}

		pattr = p;
		*(p++) = vp->attribute & 0xff;
		plength = p;
		*(p++) = 0;

		for (i = 0; i < num_entries; i++) {
			if (fr_debug_flag > 1) {
				vp_prints(buffer, sizeof(buffer), vp);
				fr_strerror_printf("\t%s", buffer);
			}

			if (vp->flags.is_tlv) {
				VALUE_PAIR *tlv = fr_dhcp_vp2suboption(vp);
				if (vp) {
					tlv->next = vp->next;
					vp->next = tlv;
				}


				vp = vp->next;
			}

			length = fr_dhcp_vp2attr(vp, p, 0);


			if (length > 255) {
				fr_strerror_printf("WARNING Ignoring too long attribute %s!", vp->name);
				break;
			}


			if ((*plength + length) > 255) {
				fr_strerror_printf("WARNING Ignoring too long attribute %s!", vp->name);
				break;
			}

			*plength += length;
			p += length;

			if (vp->next &&
			    (vp->next->attribute == vp->attribute))
				vp = vp->next;
		}

	next:
		vp = vp->next;
	}

	p[0] = 0xff;
	p[1] = 0x00;
	p += 2;
	dhcp_size = p - packet->data;


	packet->data_len = dhcp_size;

	if (original) {


		packet->src_ipaddr = original->dst_ipaddr;

		packet->sockfd = original->sockfd;
	}

	if (packet->data_len < DEFAULT_PACKET_SIZE) {
		memset(packet->data + packet->data_len, 0,
		       DEFAULT_PACKET_SIZE - packet->data_len);
		packet->data_len = DEFAULT_PACKET_SIZE;
	}

	if ((fr_debug_flag > 2) && fr_log_fp) {
		for (i = 0; i < packet->data_len; i++) {
			if ((i & 0x0f) == 0x00) fprintf(fr_log_fp, "%d: ", i);
			fprintf(fr_log_fp, "%02x ", packet->data[i]);
			if ((i & 0x0f) == 0x0f) fprintf(fr_log_fp, "\n");
		}
		fprintf(fr_log_fp, "\n");
	}

	return 0;
}
