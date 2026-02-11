vxml_parser_buffer_reset_reader(vxml_parser_t *vp)
{
	if (vp->input != NULL) {
		struct vxml_buffer *vb = vp->input->data;
		if (VXML_BUFFER_MEMORY == vb->type) {
			vb->u.m->reader = NULL;
		}
	}
}
