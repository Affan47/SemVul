getdir( pfs_name *name ) {
		struct dirent *d;
		DIR *dir;
		pfs_dir *result = 0;

		if(!pfs_acl_check_dir(name,IBOX_ACL_LIST)) return 0;

		debug(D_LOCAL,"getdir %s",name->rest);
		dir = ::opendir(name->rest);
		if(dir) {
			result = new pfs_dir(name);
			while((d=::readdir(dir))) {
				if(!strcmp(d->d_name,IBOX_ACL_BASE_NAME)) continue;
				result->append(d->d_name);
			}
			if(!strcmp(name->rest,"/")) {
				result->append("chirp");
			}
			closedir(dir);
		} else {
			result = 0;
       		}
		debug(D_LOCAL,"= %s",result ? "Success" : strerror(errno));
		return result;
	}
