initialize(int argc, char** argv)
{
    FaxServer::initialize(argc, argv);
    faxApp::initialize(argc, argv);

    for (GetoptIter iter(argc, argv, getOpts()); iter.notDone(); iter++)
	switch (iter.option()) {
	case 'c':
	    readConfigItem(iter.optArg());
	    break;
	case 'D':
	    detachFromTTY();
	    break;
	}
    modemLock = getUUCPLock(getModemDevice());


    sendModemStatus("N" | getModemNumber());
}
