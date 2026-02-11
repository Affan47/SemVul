vtty_flush(vtty_t *vtty)
{
   switch(vtty->type) {
      case VTTY_TYPE_TERM:
      case VTTY_TYPE_SERIAL:
         if (vtty->fd_array[0] != -1)
            fsync(vtty->fd_array[0]);
         break;
   }
}
