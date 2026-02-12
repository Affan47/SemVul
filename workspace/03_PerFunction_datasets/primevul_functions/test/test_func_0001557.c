inline int LegacyHowManyThreads(int max_num_threads, int rows, int cols,
                                int depth) {

  if (max_num_threads == 1) {
    return 1;
  }


  int thread_count = std::min(max_num_threads, rows / KernelRows);


  if (thread_count > 1) {

    static constexpr std::uint64_t min_cubic_size_per_thread = 64 * 1024;


    const std::uint64_t cubic_size =
        std::uint64_t(rows) * std::uint64_t(cols) * std::uint64_t(depth);

    thread_count = std::min(
        thread_count, static_cast<int>(cubic_size / min_cubic_size_per_thread));
  }

  if (thread_count < 1) {
    thread_count = 1;
  }

  assert(thread_count > 0 && thread_count <= max_num_threads);
  return thread_count;
}
