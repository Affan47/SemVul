void HHVM_FUNCTION(socket_clear_error,
                   const Variant& socket ) {
  if (!socket.isNull()) {
    cast<Socket>(socket)->setError(0);
  }
}
