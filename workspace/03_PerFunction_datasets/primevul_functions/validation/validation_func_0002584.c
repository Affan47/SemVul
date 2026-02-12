R_API void r_core_prompt_loop(RCore *r) {
	int ret;
	do {
		int err = r_core_prompt (r, false);
		if (err < 1) {

			r->num->value = 0;
			break;
		}

		if ((ret = r_core_prompt_exec (r)) == -2) {
			break;
		}
	} while (ret != R_CORE_CMD_EXIT);
}
