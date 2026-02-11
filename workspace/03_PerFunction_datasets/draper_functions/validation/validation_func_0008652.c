orderedChildren() {
	QList<QObject*> result;
	for(int i=0; i < count(); i++) {
		ModelPart *mp = itemModelPart(item(i));
		if(mp) {
			result << mp;
		}
	}
	return result;
}
