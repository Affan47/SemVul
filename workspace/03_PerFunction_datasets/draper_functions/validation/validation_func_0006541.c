gbser_init(const char* port_name)
{
  gbser_handle* h;

  gbser__db(4, "gbser_init(\"%s\")\n", port_name);

  h = (gbser_handle*) xcalloc(sizeof *h, 1);
  h->magic = MYMAGIC;
  h->vmin = h->vtime = 0;

  if (0 == strcmp(port_name, "-")) {
    h->fd = 0;
    return h;
  } else if (h->fd = open(port_name, O_RDWR | O_NOCTTY), h->fd == -1) {
    warning("Failed to open port (%s)\n", strerror(errno));
    goto failed;
  }

  if (!isatty(h->fd)) {
    warning("%s is not a TTY\n", port_name);
    goto failed;
  }

  if (gbser_set_port(h, 4800, 8, 0, 1)) {
    warning("gbser_set_port() failed\n");
    goto failed;
  }

  return h;

failed:
  if (h->fd != -1) {
    close(h->fd);
  }

  xfree(h);

  return NULL;
}
