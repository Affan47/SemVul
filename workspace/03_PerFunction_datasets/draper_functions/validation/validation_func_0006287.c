DataSend()
    {
        if (MidiSend(fNetMidiCaptureBuffer, fParams.fSendMidiChannels, fParams.fSendAudioChannels) == SOCKET_ERROR) {
            return SOCKET_ERROR;
        }
        return AudioSend(fNetAudioCaptureBuffer, fParams.fSendAudioChannels);
    }
