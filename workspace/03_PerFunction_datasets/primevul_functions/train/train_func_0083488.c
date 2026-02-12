int main(int argc, char *argv[])
{

#ifdef HAVE_GUSI_H
    GUSISetup(GUSIwithSIOUXSockets);
    GUSISetup(GUSIwithInternetSockets);
#endif

#ifdef WITH_TCPWRAPPER


    dcmTCPWrapperDaemonName.set(NULL);
#endif

#ifdef HAVE_WINSOCK_H
    WSAData winSockData;

    WORD winSockVersionNeeded = MAKEWORD( 1, 1 );
    WSAStartup(winSockVersionNeeded, &winSockData);
#endif

    OFCmdUnsignedInt opt_port = 0;
    Uint32           clientID = 0;

    OFConsoleApplication app(OFFIS_CONSOLE_APPLICATION , "Sample message server for class DVPSIPCClient", rcsid);
    OFCommandLine cmd;
    cmd.setOptionColumns(LONGCOL, SHORTCOL);
    cmd.setParamColumn(LONGCOL + SHORTCOL + 2);

    cmd.addParam("port", "port number to listen at");

    cmd.addGroup("general options:", LONGCOL, SHORTCOL);
      cmd.addOption("--help", "-h", "print this help text and exit", OFCommandLine::AF_Exclusive);
      OFLog::addOptions(cmd);


    prepareCmdLineArgs(argc, argv, OFFIS_CONSOLE_APPLICATION);
    if (app.parseCommandLine(cmd, argc, argv))
    {
      cmd.getParam(1, opt_port);
      OFLog::configureFromCommandLine(cmd, app);
    }

    OFLOG_DEBUG(msgservLogger, rcsid << OFendl);

    unsigned short networkPort = (unsigned short) opt_port;
    if (networkPort==0)
    {
      OFLOG_FATAL(msgservLogger, "no or invalid port number");
      return 10;
    }

#ifndef DISABLE_PORT_PERMISSION_CHECK
#ifdef HAVE_GETEUID

    if ((networkPort < 1024)&&(geteuid() != 0))
    {
      OFLOG_FATAL(msgservLogger, "cannot listen on port " << networkPort << ", insufficient privileges");
      return 10;
    }
#endif
#endif


    int s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0)
    {
      OFLOG_FATAL(msgservLogger, "failed to create socket");
      return 10;
    }

#ifdef HAVE_GUSI_H

#else
    int reuse = 1;
    if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR, (char *) &reuse, sizeof(reuse)) < 0)
    {
      OFLOG_FATAL(msgservLogger, "failed to set socket options");
      return 10;
    }
#endif


    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = (unsigned short) htons(networkPort);
    if (bind(s, (struct sockaddr *) & server, sizeof(server)))
    {
      OFLOG_FATAL(msgservLogger, "failed to bind socket to port, already in use?");
      return 10;
    }
    listen(s, 64);

#if defined(HAVE_SETUID) && defined(HAVE_GETUID)


      setuid(getuid());
#endif

    fd_set fdset;
    struct timeval t;
    int nfound;
    while (1)
    {

      FD_ZERO(&fdset);
      FD_SET(s, &fdset);
      t.tv_sec = 10;
      t.tv_usec = 0;

#ifdef HAVE_INTP_SELECT
      nfound = select(s + 1, (int *)(&fdset), NULL, NULL, &t);
#else
      nfound = select(s + 1, &fdset, NULL, NULL, &t);
#endif


      if (nfound > 0)
      {

        int sock=0;
        struct sockaddr from;
#ifdef HAVE_DECLARATION_SOCKLEN_T
        socklen_t len = sizeof(from);
#elif !defined(HAVE_PROTOTYPE_ACCEPT) || defined(HAVE_INTP_ACCEPT)
        int len = sizeof(from);
#else
        size_t len = sizeof(from);
#endif
        do
        {
          sock = accept(s, &from, &len);
        } while ((sock == -1)&&(errno == EINTR));

        if (sock < 0)
        {
          OFLOG_FATAL(msgservLogger, "unable to accept incoming connection");
          return 10;
        }

#ifdef HAVE_GUSI_H

#else
        reuse = 1;
        if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char *) &reuse, sizeof(reuse)) < 0)
        {
          OFLOG_FATAL(msgservLogger, "failed to set socket options");
          return 10;
        }
#endif


        DcmTCPConnection connection(sock);
        DVPSIPCMessage msg;
        Uint32 i=0;
        Uint32 msgType=0;
        OFString str;

        OFBool finished = OFFalse;
        while (!finished)
        {
          while (! connection.networkDataAvailable(1))
          {

          }
          if (msg.receive(connection))
          {
            OFOStringStream oss;

            msgType = msg.getMessageType();
            if (msgType == DVPSIPCMessage::OK)
            {
                oss << "received 'OK' (should not happen)" << OFendl;
            } else if (msgType == DVPSIPCMessage::requestApplicationID) {
                oss << "New client requests application ID, assigning #" << clientID+1 << OFendl
                     << "Application Type: ";
                if (msg.extractIntFromPayload(i)) oss << applicationType(i) << OFendl; else oss << "(none)" << OFendl;
                if (msg.extractStringFromPayload(str)) oss << str << OFendl; else oss << "No description (should not happen)." << OFendl;
            } else if (msgType == DVPSIPCMessage::assignApplicationID) {
                oss << "received 'AssignApplicationID' (should not happen)." << OFendl;
            } else if (msgType == DVPSIPCMessage::applicationTerminates) {
                if (msg.extractIntFromPayload(i)) oss << "#" << i << ": "; else oss << "unknown client: ";
                oss << "Application Terminates, status: ";
                if (msg.extractIntFromPayload(i)) oss << statusString(i) << OFendl; else oss << "(none)" << OFendl;
            } else if (msgType == DVPSIPCMessage::receivedUnencryptedDICOMConnection) {
                if (msg.extractIntFromPayload(i)) oss << "#" << i << ": "; else oss << "unknown client: ";
                oss << "Received Unencrypted DICOM Connection, status: ";
                if (msg.extractIntFromPayload(i)) oss << statusString(i) << OFendl; else oss << "(none)" << OFendl;
                if (msg.extractStringFromPayload(str)) oss << str << OFendl; else oss << "No description (should not happen)." << OFendl;
            } else if (msgType == DVPSIPCMessage::receivedEncryptedDICOMConnection) {
                if (msg.extractIntFromPayload(i)) oss << "#" << i << ": "; else oss << "unknown client: ";
                oss << "Received Encrypted DICOM Connection, status: ";
                if (msg.extractIntFromPayload(i)) oss << statusString(i) << OFendl; else oss << "(none)" << OFendl;
                if (msg.extractStringFromPayload(str)) oss << str << OFendl; else oss << "No description (should not happen)." << OFendl;
            } else if (msgType == DVPSIPCMessage::connectionClosed) {
                if (msg.extractIntFromPayload(i)) oss << "#" << i << ": "; else oss << "unknown client: ";
                oss << "Connection Closed, status: ";
                if (msg.extractIntFromPayload(i)) oss << statusString(i) << OFendl; else oss << "(none)" << OFendl;
            } else if (msgType == DVPSIPCMessage::connectionAborted) {
                if (msg.extractIntFromPayload(i)) oss << "#" << i << ": "; else oss << "unknown client: ";
                oss << "Connection Aborted, status: ";
                if (msg.extractIntFromPayload(i)) oss << statusString(i) << OFendl; else oss << "(none)" << OFendl;
                if (msg.extractStringFromPayload(str)) oss << str << OFendl; else oss << "No description (should not happen)." << OFendl;
            } else if (msgType == DVPSIPCMessage::requestedUnencryptedDICOMConnection) {
                if (msg.extractIntFromPayload(i)) oss << "#" << i << ": "; else oss << "unknown client: ";
                oss << "Requested Unencrypted DICOM Connection, status: ";
                if (msg.extractIntFromPayload(i)) oss << statusString(i) << OFendl; else oss << "(none)" << OFendl;
                if (msg.extractStringFromPayload(str)) oss << str << OFendl; else oss << "No description (should not happen)." << OFendl;
            } else if (msgType == DVPSIPCMessage::requestedEncryptedDICOMConnection) {
                if (msg.extractIntFromPayload(i)) oss << "#" << i << ": "; else oss << "unknown client: ";
                oss << "Requested Encrypted DICOM Connection, status: ";
                if (msg.extractIntFromPayload(i)) oss << statusString(i) << OFendl; else oss << "(none)" << OFendl;
                if (msg.extractStringFromPayload(str)) oss << str << OFendl; else oss << "No description (should not happen)." << OFendl;
            } else if (msgType == DVPSIPCMessage::receivedDICOMObject) {
                if (msg.extractIntFromPayload(i)) oss << "#" << i << ": "; else oss << "unknown client: ";
                oss << "Received DICOM Object, status: ";
                if (msg.extractIntFromPayload(i)) oss << statusString(i) << OFendl; else oss << "(none)" << OFendl;
                if (msg.extractStringFromPayload(str)) oss << str << OFendl; else oss << "No description (should not happen)." << OFendl;
            } else if (msgType == DVPSIPCMessage::sentDICOMObject) {
                if (msg.extractIntFromPayload(i)) oss << "#" << i << ": "; else oss << "unknown client: ";
                oss << "Sent DICOM Object, status: ";
                if (msg.extractIntFromPayload(i)) oss << statusString(i) << OFendl; else oss << "(none)" << OFendl;
                if (msg.extractStringFromPayload(str)) oss << str << OFendl; else oss << "No description (should not happen)." << OFendl;
            } else {
                if (msg.extractIntFromPayload(i)) oss << "#" << i << ": "; else oss << "unknown client: ";
                oss << "received unknown message type " << msg.getMessageType() << ", status: ";
                if (msg.extractIntFromPayload(i)) oss << statusString(i) << OFendl; else oss << "(none)" << OFendl;
            }
            oss << OFStringStream_ends;
            OFSTRINGSTREAM_GETSTR(oss, result);
            OFLOG_INFO(msgservLogger, result);
            OFSTRINGSTREAM_FREESTR(result);
            msg.erasePayload();
            if (msg.getMessageType() == DVPSIPCMessage::requestApplicationID)
            {
              msg.setMessageType(DVPSIPCMessage::assignApplicationID);
              msg.addIntToPayload(++clientID);
            } else {
              msg.setMessageType(DVPSIPCMessage::OK);
            }
            if (! msg.send(connection))
            {
              OFLOG_WARN(msgservLogger, "unable to send response message, closing connection");
              finished = OFTrue;
            }
          } else finished = OFTrue;
        }


        connection.close();
      }
    }

#ifdef HAVE_WINSOCK_H
    WSACleanup();
#endif

    return 0;
}
