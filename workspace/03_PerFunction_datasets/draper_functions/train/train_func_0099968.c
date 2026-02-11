ho_next(struct irs_ho *this) {
	struct pvt *pvt = (struct pvt *)this->private;
	struct hostent *ho = &pvt->host;
	char *body;
	size_t bodylen;
	int code;
	char text[256];

	if (irs_irp_connection_setup(pvt->girpdata, &pvt->warned) != 0) {
		return (NULL);
	}

	if (irs_irp_send_command(pvt->girpdata, "gethostent") != 0) {
		return (NULL);
	}

	if (irs_irp_get_full_response(pvt->girpdata, &code,
				      text, sizeof text,
				      &body, &bodylen) != 0) {
		return (NULL);
	}

	if (code == IRPD_GETHOST_OK) {
		free_host(ho);
		if (irp_unmarshall_ho(ho, body) != 0) {
			ho = NULL;
		}
	} else {
		ho = NULL;
	}

	if (body != NULL) {
		memput(body, bodylen);
	}

	return (ho);
}
