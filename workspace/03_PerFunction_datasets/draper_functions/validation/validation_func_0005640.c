pb_print_to(sge_pack_buffer *pb, bool only_header, FILE* file)
{
   int i;

   fprintf(file, "head_ptr: %p\n", pb->head_ptr);
   fprintf(file, "cur_ptr: %p\n", pb->cur_ptr);
   fprintf(file, "mem_size: %d\n", (int)pb->mem_size);
   fprintf(file, "bytes_used: %d\n", (int)pb->bytes_used);
   fprintf(file, "buffer:\n");
   if (!only_header) {
      for (i = 0; i < pb->bytes_used; i++) {
         fprintf(file, "%3d ", pb->head_ptr[i]);
         if ((i + 1) % 15 == 0) {
            fprintf(file, "\n");
         }
      }
      fprintf(file, "\n");
   }
}
