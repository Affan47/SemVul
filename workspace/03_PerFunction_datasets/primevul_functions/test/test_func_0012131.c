drill_parse_header_is_metric(gerb_file_t *fd, drill_state_t *state,
			gerbv_image_t *image, ssize_t file_line)
{
    gerbv_drill_stats_t *stats = image->drill_stats;
    char c, op[3];

    dprintf("    %s(): entering\n", __FUNCTION__);


    if (DRILL_HEADER != state->curr_section)
	return 0;

    switch (file_check_str(fd, "METRIC")) {
    case -1:
	gerbv_stats_printf(stats->error_list, GERBV_MESSAGE_ERROR, -1,
		_("Unexpected EOF found while parsing \"%s\" string "
		    "in file \"%s\""), "METRIC", fd->filename);
	return 0;

    case 0:
	return 0;
    }

header_again:

    if (',' != gerb_fgetc(fd)) {
	gerb_ungetc(fd);
	eat_line(fd);
    } else {

	switch (c = gerb_fgetc(fd)) {
	case 'T':
	case 'L':
	    if ('Z' != gerb_fgetc(fd))
		goto header_junk;

	    if (c == 'L') {
		dprintf ("    %s(): Detected a file that probably has "
			"trailing zero suppression\n", __FUNCTION__);
		if (state->autod)
		    image->format->omit_zeros = GERBV_OMIT_ZEROS_TRAILING;
	    } else {
		dprintf ("    %s(): Detected a file that probably has "
			"leading zero suppression\n", __FUNCTION__);
		if (state->autod)
		    image->format->omit_zeros = GERBV_OMIT_ZEROS_LEADING;
	    }

	    if (state->autod) {


		state->header_number_format =
		    state->number_format = FMT_000_000;
		state->decimals = 3;
	    }

	    if (',' == gerb_fgetc(fd))

		goto header_again;

	    gerb_ungetc(fd);

	    break;

	case '0':
	    if ('0' != gerb_fgetc(fd)
	    ||  '0' != gerb_fgetc(fd))
		goto header_junk;


	    op[0] = gerb_fgetc(fd);
	    op[1] = gerb_fgetc(fd);
	    op[2] = '\0';
	    if (EOF == op[0]
	    ||  EOF == op[1])
		goto header_junk;

	    if (0 == strcmp(op, "0.")) {


		if ('0' != gerb_fgetc(fd)
		||  '0' != gerb_fgetc(fd))
		    goto header_junk;

		eat_line(fd);

		if (state->autod) {
		    state->number_format = FMT_0000_00;
		    state->decimals = 2;
		}
		break;
	    }

	    if (0 != strcmp(op, ".0"))
		goto header_junk;


	    if ('0' != gerb_fgetc(fd))
		goto header_junk;

	    if ('0' == gerb_fgetc(fd)
	    &&  state->autod) {
		state->number_format = FMT_000_000;
		state->decimals = 3;
	    } else {
		gerb_ungetc(fd);

		if (state->autod) {
		    state->number_format = FMT_000_00;
		    state->decimals = 2;
		}
	    }

	    eat_line(fd);
	    break;

	default:
header_junk:
	    gerb_ungetc(fd);
	    eat_line(fd);

	    gerbv_stats_printf(stats->error_list,
		    GERBV_MESSAGE_WARNING, -1,
		    _("Found junk after METRIC command "
			"at line %ld in file \"%s\""),
		    file_line, fd->filename);
	    break;
	}
    }

    state->unit = GERBV_UNIT_MM;

    return 1;
}
