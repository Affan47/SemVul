uptime_report(int idx, int details)
{
  if (details) {
    int size = uptime_expmem();

    dprintf(idx, "    %d uptime packet%s sent\n", uptimecount,
            (uptimecount != 1) ? "s" : "");
    dprintf(idx, "    Using %d byte%s of memory\n", size,
            (size != 1) ? "s" : "");
  }
}
