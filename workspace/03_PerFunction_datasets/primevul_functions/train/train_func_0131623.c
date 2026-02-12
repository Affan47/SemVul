void RemoteFsDevice::load()
{
    if (isConnected()) {
        setAudioFolder();
        readOpts(settingsFileName(), opts, true);
        rescan(false);
    }
}
