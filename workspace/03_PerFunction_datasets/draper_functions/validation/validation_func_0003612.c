processModule() {
  ST_DEBUG("begin processModule!\n");


  for (Module::const_global_iterator I = TheModule->global_begin(),
         E = TheModule->global_end(); I != E; ++I) {
    if (!I->hasName())
      CreateModuleSlot(I);
  }


  for (Module::const_named_metadata_iterator
         I = TheModule->named_metadata_begin(),
         E = TheModule->named_metadata_end(); I != E; ++I) {
    const NamedMDNode *NMD = I;
    for (unsigned i = 0, e = NMD->getNumOperands(); i != e; ++i)
      CreateMetadataSlot(NMD->getOperand(i));
  }


  for (Module::const_iterator I = TheModule->begin(), E = TheModule->end();
       I != E; ++I)
    if (!I->hasName())
      CreateModuleSlot(I);

  ST_DEBUG("end processModule!\n");
}
