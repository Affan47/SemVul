printModule(const std::string& fname,
                            const std::string& mName) {
  nl(Out) << "Module* " << fname << "() {";
  nl(Out,1) << "// Module Construction";
  nl(Out) << "Module* mod = new Module(\"";
  printEscapedString(mName);
  Out << "\", getGlobalContext());";
  if (!TheModule->getTargetTriple().empty()) {
    nl(Out) << "mod->setDataLayout(\"" << TheModule->getDataLayout() << "\");";
  }
  if (!TheModule->getTargetTriple().empty()) {
    nl(Out) << "mod->setTargetTriple(\"" << TheModule->getTargetTriple()
            << "\");";
  }

  if (!TheModule->getModuleInlineAsm().empty()) {
    nl(Out) << "mod->setModuleInlineAsm(\"";
    printEscapedString(TheModule->getModuleInlineAsm());
    Out << "\");";
  }
  nl(Out);


  Module::lib_iterator LI = TheModule->lib_begin();
  Module::lib_iterator LE = TheModule->lib_end();
  while (LI != LE) {
    Out << "mod->addLibrary(\"" << *LI << "\");";
    nl(Out);
    ++LI;
  }
  printModuleBody();
  nl(Out) << "return mod;";
  nl(Out,-1) << "}";
  nl(Out);
}
