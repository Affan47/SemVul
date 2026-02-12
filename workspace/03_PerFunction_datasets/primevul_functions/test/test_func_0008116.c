GF_Err gf_bifs_decode_command_list(GF_BifsDecoder *codec, u16 ESID, u8 *data, u32 data_length, GF_List *com_list)
{
	GF_BitStream *bs;
	GF_Err e;

	if (!codec || !data || !codec->dec_memory_mode || !com_list) return GF_BAD_PARAM;

	codec->info = gf_bifs_dec_get_stream(codec, ESID);
	if (!codec->info) return GF_BAD_PARAM;
	if (codec->info->config.elementaryMasks ) return GF_NOT_SUPPORTED;


	assert(codec->scenegraph);

	codec->current_graph = codec->scenegraph;

	codec->ActiveQP = (M_QuantizationParameter*) codec->scenegraph->global_qp;

	bs = gf_bs_new(data, data_length, GF_BITSTREAM_READ);
	gf_bs_set_eos_callback(bs, BM_EndOfStream, codec);

	e = BM_ParseCommand(codec, bs, com_list);
	gf_bs_del(bs);


	if (!e) {
		gf_bifs_flush_command_list(codec);
	}

	while (gf_list_count(codec->command_buffers)) {
		CommandBufferItem *cbi = (CommandBufferItem *)gf_list_get(codec->command_buffers, 0);
		gf_node_unregister(cbi->node, NULL);
		gf_free(cbi);
		gf_list_rem(codec->command_buffers, 0);
	}


	codec->info = NULL;
	codec->current_graph = NULL;


	return e;
}
