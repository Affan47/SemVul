GetSmallSpanStats(SmallSpanStats* result) {
  for (int s = 0; s < kMaxPages; s++) {
    result->normal_length[s] = DLL_Length(&free_[s].normal);
    result->returned_length[s] = DLL_Length(&free_[s].returned);
  }
}
