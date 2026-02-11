refreshTokenState()
{
    if( cardStateMayHaveChanged() ) {
        log->log("card changed\n");
	invalidateLogin(true);
        closeAllSessions();
	unloadObjects();
        connectToToken();

        if( state & APPLET_PERSONALIZED ) {
            try {
                loadObjects();
            } catch(PKCS11Exception&) {
                log->log("refreshTokenState: Failed to load objects.\n");
                unloadObjects();
            }
        } else if (state & APPLET_SELECTABLE) {
	    initEmpty();
	}

    }
}
