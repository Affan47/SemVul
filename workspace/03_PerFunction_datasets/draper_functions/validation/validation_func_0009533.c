Aset_I_print(Aset_I A){
 int i,r;
#ifdef LOG_PRINT
fprintf(msd_out," R=%d, N=%d, M=%d \n",A_r(A),A_n(A),A_m(A));
   fprintf(msd_out," tops = <")
#endif
;
   for(i=1;i<=A_r(A);i++){
 #ifdef LOG_PRINT
    fprintf(msd_out,"%d ",A_npts(A,i))
#endif
;
         if (i<A_r(A))
#ifdef LOG_PRINT
fprintf(msd_out,",")
#endif
;
   }
 #ifdef LOG_PRINT
  fprintf(msd_out,">\n");
   fprintf(msd_out," sts = <")
#endif
;
      for(i=1;i<=A_r(A);i++){
#ifdef LOG_PRINT
         fprintf(msd_out,"%d ",A_ptst(A,i))
#endif
;
         if (i<A_r(A))
#ifdef LOG_PRINT
fprintf(msd_out,",")
#endif
;
   }
#ifdef LOG_PRINT
   fprintf(msd_out,">\n")
#endif
;
   for(r=1;r<=A_r(A);r++){
#ifdef LOG_PRINT
    fprintf(msd_out,"configuration %d :\n",r)
#endif
;
    for(i=1;i<=A_npts(A,r);i++) {
      pnt_print(A_pt(A,r,i));
    }
   }
}
