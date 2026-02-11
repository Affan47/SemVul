FB(const bool *whatd,const Mesh & Th,const Triangle & K,const R2 & PHat,RNMK_ & val) const
{

  R2 P(K(PHat));
  R2 A(K[0]), B(K[1]),C(K[2]);


  if (val.N() <3)
   throwassert(val.N() >=3);
  throwassert(val.M()==2 );

  val=0;
  R a=1./(2*K.area);
  R a0=   K.EdgeOrientation(0) * a ;
  R a1=   K.EdgeOrientation(1) * a  ;
  R a2=   K.EdgeOrientation(2) * a ;


  if (whatd[op_id])
   {
   assert(val.K()>op_id);
  RN_ f0(val('.',0,0));
  RN_ f1(val('.',1,0));
  f1[0] =  (P.x-A.x)*a0;
  f0[0] = -(P.y-A.y)*a0;

  f1[1] =  (P.x-B.x)*a1;
  f0[1] = -(P.y-B.y)*a1;

  f1[2] =  (P.x-C.x)*a2;
  f0[2] = -(P.y-C.y)*a2;
  }

    if (whatd[op_dx])
   {
   assert(val.K()>op_dx);
   val(0,1,op_dx) =  a0;
   val(1,1,op_dx) =  a1;
   val(2,1,op_dx) =  a2;
  }
    if (whatd[op_dy])
   {
   assert(val.K()>op_dy);
    val(0,0,op_dy) =  -a0;
    val(1,0,op_dy) =  -a1;
    val(2,0,op_dy) =  -a2;
  }
}
