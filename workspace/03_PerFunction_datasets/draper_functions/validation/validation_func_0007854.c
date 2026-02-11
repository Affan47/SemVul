PNM_Image_Filter (
  istream& in, boolean return_fd, int& fd, const char* filter
) {
  GraphicComp* comp = nil;
  int outfd = Pipe_Filter(in, filter);

  if (return_fd) {
    fd = outfd;
  }
  else {
#if __GNUC__<3
    ifstream in2;
    in2.rdbuf()->attach(outfd);
#else
    FILE* infptr = fdopen(outfd, "r");
    fileptr_filebuf fbuf(infptr, ios_base::in);
    istream in2(&fbuf);
#endif

    comp = PNM_Image(in2);

    if(close(outfd)==-1)
      cerr << "error in parent closing last end of the pipes\n";
#if __GNUC__>=3
    if (infptr) fclose(infptr);
#endif
  }

  return comp;
}
