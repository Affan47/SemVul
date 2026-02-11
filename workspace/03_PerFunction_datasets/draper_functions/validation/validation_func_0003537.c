zretrieveUnmapFile(fd)int fd;
{
  if(-1==munmap(Zpack.ice, Zpack.flen))
  {
    H("\343 PKG: zretrieve: error unmapping file.  errno=%d\n",errno);
  }
  close(fd);
}
