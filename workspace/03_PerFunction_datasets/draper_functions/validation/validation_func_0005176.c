tryChannelQueued()
	{
		if(!pendingChannels.isEmpty())
		{
			QList<QHostAddress> actualPerms = allocate->permissions();
			QList<StunAllocate::Channel> list;
			for(int n = 0; n < pendingChannels.count(); ++n)
			{
				if(actualPerms.contains(pendingChannels[n].address))
				{
					list += pendingChannels[n];
					pendingChannels.removeAt(n);
					--n;
				}
			}

			if(!list.isEmpty())
				ensureChannels(list);
		}
	}
