crush_destroy_bucket(struct crush_bucket *b)
{
	switch (b->alg) {
	case CRUSH_BUCKET_UNIFORM:
		crush_destroy_bucket_uniform((struct crush_bucket_uniform *)b);
		break;
	case CRUSH_BUCKET_LIST:
		crush_destroy_bucket_list((struct crush_bucket_list *)b);
		break;
	case CRUSH_BUCKET_TREE:
		crush_destroy_bucket_tree((struct crush_bucket_tree *)b);
		break;
	case CRUSH_BUCKET_STRAW:
		crush_destroy_bucket_straw((struct crush_bucket_straw *)b);
		break;
	}
}
