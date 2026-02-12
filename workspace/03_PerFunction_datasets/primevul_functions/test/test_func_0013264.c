void WasmBinaryBuilder::visitRefFunc(RefFunc* curr) {
  BYN_TRACE("zz node: RefFunc\n");
  Index index = getU32LEB();


  functionRefs[index].push_back(curr);


  curr->finalize(Type(getTypeByFunctionIndex(index), NonNullable));
}
