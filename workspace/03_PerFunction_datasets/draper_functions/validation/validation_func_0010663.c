box2d_same(BOX2DFLOAT4 *box1, BOX2DFLOAT4 *box2)
{
	return(	(box1->xmax==box2->xmax) &&
		(box1->xmin==box2->xmin) &&
		(box1->ymax==box2->ymax) &&
		(box1->ymin==box2->ymin));
#if 0
	return(FPeq(box1->xmax, box2->xmax) &&
				   FPeq(box1->xmin, box2->xmin) &&
				   FPeq(box1->ymax, box2->ymax) &&
				   FPeq(box1->ymin, box2->ymin));
#endif
}
