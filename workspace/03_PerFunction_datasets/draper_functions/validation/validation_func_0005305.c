close()
{
    disconnect( &The::audioController().m_thread, SIGNAL( httpBufferSizeChanged( int ) ),
        this,                                     SLOT( onHttpBufferSizeChanged( int ) ) );

    disconnect( &The::audioController().m_thread, SIGNAL( decodedBufferSizeChanged( int ) ),
        this,                                     SLOT( onDecodedBufferSizeChanged( int ) ) );

    disconnect( &The::audioController().m_thread, SIGNAL( outputBufferSizeChanged( int ) ),
        this,                                     SLOT( onOutputBufferSizeChanged( int ) ) );

    if( m_logFile.is_open() )
    {
        m_logFile.close();
    }
    m_logTimer->stop();

    QDialog::accept();
}
