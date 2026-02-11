checkpointeverything (void)
{
  DPRINTF("thread:%d performing checkpoint.\n", mtcp_sys_kernel_gettid ());


  int tmpDMTCPHeaderFd = perform_callback_write_ckpt_header();

  int forked_ckpt_status = test_and_prepare_for_forked_ckpt(tmpDMTCPHeaderFd);
  if (forked_ckpt_status == FORKED_CKPT_PARENT) {
    DPRINTF("*** Using forked checkpointing.\n");
    return;
  }


  int use_compression = 0;
  int fdCkptFileOnDisk = -1;
  int fd = perform_open_ckpt_image_fd(&use_compression, &fdCkptFileOnDisk);
  MTCP_ASSERT( fdCkptFileOnDisk >= 0 );
  MTCP_ASSERT( use_compression || fd == fdCkptFileOnDisk );

  write_ckpt_to_file(fd, tmpDMTCPHeaderFd, fdCkptFileOnDisk);

#ifndef FAST_CKPT_RST_VIA_MMAP
  if (use_compression) {


    if ( mtcp_sys_wait4(mtcp_ckpt_extcomp_child_pid, NULL, 0, NULL ) == -1 ) {
      DPRINTF("(compression): waitpid: %s\n", strerror(mtcp_sys_errno));
    }
    mtcp_ckpt_extcomp_child_pid = -1;
    sigaction(SIGCHLD, &sigactions[SIGCHLD], NULL);
    if (fsync(fdCkptFileOnDisk) < 0) {
      MTCP_PRINTF("(compression): fsync error on checkpoint file: %s\n",
                  strerror(errno));
      mtcp_abort ();
    }
    if (close(fdCkptFileOnDisk) < 0) {
      MTCP_PRINTF("(compression): error closing checkpoint file: %s\n",
                  strerror(errno));
      mtcp_abort ();
    }
  }
#endif


  if (verify_total != 0) --verify_count;


  else renametempoverperm ();

  if (forked_ckpt_status == FORKED_CKPT_CHILD)
    mtcp_sys_exit (0);

  DPRINTF("checkpoint complete\n");
}
