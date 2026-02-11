init_ped_loc_all()
{
int a,b,c;

locusvalues **templocus;

   templocus = thislocus;

if (totalNumPed==0)
  {

  fprintf(stderr,"foundped() found 0 pedigree's - wrong.\n");
  exit(EXIT_FAILURE);
  }
ped_loc_all = NULL;
ped_loc_all = (loc_all *)malloc(totalNumPed*sizeof(loc_all));
if (ped_loc_all==NULL)
  malloc_err("ped_loc_all");

  ped_new_allele_count = NULL;
  ped_new_allele_count = (new_allele_count *)
      malloc(totalNumPed * sizeof(new_allele_count));


for (a=0;a<totalNumPed;a++)
  {
  for (b=0;b<maxlocus;b++)
    {
      ped_new_allele_count[a][b] = 0;
      ped_loc_all[a][b][0].present = FALSE;
      ped_loc_all[a][b][0].new_allele = 0;
      ped_loc_all[a][b][0].old_allele = 0;
      for (c=1;c<=maxall;c++)
	{
	  ped_loc_all[a][b][c].present = FALSE;
	  ped_loc_all[a][b][c].new_allele = 0;
	  ped_loc_all[a][b][c].old_allele = 0;
	}
    }
  }
return;
}
