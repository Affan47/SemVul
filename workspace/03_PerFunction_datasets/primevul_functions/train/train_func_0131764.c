void Greeter::stop() {

        if (!m_started)
            return;


        qDebug() << "Greeter stopping...";

        if (daemonApp->testing()) {

            m_process->terminate();


            if (!m_process->waitForFinished(5000))
                m_process->kill();
        }
    }
