xsh_image_clean_badpixel(cpl_frame* in)
{


  cpl_image* ima=NULL;
  cpl_image* err=NULL;
  cpl_image* qua=NULL;
  cpl_propertylist* hima=NULL;
  cpl_propertylist* herr=NULL;
  cpl_propertylist* hqua=NULL;


  const char* name=NULL;
  double* pima=NULL;
  int* pqua=NULL;
  int nx=0;
  int ny=0;
  int i=0;
  int j=0;
  int rx=5;
  int ry=5;

  name=cpl_frame_get_filename(in);
  hima=cpl_propertylist_load(name,0);
  herr=cpl_propertylist_load(name,1);
  hqua=cpl_propertylist_load(name,2);
  ima=cpl_image_load(name,CPL_TYPE_DOUBLE,0,0);
  err=cpl_image_load(name,CPL_TYPE_DOUBLE,0,1);
  qua=cpl_image_load(name,CPL_TYPE_INT,0,2);

  nx=cpl_image_get_size_x(ima);
  ny=cpl_image_get_size_y(ima);

  pima=cpl_image_get_data_double(ima);
  pqua=cpl_image_get_data_int(qua);

  for(j=ry;j<ny-ry;j++) {
    for(i=rx;i<nx-rx;i++) {
      if(pqua[i+j*nx]!=0) {
	pima[i+j*nx]=cpl_image_get_median_window(ima,i-rx,j-ry,i+rx,j+ry);
      }
    }
  }
  check(cpl_image_save(ima,name,XSH_PRE_DATA_BPP,hima,CPL_IO_DEFAULT));
  check(cpl_image_save(err,name,XSH_PRE_ERRS_BPP,herr,CPL_IO_EXTEND));
  check(cpl_image_save(qua,name,XSH_PRE_QUAL_BPP,hqua,CPL_IO_EXTEND));

 cleanup:
  xsh_free_image(&ima);
  xsh_free_image(&err);
  xsh_free_image(&qua);
  xsh_free_propertylist(&hima);
  xsh_free_propertylist(&herr);
  xsh_free_propertylist(&hqua);

  return cpl_error_get_code();

}
