dump_mem_insn (FILE *file)
{
  dump_insn_slim (file, mem_insn.insn);

  if (mem_insn.reg1_is_const)
    fprintf (file, "found mem(%d) *(r[%d]+%d)\n",
	     INSN_UID (mem_insn.insn),
	     REGNO (mem_insn.reg0), (int) mem_insn.reg1_val);
  else
    fprintf (file, "found mem(%d) *(r[%d]+r[%d])\n",
	     INSN_UID (mem_insn.insn),
	     REGNO (mem_insn.reg0), REGNO (mem_insn.reg1));
}
