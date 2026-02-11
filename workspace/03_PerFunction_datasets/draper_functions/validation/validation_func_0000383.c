cast(const char *n)
{
  if (strcmp(n, "InfiniteSource") == 0)
    return (InfiniteSource *)this;
  else if (strcmp(n, Notifier::EMPTY_NOTIFIER) == 0)
    return static_cast<Notifier *>(this);
  else
    return 0;
}
