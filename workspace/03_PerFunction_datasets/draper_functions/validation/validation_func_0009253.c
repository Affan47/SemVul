saveIntoItem(int x)
{
	ProxyItem &s = d->list[x];
	s.name = le_name->text();
	int i = cb_type->currentItem();
	s.type = "http";
	if(i == 0)
		s.type = "http";
	else if(i == 1)
		s.type = "socks";
	else if(i == 2)
		s.type = "poll";
	s.settings = d->pe_settings->proxySettings();
}
