int rad_vp2attr(const RADIUS_PACKET *packet, const RADIUS_PACKET *original,
		const char *secret, const VALUE_PAIR *vp, uint8_t *ptr)
{
	int		vendorcode;
	int		offset, len, total_length;
	uint32_t	lvalue;
	uint8_t		*length_ptr, *vsa_length_ptr;
	const uint8_t	*data = NULL;
	uint8_t		array[4];

	vendorcode = total_length = 0;
	length_ptr = vsa_length_ptr = NULL;


	if ((vendorcode = VENDOR(vp->attribute)) != 0) {


		*ptr++ = PW_VENDOR_SPECIFIC;
		vsa_length_ptr = ptr;
		*ptr++ = 6;
		lvalue = htonl(vendorcode);
		memcpy(ptr, &lvalue, 4);
		ptr += 4;
		total_length += 6;

		if (vendorcode == VENDORPEC_USR) {
			lvalue = htonl(vp->attribute & 0xFFFF);
			memcpy(ptr, &lvalue, 4);

			length_ptr = vsa_length_ptr;

			total_length += 4;
			*length_ptr  += 4;
			ptr          += 4;


			vsa_length_ptr = NULL;

		} else if (vendorcode == VENDORPEC_LUCENT) {


			*ptr++ = ((vp->attribute >> 8) & 0xFF);
			*ptr++ = (vp->attribute & 0xFF);
			length_ptr = ptr;
			*vsa_length_ptr += 3;
			*ptr++ = 3;
			total_length += 3;

		} else if (vendorcode == VENDORPEC_STARENT) {


			*ptr++ = ((vp->attribute >> 8) & 0xFF);
			*ptr++ = (vp->attribute & 0xFF);
			*ptr++ = 0;
			length_ptr = ptr;
			*vsa_length_ptr += 4;
			*ptr++ = 4;
			total_length += 4;
		} else {


			*vsa_length_ptr += 2;
			goto rfc;
		}
	} else {
	rfc:


		*ptr++ = (vp->attribute & 0xFF);
		length_ptr = ptr;
		*ptr++ = 2;
		total_length += 2;
	}

	offset = 0;
	if (vp->flags.has_tag) {
		if (TAG_VALID(vp->flags.tag)) {
			ptr[0] = vp->flags.tag & 0xff;
			offset = 1;

		} else if (vp->flags.encrypt == FLAG_ENCRYPT_TUNNEL_PASSWORD) {


			ptr[0] = 0;
			offset = 1;
		}
	}


	data = vp->strvalue;
	len = vp->length;


	if (vp->flags.encrypt && (len > MAX_PASS_LEN)) {
		len = MAX_PASS_LEN;
	}

	switch(vp->type) {
	case PW_TYPE_STRING:
	case PW_TYPE_OCTETS:
	case PW_TYPE_IFID:
	case PW_TYPE_IPV6ADDR:
	case PW_TYPE_IPV6PREFIX:
	case PW_TYPE_ABINARY:

		break;

	case PW_TYPE_INTEGER:
		len = 4;
		lvalue = htonl(vp->lvalue);
		memcpy(array, &lvalue, sizeof(lvalue));


		data = &array[offset];
		len -= offset;
		break;

	case PW_TYPE_IPADDR:
		data = (const uint8_t *) &vp->lvalue;
		len = 4;
		break;


	case PW_TYPE_DATE:
		lvalue = htonl(vp->lvalue);
		data = (const uint8_t *) &lvalue;
		len = 4;
		break;

	default:
		librad_log("ERROR: Unknown attribute type %d", vp->type);
		return -1;
	}


	if (len + offset + total_length > 255) {
		len = 255 - offset - total_length;
	}


	switch (vp->flags.encrypt) {
	case FLAG_ENCRYPT_USER_PASSWORD:
		make_passwd(ptr + offset, &len,
			    data, len,
			    secret, packet->vector);
		break;

	case FLAG_ENCRYPT_TUNNEL_PASSWORD:
		if (!original) {
			librad_log("ERROR: No request packet, cannot encrypt %s attribute in the vp.", vp->name);
			return -1;
		}


		if ((255 - offset - total_length) < 18) return 0;


		make_tunnel_passwd(ptr + offset, &len,
				   data, len, 255 - offset - total_length,
				   secret, original->vector);
		break;


	case FLAG_ENCRYPT_ASCEND_SECRET:
		make_secret(ptr + offset, packet->vector,
			    secret, data);
		len = AUTH_VECTOR_LEN;
		break;


	default:


		memcpy(ptr + offset, data, len);
		break;
	}


	len += offset;


	if (len == 0) return 0;


	*length_ptr += len;
	if (vsa_length_ptr) *vsa_length_ptr += len;
	ptr += len;
	total_length += len;

	return total_length;
}
