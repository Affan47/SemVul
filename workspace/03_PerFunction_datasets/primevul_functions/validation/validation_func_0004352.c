void analyzeUnitTest() {
  struct ndpi_analyze_struct *s = ndpi_alloc_data_analysis(32);
  u_int32_t i;

  for(i=0; i<256; i++) {
    ndpi_data_add_value(s, rand()*i);

  }


#ifdef RUN_DATA_ANALYSIS_THEN_QUIT
  printf("Average: [all: %f][window: %f]\n",
	 ndpi_data_average(s), ndpi_data_window_average(s));
  printf("Entropy: %f\n", ndpi_data_entropy(s));

  printf("Min/Max: %u/%u\n",
	  ndpi_data_min(s), ndpi_data_max(s));
#endif

  ndpi_free_data_analysis(s);

#ifdef RUN_DATA_ANALYSIS_THEN_QUIT
  exit(0);
#endif
}
