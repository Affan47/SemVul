KCleanup::cleanTitle() const
{


    QString title = _title;

    if ( title.isEmpty() )
    {
	title = _id;
    }


    title.replace( QRegExp( "&" ), "" );

    return title;
}
