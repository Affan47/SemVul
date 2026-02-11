updateMatchedLabel()
{
    qint64 fields = m_providersModel->reliableTrackMetadataIntersection();
    QString fieldNames = m_providersModel->fieldsToString( fields );
    matchLabel->setText( i18n( "Tracks matched by: %1", fieldNames ) );
}
