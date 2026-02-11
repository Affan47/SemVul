delete_instance()
{
    if (SignalHandler::d_instance) {
        for (int i = 0; i < NSIG; ++i) {


        	d_signal_handlers[i] = 0;
            d_old_handlers[i] = 0;
        }

        delete SignalHandler::d_instance;
        SignalHandler::d_instance = 0;
    }
}
