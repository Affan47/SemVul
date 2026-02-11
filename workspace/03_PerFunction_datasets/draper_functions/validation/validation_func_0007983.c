gf_odf_read_qos(GF_BitStream *bs, GF_QoS_Descriptor *qos, u32 DescSize)
{
	GF_Err e;
	GF_QoS_Default *tmp;
	u32 tmp_size, nbBytes = 0;
	if (!qos) return GF_BAD_PARAM;

	qos->predefined = gf_bs_read_int(bs, 8);
	nbBytes += 1;

	if (qos->predefined) {
		if (nbBytes != DescSize) return GF_ODF_INVALID_DESCRIPTOR;
		return GF_OK;
	}

	while (nbBytes < DescSize) {
		tmp = NULL;
		e = gf_odf_parse_qos(bs, &tmp, &tmp_size);
		if (!tmp) return GF_ODF_INVALID_DESCRIPTOR;
		e = gf_list_add(qos->QoS_Qualifiers, tmp);
		if (e) return e;
		nbBytes += tmp_size;
	}
	if (nbBytes != DescSize) return GF_ODF_INVALID_DESCRIPTOR;
	return GF_OK;
}
