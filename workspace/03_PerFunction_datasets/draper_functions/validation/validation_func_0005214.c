parseReleaseList( const QDomElement &e )
{
    QDomNode dNode = e.firstChild();
    QDomElement dElement;
    QStringList list;

    while( !dNode.isNull() )
    {
        if( dNode.isElement() )
        {
            dElement = dNode.toElement();

            if( dElement.tagName() == "release" )
                list << parseRelease( dElement );
        }
        dNode = dNode.nextSibling();
    }
    list.removeDuplicates();
    return list;
}
