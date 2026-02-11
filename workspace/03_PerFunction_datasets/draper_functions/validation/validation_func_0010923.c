c6sup1_set_irq(vm_instance_t *vm,u_int irq)
{
   __maybe_unused c6sup1_t *router = VM_C6SUP1(vm);
   cpu_mips_t *cpu0 = CPU_MIPS64(vm->boot_cpu);
   u_int slot,port;

   switch(irq) {
      case 0 ... 7:
         mips64_set_irq(cpu0,irq);

         if (cpu0->irq_idle_preempt[irq])
            cpu_idle_break_wait(cpu0->gen);
         break;

      case C6SUP1_NETIO_IRQ_BASE ... C6SUP1_NETIO_IRQ_END:
         c6sup1_net_irq_get_slot_port(irq,&slot,&port);

         break;
   }
}
