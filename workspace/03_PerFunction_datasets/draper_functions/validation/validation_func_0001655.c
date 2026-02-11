smooth_imap(int *imap, const int mw, const int mh,
                 const DIR2RAD *dir2rad, const LFSPARMS *lfsparms)
{
   int mx, my;
   int *iptr;
   int avrdir, nvalid;
   double dir_strength;

   print2log("SMOOTH MAP\n");

   iptr = imap;
   for(my = 0; my < mh; my++){
      for(mx = 0; mx < mw; mx++){


         average_8nbr_dir(&avrdir, &dir_strength, &nvalid,
                          imap, mx, my, mw, mh, dir2rad);


         if(dir_strength >= lfsparms->dir_strength_min){

            if(*iptr != INVALID_DIR){

               if(nvalid >= lfsparms->rmv_valid_nbr_min){

#ifdef LOG_REPORT
                  fprintf(logfp, "   BLOCK %2d (%2d, %2d)\n",
                          mx+(my*mw), mx, my);
                  fprintf(logfp, "      Average NBR :   %2d %6.3f %d\n",
                          avrdir, dir_strength, nvalid);
                  fprintf(logfp, "      1. Valid NBR (%d >= %d)\n",
                          nvalid, lfsparms->rmv_valid_nbr_min);
                  fprintf(logfp, "      Valid Direction = %d\n", *iptr);
                  fprintf(logfp, "      Smoothed Direction = %d\n", avrdir);
#endif


                  *iptr = avrdir;
               }
            }

            else{


               if(nvalid >= lfsparms->smth_valid_nbr_min){

#ifdef LOG_REPORT
                  fprintf(logfp, "   BLOCK %2d (%2d, %2d)\n",
                          mx+(my*mw), mx, my);
                  fprintf(logfp, "      Average NBR :   %2d %6.3f %d\n",
                          avrdir, dir_strength, nvalid);
                  fprintf(logfp, "      2. Invalid NBR (%d >= %d)\n",
                          nvalid, lfsparms->smth_valid_nbr_min);
                  fprintf(logfp, "      Invalid Direction = %d\n", *iptr);
                  fprintf(logfp, "      Smoothed Direction = %d\n", avrdir);
#endif


                  *iptr = avrdir;
               }
            }
         }


         iptr++;
      }
   }
}
