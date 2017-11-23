#ifndef _HSV_CONV_H_
#define _HSV_CONV_H_

typedef struct {
    double r;       // a fraction between 0 and 1
    double g;       // a fraction between 0 and 1
    double b;       // a fraction between 0 and 1
} rgb_dbl_t;

typedef struct {
    double h;       // angle in degrees
    double s;       // a fraction between 0 and 1
    double v;       // a fraction between 0 and 1
} hsv_dbl_t;

hsv_dbl_t   rgb2hsv(rgb_dbl_t in);
rgb_dbl_t   hsv2rgb(hsv_dbl_t in);

#endif // _HSV_CONV_H_
