#ifndef layout_h
#define layout_h
typedef struct {
	int x;
	int y;
} point;


typedef struct {
	point *start;
	int len;
} h_line;

typedef struct {
	point *start;
	int len;
} v_line;

typedef struct {
	h_line *top;
	h_line *bottom;
	v_line *left;
	v_line *right;
} rect;

typedef struct rect_list{
	rect *current;
	struct rect_list *next;
} rect_list;

typedef rect_list layout;


rect *make_layout(point *size);
point *make_point(int x, int y);
void split_rect_vertically(rect_list **l, rect *r, point *p);
rect *find_rect_containing(rect_list *l, point *p);
void split_rect_horizontally(rect_list **l, rect *r, point *p);


#endif
