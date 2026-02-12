ZoneSplayTree<Config>::~ZoneSplayTree() {


  SplayTree<Config, ZoneAllocationPolicy>::ResetRoot();
}
