dump_dvb_parameters (FILE *f, struct transponder *t)
{
	switch (output_format)
	{
	case OUTPUT_VDR:
	case OUTPUT_VDR_16x:
		vdr_dump_dvb_parameters(f, t, override_orbital_pos);
		break;

	case OUTPUT_ZAP:
		zap_dump_dvb_parameters(f, t, sat_number(t));
		break;

	default:
		break;
	}
}
