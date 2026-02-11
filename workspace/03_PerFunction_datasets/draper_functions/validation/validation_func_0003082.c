getXmlDescription(Rules& r){
	Q_UNUSED(r);

	QString s="<ConstraintSubjectActivityTagPreferredRooms>\n";
	s+="	<Weight_Percentage>"+CustomFETString::number(weightPercentage)+"</Weight_Percentage>\n";
	s+="	<Subject>"+protect(this->subjectName)+"</Subject>\n";
	s+="	<Activity_Tag>"+protect(this->activityTagName)+"</Activity_Tag>\n";
	s+="	<Number_of_Preferred_Rooms>"+CustomFETString::number(this->roomsNames.count())+"</Number_of_Preferred_Rooms>\n";
	for(QStringList::Iterator it=this->roomsNames.begin(); it!=this->roomsNames.end(); it++)
		s+="	<Preferred_Room>"+protect(*it)+"</Preferred_Room>\n";

	s+="	<Active>"+trueFalse(active)+"</Active>\n";
	s+="	<Comments>"+protect(comments)+"</Comments>\n";
	s+="</ConstraintSubjectActivityTagPreferredRooms>\n";

	return s;
}
