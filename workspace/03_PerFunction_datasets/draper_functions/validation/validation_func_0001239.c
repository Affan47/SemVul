main( int argc, char *argv[] ) {
  int status;

  if ( argc != 3 ) {
    cerr << "Invalid number of arguments" << endl
         << "Usage: " << argv[0] << "<icons.bmp> <outfile>" << endl;
    exit(-1);
  }


  if ( SDL_Init(0) < 0 ) {
    cerr << "Couldn't init SDL: " << SDL_GetError() << endl;
    exit(-1);
  }
  atexit(SDL_Quit);

  File out( argv[2] );
  if ( !out.Open( "wb" ) ) {
    cerr << "Couldn't open output file " << argv[5] << endl;
    exit(-1);
  }


  MkSurface img;
  status = img.SaveImageData( argv[1], out, true );
  out.Close();
  return status;
}
