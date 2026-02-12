static void ASetMode(int on)
{
	int i;

	for (i = 0; i < curr->w_NumArgs; ++i) {
		switch (curr->w_args[i]) {

		case 4:
			curr->w_insert = on;
			LAY_DISPLAYS(&curr->w_layer, InsertMode(on));
			break;

		case 20:
			curr->w_autolf = on;
			break;
		case 34:
			curr->w_curvvis = !on;
			LCursorVisibility(&curr->w_layer, curr->w_curinv ? -1 : curr->w_curvvis);
			break;
		default:
			break;
		}
	}
}
