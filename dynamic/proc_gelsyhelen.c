#include "../rpc.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

typedef struct {
    reportable_t parent;
    long unsigned int a;
    long unsigned int b;
    long unsigned int c;
    bool can_form_triangle;
    double perimeter;
    double area;
} my_struct_t;

bool can_form_triangle(long unsigned int a, long unsigned int b, long unsigned int c) {
    if (a + b > c && a + c > b && b + c > a) {
        return true;
    }
    return false;
}

void *parse_parameters(void *data) {
    const char *buf = (const char *)data;
    my_struct_t *d = malloc(sizeof(my_struct_t));
    if (d) {
        sscanf(buf, "%ld %ld %ld", &d->a, &d->b, &d->c);
    }
    return (void *)d;
}

void *do_work(void *data) {
    my_struct_t *d = (my_struct_t *)data;
    d->can_form_triangle = can_form_triangle(d->a, d->b, d->c);
    if (d->can_form_triangle) {
        d->perimeter = d->a + d->b + d->c;
        double s = d->perimeter / 2.0;
        d->area = sqrt(s * (s - d->a) * (s - d->b) * (s - d->c));
    }
    return (void *)data;
}

reportable_t *report(void *data) {
    my_struct_t *d = (my_struct_t *)data;
    d->parent.data = malloc(255 * sizeof(char));
    if (d->can_form_triangle) {
        snprintf(d->parent.data, 255, "The numbers %ld, %ld, and %ld can form a triangle with perimeter %.2f and area %.2f.\n",
                 d->a, d->b, d->c, d->perimeter, d->area);
    } else {
        snprintf(d->parent.data, 255, "The numbers %ld, %ld, and %ld cannot form a triangle.\n", d->a, d->b, d->c);
    }
    d->parent.len = strlen(d->parent.data);
    return (reportable_t *)data;
}

void clean_up(void *params, void *result, reportable_t *report) {
    if (report && report->data) {
        free(report->data);
    }
    if (params) {
        free(params);
    }
}