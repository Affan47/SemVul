run()
{
#define _x m_xmlWriter
    _x->setAutoFormatting( true );
    _x->writeStartDocument();
    _x->writeStartElement( "opml" );
    _x->writeAttribute( "version", "2.0" );
    _x->writeStartElement( "head" );
    QMapIterator<QString, QString> ai( m_headerData );
    while( ai.hasNext() )
    {
        ai.next();
        _x->writeTextElement( ai.key(), ai.value() );
    }
    _x->writeEndElement();
    _x->writeStartElement( "body" );
    foreach( const OpmlOutline *childOutline, m_rootOutlines )
        writeOutline( childOutline );
    _x->writeEndDocument();
    emit result( 0 );
}
