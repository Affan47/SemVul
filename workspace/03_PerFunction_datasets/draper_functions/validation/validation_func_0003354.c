ep_satt(V v,S s,I val){I z=qz((A)val);if(!v->atb){if(z)R 1;else v->atb=atbi();}
 R (z?htxi(v->atb,s,1):htsi(v->atb,s,val,1,(I(*)())atti));}
