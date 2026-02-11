ntreeify(struct aln_tree_node* p,int ntree)
{
	int i = 0;
	int c = 0;
	struct aln_tree_node* tmp1 = 0;
	struct aln_tree_node* tmp2 = 0;
	if (p->links[0]){
		ntreeify(p->links[0],ntree);
	}
	if (p->links[1]){
		ntreeify(p->links[1],ntree);
	}

	if (!p->done){
		tmp1 = p->links[0];
		tmp2 = p->links[1];

		p->done = tmp1->done + tmp2->done;
		i = 0;
		c = 0;
		if(tmp1->done != 1){

			while(tmp1->internal_lables[i]){
				p->internal_lables[c] = tmp1->internal_lables[i];
				i++;
				c++;
			}
			if(tmp2->done != 1){
				i = 0;
				while(tmp2->internal_lables[i]){
					p->internal_lables[c] = tmp2->internal_lables[i];
					c++;
					i++;
				}
			}
		}else if(tmp2->done != 1){
			i = 0;
			while(tmp2->internal_lables[i]){
				p->internal_lables[c] = tmp2->internal_lables[i];
				c++;
				i++;
			}
		}
		p->internal_lables[c] = p->num;


		if (tmp1->done > 1){
			for ( i = 0;i < tmp1->done;i++){
				p->links[i] = tmp1->links[i];
				tmp1->links[i] = 0;
			}
		}

		if (tmp2->done > 1){
			for ( i = 0; i < tmp2->done;i++){
				p->links[tmp1->done+i] = tmp2->links[i];
				tmp2->links[i] = 0;
			}
			free(tmp2->internal_lables);
			free(tmp2->links);
			free(tmp2);
		}else{
			p->links[tmp1->done] = tmp2;
		}

		p->links[p->done] = 0;

		if (tmp1->done > 1){
			free(tmp1->internal_lables);
			free(tmp1->links);
			free(tmp1);
		}

		if (p->done >= ntree){
			p->done = 1;


		}
	}
}
