static void RecBlk(GmfMshSct *msh, const void *blk, int siz)
{

   if(siz)
   {
      memcpy(&msh->blk[ msh->pos ], blk, (size_t)(siz * WrdSiz));
      msh->pos += siz * WrdSiz;
   }


   if( (msh->pos > BufSiz) || (!siz && msh->pos) )
   {
#ifdef GMF_WINDOWS


#ifdef WITH_GMF_AIO
      if(write(msh->FilDes, msh->blk, (int)msh->pos) != (ssize_t)msh->pos)
#else
      if(fwrite(msh->blk, 1, (size_t)msh->pos, msh->hdl) != msh->pos)
#endif
         longjmp(msh->err, -30);
#else
#ifdef WITH_GMF_AIO
      if(write(msh->FilDes, msh->blk, msh->pos) != (ssize_t)msh->pos)
#else
      if(fwrite(msh->blk, 1, msh->pos, msh->hdl) != msh->pos)
#endif
         longjmp(msh->err, -31);
#endif
      msh->pos = 0;
   }
}
