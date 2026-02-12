RADIUS_PACKET *rad_recv(int fd)
{
	RADIUS_PACKET		*packet;
	struct sockaddr_in	saremote;
	int			totallen;
	socklen_t		salen;
	uint8_t			*attr;
	int			count;
	radius_packet_t		*hdr;
	char			host_ipaddr[16];
	int			require_ma = 0;
	int			seen_ma = 0;
	uint8_t			data[MAX_PACKET_LEN];
	int			num_attributes;


	if ((packet = malloc(sizeof(RADIUS_PACKET))) == NULL) {
		librad_log("out of memory");
		return NULL;
	}
	memset(packet, 0, sizeof(RADIUS_PACKET));


	salen = sizeof(saremote);
	memset(&saremote, 0, sizeof(saremote));
#ifndef WITH_UDPFROMTO
	packet->data_len = recvfrom(fd, data, sizeof(data),
				    0, (struct sockaddr *)&saremote, &salen);
	packet->dst_ipaddr = htonl(INADDR_ANY);
#else
	{
		socklen_t		salen_local;
		struct sockaddr_in	salocal;
		salen_local = sizeof(salocal);
		memset(&salocal, 0, sizeof(salocal));
		packet->data_len = recvfromto(fd, data, sizeof(data), 0,
					      (struct sockaddr *)&saremote, &salen,
					      (struct sockaddr *)&salocal, &salen_local);
		packet->dst_ipaddr = salocal.sin_addr.s_addr;
	}
#endif


	if (packet->data_len < 0) {
		librad_log("Error receiving packet: %s", strerror(errno));
		free(packet);
		return NULL;
	}


	packet->sockfd = fd;
	packet->src_ipaddr = saremote.sin_addr.s_addr;
	packet->src_port = ntohs(saremote.sin_port);


	packet->vps = NULL;


	if (packet->data_len < AUTH_HDR_LEN) {
		librad_log("WARNING: Malformed RADIUS packet from host %s: too short (received %d < minimum %d)",
			   ip_ntoa(host_ipaddr, packet->src_ipaddr),
			   packet->data_len, AUTH_HDR_LEN);
		free(packet);
		return NULL;
	}


	if (packet->data_len > MAX_PACKET_LEN) {
		librad_log("WARNING: Malformed RADIUS packet from host %s: too long (received %d > maximum %d)",
			   ip_ntoa(host_ipaddr, packet->src_ipaddr),
			   packet->data_len, MAX_PACKET_LEN);
		free(packet);
		return NULL;
	}


	totallen = (data[2] << 8) | data[3];
	hdr = (radius_packet_t *)data;


	if ((hdr->code == 0) ||
	    (hdr->code >= 52)) {
		librad_log("WARNING: Bad RADIUS packet from host %s: unknown packet code %d",
			   ip_ntoa(host_ipaddr, packet->src_ipaddr),
			   hdr->code);
		free(packet);
		return NULL;
	}


	if (hdr->code == PW_STATUS_SERVER) require_ma = 1;


	if (totallen < AUTH_HDR_LEN) {
		librad_log("WARNING: Malformed RADIUS packet from host %s: too short (length %d < minimum %d)",
			   ip_ntoa(host_ipaddr, packet->src_ipaddr),
			   totallen, AUTH_HDR_LEN);
		free(packet);
		return NULL;
	}


	if (totallen > MAX_PACKET_LEN) {
		librad_log("WARNING: Malformed RADIUS packet from host %s: too long (length %d > maximum %d)",
			   ip_ntoa(host_ipaddr, packet->src_ipaddr),
			   totallen, MAX_PACKET_LEN);
		free(packet);
		return NULL;
	}


	if (packet->data_len < totallen) {
		librad_log("WARNING: Malformed RADIUS packet from host %s: received %d octets, packet length says %d",
			   ip_ntoa(host_ipaddr, packet->src_ipaddr),
			   packet->data_len, totallen);
		free(packet);
		return NULL;
	}


	if (packet->data_len > totallen) {


		memset(data + totallen, 0, packet->data_len - totallen);
		packet->data_len = totallen;
	}


	attr = hdr->data;
	count = totallen - AUTH_HDR_LEN;
	num_attributes = 0;

	while (count > 0) {


		if (attr[0] == 0) {
			librad_log("WARNING: Malformed RADIUS packet from host %s: Invalid attribute 0",
				   ip_ntoa(host_ipaddr, packet->src_ipaddr));
			free(packet);
			return NULL;
		}


       		if (attr[1] < 2) {
			librad_log("WARNING: Malformed RADIUS packet from host %s: attribute %d too short",
				   ip_ntoa(host_ipaddr, packet->src_ipaddr),
				   attr[0]);
			free(packet);
			return NULL;
		}


		switch (attr[0]) {
		default:
			break;


		case PW_EAP_MESSAGE:
			require_ma = 1;
			break;

		case PW_MESSAGE_AUTHENTICATOR:
			if (attr[1] != 2 + AUTH_VECTOR_LEN) {
				librad_log("WARNING: Malformed RADIUS packet from host %s: Message-Authenticator has invalid length %d",
					   ip_ntoa(host_ipaddr, packet->src_ipaddr),
					   attr[1] - 2);
				free(packet);
				return NULL;
			}
			seen_ma = 1;
			break;
		}


		count -= attr[1];
		attr += attr[1];
		num_attributes++;
	}


	if (count != 0) {
		librad_log("WARNING: Malformed RADIUS packet from host %s: packet attributes do NOT exactly fill the packet",
			   ip_ntoa(host_ipaddr, packet->src_ipaddr));
		free(packet);
		return NULL;
	}


	if ((librad_max_attributes > 0) &&
	    (num_attributes > librad_max_attributes)) {
		librad_log("WARNING: Possible DoS attack from host %s: Too many attributes in request (received %d, max %d are allowed).",
			   ip_ntoa(host_ipaddr, packet->src_ipaddr),
			   num_attributes, librad_max_attributes);
		free(packet);
		return NULL;
	}


	if (require_ma && ! seen_ma) {
		librad_log("WARNING: Insecure packet from host %s:  Packet does not contain required Message-Authenticator attribute",
			   ip_ntoa(host_ipaddr, packet->src_ipaddr));
		free(packet);
		return NULL;
	}

	if (librad_debug) {
		if ((hdr->code > 0) && (hdr->code < 52)) {
			printf("rad_recv: %s packet from host %s:%d",
			       packet_codes[hdr->code],
			       ip_ntoa(host_ipaddr, packet->src_ipaddr), packet->src_port);
		} else {
			printf("rad_recv: Packet from host %s:%d code=%d",
			       ip_ntoa(host_ipaddr, packet->src_ipaddr), packet->src_port,
			       hdr->code);
		}
		printf(", id=%d, length=%d\n", hdr->id, totallen);
	}


	packet->code = hdr->code;
	packet->id = hdr->id;
	memcpy(packet->vector, hdr->vector, AUTH_VECTOR_LEN);


	if ((packet->data = malloc(packet->data_len)) == NULL) {
	  free(packet);
	  librad_log("out of memory");
	  return NULL;
	}
	memcpy(packet->data, data, packet->data_len);

	return packet;
}
