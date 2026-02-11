updateVidOutFormat()
{
	v4l2_fmtdesc desc;
	v4l2_format fmt;

	g_fmt_out(fmt);
	if (enum_fmt_out(desc, true)) {
		do {
			if (desc.pixelformat == fmt.fmt.pix.pixelformat)
				break;
		} while (enum_fmt_out(desc));
	}
	if (desc.pixelformat != fmt.fmt.pix.pixelformat)
		return;
	m_vidCapFormats->setCurrentIndex(desc.index);
}
