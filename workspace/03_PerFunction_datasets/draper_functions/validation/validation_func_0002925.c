tok(void)
{
  jmp_buf b;
  CX c=Cx;


   jmptype j=J;
   I *k=K,z;


   if (setjmp(J=b)) {
     z = 0;
   } else {
     z = ra(bal(0));
   }


   K=k,Cx=c;
   J=j;
   R z;

}
