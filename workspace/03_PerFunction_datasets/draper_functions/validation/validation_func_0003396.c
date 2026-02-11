addItem(ProviderItem *item, int priority)
{
	if(priority < 0)
	{

		if(!providerItemList.isEmpty())
		{
			ProviderItem *last = providerItemList.last();
			item->priority = last->priority;
		}
		else
			item->priority = 0;

		providerItemList.append(item);
		providerList.append(item->p);
	}
	else
	{

		int n = 0;
		for(; n < providerItemList.count(); ++n)
		{
			ProviderItem *i = providerItemList[n];
			if(i->priority >= priority)
				break;
		}

		item->priority = priority;
		providerItemList.insert(n, item);
		providerList.insert(n, item->p);
	}

	logDebug(QString("item added [%1]").arg(item->p->name()));
}
