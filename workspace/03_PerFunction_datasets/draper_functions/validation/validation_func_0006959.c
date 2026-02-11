xdes_in_segment(

	const xdes_t*	descr,
	ib_id_t		seg_id,
	mtr_t*		mtr)
{
	ulint		state = xdes_get_state(descr, mtr);

	if (state != XDES_FSEG && state != XDES_FSEG_FRAG) {
		return(FALSE);
	}

	return(mach_read_from_8(descr + XDES_ID) == seg_id);
}
