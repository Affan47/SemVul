fillInstance(KComponentData &ins, const QString &srcdir)
{
    QByteArray catalogs;

    if ( srcdir.isEmpty() ) {
        catalogs += KUrl::fromLocalFile( ins.dirs()->findResource("data", "ksgmltools2/customization/catalog.xml") ).toEncoded();
        ins.dirs()->addResourceType("dtd", "data", "ksgmltools2/");
    } else {
        catalogs += KUrl::fromLocalFile( srcdir +"/customization/catalog.xml" ).toEncoded();
        ins.dirs()->addResourceDir("dtd", srcdir);
    }

    setenv( "XML_CATALOG_FILES", catalogs.constData(), 1 );
    xmlInitializeCatalog();
}
