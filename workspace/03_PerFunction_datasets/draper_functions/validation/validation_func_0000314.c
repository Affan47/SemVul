tun_alloc(char *dev)
{
  struct ifreq ifr;
  int fd, err;

  if ((fd = open("/dev/net/tun", O_RDWR)) < 0)
  {
    perror("open");
    return -1;
  }

  memset(&ifr, 0, sizeof(ifr));
  ifr.ifr_flags = IFF_TUN | IFF_NO_PI;

  if (*dev)
  {
    strncpy(ifr.ifr_name, dev, IFNAMSIZ);
  }

  if ((err = ioctl(fd, TUNSETIFF, (void *) &ifr)) < 0)
  {
    perror("ioctl");
    close(fd);
    return err;
  }
  strcpy(dev, ifr.ifr_name);

  return fd;
}
