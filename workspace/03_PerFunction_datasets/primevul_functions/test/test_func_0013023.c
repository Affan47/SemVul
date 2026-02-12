static void reds_late_initialization(RedsState *reds)
{

    if (reds->late_initialization_done) {
        return;
    }


    for (auto dev: reds->char_devices) {
        auto stream_dev = dynamic_cast<StreamDevice*>(dev.get());
        if (stream_dev) {
            stream_dev->create_channel();
        }
    }
    reds->late_initialization_done = true;
}
