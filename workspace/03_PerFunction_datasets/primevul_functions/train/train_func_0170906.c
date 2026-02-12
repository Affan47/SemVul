Http2Options::Http2Options(Http2State* http2_state, SessionType type) {
  nghttp2_option* option;
  CHECK_EQ(nghttp2_option_new(&option), 0);
  CHECK_NOT_NULL(option);
  options_.reset(option);


  nghttp2_option_set_no_closed_streams(option, 1);


  nghttp2_option_set_no_auto_window_update(option, 1);


  if (type == NGHTTP2_SESSION_CLIENT) {
    nghttp2_option_set_builtin_recv_extension_type(option, NGHTTP2_ALTSVC);
    nghttp2_option_set_builtin_recv_extension_type(option, NGHTTP2_ORIGIN);
  }

  AliasedUint32Array& buffer = http2_state->options_buffer;
  uint32_t flags = buffer[IDX_OPTIONS_FLAGS];

  if (flags & (1 << IDX_OPTIONS_MAX_DEFLATE_DYNAMIC_TABLE_SIZE)) {
    nghttp2_option_set_max_deflate_dynamic_table_size(
        option,
        buffer[IDX_OPTIONS_MAX_DEFLATE_DYNAMIC_TABLE_SIZE]);
  }

  if (flags & (1 << IDX_OPTIONS_MAX_RESERVED_REMOTE_STREAMS)) {
    nghttp2_option_set_max_reserved_remote_streams(
        option,
        buffer[IDX_OPTIONS_MAX_RESERVED_REMOTE_STREAMS]);
  }

  if (flags & (1 << IDX_OPTIONS_MAX_SEND_HEADER_BLOCK_LENGTH)) {
    nghttp2_option_set_max_send_header_block_length(
        option,
        buffer[IDX_OPTIONS_MAX_SEND_HEADER_BLOCK_LENGTH]);
  }


  nghttp2_option_set_peer_max_concurrent_streams(option, 100);
  if (flags & (1 << IDX_OPTIONS_PEER_MAX_CONCURRENT_STREAMS)) {
    nghttp2_option_set_peer_max_concurrent_streams(
        option,
        buffer[IDX_OPTIONS_PEER_MAX_CONCURRENT_STREAMS]);
  }


  if (flags & (1 << IDX_OPTIONS_PADDING_STRATEGY)) {
    PaddingStrategy strategy =
        static_cast<PaddingStrategy>(
            buffer.GetValue(IDX_OPTIONS_PADDING_STRATEGY));
    set_padding_strategy(strategy);
  }


  if (flags & (1 << IDX_OPTIONS_MAX_HEADER_LIST_PAIRS))
    set_max_header_pairs(buffer[IDX_OPTIONS_MAX_HEADER_LIST_PAIRS]);


  if (flags & (1 << IDX_OPTIONS_MAX_OUTSTANDING_PINGS))
    set_max_outstanding_pings(buffer[IDX_OPTIONS_MAX_OUTSTANDING_PINGS]);


  if (flags & (1 << IDX_OPTIONS_MAX_OUTSTANDING_SETTINGS))
    set_max_outstanding_settings(buffer[IDX_OPTIONS_MAX_OUTSTANDING_SETTINGS]);


  if (flags & (1 << IDX_OPTIONS_MAX_SESSION_MEMORY))
    set_max_session_memory(buffer[IDX_OPTIONS_MAX_SESSION_MEMORY] * 1000000);

  if (flags & (1 << IDX_OPTIONS_MAX_SETTINGS)) {
    nghttp2_option_set_max_settings(
        option,
        static_cast<size_t>(buffer[IDX_OPTIONS_MAX_SETTINGS]));
  }
}
