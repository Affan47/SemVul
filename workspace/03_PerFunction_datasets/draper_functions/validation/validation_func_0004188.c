Face_Create( PFace  face)
  {
    TT_Error      error;


    if (
         LOAD_(MaxProfile)                  ||


         LOAD_(CVT)                         ||

         LOAD_(Programs)


        )
      goto Fail;

    return TT_Err_Ok;

  Fail :
    Face_Destroy( face );
    return error;
  }
