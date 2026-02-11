OpFclose()
{
   fah_fclose_it in ;
   fah_fclose_ot out ;
   u_short fid ;

   if (!readn(newsock, (char *)&in, sizeof(in)))
      return ;
   fid = ntohs(in.fid) ;

   if (!(fid < TABLE_SIZE && table[fid].fp != NULL))
    {
       out.status = htons(FAILURE) ;
       out.error = htons(FAH_ER_NOTOPEN) ;
    }
   else
      if (fclose(table[fid].fp) == EOF)
       {
	  out.status = htons(FAILURE) ;
	  out.error = htons(FAH_ER_FCLOSE) ;
       }
      else
       {
	  table[fid].fp = NULL ;
	  out.status = htons(SUCCESS) ;
	  out.error = htons(FAH_ER_NOERROR) ;
       }
   writen(newsock, (char *)&out, sizeof(out)) ;
}
