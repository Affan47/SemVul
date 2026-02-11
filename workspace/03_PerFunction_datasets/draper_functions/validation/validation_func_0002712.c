load_chainsetup(const std::string& filename)
{

  DBC_REQUIRE(filename.empty() != true);


  set_cs_param_defaults();

  ECA_CHAINSETUP* new_setup = new ECA_CHAINSETUP(filename);
  if (new_setup->interpret_result() != true) {
    string temp = new_setup->interpret_result_verbose();
    delete new_setup;
    selected_chainsetup_repp = 0;
    ECA_LOG_MSG(ECA_LOGGER::info, "Error loading chainsetup: " + temp);
  }
  else {
    add_chainsetup(new_setup);
    if (selected_chainsetup_repp == 0) {

      delete new_setup;
    }
  }


  DBC_ENSURE((selected_chainsetup_repp != 0 &&
	      selected_chainsetup_repp->filename() == filename) ||
	     selected_chainsetup_repp == 0);

}
