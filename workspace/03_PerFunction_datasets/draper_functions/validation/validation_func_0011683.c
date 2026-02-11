statusEntriesFunc(void *baton,
                    const char *path,
                    svn_wc_status2_t *status)
  {
    StatusEntries * entries = static_cast<StatusEntries *>(baton);

    entries->push_back(Status(path, status));
  }
