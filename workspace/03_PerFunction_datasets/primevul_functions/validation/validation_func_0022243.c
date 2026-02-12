link_command()
{
    AXIS *primary_axis = NULL;
    AXIS *secondary_axis = NULL;
    TBOOLEAN linked = FALSE;
    int command_token = c_token;

    c_token++;


	strcpy(c_dummy_var[0], "x");
	strcpy(c_dummy_var[1], "y");
	if (equals(c_token, "z") || equals(c_token, "cb"))
	    strcpy(c_dummy_var[0], "z");
	if (equals(c_token, "r"))
	    strcpy(c_dummy_var[0], "r");


    if (equals(command_token,"nonlinear")) {
	AXIS_INDEX axis;
	if ((axis = lookup_table(axisname_tbl, c_token)) >= 0)
	    secondary_axis = &axis_array[axis];
	else
	    int_error(c_token,"not a valid nonlinear axis");
	primary_axis = get_shadow_axis(secondary_axis);


	if (secondary_axis->linked_to_primary && secondary_axis->linked_to_primary->index > 0)
	    int_error(NO_CARET,"must unlink axis before setting it to nonlinear");
	if (secondary_axis->linked_to_secondary && secondary_axis->linked_to_secondary->index > 0)
	    int_error(NO_CARET,"must unlink axis before setting it to nonlinear");

	secondary_axis->log = FALSE;
	secondary_axis->ticdef.logscaling = FALSE;


    } else {
	if (almost_equals(c_token,"x$2")) {
	    primary_axis = &axis_array[FIRST_X_AXIS];
	    secondary_axis = &axis_array[SECOND_X_AXIS];
	} else if (almost_equals(c_token,"y$2")) {
	    primary_axis = &axis_array[FIRST_Y_AXIS];
	    secondary_axis = &axis_array[SECOND_Y_AXIS];
	} else {
	    int_error(c_token,"expecting x2 or y2");
	}

	if (primary_axis->linked_to_primary)
	    int_error(NO_CARET, "You must clear nonlinear x or y before linking it");

	if (secondary_axis->linked_to_primary && secondary_axis->linked_to_primary->index <= 0)
	    int_error(NO_CARET, "You must clear nonlinear x2 or y2 before linking it");
    }
    c_token++;


    if (equals(command_token-1,"unset")) {
	primary_axis->linked_to_secondary = NULL;
	if (secondary_axis->linked_to_primary == NULL)

	    return;
	else
	    secondary_axis->linked_to_primary = NULL;

	linked = FALSE;
    } else {
	linked = TRUE;
    }


    if (!primary_axis->link_udf) {
	primary_axis->link_udf = gp_alloc(sizeof(udft_entry),"link_at");
	memset(primary_axis->link_udf, 0, sizeof(udft_entry));
    }
    if (!secondary_axis->link_udf) {
	secondary_axis->link_udf = gp_alloc(sizeof(udft_entry),"link_at");
	memset(secondary_axis->link_udf, 0, sizeof(udft_entry));
    }

    if (equals(c_token,"via")) {
	parse_link_via(secondary_axis->link_udf);
	if (almost_equals(c_token,"inv$erse")) {
	    parse_link_via(primary_axis->link_udf);
	} else {
	    int_warn(c_token,"inverse mapping function required");
	    linked = FALSE;
	}
    }

    else if (equals(command_token,"nonlinear") && linked) {
	int_warn(c_token,"via mapping function required");
	linked = FALSE;
    }

    if (equals(command_token,"nonlinear") && linked) {

	struct udft_entry *temp = primary_axis->link_udf;
	primary_axis->link_udf = secondary_axis->link_udf;
	secondary_axis->link_udf = temp;
	secondary_axis->linked_to_primary = primary_axis;
	primary_axis->linked_to_secondary = secondary_axis;
	clone_linked_axes(secondary_axis, primary_axis);
    } else if (linked) {

	secondary_axis->linked_to_primary = primary_axis;
	primary_axis->linked_to_secondary = secondary_axis;
	clone_linked_axes(primary_axis, secondary_axis);
    } else {
	free_at(secondary_axis->link_udf->at);
	secondary_axis->link_udf->at = NULL;
	free_at(primary_axis->link_udf->at);
	primary_axis->link_udf->at = NULL;

	primary_axis->linked_to_secondary = NULL;
	secondary_axis->linked_to_primary = NULL;
    }

    if (secondary_axis->index == POLAR_AXIS)
	rrange_to_xy();
}
