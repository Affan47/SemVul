Sort()
{

	if ( ! this->tree.qualifiers.empty() ) {
		sort ( this->tree.qualifiers.begin(), this->tree.qualifiers.end(), CompareNodeNames );
		SortWithinOffspring ( this->tree.qualifiers );
	}

	if ( ! this->tree.children.empty() ) {

		sort ( this->tree.children.begin(), this->tree.children.end(), CompareNodeValues );
		SortWithinOffspring ( this->tree.children );
	}

}
