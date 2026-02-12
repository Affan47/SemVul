static bool load_rand_file(const char *file, int *egdsocket, int *seeded) {
    char buffer[PATH_MAX];

    *egdsocket = 0;
    *seeded = 0;
    if (file == nullptr) {
      file = RAND_file_name(buffer, sizeof(buffer));
#if !defined(OPENSSL_NO_RAND_EGD) && !defined(OPENSSL_NO_EGD)
    } else if (RAND_egd(file) > 0) {


      *egdsocket = 1;
      return true;
#endif
    }

    if (file == nullptr || !RAND_load_file(file, -1)) {
      if (RAND_status() == 0) {
        raise_warning("unable to load random state; not enough data!");
        return false;
      }
      return false;
    }
    *seeded = 1;
    return true;
  }
