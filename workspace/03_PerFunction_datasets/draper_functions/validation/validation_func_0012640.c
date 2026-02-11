walletAsyncOpened(int tId, int handle) {
#ifdef HAVE_KSECRETSSERVICE
    if (walletLauncher->m_useKSecretsService) {

        Q_ASSERT(0);
    }
    else {
#endif

        if (d->transactionId != tId || d->handle != -1) {
            return;
        }


        disconnect(this, SLOT(walletAsyncOpened(int,int)));

        d->handle = handle;
        emit walletOpened(handle > 0);
#ifdef HAVE_KSECRETSSERVICE
    }
#endif
}
