void Display::displayServerStarted() {

        if (m_started)
            return;


        m_displayServer->setupDisplay();


        qDebug() << "Display server started.";

        if ((daemonApp->first || mainConfig.Autologin.Relogin.get()) &&
            !mainConfig.Autologin.User.get().isEmpty()) {

            daemonApp->first = false;


            m_started = true;

            bool success = attemptAutologin();
            if (success) {
                return;
            }
        }


        m_socketServer->start(m_displayServer->display());

        if (!daemonApp->testing()) {

            struct passwd *pw = getpwnam("sddm");
            if (pw) {
                if (chown(qPrintable(m_socketServer->socketAddress()), pw->pw_uid, pw->pw_gid) == -1) {
                    qWarning() << "Failed to change owner of the socket";
                    return;
                }
            }
        }


        m_greeter->setDisplay(this);
        m_greeter->setAuthPath(qobject_cast<XorgDisplayServer *>(m_displayServer)->authPath());
        m_greeter->setSocket(m_socketServer->socketAddress());
        m_greeter->setTheme(findGreeterTheme());


        m_greeter->start();


        daemonApp->first = false;


        m_started = true;
    }
