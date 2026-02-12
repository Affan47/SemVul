yaffsfs_close(TSK_FS_INFO *fs)
{
    if(fs != NULL){
        YAFFSFS_INFO *yfs = (YAFFSFS_INFO *)fs;

        fs->tag = 0;


        yaffscache_objects_free(yfs);
        yaffscache_chunks_free(yfs);


        tsk_fs_free(fs);
	}
}
