getMaskedMIMGOp(uint16_t Opcode, unsigned Channels) const {
  switch (Channels) {
  default: return Opcode;
  case 1: return AMDGPU::getMaskedMIMGOp(Opcode, AMDGPU::Channels_1);
  case 2: return AMDGPU::getMaskedMIMGOp(Opcode, AMDGPU::Channels_2);
  case 3: return AMDGPU::getMaskedMIMGOp(Opcode, AMDGPU::Channels_3);
  }
}
