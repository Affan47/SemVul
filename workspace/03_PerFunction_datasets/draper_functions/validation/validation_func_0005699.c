GdipCreateCustomLineCap (GpPath *fillPath, GpPath *strokePath, GpLineCap baseCap, float baseInset, GpCustomLineCap **customCap)
{
	GpCustomLineCap *cap;
	GpPath *fillpath_clone = NULL, *strokepath_clone = NULL;

	if ((!fillPath && !strokePath) || !customCap)
		return InvalidParameter;

	cap = gdip_custom_linecap_new ();
	if (!cap)
		return OutOfMemory;

	if (fillPath) {
		if (GdipClonePath (fillPath, &fillpath_clone) != Ok) {
			if (fillpath_clone != NULL)
				GdipFree (fillpath_clone);
			GdipFree (cap);
			return OutOfMemory;
		}
	}
	cap->fill_path = fillpath_clone;

	if (strokePath) {
		if (GdipClonePath (strokePath, &strokepath_clone) != Ok) {
			if (strokepath_clone != NULL)
				GdipFree (strokepath_clone);
			GdipFree (fillpath_clone);
			GdipFree (cap);
			return OutOfMemory;
		}
	}
	cap->stroke_path = strokepath_clone;

	cap->base_cap = baseCap;
	cap->base_inset = baseInset;

	*customCap = cap;

	return Ok;
}
