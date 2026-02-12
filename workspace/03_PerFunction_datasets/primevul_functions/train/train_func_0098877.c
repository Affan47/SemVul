DEFINE_IDTENTRY_RAW(xenpv_exc_debug)
{


	if (user_mode(regs))
		noist_exc_debug(regs);
	else
		exc_debug(regs);
}
