binary_search (int lowi, int highi, Genomicpos_T *positions, Genomicpos_T goal) {
  bool foundp = false;
  int middlei;

  debug10(printf("entered binary search with lowi=%d, highi=%d, goal=%u\n",lowi,highi,goal));

  while (!foundp && lowi < highi) {
    middlei = (lowi+highi)/2;
    debug10(printf("  binary: %d:%u %d:%u %d:%u   vs. %u\n",
		   lowi,positions[lowi],middlei,positions[middlei],
		   highi,positions[highi],goal));
    if (goal < positions[middlei]) {
      highi = middlei;
    } else if (goal > positions[middlei]) {
      lowi = middlei + 1;
    } else {
      foundp = true;
    }
  }

  if (foundp == true) {
    debug10(printf("binary search returns %d\n",middlei));
    return middlei;
  } else {
    debug10(printf("binary search returns %d\n",highi));
    return highi;
  }
}
