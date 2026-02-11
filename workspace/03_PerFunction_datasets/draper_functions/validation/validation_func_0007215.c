CategorizeAllMatchingFlags(
    const set<const CommandLineFlagInfo *> &all_matches,
    const string &search_token,
    const string &module,
    const string &package_dir,
    NotableFlags *notable_flags) {
  notable_flags->perfect_match_flag.clear();
  notable_flags->module_flags.clear();
  notable_flags->package_flags.clear();
  notable_flags->most_common_flags.clear();
  notable_flags->subpackage_flags.clear();

  for (set<const CommandLineFlagInfo *>::const_iterator it =
        all_matches.begin();
      it != all_matches.end();
      ++it) {


    string::size_type pos = string::npos;
    if (!package_dir.empty())
      pos = (*it)->filename.find(package_dir);
    string::size_type slash = string::npos;
    if (pos != string::npos)
      slash = (*it)->filename.find(
          PATH_SEPARATOR,
          pos + package_dir.size() + 1);

    if ((*it)->name == search_token) {

      notable_flags->perfect_match_flag.insert(*it);

    } else if (!module.empty() && (*it)->filename == module) {

      notable_flags->module_flags.insert(*it);

    } else if (!package_dir.empty() &&
        pos != string::npos && slash == string::npos) {

      notable_flags->package_flags.insert(*it);

    } else if (false) {


    } else if (!package_dir.empty() &&
        pos != string::npos && slash != string::npos) {

      notable_flags->subpackage_flags.insert(*it);

    }


  }
}
