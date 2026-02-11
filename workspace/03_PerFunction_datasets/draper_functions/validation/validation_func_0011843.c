get_next_request_id(int old_request_id)
{
  int result = old_request_id + 1;

  if ((result & 0xffff) == 0) {
    log_packet("INFORMATION: request_id has wrapped around; "
               "setting from %d to 2", result);
    result = 2;
  }
  fc_assert(0 != result);
  return result;
}
