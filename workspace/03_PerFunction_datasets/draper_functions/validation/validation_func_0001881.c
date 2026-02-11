parse_public_key_or_subkey (GQuark schema,
                            guint n_columns,
                            const guchar *beg,
                            const guchar **at,
                            const guchar *end,
                            GcrOpenpgpParseFlags flags,
                            GPtrArray *records)
{
	gchar *fingerprint = NULL;
	gchar *keyid;
	GcrRecord *record;
	guint8 version;
	guint32 timestamp;
	guint16 ndays = 0;
	guint8 algo;
	guint16 bits;
	gulong expiry;
	const guchar *data;


	data = *at;


	if (!read_byte (at, end, &version))
		return FALSE;
	if (version < 2 || version > 4)
		return FALSE;


	if (!read_uint32 (at, end, &timestamp))
		return FALSE;

	if (version < 4) {
		if (!read_uint16 (at, end, &ndays))
			return FALSE;
	}


	if (!read_byte (at, end, &algo))
		return FALSE;


	if (version < 4) {
		if (!parse_v3_rsa_bits_and_keyid (at, end, &bits, &keyid))
			return FALSE;


	} else {
		if (!parse_v4_algo_bits (at, end, algo, &bits))
			return FALSE;
		keyid = hash_v4_keyid (data, *at, &fingerprint);
	}

	record = _gcr_record_new (schema, n_columns, ':');
	_gcr_record_set_uint (record, GCR_RECORD_KEY_BITS, bits);
	_gcr_record_set_uint (record, GCR_RECORD_KEY_ALGO, algo);
	_gcr_record_take_raw (record, GCR_RECORD_KEY_KEYID, keyid);
	_gcr_record_set_ulong (record, GCR_RECORD_KEY_TIMESTAMP, timestamp);
	if (schema != GCR_RECORD_SCHEMA_SEC && schema != GCR_RECORD_SCHEMA_SSB)
		_gcr_record_set_raw (record, GCR_RECORD_PUB_CAPS, default_caps_for_algo (algo));

	if (ndays > 0) {
		expiry = (gulong)timestamp + ((gulong)ndays * 86400);
		_gcr_record_set_ulong (record, GCR_RECORD_KEY_EXPIRY, expiry);
	}

	g_ptr_array_add (records, record);

	if (fingerprint && (schema == GCR_RECORD_SCHEMA_PUB || schema == GCR_RECORD_SCHEMA_SEC)) {
		record = _gcr_record_new (GCR_RECORD_SCHEMA_FPR, GCR_RECORD_FPR_MAX, ':');
		_gcr_record_take_raw (record, GCR_RECORD_FPR_FINGERPRINT, fingerprint);
		g_ptr_array_add (records, record);
		fingerprint = NULL;
	}

	g_free (fingerprint);
	return TRUE;
}
