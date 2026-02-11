mv_mul3(matrix, vector, v_result)
const hmat3_t *matrix;
const hvec3_t *vector;
hvec3_t *v_result;
{
   int row, inplace;
   hvec3_t buf;

   if(v_result == vector)
   {
     v_result = &buf;
     inplace = 1;
   }
   else
   {
     v_result = gm_ALLOC(hvec3_t, v_result, "mv_mul3()");
     inplace = 0;
   };

   for(row=0; row<4; row++)
        v_elem(*v_result, row) = m_elem(*matrix, row, 0) *
	v_elem(*vector, 0) + m_elem(*matrix, row, 1) *
	v_elem(*vector, 1) + m_elem(*matrix, row, 2) *
	v_elem(*vector, 2) + m_elem(*matrix, row, 3) *
	v_elem(*vector, 3);

   if(inplace)
   {
     v_cpy3(v_result, (hvec3_t *)vector);
     return (hvec3_t *) vector;
   };

   return  v_result;
}
