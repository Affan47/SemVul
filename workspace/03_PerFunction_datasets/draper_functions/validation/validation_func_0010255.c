floor_item_increase(int item, int num)
{
	object_type *o_ptr = object_byid(item);


	num += o_ptr->number;


	if (num > 255) num = 255;
	else if (num < 0) num = 0;


	num -= o_ptr->number;


	o_ptr->number += num;
}
