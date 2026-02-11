print(raw_ostream &ROS, bool ) const {
  PrintLLVMName(ROS, getName(), ComdatPrefix);
  ROS << " = comdat ";

  switch (getSelectionKind()) {
  case Comdat::Any:
    ROS << "any";
    break;
  case Comdat::ExactMatch:
    ROS << "exactmatch";
    break;
  case Comdat::Largest:
    ROS << "largest";
    break;
  case Comdat::NoDuplicates:
    ROS << "noduplicates";
    break;
  case Comdat::SameSize:
    ROS << "samesize";
    break;
  }

  ROS << '\n';
}
