errorCondToDesc(int x)
	{
		for(int n = 0; errorDescriptions[n].str; ++n) {
			if(x == errorDescriptions[n].cond)
				return QPair<QString,QString>(QObject::tr(errorDescriptions[n].name), QObject::tr(errorDescriptions[n].str));
		}
		return QPair<QString,QString>();
	}
