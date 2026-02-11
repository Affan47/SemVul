ahc_validate_width(struct ahc_softc *ahc, struct ahc_initiator_tinfo *tinfo,
		   u_int *bus_width, role_t role)
{
	switch (*bus_width) {
	default:
		if (ahc->features & AHC_WIDE) {

			*bus_width = MSG_EXT_WDTR_BUS_16_BIT;
			break;
		}

	case MSG_EXT_WDTR_BUS_8_BIT:
		*bus_width = MSG_EXT_WDTR_BUS_8_BIT;
		break;
	}
	if (tinfo != NULL) {
		if (role == ROLE_TARGET)
			*bus_width = min((u_int)tinfo->user.width, *bus_width);
		else
			*bus_width = min((u_int)tinfo->goal.width, *bus_width);
	}
}
