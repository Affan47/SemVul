compute_array_to_seek(int32 *user_seek,
                      int32 *array_indicies,
                      int32 nt_size,
                      int32 ndims,
                      DIM_REC *ddims          )
{
    int32 j;
    int32 cnum;


    *user_seek = array_indicies[ndims - 1];
    if (ndims > 1)
      {
          cnum = 1;
          for(j = ndims - 2; j >= 0 ; j--)
            {
                cnum *= ddims[j + 1].dim_length;
                *user_seek += (array_indicies[j] * cnum );
            }
      }


    *user_seek = *user_seek * nt_size;

}
