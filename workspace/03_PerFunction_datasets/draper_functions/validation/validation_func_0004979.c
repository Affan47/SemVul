eventThread(void* arg)
{
    VideoRendererWithLock* vr = (VideoRendererWithLock*) arg;
    while (!vr->m_bQuit) {

	vr->processEvent();
    }
    return 0;
}
