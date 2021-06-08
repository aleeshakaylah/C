#include <getopt.h>
#include <math.h>
#include <stdio.h>
//#define PI 3.141592653589793238;
#define OPTIONS "sctea"

// Sine FunctionP
double Sin(double x){
    // x squared to assist with Horner normal form
    double x2 = x * x;
    // numerator
  double n = x * ((x2*(52785432 - 479249 * x2) - 1640635920) * x2 + 11511339840);
  // denominator
    double d = ((18361 * x2 + 3177720) * x2 + 277920720) * x2 + 11511339840;
    return (n/d);
}

// Cosine Function
double Cos(double x){
    // x squared to assist with Horner normal form
    double x2 = x * x;
    // numerator
  double n = (x2 * (1075032 - (14615 * x2)) - 18471600) * x2 + 39251520;
  // denominator
    double d = ((127 * x2 + 16632) * x2 + 1154160) * x2 + 39251520;
    return (n/d);
}

// Tangent Function
double Tan(double x){
    //x squared to assist with Horner normal form
    double x2 = x * x;
    // numerator
  double n = x * (x2 * (x2 * (x2 * (x2 - 990) + 135135) - 4729725) + 34459425);
  // denominator
    double d = 45 * (x2 * (x2 * (x2 * (x2 - 308) + 21021) - 360360) + 765765);
    return (n/d);
}


double term(double x, int n)
{
    double ret = 1.0;
    for (int i = 1; i <= n; i++)
    {
        ret = (x / i)*ret;
    }
    return ret;
}

double Exp(double x)
{
    double epsilon = 0.000000001;
    double termVal = 1.0;
    int n = 0;
    double total = 1.0;

    while (termVal > epsilon)
    {
        n = n + 1;
        termVal = term(x, n);
        total = total + termVal;
    }
    return total;
}

/* void usage()
{
    printf ("USAGE: ./main -<options>\n");
    printf ("       <options>  [s,c,t,e,a] \n");
    printf ("       e.g. ./main -s \n");
    printf ("            ./main -sc \n");
    printf ("            ./main -s -c \n");
}
*/

int main(int argc, char **argv) {
    int c = 0;
    double pi = M_PI;
    double step_sct = (pi/16);
    double step_exp = 0.1;

/*  if (argc != 0)
  {
     usage();
  } */
    while ((c = getopt(argc, argv, OPTIONS)) != -1){
        double x, new_val, actual_val;

        switch(c){
            case 's':
                printf("x\tSin\t\tLibrary\t\tDifference\n");
                printf("-\t---\t\t-------\t\t----------\n");

              for (x = -2 * pi; x <= 2 * pi; x = x + step_sct){
                  new_val = Sin(x);
                  actual_val = sin(x);

                    printf("%6.4lf\t%10.8lf\t%10.8lf\t%12.10lf\n", x, new_val, actual_val, (new_val - actual_val));
                }
                break;

            case 'c':
                printf("x\tCos\t\tLibrary\t\tDifference\n");
                printf("-\t---\t\t-------\t\t----------\n");

              for (x = -2 * pi; x <= 2 * pi; x = x + step_sct){
                new_val = Cos(x);
                actual_val = cos(x);

                    printf("%6.4lf\t%10.8lf\t%10.8lf\t%12.10lf\n", x, new_val, actual_val, (new_val - actual_val));
                }
                break;

            case 't':
                printf("x\tTan\t\tLibrary\t\tDifference\n");
                printf("-\t---\t\t-------\t\t----------\n");

              for (x = pi / -3; x <= pi / 3; x = x + step_sct){
                new_val = Tan(x);
                actual_val = tan(x);

                    printf("%6.4lf\t%10.8lf\t%10.8lf\t%12.10lf\n", x, new_val, actual_val, (new_val - actual_val));
                }
                break;

            case 'e':
                printf("x\tExp\t\tLibrary\t\tDifference\n");
                printf("-\t---\t\t-------\t\t----------\n");

              for (x = 0; x <= 9; x = x + step_exp){
                new_val = Exp(x);
                actual_val = exp(x);

                    printf("%6.4lf\t%10.8lf\t%10.8lf\t%12.10lf\n", x, new_val, actual_val, (new_val - actual_val));
                }
                break;

            case 'a':
                printf("x\tSin\t\tLibrary\t\tDifference\n");
                printf("-\t---\t\t-------\t\t----------\n");

              for (x = -2 * pi; x <= 2 * pi; x = x + step_sct){
                new_val = Sin(x);
                actual_val = sin(x);

                    printf("%6.4lf\t%10.8lf\t%10.8lf\t%12.10lf\n", x, new_val, actual_val, (new_val - actual_val));
                }
            
                printf("x\tCos\t\tLibrary\t\tDifference\n");
                printf("-\t---\t\t-------\t\t----------\n");

              for (x = -2 * pi; x <= 2 * pi; x = x + step_sct){
                new_val = Cos(x);
                actual_val = cos(x);

                    printf("%6.4lf\t%10.8lf\t%10.8lf\t%12.10lf\n", x, new_val, actual_val, (new_val - actual_val));
                }

                printf("x\tTan\t\tLibrary\t\tDifference\n");
                printf("-\t---\t\t-------\t\t----------\n");

              for (x = pi / -3; x <= pi / 3; x = x + step_sct){
                  new_val = Tan(x);
                  actual_val = tan(x);

                    printf("%6.4lf\t%10.8lf\t%10.8lf\t%12.10lf\n", x, new_val, actual_val, (new_val - actual_val));
                }

                printf("x\tExp\t\tLibrary\t\tDifference\n");
                printf("-\t---\t\t-------\t\t----------\n");

              for (x = 0; x <= 9; x = x + step_exp){
                  new_val = Exp(x);
                  actual_val = exp(x);

                    printf("%6.4lf\t%10.8lf\t%10.8lf\t%12.10lf\n", x, new_val, actual_val, (new_val - actual_val));
                }
                break;

      default :
         printf ("Incorrect arguments \n");
         break;
    }
  }
  return 0;
}

