EmitProcessorLookup(raw_ostream &OS) {

  std::vector<Record*> ProcessorList =
                          Records.getAllDerivedDefinitions("Processor");
  std::sort(ProcessorList.begin(), ProcessorList.end(), LessRecordFieldName());


  OS << "\n";
  OS << "// Sorted (by key) array of itineraries for CPU subtype.\n"
     << "llvm::SubtargetInfoKV "
     << Target << "ProcItinKV[] = {\n";


  for (unsigned i = 0, N = ProcessorList.size(); i < N;) {

    Record *Processor = ProcessorList[i];

    const std::string &Name = Processor->getValueAsString("Name");
    const std::string &ProcItin =
      Processor->getValueAsDef("ProcItin")->getName();


    OS << "  { "
       << "\"" << Name << "\", "
       << "(void *)&" << ProcItin;

    OS << " }";


    if (++i < N) OS << ",";

    OS << "\n";
  }


  OS << "};\n";
}
