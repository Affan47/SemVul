is_material_draw() const
{
	if (material[WHITE] == 0 && material[BLACK] == 0) {

		return true;
#if 0
	} else if (get_pawns(WHITE) || get_pawns(BLACK)) {

 		return false;
	} else if ((material[WHITE] < mat_values[ROOK]
			|| (material[WHITE] == 2 * mat_values[KNIGHT]
				&& get_knights(WHITE).popcnt() == 2))
		&& (material[BLACK] < mat_values[ROOK]
			|| (material[BLACK] == 2 * mat_values[KNIGHT]
				&& get_knights(BLACK).popcnt() == 2))) {


		return true;
#endif
	}


	return false;
}
