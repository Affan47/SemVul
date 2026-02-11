play( RadioPlaylist& playlist )
{
    m_playlist = &playlist;
    loadNext();


    AudioControllerThread::ResetBufferSizeEvent* e =
        new AudioControllerThread::ResetBufferSizeEvent();
    QCoreApplication::postEvent( m_thread.eventHandler(), e );
}
