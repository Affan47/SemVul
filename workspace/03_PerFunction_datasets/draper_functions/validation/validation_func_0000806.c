scheduleStartSignalHandlers(Capability *cap)
{
    if (RtsFlags.MiscFlags.install_signal_handlers && signals_pending()) {

	startSignalHandlers(cap);
    }
}
