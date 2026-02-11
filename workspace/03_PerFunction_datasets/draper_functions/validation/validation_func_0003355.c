last_write_time(const path& p, system::error_code* ec)
  {
#   ifdef BOOST_POSIX_API

    struct stat path_stat;
    if (error(::stat(p.c_str(), &path_stat)!= 0,
      p, ec, "boost::filesystem::last_write_time"))
        return std::time_t(-1);
    return path_stat.st_mtime;

#   else

    handle_wrapper hw(
      create_file_handle(p.c_str(), 0,
        FILE_SHARE_DELETE | FILE_SHARE_READ | FILE_SHARE_WRITE, 0,
        OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, 0));

    if (error(hw.handle == INVALID_HANDLE_VALUE,
      p, ec, "boost::filesystem::last_write_time"))
        return std::time_t(-1);

    FILETIME lwt;

    if (error(::GetFileTime(hw.handle, 0, 0, &lwt)== 0,
      p, ec, "boost::filesystem::last_write_time"))
        return std::time_t(-1);

    return to_time_t(lwt);
#   endif
  }
