int test_multi_curves(void) {
    spiro_cp **spiro = NULL;
    spiro_cp *temp;
    int *pk, **nextknot = NULL;
    int *scl = NULL;
    test_bezctx **bc;
    int i, j, k, l, ret;
    double x, y;
    char ty;


#define S_TESTS S_TESTP*5

#ifdef HAVE_PTHREADS
    pthread_attr_t tattr;
    pthread_t curve_test[S_TESTS];
    pthread_pcurve pdata[S_TESTS];

    printf("---\nMulti-thread testing of libspiro.\n");
#else
    printf("---\nSequential tests of libspiro.\n");
#endif

    ret = -1;


    if ( (bc=(test_bezctx**)calloc(S_TESTS,sizeof(test_bezctx*)))==NULL )
	goto test_multi_curves_exit;
    for (i=0; i < S_TESTS; i++) {
	if ( (bc[i]=(test_bezctx*)malloc(sizeof(test_bezctx)))==NULL )
	    goto test_multi_curves_exit;
	bc[i]->base.moveto = test_s_moveto;
	bc[i]->base.lineto = test_s_lineto;
	bc[i]->base.quadto = test_s_quadto;
	bc[i]->base.curveto = test_s_curveto;
	bc[i]->base.mark_knot = test_s_mark_knot;
	if ( (bc[i]->my_curve=(my_curve_data*)calloc(S_RESULTS,sizeof(my_curve_data)))==NULL )
	    goto test_multi_curves_exit;
	bc[i]->len = 0;
	bc[i]->is_open = 0;
	bc[i]->c_id = i;
    }

    if ( (scl=(int*)malloc(S_TESTS*sizeof(int)))==NULL || \
	 (spiro=(spiro_cp**)calloc(S_TESTS,sizeof(spiro_cp*)))==NULL || \
	 (nextknot=(int**)calloc(S_TESTS,sizeof(int*)))==NULL )
	goto test_multi_curves_exit;
    for (i=0; i < S_TESTS; ) {


	if ( (spiro[i]=malloc(cl[0]*sizeof(spiro_cp)))==NULL || \
	      (nextknot[i]=calloc(cl[0],sizeof(int)))==NULL )
	    goto test_multi_curves_exit;
	load_test_curve(spiro[i],nextknot[i],0);
	scl[i++]=cl[0];
	if ( (spiro[i]=malloc(cl[1]*sizeof(spiro_cp)))==NULL || \
	      (nextknot[i]=calloc(cl[1],sizeof(int)))==NULL )
	    goto test_multi_curves_exit;
	load_test_curve(spiro[i],nextknot[i],1);
	scl[i++]=cl[1];
	if ( (spiro[i]=malloc(cl[2]*sizeof(spiro_cp)))==NULL || \
	      (nextknot[i]=calloc(cl[2],sizeof(int)))==NULL )
	    goto test_multi_curves_exit;
	load_test_curve(spiro[i],nextknot[i],2);
	scl[i++]=cl[2];
	if ( (spiro[i]=malloc(cl[5]*sizeof(spiro_cp)))==NULL || \
	      (nextknot[i]=calloc(cl[5],sizeof(int)))==NULL )
	    goto test_multi_curves_exit;
	load_test_curve(spiro[i],nextknot[i],5);
	scl[i++]=cl[5];
	if ( (spiro[i]=malloc(cl[6]*sizeof(spiro_cp)))==NULL || \
	      (nextknot[i]=calloc(cl[6],sizeof(int)))==NULL )
	    goto test_multi_curves_exit;
	load_test_curve(spiro[i],nextknot[i],6);
	scl[i++]=cl[6];
    }


    for (i=0; i < S_TESTS; i++) {
	temp = spiro[i];
	for (j=0; j < scl[i]; j++) {
	    if ( i&1 ) {
		temp[j].x = temp[j].x * (i/S_TESTS+1) + i;
		temp[j].y = temp[j].y * (i/S_TESTS+1) + i;
	    } else {

		temp[j].x *= (i+1); temp[j].x += i*1000. - 5000.;
		temp[j].y *= (i+1); temp[j].y += i*3000. - 9000.;
	    }
	}
    }

    --ret;

#ifdef HAVE_PTHREADS


    for (i=0; i < S_TESTS; i++) {
	pdata[i].spiro = spiro[i];
	pdata[i].bc = (bezctx*)(bc[i]);
	pdata[i].ret = i;
    }

    j=0;
    for (k=0; k < S_TESTS;) {

	pthread_attr_init(&tattr);
	pthread_attr_setdetachstate(&tattr,PTHREAD_CREATE_JOINABLE);


	for (i=k; i < S_TESTS-1; i++) {

	    if ( pthread_create(&curve_test[i],&tattr,test_a_curve,(void *)&pdata[i]) ) {
		if ( i-k < 20 ) {
		    printf("bad pthread_create[%d]\n",i);
		    j=-1;
		}
		break;
	    }
	}
	pthread_attr_destroy(&tattr);
	if ( j!=-1 ) {

	    pdata[i].ret = TaggedSpiroCPsToBezier2(pdata[i].spiro,0,pdata[i].bc);
	    printf("running simultaneous threads[%d..%d]\n",k,i);
	}
	l=i;
	while (--i >= k)
	    if ( pthread_join(curve_test[i],NULL) ) {
		fprintf(stderr,"bad pthread_join[%d]\n",i);
		j=-1;
	    }
	k=++l;
	if (j) goto test_multi_curves_exit;
    }

    for (i=0; i < S_TESTS; i++)
	if ( pdata[i].ret!=1 ) {
	    ret=ret-i;
	    fprintf(stderr,"error %d with TaggedSpiroCPsToBezier2() using data=%d.\n",ret,i);
	    goto test_multi_curves_exit;
	}

#else


    for (i=0; i < S_TESTS; i++) {
	if ( TaggedSpiroCPsToBezier0(spiro[i],(bezctx*)(bc[i]))!=1 ) {
	    ret=ret-i;
	    fprintf(stderr,"error %d with TaggedSpiroCPsToBezier0() using data=%d.\n",ret,i);
	    goto test_multi_curves_exit;
	}
    }
#endif
    ret=ret-S_TESTS;


    for (i=0; i < S_TESTS; i++) {
	temp = spiro[i];
	pk = nextknot[i];
	k=0;
#ifdef VERBOSE
	printf("test[%d], input spiro[0..%d], output bc->my_curve[0..%d]\n", \
		   i, scl[i]-1, bc[i]->len-1);
#endif
	for (j=l=0; j < scl[i] && temp[j].ty!='z'; j++,l++) {
	    if (temp[j].ty=='h') {
#ifdef VERBOSE
		printf("  s[%d][ty=%c x=%g y=%g] is handle 'h' to anchor 'a'.\n", \
			l-1,temp[j].ty,temp[j].x,temp[j].y);
#endif
		--l;
	    } else {
		ty = bc[i]->my_curve[k].ty;
		x  = bc[i]->my_curve[k].x1;
		y  = bc[i]->my_curve[k].y1;
		if ( ty=='q' ) {
		    x = bc[i]->my_curve[k].x2;
		    y = bc[i]->my_curve[k].y2;
		}
		if ( ty=='c' ) {
		    x = bc[i]->my_curve[k].x3;
		    y = bc[i]->my_curve[k].y3;
		}
#ifdef VERBOSE
		printf("  s[%d][ty=%c x=%g y=%g], pk=%d mc[%d][x=%g y=%g]\n", \
			l,temp[j].ty,temp[j].x,temp[j].y,pk[j],k,x,y);
#endif
		if ( (fabs(temp[j].x - x) > 1e-5) || (fabs(temp[j].y - y) > 1e-5) ) {

		    if ( j == scl[i]-2 && temp[j+1].ty=='z' )
			;


		    else {
			ret=ret-i;
			fprintf(stderr,"error %d with test_multi_curves() using data %d\n",ret,i);
			goto test_multi_curves_exit;
		    }
		}
		k += pk[l]+1;
	    }
	}
    }

#ifdef HAVE_PTHREADS
    printf("Multi-thread testing of libspiro passed.\n");
#else
    printf("Sequential tests of libspiro passed.\n");
#endif
    ret = 0;

test_multi_curves_exit:
    if ( nextknot!=NULL ) for (i=0; i < S_TESTS; i++) free(nextknot[i]);
    if ( spiro!=NULL ) for (i=0; i < S_TESTS; i++) free(spiro[i]);
    free(nextknot); free(spiro); free(scl);
    if ( bc!=NULL ) for (i=0; i < S_TESTS; i++) {
	free(bc[i]->my_curve); free(bc[i]);
    }
    free(bc);
    return ret;
}
