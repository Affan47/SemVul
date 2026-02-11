write( const void *data, pfs_size_t length, pfs_off_t offset ) {
		pfs_ssize_t result;

		hdfs_dircache.invalidate();


		debug(D_HDFS, "writing to file %s ", name.rest);
		result = hdfs->write(fs, handle, data, length);
		HDFS_END
	}
}
