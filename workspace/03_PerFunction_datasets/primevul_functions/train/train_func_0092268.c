static void posix_locks_value_destroy(gpointer data)
{
    struct lo_inode_plock *plock = data;


    close(plock->fd);
    free(plock);
}
