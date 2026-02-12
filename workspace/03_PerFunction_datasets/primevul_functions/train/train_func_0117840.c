void Display::login(QLocalSocket *socket,
                        const QString &user, const QString &password,
                        const Session &session) {
        m_socket = socket;


        if (user == QLatin1String("sddm")) {
            return;
        }


        startAuth(user, password, session);
    }
