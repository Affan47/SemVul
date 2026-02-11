main(int argc, char **argv)
{
   colortail = NULL;


   colortail = new ColorTail();


   signal (SIGINT,  clean_up);
   signal (SIGHUP,  clean_up);
   signal (SIGKILL, clean_up);


   int ret = colortail->start(argc, argv);

   delete colortail;

   return ret;
}
