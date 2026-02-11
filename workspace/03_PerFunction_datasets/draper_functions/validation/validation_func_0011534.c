runOnModule(Module &M) {
  for (GlobalVariable &GV : M.globals()) {

    if (GV.hasLocalLinkage()) {


      GV.setName(cleanUpName(GV.getName()));
    }
  }

  return true;
}
