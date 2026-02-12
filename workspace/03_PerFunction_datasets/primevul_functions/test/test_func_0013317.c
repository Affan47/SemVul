Index WasmBinaryBuilder::getAbsoluteLocalIndex(Index index) {


  int64_t relative = index;
  for (auto i = int64_t(letStack.size()) - 1; i >= 0; i--) {
    auto& info = letStack[i];
    int64_t currNum = info.num;


    if (relative < currNum) {
      return info.absoluteStart + relative;
    }
    relative -= currNum;
  }


  return relative;
}
