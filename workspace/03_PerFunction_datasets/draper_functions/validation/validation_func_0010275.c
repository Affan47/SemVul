vep_emit_verbatim(const struct vep_state *vep, ssize_t l, ssize_t l_crc)
{
	uint8_t buf[4];

	if (cache_param->esi_syntax & 0x20) {
		Debug("---> VERBATIM(%jd)\n", (intmax_t)l);
	}
	vep_emit_len(vep, l, VEC_V1, VEC_V2, VEC_V8);
	if (vep->dogzip) {
		vep_emit_len(vep, l_crc, VEC_C1, VEC_C2, VEC_C8);
		vbe32enc(buf, vep->crc);
		VSB_bcat(vep->vsb, buf, sizeof buf);
	}
}
