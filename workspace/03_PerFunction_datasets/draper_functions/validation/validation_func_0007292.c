uv_udp_init(uv_loop_t* loop, uv_udp_t* handle) {
  uv__handle_init(loop, (uv_handle_t*)handle, UV_UDP);
  handle->alloc_cb = NULL;
  handle->recv_cb = NULL;
  uv__io_init(&handle->io_watcher, uv__udp_io, -1);
  QUEUE_INIT(&handle->write_queue);
  QUEUE_INIT(&handle->write_completed_queue);
  return 0;
}
