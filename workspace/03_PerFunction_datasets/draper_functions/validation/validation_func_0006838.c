CSParseri(SumRandom ** pIntArriv, SumRandom ** pPktSize, TDistro &
IntArrivDistro, TDistro & PktSizeDistro){

	delete(*pIntArriv);

	IntArrivDistro = pdStudent;
	Student *Student_rv = new Student(41.6858, 0.0694393, 1.08341);
	*pIntArriv = new SumRandom(1 * (*Student_rv));


	delete(*pPktSize);


	PktSizeDistro=pdDiscrete;

	Real val[8];
	Real prob[8];

	val[0]=27;
	prob[0]=0.8312;

	val[1]=28;
	prob[1]=0.0018;

	val[2]=29;
	prob[2]=0.0453;

	val[3]=30;
	prob[3]=0.0195;

	val[4]=31;
	prob[4]=0.0879;

	val[5]=32;
	prob[5]=0.0024;

	val[6]=33;
	prob[6]=0.0106;

	val[7]=35;
	prob[7]=0.0013;

	static DiscreteGen P(8,prob,val);

	*pPktSize = new SumRandom(1 * P);
}
