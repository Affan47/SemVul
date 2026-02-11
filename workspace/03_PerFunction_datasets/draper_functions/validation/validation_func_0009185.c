heim_ntlm_encode_targetinfo(const struct ntlm_targetinfo *ti,
			    int ucs2,
			    struct ntlm_buf *data)
{
    krb5_error_code ret;
    krb5_storage *out;

    data->data = NULL;
    data->length = 0;

    out = krb5_storage_emem();
    if (out == NULL)
	return ENOMEM;

    krb5_storage_set_byteorder(out, KRB5_STORAGE_BYTEORDER_LE);

    if (ti->servername)
	CHECK(encode_ti_string(out, 1, ucs2, ti->servername), 0);
    if (ti->domainname)
	CHECK(encode_ti_string(out, 2, ucs2, ti->domainname), 0);
    if (ti->dnsservername)
	CHECK(encode_ti_string(out, 3, ucs2, ti->dnsservername), 0);
    if (ti->dnsdomainname)
	CHECK(encode_ti_string(out, 4, ucs2, ti->dnsdomainname), 0);
    if (ti->dnstreename)
	CHECK(encode_ti_string(out, 5, ucs2, ti->dnstreename), 0);
    if (ti->avflags) {
	CHECK(krb5_store_uint16(out, 6), 0);
	CHECK(krb5_store_uint16(out, 4), 0);
	CHECK(krb5_store_uint32(out, ti->avflags), 0);
    }
    if (ti->timestamp) {
	CHECK(krb5_store_uint16(out, 7), 0);
	CHECK(krb5_store_uint16(out, 8), 0);
	CHECK(krb5_store_uint32(out, ti->timestamp & 0xffffffff), 0);
	CHECK(krb5_store_uint32(out, (ti->timestamp >> 32) & 0xffffffff), 0);
    }
    if (ti->targetname) {
	CHECK(encode_ti_string(out, 9, ucs2, ti->targetname), 0);
    }
    if (ti->channel_bindings.length) {
	CHECK(krb5_store_uint16(out, 10), 0);
	CHECK(krb5_store_uint16(out, ti->channel_bindings.length), 0);
	CHECK_SIZE(krb5_storage_write(out, ti->channel_bindings.data, ti->channel_bindings.length), ti->channel_bindings.length);
    }


    CHECK(krb5_store_int16(out, 0), 0);
    CHECK(krb5_store_int16(out, 0), 0);

    {
	krb5_data d;
	ret = krb5_storage_to_data(out, &d);
	data->data = d.data;
	data->length = d.length;
    }
out:
    krb5_storage_free(out);
    return ret;
}
