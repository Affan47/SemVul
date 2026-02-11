requestListNames()
{
	GetPrivacyListsTask* t = new GetPrivacyListsTask ( rootTask_ );
	connect ( t,SIGNAL (finished()),SLOT (receiveLists()) );
	t->go ( true );
}
