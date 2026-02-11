getMouseData(int fd, Gpm_Type *type, int kd_mode)
{
   static unsigned char data[32];
   char *edata=data+type->packetlen;
   int howmany=type->howmany;
   int i,j;


   if (read(fd, data, howmany)!=howmany) {
      if (opt_test) exit(0);
      gpm_report(GPM_PR_ERR,GPM_MESS_READ_FIRST, strerror(errno));
      return NULL;
   }

   if ((kd_mode!=KD_TEXT || option.force_repeat) && fifofd != -1 && opt_rawrep)
      write(fifofd, data, howmany);

   if ((data[0]&((which_mouse->m_type)->proto)[0]) != ((which_mouse->m_type)->proto)[1]) {
      if ((which_mouse->m_type)->getextra == 1) {
         data[1]=GPM_EXTRA_MAGIC_1; data[2]=GPM_EXTRA_MAGIC_2;
         gpm_report(GPM_PR_DEBUG,GPM_EXTRA_DATA,data[0]);
         return data;
      }
      gpm_report(GPM_PR_DEBUG,GPM_MESS_PROT_ERR);
      return NULL;
   }


   if((i=(which_mouse->m_type)->packetlen-howmany))
      do {
         j = read(fd,edata-i,i);
         if ((kd_mode!=KD_TEXT || option.force_repeat)
              && fifofd != -1 && opt_rawrep && j > 0)
            write(fifofd, edata-i, j);
         i -= j;
      } while (i && j);

   if (i) {
      gpm_report(GPM_PR_ERR,GPM_MESS_READ_REST, strerror(errno));
      return NULL;
   }

   if ((data[1]&((which_mouse->m_type)->proto)[2]) != ((which_mouse->m_type)->proto)[3]) {
      gpm_report(GPM_PR_INFO,GPM_MESS_SKIP_DATA);
      return NULL;
   }
   gpm_report(GPM_PR_DEBUG,GPM_MESS_DATA_4,data[0],data[1],data[2],data[3]);
   return data;
}
