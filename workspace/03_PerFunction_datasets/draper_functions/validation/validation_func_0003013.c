uv_fs_req_cleanup(uv_fs_t* req) {
  free((void*) req->path);
  req->path = NULL;
  req->new_path = NULL;

  if (req->ptr != &req->statbuf)
    free(req->ptr);
  req->ptr = NULL;
}
