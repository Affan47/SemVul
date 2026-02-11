f_3201(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_stack_overflow_check;
loop:
t2=t1;
t3=((C_word*)t0)[2];
t4=C_fixnum_greater_or_equal_p(t2,t3);
if(C_truep(t4)){
return(t4);}
else{
t5=C_i_string_ref(((C_word*)t0)[3],t1);
if(C_truep(C_i_char_equalp(((C_word*)t0)[4],t5))){
t6=C_fixnum_plus(t1,C_fix(1));
t8=t6;
t1=t8;
goto loop;}
else{
return(C_SCHEME_FALSE);}}}
