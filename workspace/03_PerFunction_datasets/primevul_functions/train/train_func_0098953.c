void createDirectory(const string &path) const {


		if (mkdir(path.c_str(), parseModeString("u=rwx,g=rx,o=rx")) == -1) {
			int e = errno;
			throw FileSystemException("Cannot create server instance directory '" +
				path + "'", e, path);
		}

		if (chmod(path.c_str(), parseModeString("u=rwx,g=rx,o=rx")) == -1) {
			int e = errno;
			throw FileSystemException("Cannot set permissions on server instance directory '" +
				path + "'", e, path);
		}


		if (chown(path.c_str(), geteuid(), getegid()) == -1) {
			int e = errno;
			throw FileSystemException("Cannot change the permissions of the server "
				"instance directory '" + path + "'", e, path);
		}
	}
