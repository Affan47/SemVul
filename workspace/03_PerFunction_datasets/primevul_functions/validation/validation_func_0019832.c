static int get_swift_versioning_settings(
  req_state * const s,
  boost::optional<std::string>& swift_ver_location)
{


  const std::string vlocdel =
    s->info.env->get("HTTP_X_REMOVE_VERSIONS_LOCATION", "");
  if (vlocdel.size()) {
    swift_ver_location = boost::in_place(std::string());
  }

  if (s->info.env->exists("HTTP_X_VERSIONS_LOCATION")) {


    if (! s->cct->_conf->rgw_swift_versioning_enabled) {
      return -ERR_PRECONDITION_FAILED;
    }

    swift_ver_location = s->info.env->get("HTTP_X_VERSIONS_LOCATION", "");
  }

  return 0;
}
