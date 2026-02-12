mono_thread_init_apartment_state (void)
{
#ifdef HOST_WIN32
	MonoInternalThread* thread = mono_thread_internal_current ();


	if (CoInitializeEx(NULL, (thread->apartment_state == ThreadApartmentState_STA)
			? COINIT_APARTMENTTHREADED
			: COINIT_MULTITHREADED) < 0) {
		thread->apartment_state = ThreadApartmentState_Unknown;
	}
#endif
}
