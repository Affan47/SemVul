yaffsfs_jblk_walk(TSK_FS_INFO * , TSK_DADDR_T ,
    TSK_DADDR_T , int , TSK_FS_JBLK_WALK_CB ,
    void * )
{
    tsk_error_reset();
    tsk_error_set_errno(TSK_ERR_FS_UNSUPFUNC);
    tsk_error_set_errstr("Journal support for YAFFS is not implemented");
    return 1;
}
