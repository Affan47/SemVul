ves_icall_System_Environment_Exit (int result)
{
	MONO_ARCH_SAVE_REGS;

	mono_threads_set_shutting_down ();

	mono_runtime_set_shutting_down ();


	mono_thread_pool_cleanup ();


	mono_thread_suspend_all_other_threads ();

	mono_runtime_quit ();


	exit (result);
}
