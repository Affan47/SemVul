reduce_frames_load(struct image_file_list *imfl, struct ccd_reduce *ccdr)
{
	int ret, nframes;
	struct image_file *imf;
	struct ccd_frame *fr = NULL;
	GList *gl;

	g_return_val_if_fail(imfl != NULL, NULL);
	g_return_val_if_fail(ccdr != NULL, NULL);

	nframes = g_list_length(imfl->imlist);
	if (!(ccdr->ops & IMG_OP_STACK)) {
		gl = imfl->imlist;
		while (gl != NULL) {
			imf = gl->data;
			gl = g_list_next(gl);
			if (imf->flags & IMG_SKIP)
				continue;
			ret = reduce_frame(imf, ccdr, progress_print, NULL);
			if (ret)
				continue;
			if (ccdr->ops & IMG_OP_INPLACE) {
				save_image_file(imf, NULL, 1, NULL, progress_print, NULL);
			}
			if (fr == NULL) {
				fr = imf->fr;
				get_frame(fr);
			}
		}
		return fr;
	}

	d3_printf("stacking\n");
	if (P_INT(CCDRED_STACK_METHOD) == PAR_STACK_METHOD_KAPPA_SIGMA ||
	    P_INT(CCDRED_STACK_METHOD) == PAR_STACK_METHOD_MEAN_MEDIAN ) {
		if (!(ccdr->ops & IMG_OP_BG_ALIGN_MUL))
			ccdr->ops |= IMG_OP_BG_ALIGN_ADD;
	}
	if (reduce_frames(imfl, ccdr, progress_print, NULL))
		return NULL;
	if ((fr = stack_frames(imfl, ccdr, progress_print, NULL)) == NULL)
		return NULL;
	return fr;
}
