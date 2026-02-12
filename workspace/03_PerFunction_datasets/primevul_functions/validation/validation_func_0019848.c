void RGWListBuckets_ObjStore_SWIFT::send_response_data(RGWUserBuckets& buckets)
{
  if (! sent_data) {
    return;
  }


  const std::map<std::string, RGWBucketEnt>& m = buckets.get_buckets();
  for (auto iter = m.lower_bound(prefix);
       iter != m.end() && boost::algorithm::starts_with(iter->first, prefix);
       ++iter) {
    dump_bucket_entry(iter->second);
  }
}
