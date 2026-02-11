w5100_write_socket_mr( nic_w5100_socket_t *socket, libspectrum_byte b )
{
  nic_w5100_debug( "w5100: writing 0x%02x to S%d_MR\n", b, socket->id );

  w5100_socket_mode mode = b & 0x0f;
  libspectrum_byte flags = b & 0xf0;

  switch( mode ) {
    case W5100_SOCKET_MODE_CLOSED:
      break;
    case W5100_SOCKET_MODE_TCP:

      if( flags != 0x20 ) {
        ui_error( UI_ERROR_WARNING, "w5100: unsupported flags 0x%02x set for TCP mode on socket %d\n", b & 0xf0, socket->id );
        flags = 0x20;
      }
      break;
    case W5100_SOCKET_MODE_UDP:

      if( flags != 0x00 ) {
        ui_error( UI_ERROR_WARNING, "w5100: unsupported flags 0x%02x set for UDP mode on socket %d\n", b & 0xf0, socket->id );
        flags = 0;
      }
      break;
    case W5100_SOCKET_MODE_IPRAW:
    case W5100_SOCKET_MODE_MACRAW:
    case W5100_SOCKET_MODE_PPPOE:
    default:
      ui_error( UI_ERROR_WARNING, "w5100: unsupported mode 0x%02x set on socket %d\n", b, socket->id );
      mode = W5100_SOCKET_MODE_CLOSED;
      break;
  }

  socket->mode = mode;
  socket->flags = flags;
}
