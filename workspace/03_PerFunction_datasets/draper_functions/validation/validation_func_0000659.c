PNM_Image (istream& in, const char* creator) {

  FileType filetype;
  if (!creator) creator = ReadCreator(in, filetype);

  if (strncmp(creator, "PPM", 3)==0) {
    boolean asciiflag = creator[3] == 'A';
    return PPM_Image(in, asciiflag);
  } else
  if (strncmp(creator, "PGM", 3)==0) {
    boolean asciiflag =creator[3] == 'A';
    return PGM_Image(in, asciiflag);
  } else
  if (strncmp(creator, "PBM", 3)==0) {
    return PBM_Image(in);
  } else
    return nil;
}
