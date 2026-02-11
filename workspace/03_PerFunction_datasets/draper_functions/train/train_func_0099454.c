CreateNode(unsigned int depth,
                                            nSearchTreeNode parent,
                                            nSearchTreeLabel label,
                                            unsigned int labelstart,
                                            unsigned int labellen)
{
    return new SearchTreeNode(depth,parent,label,labelstart,labellen);
}
