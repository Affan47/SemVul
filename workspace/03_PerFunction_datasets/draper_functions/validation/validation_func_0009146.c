GetAcidityColor (int Z, GdkRGBA *rgba)
{
	rgba->red= rgba->green = rgba->blue = 0.;
	Element *elt = Element::GetElement (Z);
	int value = elt->GetIntegerProperty ("acidicbehaviour");
	if (value == GCU_ERROR)
		return;


	switch (value) {
	case 0:
		rgba->red = 1.;
		return;

	case 1:
		rgba->blue = 1.;
		return;

	case 2:
		rgba->green = 1.;
		return;

	case 3:
		rgba->red = 1.;
		rgba->blue =1.;
		return;
	}
}
