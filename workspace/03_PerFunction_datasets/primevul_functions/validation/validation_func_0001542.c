SampleProfiler() : Profiler(true) {
    struct timeval  now;
    uint64_t truncated_us;
    uint64_t truncated_tsc;


    m_last_sample_tsc = cpuCycles();


    gettimeofday(&m_last_sample_time, 0);
    now = m_last_sample_time;
    hp_trunc_time(&m_last_sample_time, SAMPLING_INTERVAL);


    truncated_us  = get_us_interval(&m_last_sample_time, &now);
    truncated_tsc = truncated_us * m_MHz;
    if (m_last_sample_tsc > truncated_tsc) {

      m_last_sample_tsc -= truncated_tsc;
    }


    m_sampling_interval_tsc = SAMPLING_INTERVAL * m_MHz;
  }
