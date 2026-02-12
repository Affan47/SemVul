void Display::startAuth(const QString &user, const QString &password, const Session &session) {
        m_passPhrase = password;


        if (!session.isValid()) {
            qCritical() << "Invalid session" << session.fileName();
            return;
        }
        if (session.xdgSessionType().isEmpty()) {
            qCritical() << "Failed to find XDG session type for session" << session.fileName();
            return;
        }
        if (session.exec().isEmpty()) {
            qCritical() << "Failed to find command for session" << session.fileName();
            return;
        }

        QString existingSessionId;

        if (Logind::isAvailable() && mainConfig.Users.ReuseSession.get()) {
            OrgFreedesktopLogin1ManagerInterface manager(Logind::serviceName(), Logind::managerPath(), QDBusConnection::systemBus());
            auto reply = manager.ListSessions();
            reply.waitForFinished();

            foreach(const SessionInfo &s, reply.value()) {
                if (s.userName == user) {
                    OrgFreedesktopLogin1SessionInterface session(Logind::serviceName(), s.sessionPath.path(), QDBusConnection::systemBus());
                    if (session.service() == QLatin1String("sddm")) {
                        existingSessionId =  s.sessionId;
                        break;
                    }
                }
            }
        }


        m_lastSession = session;


        m_sessionName = session.fileName();


        qDebug() << "Session" << m_sessionName << "selected, command:" << session.exec();


        int vt = terminalId();
        if (session.xdgSessionType() == QLatin1String("wayland"))
            vt = VirtualTerminal::setUpNewVt();
        m_lastSession.setVt(vt);

        QProcessEnvironment env;
        env.insert(QStringLiteral("PATH"), mainConfig.Users.DefaultPath.get());
        if (session.xdgSessionType() == QLatin1String("x11"))
            env.insert(QStringLiteral("DISPLAY"), name());
        env.insert(QStringLiteral("XDG_SEAT_PATH"), daemonApp->displayManager()->seatPath(seat()->name()));
        env.insert(QStringLiteral("XDG_SESSION_PATH"), daemonApp->displayManager()->sessionPath(QStringLiteral("Session%1").arg(daemonApp->newSessionId())));
        env.insert(QStringLiteral("DESKTOP_SESSION"), session.desktopSession());
        env.insert(QStringLiteral("XDG_CURRENT_DESKTOP"), session.desktopNames());
        env.insert(QStringLiteral("XDG_SESSION_CLASS"), QStringLiteral("user"));
        env.insert(QStringLiteral("XDG_SESSION_TYPE"), session.xdgSessionType());
        env.insert(QStringLiteral("XDG_SEAT"), seat()->name());

        env.insert(QStringLiteral("XDG_SESSION_DESKTOP"), session.desktopNames());
        if (seat()->name() == QLatin1String("seat0")) {
            env.insert(QStringLiteral("XDG_VTNR"), QString::number(vt));
        }

        m_auth->insertEnvironment(env);

        m_auth->setUser(user);
        if (existingSessionId.isNull()) {
            m_auth->setSession(session.exec());
        } else {


            connect(m_auth, &Auth::authentication, this, [=](const QString &, bool success){
                if(!success)
                    return;
                qDebug() << "activating existing seat";
                OrgFreedesktopLogin1ManagerInterface manager(Logind::serviceName(), Logind::managerPath(), QDBusConnection::systemBus());
                manager.UnlockSession(existingSessionId);
                manager.ActivateSession(existingSessionId);
            });
        }
        m_auth->start();
    }
