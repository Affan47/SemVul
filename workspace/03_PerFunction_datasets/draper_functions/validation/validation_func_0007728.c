ladish_room_proxy_set_project_notes(
  ladish_room_proxy_handle proxy,
  const char * notes)
{
  uint64_t new_version;

  if (!cdbus_call(0, proxy_ptr->service, proxy_ptr->object, IFACE_ROOM, "SetProjectNotes", "s", &notes, "t", &new_version))
  {
    log_error("SetProjectNotes(%s) failed.", notes);
    return false;
  }

  return true;
}
