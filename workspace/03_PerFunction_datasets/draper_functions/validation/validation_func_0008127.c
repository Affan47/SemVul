tux_rendering_validate()
{

	if (tux_rendering.motion_class_names.size < 1) {
		ErrorMessage(__FUNCTION__,
			"Tux rendering specification is invalid: at least one motion_class is needed",
			PLEASE_INFORM, IS_FATAL);
	}


	int i, j;
	for (i = 0; i < tux_rendering.motion_class_names.size; i++) {
		for (j = 0; j < MAX_TUX_DIRECTIONS; j++) {
			if (tux_rendering.render_order[i][j] == NULL) {
				ErrorMessage(__FUNCTION__,
					"Tux rendering specification is invalid: no rendering order defined for motion_class \"%s\""
					" and rotation index %d",
					PLEASE_INFORM, IS_FATAL,
					get_motion_class_name_by_id(i), j);
			} else {


				int phase;
				int check_phase[TUX_TOTAL_PHASES];
				memset(check_phase, 0, TUX_TOTAL_PHASES*sizeof(int));

				struct tux_part_render_set *render_order_ptr = tux_rendering.render_order[i][j];
				while (render_order_ptr != NULL) {
					for (phase = render_order_ptr->phase_start; phase <= render_order_ptr->phase_end; phase++) {
						check_phase[phase] = 1;
					}
					render_order_ptr = render_order_ptr->next;
				}

				for (phase = 0; phase < TUX_TOTAL_PHASES; phase++) {
					if (check_phase[phase] == 0) {
						ErrorMessage(__FUNCTION__,
							"Tux rendering specification is invalid: no rendering order defined for motion_class \"%s\","
							" rotation index %d and animation phase %d",
							PLEASE_INFORM, IS_FATAL,
							get_motion_class_name_by_id(i), j, phase);
					}
				}
			}
		}
	}
}
