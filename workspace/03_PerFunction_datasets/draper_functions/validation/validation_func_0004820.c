matrix_invert( GLmatrix *mat )
{
   if (inv_mat_tab[mat->type](mat)) {
      mat->flags &= ~MAT_FLAG_SINGULAR;
      return GL_TRUE;
   } else {
      mat->flags |= MAT_FLAG_SINGULAR;
      memcpy( mat->inv, Identity, sizeof(Identity) );
      return GL_FALSE;
   }
}
