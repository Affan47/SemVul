createARMMachObjectWriter(raw_pwrite_stream &OS,
                                                bool Is64Bit, uint32_t CPUType,
                                                uint32_t CPUSubtype) {
  return createMachObjectWriter(new ARMMachObjectWriter(Is64Bit,
                                                        CPUType,
                                                        CPUSubtype),
                                OS, true);
}
