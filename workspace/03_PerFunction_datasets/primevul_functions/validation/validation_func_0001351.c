int64_t HHVM_FUNCTION(levenshtein,
                      const String& str1,
                      const String& str2,
                      int cost_ins ,
                      int cost_rep ,
                      int cost_del ) {
  return string_levenshtein(str1.data(), str1.size(), str2.data(), str2.size(),
                            cost_ins, cost_rep, cost_del);
}
