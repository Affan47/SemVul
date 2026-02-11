storedPut( const QByteArray& arr, const KUrl& url, int permissions,
                                   JobFlags flags )
{
    KIO_ARGS << url << qint8( (flags & Overwrite) ? 1 : 0 ) << qint8( (flags & Resume) ? 1 : 0 ) << permissions;
    StoredTransferJob * job = StoredTransferJobPrivate::newJob(url, CMD_PUT, packedArgs, QByteArray(), flags );
    job->setData( arr );
    return job;
}
