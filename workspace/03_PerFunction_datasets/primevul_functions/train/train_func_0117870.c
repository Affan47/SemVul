void Display::stop() {

        if (!m_started)
            return;


        m_greeter->stop();


        m_socketServer->stop();


        m_displayServer->blockSignals(true);
        m_displayServer->stop();
        m_displayServer->blockSignals(false);


        m_started = false;


        emit stopped();
    }
