PropagateMatch(const vector<int>& atom_ids,
                                   IntMap* regexps) const {
  IntMap count(entries_.size());
  IntMap work(entries_.size());
  for (int i = 0; i < atom_ids.size(); i++)
    work.set(atom_ids[i], 1);
  for (IntMap::iterator it = work.begin(); it != work.end(); ++it) {
    const Entry& entry = entries_[it->index()];
    VLOG(10) << "Processing: " << it->index();

    for (int i = 0; i < entry.regexps.size(); i++) {
      VLOG(10) << "Regexp triggered: " << entry.regexps[i];
      regexps->set(entry.regexps[i], 1);
    }
    int c;

    for (StdIntMap::iterator it = entry.parents->begin();
         it != entry.parents->end();
         ++it) {
      int j = it->first;
      const Entry& parent = entries_[j];
      VLOG(10) << " parent= " << j << " trig= " << parent.propagate_up_at_count;

      if (parent.propagate_up_at_count > 1) {
        if (count.has_index(j)) {
          c = count.get_existing(j) + 1;
          count.set_existing(j, c);
        } else {
          c = 1;
          count.set_new(j, c);
        }
        if (c < parent.propagate_up_at_count)
          continue;
      }
      VLOG(10) << "Triggering: " << j;

      work.set(j, 1);
    }
  }
}
