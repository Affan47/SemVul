static noinline struct btrfs_fs_devices *find_fsid(
		const u8 *fsid, const u8 *metadata_fsid)
{
	struct btrfs_fs_devices *fs_devices;

	ASSERT(fsid);

	if (metadata_fsid) {


		list_for_each_entry(fs_devices, &fs_uuids, fs_list) {
			if (fs_devices->fsid_change &&
			    memcmp(metadata_fsid, fs_devices->fsid,
				   BTRFS_FSID_SIZE) == 0 &&
			    memcmp(fs_devices->fsid, fs_devices->metadata_uuid,
				   BTRFS_FSID_SIZE) == 0) {
				return fs_devices;
			}
		}


		list_for_each_entry(fs_devices, &fs_uuids, fs_list) {
			if (fs_devices->fsid_change &&
			    memcmp(fs_devices->metadata_uuid,
				   fs_devices->fsid, BTRFS_FSID_SIZE) != 0 &&
			    memcmp(metadata_fsid, fs_devices->metadata_uuid,
				   BTRFS_FSID_SIZE) == 0) {
				return fs_devices;
			}
		}
	}


	list_for_each_entry(fs_devices, &fs_uuids, fs_list) {
		if (metadata_fsid) {
			if (memcmp(fsid, fs_devices->fsid, BTRFS_FSID_SIZE) == 0
			    && memcmp(metadata_fsid, fs_devices->metadata_uuid,
				      BTRFS_FSID_SIZE) == 0)
				return fs_devices;
		} else {
			if (memcmp(fsid, fs_devices->fsid, BTRFS_FSID_SIZE) == 0)
				return fs_devices;
		}
	}
	return NULL;
}
