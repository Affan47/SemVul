read_indent(const char *input, int indent, int size, int in_index, int *out_index, char *output)
{
    int k = 0, j;

    while (in_index < size) {
        if (input[in_index] == ' ') {
            k++;
        } else if (input[in_index] == '\t') {

            k += 8;
        } else  if (input[in_index] == '\\' && input[in_index + 1] == 't') {

            k += 8;
            ++in_index;
        } else {
            break;
        }
        ++in_index;
        if (k >= indent) {
            for (j = k - indent; j > 0; --j) {
                output[*out_index] = ' ';
                if (j > 1) {
                    ++(*out_index);
                }
            }
            break;
        }
    }
    return in_index - 1;
}
