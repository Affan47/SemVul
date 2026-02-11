setSupportsRegularExpressionFind( bool supports )
{
    if (supports) d->enabled |= KFind::RegularExpression;
    else d->enabled &= ~KFind::RegularExpression;
    d->regExp->setEnabled( supports );
    d->regExp->setChecked( supports && (options() & KFind::RegularExpression) );
    if( !supports)
    {
       d->regExpItem->hide();
       d->regExp->hide();
    }
    else
    {
       d->regExpItem->show();
       d->regExp->show();
    }
}
