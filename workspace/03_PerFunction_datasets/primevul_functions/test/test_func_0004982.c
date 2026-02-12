GF_Err tx3g_box_size(GF_Box *s)
{

	s->size += 18 + GPP_BOX_SIZE + GPP_STYLE_SIZE;
	return GF_OK;
}
