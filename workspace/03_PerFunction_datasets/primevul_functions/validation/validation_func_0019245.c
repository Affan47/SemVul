ldns_rdf_bitmap_known_rr_types_set(ldns_rdf** rdf, int value)
{
	uint8_t  window;
	uint8_t  subtype;
	uint16_t windows[256]
#ifndef S_SPLINT_S
	                      = { 0 }
#endif
	                             ;
	ldns_rr_descriptor* d;
	size_t i;

	size_t sz;
	uint8_t* data = NULL;
	uint8_t* dptr;

	assert(rdf != NULL);


	for (d=rdata_field_descriptors; d < rdata_field_descriptors_end; d++) {
		window  = d->_type >> 8;
		subtype = d->_type & 0xff;
		if (windows[window] < subtype) {
			windows[window] = subtype;
		}
	}


	sz = 0;
	for (i = 0; i < 256; i++) {
		if (windows[i]) {
			sz += windows[i] / 8 + 3;
		}
	}
	if (sz > 0) {


		dptr = data = LDNS_XMALLOC(uint8_t, sz);
		if (!data) {
			return LDNS_STATUS_MEM_ERR;
		}
		memset(data, value, sz);
		for (i = 0; i < 256; i++) {
			if (windows[i]) {
				*dptr++ = (uint8_t)i;
				*dptr++ = (uint8_t)(windows[i] / 8 + 1);
				dptr += dptr[-1];
			}
		}
	}


	*rdf = ldns_rdf_new(LDNS_RDF_TYPE_BITMAP, sz, data);
	if (!*rdf) {
		LDNS_FREE(data);
		return LDNS_STATUS_MEM_ERR;
	}
	return LDNS_STATUS_OK;
}
