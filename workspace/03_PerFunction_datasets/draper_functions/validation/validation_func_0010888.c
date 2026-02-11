CDE_begin_file_linkat(struct tcb* tcp) {
  char* oldpath = strcpy_from_child(tcp, tcp->u_arg[1]);
  char* newpath = strcpy_from_child(tcp, tcp->u_arg[3]);

  if (CDE_verbose_mode) {
    printf("[%d] BEGIN linkat(%s, %s)\n", tcp->pid, oldpath, newpath);
  }

  if (!IS_ABSPATH(oldpath) && tcp->u_arg[0] != AT_FDCWD) {
    fprintf(stderr,
            "CDE WARNING: linkat '%s' is a relative path and dirfd != AT_FDCWD\n",
            oldpath);
    goto done;
  }
  if (!IS_ABSPATH(newpath) && tcp->u_arg[2] != AT_FDCWD) {
    fprintf(stderr,
            "CDE WARNING: linkat '%s' is a relative path and dirfd != AT_FDCWD\n",
            newpath);
    goto done;
  }


  if (CDE_exec_mode) {
    modify_syscall_second_and_fourth_args(tcp);
  }
  else {


    char* redirected_oldpath = redirect_filename_into_cderoot(oldpath, tcp->current_dir, tcp);

    copy_file_into_cde_root(oldpath, tcp->current_dir);

    char* redirected_newpath = redirect_filename_into_cderoot(newpath, tcp->current_dir, tcp);

    link(redirected_oldpath, redirected_newpath);

    free(redirected_oldpath);
    free(redirected_newpath);
  }

done:
  free(oldpath);
  free(newpath);
}
