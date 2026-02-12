void RGWListBuckets_ObjStore_SWIFT::send_response_data_reversed(RGWUserBuckets& buckets)
{
  if (! sent_data) {
    return;
  }


  std::map<std::string, RGWBucketEnt>& m = buckets.get_buckets();

  auto iter = m.rbegin();
  for (;
       iter != m.rend() && !boost::algorithm::starts_with(iter->first, prefix);
       ++iter) {
    ;
  }

  for (;
       iter != m.rend() && boost::algorithm::starts_with(iter->first, prefix);
       ++iter) {
    dump_bucket_entry(iter->second);
  }
}
