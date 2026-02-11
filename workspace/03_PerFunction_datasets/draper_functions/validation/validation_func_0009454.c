XpTableLocCompareRowSpan(  loc1, loc2 )
    XpTableLoc  loc1, loc2;
{
    if ( loc1->row_span == loc2->row_span )
	return loc1->row - loc2->row;

    return loc1->row_span - loc2->row_span;
}
