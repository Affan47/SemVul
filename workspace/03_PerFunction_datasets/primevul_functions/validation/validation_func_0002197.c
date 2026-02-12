void WriteCombination(int64 batch_index, const std::vector<int>& combination,
                        int64* out) {

    uint64 hashed_output = hash_key_;
    for (size_t i = 0; i < combination.size(); ++i) {
      uint64 hash_i;
      features_[i]->ReadValue(batch_index, combination[i], &hash_i);
      hashed_output = FingerprintCat64(hashed_output, hash_i);
    }

    if (num_buckets_ > 0) {
      *out = hashed_output % num_buckets_;
    } else {

      *out = hashed_output % std::numeric_limits<int64>::max();
    }
  }
