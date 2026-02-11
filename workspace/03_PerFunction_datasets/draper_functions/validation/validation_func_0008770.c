initSpacings() {
	if (Spacings.count() == 0) {
		ShroudedSpacing = "0.1in (2.54mm)";
		Spacings.insert("1mm", "0.03937in (1.0mm)");
		Spacings.insert("1.25mm", "0.04921in (1.25mm)");
		Spacings.insert("50mil", "0.05in (1.27mm)");
		Spacings.insert("1.5mm", "0.0591in (1.5mm)");
		Spacings.insert("2mm", "0.07874in (2mm)");
		Spacings.insert("2.54mm", "0.09843in (2.54mm)");
		Spacings.insert("100mil", ShroudedSpacing);
		Spacings.insert("150mil", "0.15in (3.81mm)");
		Spacings.insert("200mil", "0.2in (5.08mm)");
	}
}
