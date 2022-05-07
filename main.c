#include <stdio.h>


//vypisanie parametrov
void parametersPrint(double m, double T, double H, double g, double vSoft, double dt) {
    printf("m=%.3lf\nT=%.3lf\nH=%.3lf\ng=%.3lf\nvsoft=%.3lf\ndt=%.3lf\n", m, T, H, g, vSoft, dt);
}


//vypisanie de
double dePrint (double H, double df) {
    double de = H - df;

    return de;
}


//funkcia s - vypnutie/zapnutie motora
int sFunction(double vSoft, double h, double v, double de) {
    double s;
    if (h <= de & v < vSoft) {
        s = 1;
    } else {
        s = 0;
    }

    return s;
}


//funkcia v - aktualna rychlost sondy
double vFunction(double dt, double v, double a) {
    v = v + (a * dt);

    return v;
}


//funkcia h - aktualna vyska sondy
double hFunction(double dt, double h, double v, double a) {
    h = h + (v * dt) + (a * dt * dt) / 2;

    return h;
}


//simulacia pristavania
void landingPrint(int s, double h, double t, double v) {
    printf("s=%d h=%08.3lf t=%.3lf v=%.3lf\n", s, h, t, v);
}


int main() {
    double m, T, H, g, vSoft, dt, de;
    scanf("%lf %lf %lf %lf %lf %lf", &m, &T, &H, &g, &vSoft, &dt);
    parametersPrint(m, T, H, g, vSoft, dt);

    double A, df;
    A = T / m;
    df = ((A - g) * H) / A;
    de = dePrint(H, df);
    printf("de=%.3lf\n", de);

    double s, v, h, t, a;
    s = 0;
    v = 0;
    h = H;
    t = 0;
    a = -g;
    landingPrint(s, h, t, v);
    int total = 0;
    int max0 = 0;
    int max = 0;

    while(h > 0) {
        t += dt;
        h = hFunction(dt, h, v, a);
        v = vFunction(dt, v, a);
        s = sFunction(vSoft, h, v, de);
        if (s == 0) {
            a = -g;
            if (total > 2) {
                max0 = 1;
            }
        } else if (s == 1) {
            a = A - g;
            total++;
            if (max0 == 0) {
                max++;
            }
        }

        if (h > 0) {
            landingPrint(s, h, t, v);
        }
    }

    printf("---Landed---\n");
    printf("h    =%08.3lf\nt    =%8.3lf\nv    =%8.3lf\ntotal=%4d\nmax  =%4d", h, t, v, total, max);

    return 0;
}