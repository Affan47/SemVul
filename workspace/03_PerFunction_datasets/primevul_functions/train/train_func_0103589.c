inline bool ReadLimiter::canRead(WordCount64 amount, Arena* arena) {


  uint64_t current = limit;
  if (KJ_UNLIKELY(unbound(amount / WORDS) > current)) {
    arena->reportReadLimitReached();
    return false;
  } else {
    limit = current - unbound(amount / WORDS);
    return true;
  }
}
