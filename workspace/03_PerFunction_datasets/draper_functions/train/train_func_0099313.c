contrastF(const KSharedConfigPtr &config)
{
    if (config) {
        KConfigGroup g( config, "KDE" );
        return 0.1 * g.readEntry( "contrast", 7 );
    }
    return 0.1 * (qreal)contrast();
}
