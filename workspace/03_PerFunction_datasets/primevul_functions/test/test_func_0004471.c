void fmtutil_read_boxes_format(deark *c, struct de_boxesctx *bctx)
{
	if(!bctx->f || !bctx->handle_box_fn) return;
	if(bctx->curbox) return;
	do_box_sequence(c, bctx, 0, bctx->f->len, -1, 0);
}
