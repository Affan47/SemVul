static int r_cmd_java_set_acc_flags (RCore *core, ut64 addr, ut16 num_acc_flag) {
	char cmd_buf [50];


	int res = false;

	num_acc_flag = R_BIN_JAVA_USHORT (((ut8*) &num_acc_flag), 0);
	res = r_core_write_at(core, addr, (const ut8 *)&num_acc_flag, 2);
	if (!res) {
		eprintf ("[X] r_cmd_java_set_acc_flags: Failed to write.\n");
		return res;
	}


	res = true;
	IFDBG r_cons_printf ("Executed cmd: %s == %d\n", cmd_buf, res);


	return res;
}
