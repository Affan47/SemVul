void Greeter::onHelperFinished(Auth::HelperExitStatus status) {

        m_started = false;


        qDebug() << "Greeter stopped.";


        m_auth->deleteLater();
        m_auth = nullptr;
    }
