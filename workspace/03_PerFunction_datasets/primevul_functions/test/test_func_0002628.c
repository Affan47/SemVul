bool OpDefEqual(const OpDef& o1, const OpDef& o2) {


  if (!RepeatedAttrDefEqual(o1.attr(), o2.attr())) return false;


  std::set<string> control_output1(o1.control_output().begin(),
                                   o1.control_output().end());
  std::set<string> control_output2(o2.control_output().begin(),
                                   o2.control_output().end());
  if (control_output1 != control_output2) return false;


  OpDef o1_copy = o1;
  OpDef o2_copy = o2;
  o1_copy.clear_attr();
  o1_copy.clear_control_output();
  o2_copy.clear_attr();
  o2_copy.clear_control_output();

  return AreSerializedProtosEqual(o1_copy, o2_copy);
}
