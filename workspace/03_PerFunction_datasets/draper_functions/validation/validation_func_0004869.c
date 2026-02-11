setMainWidget( QWidget *widget )
{
    Q_D(KDialog);
    if ( d->mMainWidget == widget )
        return;
    d->mMainWidget = widget;
    if (d->mMainWidget && d->mMainWidget->layout()) {

        d->mMainWidget->layout()->setMargin(0);
    }
    d->setupLayout();
}
