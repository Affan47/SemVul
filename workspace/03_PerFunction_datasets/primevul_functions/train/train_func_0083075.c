static char *uncompress(int16_t field_count, char *start, char *end,
			char *ptr, char *uncompressed, int uncomp_len,
			char **uncompressed_ptr)
{
	char *uptr = *uncompressed_ptr;

	debug("count %d ptr %p end %p uptr %p", field_count, ptr, end, uptr);

	while (field_count-- > 0 && ptr < end) {
		int dlen;
		int ulen;
		int pos;
		char name[NS_MAXLABEL];
		uint16_t dns_type, dns_class;
		int comp_pos;

		if (!convert_label(start, end, ptr, name, NS_MAXLABEL,
					&pos, &comp_pos))
			goto out;


		ulen = strlen(name);
		strncpy(uptr, name, uncomp_len - (uptr - uncompressed));

		debug("pos %d ulen %d left %d name %s", pos, ulen,
			(int)(uncomp_len - (uptr - uncompressed)), uptr);

		uptr += ulen;
		*uptr++ = '\0';

		ptr += pos;


		memcpy(uptr, ptr, NS_RRFIXEDSZ);

		dns_type = uptr[0] << 8 | uptr[1];
		dns_class = uptr[2] << 8 | uptr[3];

		if (dns_class != ns_c_in)
			goto out;

		ptr += NS_RRFIXEDSZ;
		uptr += NS_RRFIXEDSZ;


		if (dns_type == ns_t_cname) {
			if (!convert_label(start, end, ptr, uptr,
					uncomp_len - (uptr - uncompressed),
						&pos, &comp_pos))
				goto out;

			uptr[-2] = comp_pos << 8;
			uptr[-1] = comp_pos & 0xff;

			uptr += comp_pos;
			ptr += pos;

		} else if (dns_type == ns_t_a || dns_type == ns_t_aaaa) {
			dlen = uptr[-2] << 8 | uptr[-1];

			if (ptr + dlen > end) {
				debug("data len %d too long", dlen);
				goto out;
			}

			memcpy(uptr, ptr, dlen);
			uptr += dlen;
			ptr += dlen;

		} else if (dns_type == ns_t_soa) {
			int total_len = 0;
			char *len_ptr;


			if (!convert_label(start, end, ptr, uptr,
					uncomp_len - (uptr - uncompressed),
						&pos, &comp_pos))
				goto out;

			total_len += comp_pos;
			len_ptr = &uptr[-2];
			ptr += pos;
			uptr += comp_pos;


			if (!convert_label(start, end, ptr, uptr,
					uncomp_len - (uptr - uncompressed),
						&pos, &comp_pos))
				goto out;

			total_len += comp_pos;
			ptr += pos;
			uptr += comp_pos;


			memcpy(uptr, ptr, 20);
			uptr += 20;
			ptr += 20;
			total_len += 20;


			len_ptr[0] = total_len << 8;
			len_ptr[1] = total_len & 0xff;
		}

		*uncompressed_ptr = uptr;
	}

	return ptr;

out:
	return NULL;
}
