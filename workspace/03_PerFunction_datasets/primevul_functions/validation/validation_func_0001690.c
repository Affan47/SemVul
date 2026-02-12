void f_phprof_enable(int flags ) {
  if (RuntimeOption::EnableHotProfiler) {
    s_profiler_factory->start(ProfilerKind::Hierarchical, flags);
  }
}
