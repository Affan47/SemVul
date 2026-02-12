void Greeter::onSessionStarted(bool success) {

        m_started = success;


        if (success)
            qDebug() << "Greeter session started successfully";
        else
            qDebug() << "Greeter session failed to start";
    }
