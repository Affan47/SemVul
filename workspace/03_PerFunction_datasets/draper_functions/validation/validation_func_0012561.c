removeLabels( const QStringList labels )
{
    if ( !labels.isEmpty() )
    {
        for (int x = 0; x < labels.size(); ++x)
        {
            removeLabel( labels.at( x ) );
        }
    }
}
