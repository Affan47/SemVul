SyncLoad( const QUrl& url, int timeout ) {
    QEventLoop loop;
    syncLoadOK_ = false;
    QObject::connect( webView_, SIGNAL( loadFinished( bool ) ), &loop, SLOT( quit() ) );
    QObject::connect( webView_, SIGNAL( loadFinished( bool ) ), this, SLOT( OnLoadFinished( bool ) ) );
    if( timeout >= 0 ) {

        QTimer::singleShot( timeout, &loop, SLOT( quit() ) );
    }
    webView_->load( url );


    loop.exec();
    QObject::disconnect( this, SIGNAL( loadFinished( bool ) ), this, SLOT( OnLoadFinished( bool ) ) );
    return syncLoadOK_;
}
