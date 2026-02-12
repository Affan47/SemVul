void create(bool userSwitching, const string &defaultUser,
		            const string &defaultGroup, uid_t webServerWorkerUid,
		            gid_t webServerWorkerGid)
		{
			TRACE_POINT();
			bool runningAsRoot = geteuid() == 0;
			struct passwd *defaultUserEntry;
			uid_t defaultUid;
			gid_t defaultGid;

			defaultUserEntry = getpwnam(defaultUser.c_str());
			if (defaultUserEntry == NULL) {
				throw NonExistentUserException("Default user '" + defaultUser +
					"' does not exist.");
			}
			defaultUid = defaultUserEntry->pw_uid;
			defaultGid = lookupGid(defaultGroup);
			if (defaultGid == (gid_t) -1) {
				throw NonExistentGroupException("Default group '" + defaultGroup +
					"' does not exist.");
			}


			makeDirTree(path, "u=rwx,g=x,o=x");


			string structureVersionFile = path + "/structure_version.txt";
			createFile(structureVersionFile,
				toString(SERVER_INSTANCE_DIR_GENERATION_STRUCTURE_MAJOR_VERSION) + "." +
				toString(SERVER_INSTANCE_DIR_GENERATION_STRUCTURE_MINOR_VERSION),
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

			string passengerVersionFile = path + "/passenger_version.txt";
			createFile(passengerVersionFile,
				PASSENGER_VERSION "\n",
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);


			if (runningAsRoot) {
				makeDirTree(path + "/buffered_uploads", "u=rwx,g=,o=",
					webServerWorkerUid, webServerWorkerGid);
			} else {
				makeDirTree(path + "/buffered_uploads", "u=rwx,g=,o=");
			}


			if (runningAsRoot) {
				if (userSwitching) {


					makeDirTree(path + "/backends", "u=rwx,g=wx,o=wx,+t");
				} else {


					makeDirTree(path + "/backends", "u=rwx,g=x,o=x", defaultUid, defaultGid);
				}
			} else {


				makeDirTree(path + "/backends", "u=rwx,g=,o=");
			}

			owner = true;
		}
