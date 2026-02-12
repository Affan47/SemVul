static void lsr_read_private_element_container(GF_LASeRCodec *lsr)
{
	u32 val, len;
	GF_LSR_READ_INT(lsr, val, 4, "ch4");
	switch (val) {

	case 0:
		len = lsr_read_vluimsbf5(lsr, "len");
		gf_bs_skip_bytes(lsr->bs, len);
		break;

	case 1:
		len = lsr_read_vluimsbf5(lsr, "len");
		gf_bs_skip_bytes(lsr->bs, len);
		break;

	case 2:
		lsr_read_extend_class(lsr, NULL, 0, "reserved");
		break;

	default:
		len = lsr_read_vluimsbf5(lsr, "len");
		gf_bs_skip_bytes(lsr->bs, len);
		break;
	}
}
