void Display::slotAuthInfo(const QString &message, Auth::Info info) {

        Q_UNUSED(info);
        qWarning() << "Authentication information:" << message;
    }
