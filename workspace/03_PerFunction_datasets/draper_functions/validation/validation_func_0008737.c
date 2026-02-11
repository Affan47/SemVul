estimate_and_set_system(struct timeval *now, int offset_provided, double offset, long *offset_cs, double *dfreq_ppm, double *new_afreq_ppm)
{
  double agos[MAX_SAMPLES], offsets[MAX_SAMPLES];
  double b0, b1;
  int n_runs, best_start;
  int i;
  double freq = 0.0;
  double skew = 0.099999999;
  int found_freq;
  double slew_by;

  if (n_samples > 1) {
    for (i=0; i<n_samples; i++) {
      UTI_DiffTimevalsToDouble(&agos[i], &samples[n_samples-1].when, &samples[i].when);
      offsets[i] = samples[i].offset;
    }

    RGR_FindBestRobustRegression(agos, offsets, n_samples,
                                 1.0e-8,
                                 &b0, &b1, &n_runs, &best_start);


    freq = -b1;
    found_freq = 1;
  } else {
    if (offset_provided) {
      b0 = offset;
    } else {
      b0 = 0.0;
    }
    b1 = freq = 0.0;
    found_freq = 0;
    agos[0] = 0.0;
    offsets[0] = b0;
  }

  if (offset_provided) {
    slew_by = offset;
  } else {
    slew_by = b0;
  }

  if (found_freq) {
    LOG(LOGS_INFO, LOGF_Manual,
        "Making a frequency change of %.3f ppm and a slew of %.6f",
        1.0e6 * freq, slew_by);

    REF_SetManualReference(now,
                           slew_by,
                           freq, skew);
  } else {
    LOG(LOGS_INFO, LOGF_Manual, "Making a slew of %.6f", slew_by);
    REF_SetManualReference(now,
                           slew_by,
                           0.0, skew);
  }

  if (offset_cs) *offset_cs = (long)(0.5 + 100.0 * b0);
  if (dfreq_ppm) *dfreq_ppm = 1.0e6 * freq;
  if (new_afreq_ppm) *new_afreq_ppm = LCL_ReadAbsoluteFrequency();


  for (i=0; i<n_samples; i++) {
    samples[i].residual = offsets[i] - (b0 + agos[i] * b1);
  }

}
