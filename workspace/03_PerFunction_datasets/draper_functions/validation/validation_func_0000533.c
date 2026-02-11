run_as_daemon(void)
{
  gchar *path;
  FILE *fp;


  path = g_strdup_printf("%s/%s/%s", g_get_home_dir(),
      GJAY_DIR, GJAY_PID);
  if ((fp = fopen(path, "w")) == NULL) {
    g_error(_("Cannot open %s for writing\n"), path);
    exit(1);
  }
  g_free(path);
  fprintf(fp, "%d", getpid());
  fclose(fp);

  signal(SIGTERM, kill_signal);
  signal(SIGKILL, kill_signal);
  signal(SIGINT,  kill_signal);

  analysis_daemon();


  close(daemon_pipe_fd);
  close(ui_pipe_fd);
  unlink(daemon_pipe);
  unlink(ui_pipe);
  rmdir(gjay_pipe_dir);
  g_free(gjay_pipe_dir);
}
