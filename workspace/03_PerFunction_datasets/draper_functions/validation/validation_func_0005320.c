systematic_search(const int index, int true_ligand_atoms, int outlev, FILE *logFile) {


	if ( is_axis_index( index ) ) {
        Quat increment_q;
        Quat new_q;

		for (int i=0; i < 12; i++) {


            increment_q = raaToQuat( vertices[i], temp_rotation_angle );
            qmultiply( &new_q, &base_q, &increment_q );
			probe_point.writeQuat( new_q );
			systematic_search(Z_TRANSLATION_INDEX, true_ligand_atoms, outlev, logFile);
		}
	}


	else {
		int num_steps = DEFAULT_INCREMENTAL_STEPS;
		Real start, step_size;


		if ( is_translation_index( index ) ) step_size = TRAN_STEP;
		else if ( is_angle_index( index ) ) step_size = ROT_ANG_STEP;
		else step_size = TOR_ANG_STEP;


		if ( is_angle_index( index ) )  start = -2*num_steps*step_size;
		else start = base_point.gread(index).real - num_steps * step_size;

		for (int current = 0; current <= 2 * num_steps; current++) {

			if ( is_angle_index( index ) ) {
				temp_rotation_angle = start + current*step_size;
			}
			else {
				probe_point.write(start + current * step_size, index);
			}

			if (index == 0) {

				(void)current_energy(true_ligand_atoms,outlev,logFile);
			}
			else {

				if ( is_angle_index( index ) && current == 2 * num_steps) {
                    probe_point.writeQuat( base_point.readQuat() );
					systematic_search(Z_TRANSLATION_INDEX, true_ligand_atoms, outlev, logFile);

				}
				else {
					systematic_search(index-1, true_ligand_atoms, outlev, logFile);
				}
			}
		}
	}
}
