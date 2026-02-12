static void fuse_fs_cleanup(void)
{
	unregister_filesystem(&fuse_fs_type);
	unregister_fuseblk();


	rcu_barrier();
	kmem_cache_destroy(fuse_inode_cachep);
}
