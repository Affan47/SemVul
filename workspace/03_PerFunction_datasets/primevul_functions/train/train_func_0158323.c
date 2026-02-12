ves_icall_System_Threading_Thread_SetState (MonoInternalThread* this, guint32 state)
{
	mono_thread_set_state (this, state);

	if (state & ThreadState_Background) {


		SetEvent (background_change_event);
	}
}
