runningProcesses()
	{
#ifdef Q_WS_X11
		QDir procDir("/proc");
		QList<int> back;

		if(!procDir.exists())
			return back;

		QStringList processes = procDir.entryList(QDir::Dirs);
		foreach(const QString &processId, processes)
		{
			bool success;
			int id = processId.toInt(&success);

			if(success)
				back.append(id);
		}

		return back;
#endif
#ifdef Q_WS_WIN
		QList<int> back;
		HANDLE handle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		if(!handle)
		{
			setupLastError();
			return back;
		}

		PROCESSENTRY32 info = {0};
		info.dwSize = sizeof(PROCESSENTRY32);

		bool first = Process32First(handle, &info);
		if(!first)
		{
			CloseHandle(handle);
			setupLastError();
			return back;
		}

		do
		{
			back.append(info.th32ProcessID);
		}
		while(Process32Next(handle, &info));

		CloseHandle(handle);

		return back;
#endif
	}
