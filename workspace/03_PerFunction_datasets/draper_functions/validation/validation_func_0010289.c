providerIcon( const QString &id ) const
{
    foreach( const ProviderData &data, m_providerData )
    {
        if( data.id == id )
            return data.icon;
    }
    return QIcon();
}
