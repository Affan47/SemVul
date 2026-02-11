test_device (char *buf)
{
  int fd;
  int results;
  char rep[2];

  if ((fd = open (buf, O_RDONLY | O_NONBLOCK)) >= 0) {


    if(ioctl(fd, EVIOCGREP, rep)) {
      results = PROBE_FAILED;
    } else {

      results = PROBE_MATCH;
    }

    close(fd);

  } else {
    results = PROBE_FAILED;
  }
  return results;
}
