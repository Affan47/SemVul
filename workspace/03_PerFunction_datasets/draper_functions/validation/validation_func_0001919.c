mr_xor(big x,big y,big z)
{
     int i,nx,ny,nz,nr;
     if (x==y)
     {
         copy(x,z);
         return;
     }

#ifdef MR_FLASH
     nx=mr_lent(x);
     ny=mr_lent(y);
     nz=mr_lent(z);
#else
     ny=(y->len&(MR_OBITS));
     nx=(x->len&(MR_OBITS));
     nz=(z->len&(MR_OBITS));
#endif
     if (ny<nx) nr=ny;
     else       nr=nx;
     for (i=0;i<nr;i++)
         z->w[i]=x->w[i]^y->w[i];
     for (i=nr;i<nz;i++)
         z->w[i]=0;
     z->len=nr;
}
