checkExecutable( const QString& path )
{
    #ifdef Q_WS_MAC
    QString bundle = getBundle( path );
    if ( !bundle.isEmpty() ) {

        return bundle;
    }
    #endif
    QFileInfo info( path );
    QFileInfo orig = info;
    #if defined(Q_OS_DARWIN) || defined(Q_OS_MAC)
    FILE *file;
    if (file = fopen(orig.absoluteFilePath().toUtf8().constData(), "r")) {
        fclose(file);
        struct stat _stat;
        if ((stat(orig.absoluteFilePath().toUtf8().constData(), &_stat)) < 0) {
            return QString();
        }
        if ( _stat.st_mode & S_IXUSR ) {
            if ( ((_stat.st_mode & S_IFMT) == S_IFREG) || ((_stat.st_mode & S_IFMT) == S_IFLNK) ) {
                orig.makeAbsolute();
                return orig.filePath();
            }
        }
    }
    return QString();
    #else
    if( info.exists() && info.isSymLink() )
        info = QFileInfo( info.canonicalFilePath() );
    if( info.exists() && info.isExecutable() && info.isFile() ) {


        orig.makeAbsolute();
        return orig.filePath();
    }

    return QString();
    #endif
}
