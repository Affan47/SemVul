encodeInstruction(const MCInst &MI, raw_ostream &OS,
                         SmallVectorImpl<MCFixup> &Fixups,
                         const MCSubtargetInfo &STI) const override {


    unsigned Opcode = MI.getOpcode();
    const MCInstrDesc &Desc = MCII.get(Opcode);
    if (Opcode == TargetOpcode::COPY_TO_REGCLASS)
      return;

    uint64_t Bits = getBinaryCodeForInstr(MI, Fixups, STI);


    unsigned Size = Desc.getSize();
    switch (Size) {
    case 4:
      if (IsLittleEndian) {
        support::endian::Writer<support::little>(OS).write<uint32_t>(Bits);
      } else {
        support::endian::Writer<support::big>(OS).write<uint32_t>(Bits);
      }
      break;
    case 8:


      if (IsLittleEndian) {
        uint64_t Swapped = (Bits << 32) | (Bits >> 32);
        support::endian::Writer<support::little>(OS).write<uint64_t>(Swapped);
      } else {
        support::endian::Writer<support::big>(OS).write<uint64_t>(Bits);
      }
      break;
    default:
      llvm_unreachable ("Invalid instruction size");
    }

    ++MCNumEmitted;
  }
