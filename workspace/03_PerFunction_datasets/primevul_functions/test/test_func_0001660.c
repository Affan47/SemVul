GF_BIFSConfig *gf_odf_get_bifs_config(GF_DefaultDescriptor *dsi, u32 oti)
{
	Bool hasSize, cmd_stream;
	GF_BitStream *bs;
	GF_BIFSConfig *cfg;

	if (oti>=GF_CODECID_BIFS_EXTENDED) return NULL;

	if (!dsi || !dsi->data || !dsi->dataLength ) {

		cfg = (GF_BIFSConfig *) gf_odf_desc_new(GF_ODF_BIFS_CFG_TAG);
		cfg->pixelMetrics = GF_TRUE;
		cfg->version = 1;
		return cfg;
	}
	bs = gf_bs_new(dsi->data, dsi->dataLength, GF_BITSTREAM_READ);

	cfg = (GF_BIFSConfig *) gf_odf_desc_new(GF_ODF_BIFS_CFG_TAG);
	if (oti==2) {

		gf_bs_read_int(bs, 1);

		gf_bs_read_int(bs, 1);
	}
	cfg->nodeIDbits = gf_bs_read_int(bs, 5);
	cfg->routeIDbits = gf_bs_read_int(bs, 5);
	if (oti==2) cfg->protoIDbits = gf_bs_read_int(bs, 5);

	cmd_stream = (Bool)gf_bs_read_int(bs, 1);
	if (!cmd_stream) {
		cfg->elementaryMasks = gf_list_new();
		while (1) {
			GF_ElementaryMask* em = (GF_ElementaryMask* ) gf_odf_New_ElemMask();
			em->node_id = gf_bs_read_int(bs, cfg->nodeIDbits);
			gf_list_add(cfg->elementaryMasks, em);

			if (gf_bs_read_int(bs, 1) == 0) break;
		}
		gf_bs_align(bs);
		if (gf_bs_get_size(bs) != gf_bs_get_position(bs)) {
			GF_LOG(GF_LOG_WARNING, GF_LOG_CODEC, ("[ODF] Reading bifs config: shift in sizes (not supported)\n"));
		}
	} else {
		cfg->pixelMetrics = (Bool)gf_bs_read_int(bs, 1);
		hasSize = (Bool)gf_bs_read_int(bs, 1);
		if (hasSize) {
			cfg->pixelWidth = gf_bs_read_int(bs, 16);
			cfg->pixelHeight = gf_bs_read_int(bs, 16);
		}
		gf_bs_align(bs);
		if (gf_bs_get_size(bs) != gf_bs_get_position(bs))
			GF_LOG(GF_LOG_WARNING, GF_LOG_CODEC, ("[ODF] Reading bifs config: shift in sizes (invalid descriptor)\n"));
	}
	gf_bs_del(bs);
	return cfg;
}
