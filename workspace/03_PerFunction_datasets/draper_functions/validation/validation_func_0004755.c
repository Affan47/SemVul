doPrepareWriting(const QString &name, const QString &user,
                          const QString &group, qint64 size, mode_t perm,
                          time_t , time_t mtime, time_t ) {
    if ( !isOpen() )
    {
        kWarning(7041) << "You must open the tar file before writing to it\n";
        return false;
    }

    if ( !(mode() & QIODevice::WriteOnly) )
    {
        kWarning(7041) << "You must open the tar file for writing\n";
        return false;
    }


    QString fileName ( QDir::cleanPath( name ) );


    char buffer[ 0x201 ];
    memset( buffer, 0, 0x200 );
    if ( ( mode() & QIODevice::ReadWrite ) == QIODevice::ReadWrite )
        device()->seek(d->tarEnd);


    const QByteArray encodedFileName = QFile::encodeName(fileName);
    const QByteArray uname = user.toLocal8Bit();
    const QByteArray gname = group.toLocal8Bit();


    if ( encodedFileName.length() > 99 )
        d->writeLonglink(buffer,encodedFileName,'L',uname,gname);


    strncpy( buffer, encodedFileName, 99 );
    buffer[99] = 0;

    memset(buffer+0x9d, 0, 0x200 - 0x9d);

    QByteArray permstr = QByteArray::number( (unsigned int)perm, 8 );
    permstr = permstr.rightJustified(6, '0');
    d->fillBuffer(buffer, permstr, size, mtime, 0x30, uname, gname);


    return device()->write( buffer, 0x200 ) == 0x200;
}
