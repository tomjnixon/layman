#include <stdlib.h>
#include "layout.h"

point *make_point(int x, int y)
{
	point *p = malloc(sizeof(point));
	p->x = x;
	p->y = y;
	return p;
}


h_line *make_h_line(point *start, int len)
{
	h_line *l = malloc(sizeof(h_line));
	l->start = start;
	l->len = len;
	return l;
}


v_line *make_v_line(point *start, int len)
{
	v_line *l = malloc(sizeof(v_line));
	l->start = start;
	l->len = len;
	return l;
}


rect *make_rect(h_line *top, h_line *bottom, v_line *left, v_line *right)
{
	rect *r = malloc(sizeof(rect));
	r->top = top;
	r->bottom = bottom;
	r->left = left;
	r->right = right;
	return r;
}


rect *make_layout(point *size)
{
	h_line *top = make_h_line(make_point(0, 0), size->x);
	h_line *bottom = make_h_line(make_point(0, size->y), size->x);
	
	v_line *left = make_v_line(make_point(0, 0), size->y);
	v_line *right = make_v_line(make_point(size->x, 0), size->y);
	return make_rect(top, bottom, left, right);
}


int point_in_rect(rect *r, point *p)
{
	return r->top->start->y < p->y &&
	       r->bottom->start->y > p->y &&
	       r->left->start->x < p->x &&
	       r->right->start->x > p->x;
}


rect *find_rect_containing(rect_list *l, point *p)
{
	while (l) {
		if (point_in_rect(l->current, p))
			return l->current;
		l = l->next;
	}
	return NULL;
}


void append(rect_list **l, rect *r) {
	rect_list *new_l = malloc(sizeof(rect_list));
	new_l->current = r;
	new_l->next = *l;
	*l = new_l;
}


void remove(rect_list **l, rect *r)
{
	rect_list *prev = NULL;
	rect_list *l_p = *l;
	
	while (l_p) {
		if (l_p->current == r) {
			rect_list *to_free;
			if (prev) {
				to_free = prev->next;
				prev->next = l_p->next;
			} else {
				to_free = *l;
				*l = (*l)->next;
			}
			free(to_free);
		}
		prev = l_p;
		l_p = l_p->next;
	}
}


void split_rect_vertically(rect_list **l, rect *r, point *p)
{
	remove(l, r);
	
	v_line *new_line = make_v_line(make_point(p->x, r->top->start->y),
	                                r->bottom->start->y - r->top->start->y);
	rect *left_rect = make_rect(r->top, r->bottom, r->left, new_line);
	rect *right_rect = make_rect(r->top, r->bottom, new_line, r->right);
	append(l, left_rect);
	append(l, right_rect);
	free(r);
}


void split_rect_horizontally(rect_list **l, rect *r, point *p)
{
	remove(l, r);
	
	h_line *new_line = make_h_line(make_point(r->left->start->x, p->y),
	                                r->right->start->x - r->left->start->x);
	rect *top_rect = make_rect(r->top, new_line, r->left, r->right);
	rect *right_rect = make_rect(new_line, r->bottom, r->left, r->right);
	append(l, top_rect);
	append(l, right_rect);
	free(r);
}


rect *find_rect_above(h_line *x, rect_list *l)
{
	while (l->next && l->current->bottom != x) l = l->next;
	return l->current;
}

