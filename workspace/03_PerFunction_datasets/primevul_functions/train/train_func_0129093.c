int main(int argc, char **argv) {
    double st, en;
    int ret;
    st = get_time();

#ifdef DO_CALL_TEST0
    ret=test_curve(0);
#endif
#ifdef DO_CALL_TEST1
    ret=test_curve(1);
#endif
#ifdef DO_CALL_TEST2
    ret=test_curve(2);
#endif
#ifdef DO_CALL_TEST3
    if ( (ret=test_curve(3)==0) )
	ret = -1 ;
    else
	ret = 0;
#endif
#ifdef DO_CALL_TEST4
    ret=test_curve(4);
#endif
#ifdef DO_CALL_TEST5
    ret=test_curve(5);
#endif
#ifdef DO_CALL_TEST6
    ret=test_curve(6);
#endif
#ifdef DO_CALL_TEST7
    ret=test_curve(7);
#endif
#ifdef DO_CALL_TEST8
    ret=test_curve(8);
#endif
#ifdef DO_CALL_TEST9
    ret=test_curve(9);
#endif
#ifdef DO_CALL_TEST10


    ret=test_curve(10);
    ret = 0;
#endif
#ifdef DO_CALL_TEST11


    ret=test_curve(11);
    ret = 0;
#endif
#ifdef DO_CALL_TEST12


    ret=test_curve(12);
#endif
#ifdef DO_CALL_TEST13
    ret=test_curve(13);
#endif
#ifdef DO_CALL_TEST14
    ret=test_curve(14);
#endif
#ifdef DO_CALL_TEST15
    ret=test_curve(15);
#endif
#ifdef DO_CALL_TEST16
    ret=test_curve(16);
#endif
#ifdef DO_CALL_TEST17
    ret=test_curve(17);
#endif
#ifdef DO_CALL_TEST18
    ret=test_curve(18);
#endif
#ifdef DO_CALL_TEST19
    ret=test_curve(19);
#endif
#ifdef DO_CALL_TEST20

    if ( (ret=test_curve(20))==0 )
	if ( (ret=test_curve(21))==0 )
	    if ( (ret=test_curve(22))==0 )
		if ( (ret=test_curve(23))==0 )
		    ret=test_curve(24);
#endif
#ifdef DO_CALL_TESTM
    ret=test_multi_curves();
#endif

    en = get_time();
    printf("time %g\n", (en - st));
    return ret;
}
