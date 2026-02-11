m2ts_rewrite_avc_sample(GF_MediaImporter *import, GF_TSImport *tsimp)
{
	GF_Err e;
	u32 sc_pos, start;
	GF_BitStream *bs;
	GF_ISOSample *samp;
	u32 count = gf_isom_get_sample_count(import->dest, tsimp->track);
	if (!count || !tsimp->avccfg) return;

	samp = gf_isom_get_sample(import->dest, tsimp->track, count, NULL);
	sc_pos = 1;
	start = 0;
	bs = gf_bs_new(samp->data, samp->dataLength, GF_BITSTREAM_WRITE);
	while (1) {
		if (!samp->data[sc_pos] && !samp->data[sc_pos+1] && !samp->data[sc_pos+2] && (samp->data[sc_pos+3]==1)) {
			gf_bs_seek(bs, start);
			gf_bs_write_u32(bs, (u32) sc_pos-start-4);
			start = sc_pos;
		}
		sc_pos++;
		if (start+sc_pos>=samp->dataLength) break;
	}
	gf_bs_seek(bs, start);
	gf_bs_write_u32(bs, samp->dataLength-start-4);

	gf_bs_del(bs);

	e = gf_isom_update_sample(import->dest, tsimp->track, count, samp, 1);
	if (e) {
		GF_LOG(GF_LOG_ERROR, GF_LOG_CONTAINER, ("[MPEG-2 TS Import] Error rewriting AVC NALUs: %s\n", gf_error_to_string(e) ));
	}
	gf_isom_sample_del(&samp);
}
