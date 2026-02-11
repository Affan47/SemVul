j2k_read_cod(opj_j2k_t *j2k) {
	int len, i, pos;

	opj_cio_t *cio = j2k->cio;
	opj_cp_t *cp = j2k->cp;
	opj_tcp_t *tcp = j2k->state == J2K_STATE_TPH ? &cp->tcps[j2k->curtileno] : j2k->default_tcp;
	opj_image_t *image = j2k->image;

	len = cio_read(cio, 2);
	tcp->csty = cio_read(cio, 1);
	tcp->prg = (OPJ_PROG_ORDER)cio_read(cio, 1);
	tcp->numlayers = cio_read(cio, 2);
	tcp->mct = cio_read(cio, 1);

	pos = cio_tell(cio);
	for (i = 0; i < image->numcomps; i++) {
		tcp->tccps[i].csty = tcp->csty & J2K_CP_CSTY_PRT;
		cio_seek(cio, pos);
		j2k_read_cox(j2k, i);
	}


	if (j2k->cstr_info) {
		opj_codestream_info_t *cstr_info = j2k->cstr_info;
		cstr_info->prog = tcp->prg;
		cstr_info->numlayers = tcp->numlayers;
		cstr_info->numdecompos = (int*) opj_malloc(image->numcomps * sizeof(int));
		for (i = 0; i < image->numcomps; i++) {
			cstr_info->numdecompos[i] = tcp->tccps[i].numresolutions - 1;
		}
	}
}
