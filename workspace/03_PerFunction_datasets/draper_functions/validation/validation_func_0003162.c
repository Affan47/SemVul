sc_carve_py_rgb(
	uint8_t *image, long int nom,
	long int *width, long int *height, long int *pwidth, long int *pheight,
	const bool zoom, const bool rgb32
) {

	if ((nom > 0) && (info.original_width == info.ext_width))
		nom = 0;

	if (abs(nom) > info.si)
	    nom = (nom > 0)? info.si: -info.si;

	const int act = -info.sc;

	if (nom == act) return nom;

	const bool enlarge = (nom > act),
				extend = ((nom > 0) || (act > 0)),
				origin = (abs(nom - act) > max2(abs(nom), abs(act)));


	if (origin)
			carve_comp_py_rgb(
				image, &comp_img, &seams, &info, zoom && info.zoom,
				enlarge? +nom: -nom, origin,
				enlarge, false, &c_progress, rgb32
			);
	else
		carve_comp_py_rgb(
			image, &comp_img, &seams, &info, zoom && info.zoom,
			extend? +nom: -nom, origin, extend, enlarge ^ extend,
			&c_progress, rgb32
		);
	set_dimensions_nom(&info, height, width, pheight, pwidth, nom);

 	c_progress = -1;

	return nom;
}
