bool Greeter::start() {

        if (m_started)
            return false;

        if (daemonApp->testing()) {

            m_process = new QProcess(this);


            connect(m_process, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(finished()));

            connect(m_process, SIGNAL(readyReadStandardOutput()), SLOT(onReadyReadStandardOutput()));
            connect(m_process, SIGNAL(readyReadStandardError()), SLOT(onReadyReadStandardError()));


            qDebug() << "Greeter starting...";


            QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
            env.insert(QStringLiteral("DISPLAY"), m_display->name());
            env.insert(QStringLiteral("XAUTHORITY"), m_authPath);
            env.insert(QStringLiteral("XCURSOR_THEME"), mainConfig.Theme.CursorTheme.get());
            m_process->setProcessEnvironment(env);


            QStringList args;
            if (daemonApp->testing())
                args << QStringLiteral("--test-mode");
            args << QStringLiteral("--socket") << m_socket
                 << QStringLiteral("--theme") << m_theme;
            m_process->start(QStringLiteral("%1/sddm-greeter").arg(QStringLiteral(BIN_INSTALL_DIR)), args);


            if (m_process->state() == QProcess::NotRunning) {
                qCritical() << "Greeter failed to launch.";
                return false;
            }

            if (!m_process->waitForStarted()) {

                qCritical() << "Failed to start greeter.";


                return false;
            }


            qDebug() << "Greeter started.";


            m_started = true;
        } else {

            m_auth = new Auth(this);
            m_auth->setVerbose(true);
            connect(m_auth, SIGNAL(requestChanged()), this, SLOT(onRequestChanged()));
            connect(m_auth, SIGNAL(session(bool)), this, SLOT(onSessionStarted(bool)));
            connect(m_auth, SIGNAL(finished(Auth::HelperExitStatus)), this, SLOT(onHelperFinished(Auth::HelperExitStatus)));
            connect(m_auth, SIGNAL(info(QString,Auth::Info)), this, SLOT(authInfo(QString,Auth::Info)));
            connect(m_auth, SIGNAL(error(QString,Auth::Error)), this, SLOT(authError(QString,Auth::Error)));


            QStringList args;
            args << QStringLiteral("%1/sddm-greeter").arg(QStringLiteral(BIN_INSTALL_DIR));
            args << QStringLiteral("--socket") << m_socket
                 << QStringLiteral("--theme") << m_theme;


            QProcessEnvironment env;
            QProcessEnvironment sysenv = QProcessEnvironment::systemEnvironment();

            insertEnvironmentList({QStringLiteral("LANG"), QStringLiteral("LANGUAGE"),
                                   QStringLiteral("LC_CTYPE"), QStringLiteral("LC_NUMERIC"), QStringLiteral("LC_TIME"), QStringLiteral("LC_COLLATE"),
                                   QStringLiteral("LC_MONETARY"), QStringLiteral("LC_MESSAGES"), QStringLiteral("LC_PAPER"), QStringLiteral("LC_NAME"),
                                   QStringLiteral("LC_ADDRESS"), QStringLiteral("LC_TELEPHONE"), QStringLiteral("LC_MEASUREMENT"), QStringLiteral("LC_IDENTIFICATION"),
                                   QStringLiteral("LD_LIBRARY_PATH"),
                                   QStringLiteral("QML2_IMPORT_PATH"),
                                   QStringLiteral("QT_PLUGIN_PATH"),
                                   QStringLiteral("XDG_DATA_DIRS")
            }, sysenv, env);

            env.insert(QStringLiteral("PATH"), mainConfig.Users.DefaultPath.get());
            env.insert(QStringLiteral("DISPLAY"), m_display->name());
            env.insert(QStringLiteral("XAUTHORITY"), m_authPath);
            env.insert(QStringLiteral("XCURSOR_THEME"), mainConfig.Theme.CursorTheme.get());
            env.insert(QStringLiteral("XDG_SEAT"), m_display->seat()->name());
            env.insert(QStringLiteral("XDG_SEAT_PATH"), daemonApp->displayManager()->seatPath(m_display->seat()->name()));
            env.insert(QStringLiteral("XDG_SESSION_PATH"), daemonApp->displayManager()->sessionPath(QStringLiteral("Session%1").arg(daemonApp->newSessionId())));
            env.insert(QStringLiteral("XDG_VTNR"), QString::number(m_display->terminalId()));
            env.insert(QStringLiteral("XDG_SESSION_CLASS"), QStringLiteral("greeter"));
            env.insert(QStringLiteral("XDG_SESSION_TYPE"), m_display->sessionType());
            m_auth->insertEnvironment(env);


            qDebug() << "Greeter starting...";


            m_auth->setUser(QStringLiteral("sddm"));
            m_auth->setGreeter(true);
            m_auth->setSession(args.join(QLatin1Char(' ')));
            m_auth->start();
        }


        return true;
    }
