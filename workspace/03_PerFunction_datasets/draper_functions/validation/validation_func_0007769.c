setText( const QString& text )
{
    if( d->enableClickMsg )
    {
        update();
    }
    if( d->enableSqueezedText && isReadOnly() )
    {
        d->squeezedText = text;
        setSqueezedText();
        return;
    }

    QLineEdit::setText( text );
}
