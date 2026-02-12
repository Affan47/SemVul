getrdata(isc_buffer_t *source, dns_message_t *msg, dns_decompress_t *dctx,
	 dns_rdataclass_t rdclass, dns_rdatatype_t rdtype,
	 unsigned int rdatalen, dns_rdata_t *rdata)
{
	isc_buffer_t *scratch;
	isc_result_t result;
	unsigned int tries;
	unsigned int trysize;

	scratch = currentbuffer(msg);

	isc_buffer_setactive(source, rdatalen);


	tries = 0;
	trysize = 0;

	for (;;) {
		result = dns_rdata_fromwire(rdata, rdclass, rdtype,
					    source, dctx, 0,
					    scratch);

		if (result == ISC_R_NOSPACE) {
			if (tries == 0) {
				trysize = 2 * rdatalen;
				if (trysize < SCRATCHPAD_SIZE)
					trysize = SCRATCHPAD_SIZE;
			} else {
				INSIST(trysize != 0);
				if (trysize >= 65535)
					return (ISC_R_NOSPACE);

				trysize *= 2;
			}
			tries++;
			result = newbuffer(msg, trysize);
			if (result != ISC_R_SUCCESS)
				return (result);

			scratch = currentbuffer(msg);
		} else {
			return (result);
		}
	}
}
