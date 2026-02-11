main(int argc, char **argv){
	FILE *ifp;
	FILE *ofp;
	FILE *figfp;
	BUF_NODE ** OBUF;
	DME_TREE_NODE * OT ;
	DME_TREE_NODE ** OTmap ;
	DME_TREE_NODE * Store = (DME_TREE_NODE *) malloc(sizeof(DME_TREE_NODE));
	DME_TREE_NODE * son ;
	int remain_num_node;
	int remain_num_wire;
	int remain_total_buf_num;
	int remain_num_total_nodes;
	int remain_num_sinknode;
	ZERO = (DME_TREE_NODE *) malloc(sizeof(DME_TREE_NODE));
	if(argc > 4){
		printf("error: command inputfile\n");
		exit(1);
	}
	ifp = fopen( argv[1], "r") ;
	ofp = fopen(argv[2], "w") ;

	InputFile(ifp);
	preprocess_block(&blockage);

	init_delay_array = (double *) malloc (sizeof(double)*sink.num);


	int i;
	deferred_merge_embedding(FALSE);
 	insert_buffer(source_node, &OBUF, &OT, &OTmap) ;


	adjust_buf(OBUF,&blockage);
	output_file (ofp ,OBUF, OT, OTmap,1) ;

	return 1;
}
