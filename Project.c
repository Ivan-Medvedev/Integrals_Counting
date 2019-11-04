#include <stdio.h>
#include <string.h>
#include <math.h>

int iterations [5];

double f_example_1 (double x) {
    return (x - 2) * (x + 3);
}

double f_example_2 (double x) {
    return pow (2.718281828, x);
}

double f_example_3 (double x) {
    return sin(x);
}

double f_example_1_diff (double x) {
    return 2 * x + 1;
}

double f_example_3_diff (double x) {
    return cos(x);
}

double f_0 (double x) {
    return 0;
}

double f_1 (double x) {
    return 1;
}

double f1 (double x);
double f2 (double x) ;

double f3 (double x) ;


double f1_diff (double x);

double f2_diff (double x);

double f3_diff (double x);

double absdd (double a) {
    return a > 0 ? a : -a;
}

#ifdef NEWTON
double root(double (*f) (double x), double (*g) (double x), double a, double b,
            double eps1, double (*f_diff) (double x), double (*g_diff) (double x), int i) {
    int inc = 0, convex = 1, event = 2;
    if (f(a) - g(a) < 0)
        inc = 1;
    if (f((a + b) / 2) - g((a + b) / 2) > (f(a) - g(a) + f(b) - g(b)) / 2)
        convex = 0;
    if (inc == convex)
        event = 1;

    if (event == 1) {
        double c = b;
        while ((f(c - eps1) - g(c - eps1)) * (f(c) - g(c)) > 0) {
            iterations[i]++;
            c = c - (f(c) - g(c)) / (f_diff(c) - g_diff(c));
        }
        return c;
    }
    double c = a;
    while ((f(c + eps1) - g(c + eps1)) * (f(c) - g(c)) > 0) {
        iterations[i]++;
        c = c - (f(c) - g(c)) / (f_diff(c) - g_diff(c));
    }
    return c;
}
#else
double root(double (*f) (double x), double (*g) (double x), double a, double b, double eps1,
            double (*f_diff) (double x), double (*g_diff) (double x), int i) {
    double c;
    do{
        iterations[i]++;
        c = (a + b) / 2;
        if ((f (a) - g (a)) * (f (c) - g (c)) > 0)
            a = c;
        else
            b = c;
    } while (b - a > eps1);
    return a;
}
#endif
double integral(double (*f) (double x), double a, double b, double eps2) {
    double I2, I1;
    int d = 20;
    double I = 0, h = (b - a) / d;
    for (int i = 0; i <= d; i++)
        I += f(a + i * h);
    I -= f(a) / 2 + f(a + d * h) / 2;
    I *= h;
    d <<= 1;
    I2 = I;
    do {
        I /= h;
        h = (b - a) / d;
        for (int i = 0; i <= d >> 1; i++)
            I += f(a + h + i * h * 2);
        I *= h;
        d <<= 1;
        I1 = I2;
        I2 = I;
    } while (absdd(I1 - I2) > eps2);
    return I2;
}

// for f1, f3 [a, b] = [-1.4, -1]
// for f2, f3 [a, b] = [0.5, 1]
// for f1, f2 [a, b] = [1, 2]
// x1 = -1.307849
// x2 = 0.826774
// x3 = 1.343727

int main (void) {
    double x1 = root (f1, f3, -1.4, -1.1, 0.00001, f1_diff, f3_diff, 1),
           x2 = root (f2, f3, 0.5, 1.0, 0.00001, f2_diff, f3_diff, 2),
           x3 = root (f1, f2, 1.0, 2.0, 0.00001, f1_diff, f2_diff, 3);

    char command[16];
    double integr = integral(f1, x1, x3, 0.00001) - integral(f2, x2, x3, 0.00001) - integral(f3, x1, x2, 0.00001);
    printf ("Write your command. For full list of commands write -help.\n");
    do {
        scanf ("%s", command);
        if (strcmp (command, "-help") == 0) {
            printf("-square - square of area\n-x1 - the first root\n-x2 - the second root\n-x3 - the third root\n"
                "-rtit_i - amount of iterations in i root searching\n-test_i - integral and root testing (3 functions)\n-exit - close program\n\n");
            continue;
        }
        if (strcmp (command, "-square") == 0) {
            printf ("Square = %lf\n", integr);
            continue;
        }
        if (strcmp (command, "-x1") == 0) {
            printf ("x1 = %lf: f1, f3\n", x1);
            continue;
        }
        if (strcmp (command, "-x2") == 0) {
            printf ("x2 = %lf: f2, f3\n", x2);
            continue;
        }
        if (strcmp (command, "-x3") == 0) {
            printf ("x3 = %lf: f1, f2\n", x3);
            continue;
        }
        if (strcmp (command, "-rtit_1") == 0) {
            printf ("Iterations in searching of 1 root = %d\n", iterations[1]);
            continue;
        }
        if (strcmp (command, "-rtit_2") == 0) {
            printf ("Iterations in searching of 2 root = %d\n", iterations[2]);
            continue;
        }
        if (strcmp (command, "-rtit_3") == 0) {
            printf ("Iterations in searching of 3 root = %d\n", iterations[3]);
            continue;
        }
        if (strcmp (command, "-test_1") == 0) {
            printf ("Function for testing: f(x) = (x - 2) * (x + 3)\nRoot in range [-4, -2] = %lf\nIntegral in range [-4, -2] = %lf\n",
                    root (f_example_1, f_0, -4, -2, 0.00001, f_example_1_diff, f_0, 4), integral (f_example_1, -4, -2, 0.00001));
            continue;
        }
        if (strcmp (command, "-test_2") == 0) {
            printf ("Function for testing: f(x) = e^x\nRoot in range [-4, 4] = %lf\nIntegral in range [0, 1] = %lf\n",
                    root (f_example_2, f_1, -4, 4, 0.00001, f_example_2, f_0, 4), integral (f_example_2, 0, 1, 0.00001));
            continue;
        }
        if (strcmp (command, "-test_3") == 0) {
            printf ("Function for testing: f(x) = sin(x)\nRoot in range [3, 4] = %lf\nIntegral in range [-pi, pi] = %lf\n",
                    root (f_example_3, f_0, 3.0, 4.0, 0.00001, f_example_3_diff, f_0, 4), integral (f_example_3, -M_PI, M_PI, 0.00001));
            continue;
        }
        if (strcmp (command, "-exit") != 0)
            printf ("This command doesn't exist\n");
    } while (strcmp (command, "-exit") != 0);

    return 0;
}
