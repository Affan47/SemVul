createCDFUnit(const char* variant, int32_t log10Value, UHashtable* table, UErrorCode& status) {
  if (U_FAILURE(status)) {
    return NULL;
  }
  CDFUnit *cdfUnit = (CDFUnit*) uhash_get(table, variant);
  if (cdfUnit == NULL) {
    cdfUnit = new CDFUnit[MAX_DIGITS];
    if (cdfUnit == NULL) {
      status = U_MEMORY_ALLOCATION_ERROR;
      return NULL;
    }
    uhash_put(table, uprv_strdup(variant), cdfUnit, &status);
    if (U_FAILURE(status)) {
      return NULL;
    }
  }
  CDFUnit* result = &cdfUnit[log10Value];
  result->markAsSet();
  return result;
}
