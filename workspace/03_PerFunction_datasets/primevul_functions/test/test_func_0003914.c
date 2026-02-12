inline void GetMKLNodeDef(NodeDef* ndef) {


  AttrValue attr_kernel;
  attr_kernel.set_s(mkl_op_registry::kMklNameChangeOpLabel);
  (*ndef->mutable_attr()).insert({"_kernel", attr_kernel});
}
