do_find_deps(CmdLineObj& cmdline) {

	if (cmdline.hasOption(GLE_OPT_FINDDEPS)) {
		GLEInterface* iface = GLEGetInterfacePointer();
		CmdLineArgString* arg = (CmdLineArgString*)cmdline.getOption(GLE_OPT_FINDDEPS)->getArg(0);
		do_find_deps_sub(iface, arg->getValue());
		do_save_config();
		do_wait_for_enter();
		exit(0);
	}
}
