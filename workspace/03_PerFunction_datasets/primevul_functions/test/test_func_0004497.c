static int de_fmtutil_default_iff_chunk_handler(deark *c, struct de_iffctx *ictx)
{
	i64 dpos = ictx->chunkctx->dpos;
	i64 dlen = ictx->chunkctx->dlen;
	u32 chunktype = ictx->chunkctx->chunk4cc.id;

	switch(chunktype) {


	case CODE__c_:
		do_iff_text_chunk(c, ictx, dpos, dlen, "copyright");
		break;
	case CODE_ANNO:
		do_iff_anno(c, ictx, dpos, dlen);
		break;
	case CODE_AUTH:
		do_iff_text_chunk(c, ictx, dpos, dlen, "author");
		break;
	case CODE_NAME:
		do_iff_text_chunk(c, ictx, dpos, dlen, "name");
		break;
	case CODE_TEXT:
		do_iff_text_chunk(c, ictx, dpos, dlen, "text");
		break;
	}


	return 1;
}
