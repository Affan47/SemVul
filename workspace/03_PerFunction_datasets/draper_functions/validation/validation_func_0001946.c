get_opcode(const char *str)
{
   const int count = sizeof(tex_opcode_strs) / sizeof(tex_opcode_strs[0]);
   for (int op = 0; op < count; op++) {
      if (strcmp(str, tex_opcode_strs[op]) == 0)
	 return (ir_texture_opcode) op;
   }
   return (ir_texture_opcode) -1;
}
