qqdiv(NUMBER *q1, NUMBER *q2)
{
	NUMBER temp;

	if (qiszero(q2)) {
		math_error("Division by zero");

	}
	if ((q1 == q2) || !qcmp(q1, q2))
		return qlink(&_qone_);
	if (qisone(q1))
		return qinv(q2);
	temp.num = q2->den;
	temp.den = q2->num;
	temp.num.sign = temp.den.sign;
	temp.den.sign = 0;
	temp.links = 1;
	return qmul(q1, &temp);
}
