confirmUnsubscribe( Podcasts::SqlPodcastChannelPtr channel )
{
    KDialog unsubscribeDialog;
    unsubscribeDialog.setCaption( i18n( "Unsubscribe" ) );

    KVBox *vbox = new KVBox( &unsubscribeDialog );

    QString question( i18n( "Do you really want to unsubscribe from \"%1\"?", channel->title() ) );
    QLabel *label = new QLabel( question, vbox );
    label->setWordWrap( true );
    label->setMaximumWidth( 400 );

    QCheckBox *deleteMediaCheckBox = new QCheckBox( i18n( "Delete downloaded episodes" ), vbox );
    unsubscribeDialog.setMainWidget( vbox );
    unsubscribeDialog.setButtons( KDialog::Ok | KDialog::Cancel );

    QPair<bool, bool> result;
    result.first = unsubscribeDialog.exec() == QDialog::Accepted;
    result.second = deleteMediaCheckBox->isChecked();
    return result;
}
