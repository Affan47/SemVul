eio__1path (int type, const char *path, int pri, eio_cb cb, void *data)
{
  REQ (type); PATH; SEND;
}
