sftp_send_errno_status(struct sftpjob *job) {
  int n;
  const int errno_value = errno;

  for(n = 0;
      errnotab[n].errno_value != errno_value && errnotab[n].errno_value != -1;
      ++n)
    ;
  sftp_send_status(job, errnotab[n].status_value, strerror(errno_value));
}
