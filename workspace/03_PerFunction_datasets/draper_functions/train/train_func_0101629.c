process(const float *const *inputBuffers,
                                      RealTime timestamp)
{
    if (m_inputStepSize == 0) {
        std::cerr << "PluginBufferingAdapter::process: ERROR: Plugin has not been initialised" << std::endl;
        return FeatureSet();
    }

    FeatureSet allFeatureSets;

    if (m_unrun) {
        m_frame = RealTime::realTime2Frame(timestamp,
                                           int(m_inputSampleRate + 0.5));
        m_unrun = false;
    }


    for (size_t i = 0; i < m_channels; ++i) {
        int written = m_queue[i]->write(inputBuffers[i], m_inputBlockSize);
        if (written < int(m_inputBlockSize) && i == 0) {
            std::cerr << "WARNING: PluginBufferingAdapter::Impl::process: "
                      << "Buffer overflow: wrote " << written
                      << " of " << m_inputBlockSize
                      << " input samples (for plugin step size "
                      << m_stepSize << ", block size " << m_blockSize << ")"
                      << std::endl;
        }
    }


    while (m_queue[0]->getReadSpace() >= int(m_blockSize)) {
        processBlock(allFeatureSets);
    }

    return allFeatureSets;
}
