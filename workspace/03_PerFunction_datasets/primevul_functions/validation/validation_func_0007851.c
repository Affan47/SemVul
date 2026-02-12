static RGBType * HWB_to_RGB (HWBType HWB, RGBType * RGB)
{


	float h = HWB.H, w = HWB.W, b = HWB.B, v, n, f;
	int i;

	v = 1 - b;
	if (h == HWB_UNDEFINED) {
		RETURN_RGB(v, v, v);
	}
	i = floor(h);
	f = h - i;
	if (i & 1) {
		f = 1 - f;
	}
	n = w + f * (v - w);
	switch (i) {
		case 6:
		case 0:
			RETURN_RGB(v, n, w);
		case 1:
			RETURN_RGB(n, v, w);
		case 2:
			RETURN_RGB(w, v, n);
		case 3:
			RETURN_RGB(w, n, v);
		case 4:
			RETURN_RGB(n, w, v);
		case 5:
			RETURN_RGB(v, w, n);
	}

	return RGB;
}
