fdomain_16x0_bus_reset(struct scsi_cmnd *SCpnt)
{
   unsigned long flags;

   local_irq_save(flags);

   outb(1, port_base + SCSI_Cntl);
   do_pause( 2 );
   outb(0, port_base + SCSI_Cntl);
   do_pause( 115 );
   outb(0, port_base + SCSI_Mode_Cntl);
   outb(PARITY_MASK, port_base + TMC_Cntl);

   local_irq_restore(flags);
   return SUCCESS;
}
