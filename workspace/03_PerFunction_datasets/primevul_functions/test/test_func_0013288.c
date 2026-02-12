void WasmBinaryWriter::prepare() {


  ModuleUtils::collectHeapTypes(*wasm, types, typeIndices);
  importInfo = wasm::make_unique<ImportInfo>(*wasm);
}
