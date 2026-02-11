elm_10node_triangle_dndv_fvalue(double *F,double u,double v)
{
     double R=0.0;
     int i;

     for( i=0; i<10; i++ )
     {
         R += F[i]*( N[i][2] + N[i][3]*u + 2*N[i][5]*v + N[i][6]*u*u +
                     N[i][7]*2*u*v + 3*N[i][9]*v*v);
     }

     return R;
}
