set_preset_defaults(const vector<string>& args)
{
  extend_pardesc_vector(args.size());
  for(size_t n = 0; n < args.size(); n++) {
    if (args[n].size() > 0 && args[n][0] == '-') continue;
    impl_repp->pardesclist_rep[n]->default_value = atof(args[n].c_str());
    set_parameter(n + 1, impl_repp->pardesclist_rep[n]->default_value);

  }
}
