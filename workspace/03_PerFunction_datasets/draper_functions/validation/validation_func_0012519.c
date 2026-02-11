addFragment(const std::set<uint64_t> &F) {

  Fragments.emplace_back();
  std::vector<uint64_t> &Fragment = Fragments.back();
  uint64_t FragmentIndex = Fragments.size() - 1;

  for (auto ObjIndex : F) {
    uint64_t OldFragmentIndex = FragmentMap[ObjIndex];
    if (OldFragmentIndex == 0) {


      Fragment.push_back(ObjIndex);
    } else {


      std::vector<uint64_t> &OldFragment = Fragments[OldFragmentIndex];
      Fragment.insert(Fragment.end(), OldFragment.begin(), OldFragment.end());
      OldFragment.clear();
    }
  }


  for (uint64_t ObjIndex : Fragment)
    FragmentMap[ObjIndex] = FragmentIndex;
}
