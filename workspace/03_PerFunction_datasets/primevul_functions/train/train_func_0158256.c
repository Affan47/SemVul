ves_icall_System_Threading_Thread_ClrState (MonoInternalThread* this, guint32 state)
{
	mono_thread_clr_state (this, state);

	if (state & ThreadState_Background) {


		SetEvent (background_change_event);
	}
}
