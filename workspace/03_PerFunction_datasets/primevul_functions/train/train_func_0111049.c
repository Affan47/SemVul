void switchUser(const SpawnPreparationInfo &info) {
		if (info.userSwitching.enabled) {
			enterLveJail(&info.userSwitching.lveUserPwd);

			bool setgroupsCalled = false;
			#ifdef HAVE_GETGROUPLIST
				if (info.userSwitching.ngroups <= NGROUPS_MAX) {
					setgroupsCalled = true;
					if (setgroups(info.userSwitching.ngroups,
						info.userSwitching.gidset.get()) == -1)
					{
						int e = errno;
						printf("!> Error\n");
						printf("!> \n");
						printf("setgroups(%d, ...) failed: %s (errno=%d)\n",
							info.userSwitching.ngroups, strerror(e), e);
						fflush(stdout);
						_exit(1);
					}
				}
			#endif
			if (!setgroupsCalled && initgroups(info.userSwitching.username.c_str(),
				info.userSwitching.gid) == -1)
			{
				int e = errno;
				printf("!> Error\n");
				printf("!> \n");
				printf("initgroups() failed: %s (errno=%d)\n",
					strerror(e), e);
				fflush(stdout);
				_exit(1);
			}
			if (setgid(info.userSwitching.gid) == -1) {
				int e = errno;
				printf("!> Error\n");
				printf("!> \n");
				printf("setgid() failed: %s (errno=%d)\n",
					strerror(e), e);
				fflush(stdout);
				_exit(1);
			}
			if (setuid(info.userSwitching.uid) == -1) {
				int e = errno;
				printf("!> Error\n");
				printf("!> \n");
				printf("setuid() failed: %s (errno=%d)\n",
					strerror(e), e);
				fflush(stdout);
				_exit(1);
			}


			setenv("USER", info.userSwitching.username.c_str(), 1);
			setenv("LOGNAME", info.userSwitching.username.c_str(), 1);
			setenv("SHELL", info.userSwitching.shell.c_str(), 1);
			setenv("HOME", info.userSwitching.home.c_str(), 1);


			setenv("PWD", info.appRoot.c_str(), 1);
		}
	}
