LPF(unsigned char inImg[256][256], unsigned char outImg[256][256], int type){
		short filterh1[3][3] = {{1,1,1},
								{1,1,1},
								{1,1,1}};
		short filterh2[3][3] = {{1,1,1},
								{1,2,1},
								{1,1,1}};
		short filterh3[3][3] = {{1,2,1},
								{2,4,2},
								{1,2,1}};

		short **filter;
		int d = 0;
		if(type == 1){
			filter = (short**)filterh1;
		}
		else if(type == 2){
			filter = (short**)filterh2;
		}
		else if(type == 3){
			filter = (short**)filterh3;
		}

		for(int i=0; i<3; i++){
			for(int j=0; j<3; j++){
				d = d + filter[i][j];
			}
		}

		for(int i=1; i<255; i++){
			for(int j=1; j<255; j++){
				int sum = 0;
				for(int a=-1; a<2; a++){
					for(int b=-1; b<2; b++){
						sum = sum + inImg[i+a][j+b]*filter[a+1][b+1];
					}
				}
				sum = sum/d;
				if(sum < 0)   sum = 0;
				if(sum > 255) sum = 255;
				outImg[i][j] = sum;
			}
		}
	}
