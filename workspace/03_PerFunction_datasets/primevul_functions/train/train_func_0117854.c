void Display::start() {

        if (m_started)
            return;


        if (!m_displayServer->start()) {
            qFatal("Display server failed to start. Exiting");
        }
    }
