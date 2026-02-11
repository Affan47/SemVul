_k_networkStatusChanged( Solid::Networking::Status status )
{
    if ( status == Solid::Networking::Connected || status == Solid::Networking::Unknown ) {
        q->hide();
    } else {
        q->show();
    }
}
