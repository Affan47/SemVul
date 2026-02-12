bool OpenConnectionTask::handleStateHelper(const Imap::Responses::State *const resp)
{
    if (_dead) {
        _failed("Asked to die");
        return true;
    }
    using namespace Imap::Responses;

    if (model->accessParser(parser).connState == CONN_STATE_CONNECTED_PRETLS_PRECAPS) {
        if (!resp->tag.isEmpty()) {
            throw Imap::UnexpectedResponseReceived("Waiting for initial OK/BYE/PREAUTH, but got tagged response instead", *resp);
        }
    } else if (model->accessParser(parser).connState > CONN_STATE_CONNECTED_PRETLS_PRECAPS) {
        if (resp->tag.isEmpty()) {
            return false;
        }
    }

    switch (model->accessParser(parser).connState) {

    case CONN_STATE_AUTHENTICATED:
    case CONN_STATE_SELECTING:
    case CONN_STATE_SYNCING:
    case CONN_STATE_SELECTED:
    case CONN_STATE_FETCHING_PART:
    case CONN_STATE_FETCHING_MSG_METADATA:
    case CONN_STATE_LOGOUT:
    {
        QByteArray message = "No response expected by the OpenConnectionTask in state " +
                Imap::connectionStateToString(model->accessParser(parser).connState).toUtf8();

        throw Imap::UnexpectedResponseReceived(message.constData(), *resp);
    }

    case CONN_STATE_NONE:
    case CONN_STATE_HOST_LOOKUP:
    case CONN_STATE_CONNECTING:

    case CONN_STATE_CONNECTED_PRETLS_PRECAPS:

    {
        switch (resp->kind) {
        case PREAUTH:
            if (model->m_startTls) {


                logout(tr("Configuration requires sending STARTTLS, but the IMAP server greets us with PREAUTH. "
                          "Encryption cannot be established. If this configuration worked previously, someone "
                          "is after your data and they are pretty smart."));
                return true;
            }

            if (model->accessParser(parser).capabilitiesFresh) {

                if (TROJITA_COMPRESS_DEFLATE && model->accessParser(parser).capabilities.contains(QLatin1String("COMPRESS=DEFLATE"))) {
                    compressCmd = parser->compressDeflate();
                    model->changeConnectionState(parser, CONN_STATE_COMPRESS_DEFLATE);
                } else {

                    model->changeConnectionState(parser, CONN_STATE_AUTHENTICATED);
                    onComplete();
                }
            } else {
                model->changeConnectionState(parser, CONN_STATE_POSTAUTH_PRECAPS);
                capabilityCmd = parser->capability();
            }
            return true;

        case OK:
            if (!model->accessParser(parser).capabilitiesFresh) {
                model->changeConnectionState(parser, CONN_STATE_CONNECTED_PRETLS);
                capabilityCmd = parser->capability();
            } else {
                startTlsOrLoginNow();
            }
            return true;

        case BYE:
            logout(tr("Server has closed the connection"));
            return true;

        case BAD:
            model->changeConnectionState(parser, CONN_STATE_LOGOUT);

            if (resp->respCode != ALERT) {
                emit model->alertReceived(tr("The server replied with the following BAD response:\n%1").arg(resp->message));
            }
            logout(tr("Server has greeted us with a BAD response"));
            return true;

        default:
            throw Imap::UnexpectedResponseReceived("Waiting for initial OK/BYE/BAD/PREAUTH, but got this instead", *resp);
        }
        break;
    }

    case CONN_STATE_CONNECTED_PRETLS:

    {
        bool wasCaps = checkCapabilitiesResult(resp);
        if (wasCaps && !_finished) {
            startTlsOrLoginNow();
        }
        return wasCaps;
    }

    case CONN_STATE_STARTTLS_ISSUED:
    {
        if (resp->tag == startTlsCmd) {
            if (resp->kind == OK) {
                model->changeConnectionState(parser, CONN_STATE_STARTTLS_HANDSHAKE);
                if (!model->m_startTls) {


                    EMIT_LATER_NOARG(model, requireStartTlsInFuture);
                }
            } else {
                logout(tr("STARTTLS failed: %1").arg(resp->message));
            }
            return true;
        }
        return false;
    }

    case CONN_STATE_SSL_HANDSHAKE:
    case CONN_STATE_STARTTLS_HANDSHAKE:


        Q_ASSERT(false);
        return false;

    case CONN_STATE_STARTTLS_VERIFYING:
    case CONN_STATE_SSL_VERIFYING:
    {


        qDebug() << "OpenConnectionTask: ignoring response, we're still waiting for SSL policy decision";
        return false;
    }

    case CONN_STATE_ESTABLISHED_PRECAPS:

    {
        bool wasCaps = checkCapabilitiesResult(resp);
        if (wasCaps && !_finished) {
            if (model->accessParser(parser).capabilities.contains(QLatin1String("LOGINDISABLED"))) {
                logout(tr("Capabilities still contain LOGINDISABLED even after STARTTLS"));
            } else {
                model->changeConnectionState(parser, CONN_STATE_LOGIN);
                askForAuth();
            }
        }
        return wasCaps;
    }

    case CONN_STATE_LOGIN:

    {
        if (resp->tag == loginCmd) {
            loginCmd.clear();

            if (resp->kind == OK) {
                if (resp->respCode == CAPABILITIES || model->accessParser(parser).capabilitiesFresh) {

                    if (TROJITA_COMPRESS_DEFLATE && model->accessParser(parser).capabilities.contains(QLatin1String("COMPRESS=DEFLATE"))) {
                        compressCmd = parser->compressDeflate();
                        model->changeConnectionState(parser, CONN_STATE_COMPRESS_DEFLATE);
                    } else {
                        model->changeConnectionState(parser, CONN_STATE_AUTHENTICATED);
                        onComplete();
                    }
                } else {

                    model->changeConnectionState(parser, CONN_STATE_POSTAUTH_PRECAPS);
                    capabilityCmd = parser->capability();
                }
            } else {

                QString message;
                switch (resp->respCode) {
                case Responses::UNAVAILABLE:
                    message = tr("Temporary failure because a subsystem is down.");
                    break;
                case Responses::AUTHENTICATIONFAILED:
                    message = tr("Authentication failed.  This often happens due to bad password or wrong user name.");
                    break;
                case Responses::AUTHORIZATIONFAILED:
                    message = tr("Authentication succeeded in using the authentication identity, "
                                 "but the server cannot or will not allow the authentication "
                                 "identity to act as the requested authorization identity.");
                    break;
                case Responses::EXPIRED:
                    message = tr("Either authentication succeeded or the server no longer had the "
                                 "necessary data; either way, access is no longer permitted using "
                                 "that passphrase.  You should get a new passphrase.");
                    break;
                case Responses::PRIVACYREQUIRED:
                    message = tr("The operation is not permitted due to a lack of privacy.");
                    break;
                case Responses::CONTACTADMIN:
                    message = tr("You should contact the system administrator or support desk.");
                    break;
                default:
                    break;
                }

                if (message.isEmpty()) {
                    message = tr("Login failed: %1").arg(resp->message);
                } else {
                    message = tr("%1\n\n%2").arg(message, resp->message);
                }
                EMIT_LATER(model, authAttemptFailed, Q_ARG(QString, message));
                model->m_imapPassword.clear();
                model->m_hasImapPassword = false;
                if (model->accessParser(parser).connState == CONN_STATE_LOGOUT) {

                    _failed(QLatin1String("Connection closed after a failed login"));
                    return true;
                }
                askForAuth();
            }
            return true;
        }
        return false;
    }

    case CONN_STATE_POSTAUTH_PRECAPS:
    {
        bool wasCaps = checkCapabilitiesResult(resp);
        if (wasCaps && !_finished) {
            model->changeConnectionState(parser, CONN_STATE_AUTHENTICATED);
            onComplete();
        }
        return wasCaps;
    }

    case CONN_STATE_COMPRESS_DEFLATE:
        if (resp->tag == compressCmd) {
            model->changeConnectionState(parser, CONN_STATE_AUTHENTICATED);
            onComplete();
            return true;
        } else {
            return false;
        }
        break;

    }


    Q_ASSERT(false);
    return false;
}
