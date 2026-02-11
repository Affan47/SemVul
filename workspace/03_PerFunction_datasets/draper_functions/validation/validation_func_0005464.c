is_loop_clockwise(const int *contour_x, const int *contour_y,
                         const int ncontour, const int default_ret)
{
   int ret;
   int *chain, nchain;


   if((ret = chain_code_loop(&chain, &nchain,
                             contour_x, contour_y, ncontour)))

      return(ret);


   if(nchain == 0){


      return(default_ret);
   }


   ret = is_chain_clockwise(chain, nchain, default_ret);


   free(chain);
   return(ret);
}
