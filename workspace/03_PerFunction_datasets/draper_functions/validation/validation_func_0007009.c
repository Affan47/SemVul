swf_new_shape_rec()
{
	SWFShapeRec *style;
	GF_SAFEALLOC(style, SWFShapeRec);
	GF_SAFEALLOC(style->path, SWFPath);
	return style;
}
