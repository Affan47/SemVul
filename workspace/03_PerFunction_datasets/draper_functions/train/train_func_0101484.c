paintEvent(QPaintEvent *)
{
    if (!root) return;


    QFont font;


    QPainter painter(this);
    QColor color = Qt::white;
    QPen pen(Qt::white);
    pen.setWidth(10);
    QBrush brush(Qt::white);
    painter.setBrush(brush);
    painter.setPen(pen);


    painter.drawRect(root->rect.x()+4,
                     root->rect.y()+4,
                     root->rect.width()-8,
                     root->rect.height()-8);


    font.setPointSize(18);
    painter.setFont(font);
    pen.setWidth(5);
    pen.setColor(Qt::white);
    painter.setPen(pen);
    color = Qt::black;


    int n=1;
    QColor cHSV, cRGB;
    double factor = double(1) / double(root->children.count());
    foreach (TreeMap *first, root->children) {

        cHSV.setHsv((double)255 / (factor*n++), 255, 150);
        cRGB = cHSV.convertTo(QColor::Rgb);
        brush.setColor(cRGB);
        painter.setBrush(brush);
        painter.drawRect(first->rect);
        painter.drawText(first->rect,
                         Qt::AlignVCenter|Qt::AlignHCenter,
                         first->name);
    }


    font.setPointSize(8);
    painter.setFont(font);
    pen.setWidth(1);
    pen.setColor(Qt::lightGray);
    painter.setPen(pen);
    color = Qt::darkGray;
    color.setAlpha(127);
    brush.setColor(color);
    QColor hcolor(Qt::lightGray);
    hcolor.setAlpha(127);
    QBrush hbrush(hcolor);

    foreach (TreeMap *first, root->children)
        foreach (TreeMap *second, first->children) {
            if (second == highlight) painter.setBrush(hbrush);
            else painter.setBrush(brush);
            painter.setPen(Qt::NoPen);
            painter.drawRect(second->rect.x()+2,
                             second->rect.y()+2,
                             second->rect.width()-4,
                             second->rect.height()-4);
            painter.setPen(pen);
            painter.drawText(second->rect, Qt::AlignTop|Qt::AlignLeft, second->name);
        }
}
