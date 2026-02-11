setupDatabaseConnection()
{
    DEBUG_BLOCK

    const bool isSqlite = m_driver == FastForwardImporter::SQLite;

    QString driver = driverName();
    if( driver.isEmpty() )
    {
        emit importError( i18n( "No database driver was selected" ) );
        return;
    }

    if( isSqlite && !QFile::exists( m_databaseLocation ) )
    {
        emit importError( i18n( "Database could not be found at: %1", m_databaseLocation ) );
        return;
    }

    m_db = QSqlDatabase::addDatabase( driver );
    m_db.setDatabaseName( isSqlite ? m_databaseLocation : m_database );

    if( !isSqlite )
    {
        m_db.setHostName( m_hostname );
        m_db.setUserName( m_username );
        m_db.setPassword( m_password );
    }
}
