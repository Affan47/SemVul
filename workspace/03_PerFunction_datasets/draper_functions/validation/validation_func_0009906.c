incr_mousemode(const int amount)
{
    long int old = mouse_mode;
    mouse_mode += amount;
    if (MOUSE_COORDINATES_ALT == mouse_mode && !(mouse_alt_string || polar))
	mouse_mode += amount;
    if (mouse_mode > MOUSE_COORDINATES_ALT) {
	mouse_mode = MOUSE_COORDINATES_REAL1;
    } else if (mouse_mode <= MOUSE_COORDINATES_REAL) {
	mouse_mode = MOUSE_COORDINATES_ALT;
	if (!(mouse_alt_string || polar))
	    mouse_mode--;
    }
    UpdateStatusline();
    if (display_ipc_commands())
	fprintf(stderr, "switched mouse format from %ld to %ld\n", old, mouse_mode);
}
