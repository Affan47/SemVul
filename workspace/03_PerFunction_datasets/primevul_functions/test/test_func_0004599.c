regname_internal_riscv (unsigned int regno)
{
  const char *name = NULL;


  if (regno < ARRAY_SIZE (dwarf_regnames_riscv))
    name = dwarf_regnames_riscv [regno];
  else if (regno >= 4096 && regno <= 8191)
    {


      switch (regno)
	{
#define DECLARE_CSR(NAME,VALUE,CLASS,DEFINE_VER,ABORT_VER) \
  case VALUE + 4096: name = #NAME; break;
#include "opcode/riscv-opc.h"
#undef DECLARE_CSR

	default:
	  {
	    static char csr_name[10];
	    snprintf (csr_name, sizeof (csr_name), "csr%d", (regno - 4096));
	    name = csr_name;
	  }
	  break;
	}
    }

  return name;
}
