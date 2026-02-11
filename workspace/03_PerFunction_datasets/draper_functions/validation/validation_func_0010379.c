CertToFormattedString( const QSslCertificate& cert ) {
    QStringList message;
    message << cert.subjectInfo( QSslCertificate::CommonName );
    message << QString("Issuer: %1").arg(cert.issuerInfo( QSslCertificate::CommonName ) );
    message << QString("Not valid before: %1").arg( cert.effectiveDate().toString());
    message << QString("Valid until: %1").arg( cert.expiryDate().toString() );

    QMultiMap<QSsl::AlternateNameEntryType, QString> names = cert.alternateSubjectNames();
    if (names.count() > 0) {
        QString list;
        list += ("Alternate Names:");
        list += QStringList(names.values(QSsl::DnsEntry)).join(QLatin1String(", "));
        list += QLatin1String("\n");
        message << list;
    }
    QString result = message.join(QLatin1String("\n"));
    return result;
}
