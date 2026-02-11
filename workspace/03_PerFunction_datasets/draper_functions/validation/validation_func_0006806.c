setRefreshPause(int i) {
    refreshPause = i;
    if (refreshPause > 0)
      refresh = 1;
  }
