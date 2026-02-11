ocResolve_ELF ( ObjectCode* oc )
{
   int   shnum, ok;
   char*     ehdrC = (char*)(oc->image);
   Elf_Ehdr* ehdr  = (Elf_Ehdr*) ehdrC;
   Elf_Shdr* shdr  = (Elf_Shdr*) (ehdrC + ehdr->e_shoff);


   for (shnum = 0; shnum < ehdr->e_shnum; shnum++) {
      if (shdr[shnum].sh_type == SHT_REL) {
         ok = do_Elf_Rel_relocations ( oc, ehdrC, shdr, shnum );
         if (!ok) return ok;
      }
      else
      if (shdr[shnum].sh_type == SHT_RELA) {
         ok = do_Elf_Rela_relocations ( oc, ehdrC, shdr, shnum );
         if (!ok) return ok;
      }
   }

#if defined(powerpc_HOST_ARCH) || defined(arm_HOST_ARCH)
   ocFlushInstructionCache( oc );
#endif

   return 1;
}
