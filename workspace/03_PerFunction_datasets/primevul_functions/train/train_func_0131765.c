void Greeter::finished() {

        if (!m_started)
            return;


        m_started = false;


        qDebug() << "Greeter stopped.";


        m_process->deleteLater();
        m_process = nullptr;
    }
