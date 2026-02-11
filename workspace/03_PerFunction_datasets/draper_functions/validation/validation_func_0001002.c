findNextDialog( bool create )
{
    if ( !d->dialog && create )
    {
        d->dialog = new KFindNextDialog( d->pattern, parentWidget() );
        connect( d->dialog, SIGNAL(user1Clicked()), this, SLOT(_k_slotFindNext()) );
        connect( d->dialog, SIGNAL(finished()), this, SLOT(_k_slotDialogClosed()) );
    }
    return d->dialog;
}
