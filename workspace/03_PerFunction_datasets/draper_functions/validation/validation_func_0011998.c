cmd_pmem_w16(hypervisor_conn_t *conn,int argc,char *argv[])
{
   vm_instance_t *vm;
   m_uint64_t addr;
   m_uint16_t value;

   if (!(vm = hypervisor_find_object(conn,argv[0],OBJ_TYPE_VM)))
      return(-1);


   addr  = strtoull(argv[2],NULL,0);
   value = strtoul(argv[3],NULL,0);
   physmem_copy_u16_to_vm(vm,addr,value);

   vm_release(vm);
   hypervisor_send_reply(conn,HSC_INFO_OK,1,"OK");
   return(0);
}
