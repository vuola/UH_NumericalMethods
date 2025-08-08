#include <iostream>
#include <fstream>
#include <cmath>
#include <numbers>
#include <gsl/gsl_multimin.h>
#include <gsl/gsl_errno.h>
using namespace std;


/* Parameters of function f */
double p[7] = { 2.0, -4.0, 7.0, 3.0, 2.0, 5.0, -8.0 };

/* Hard-coded function f for exercise 8 problem 5 */
double f(double x, double y)
{
  return p[2] * exp(-pow(x - p[0], 2)) +
         p[3] * pow(x, 2) +
         p[4] * x * y +
         p[5] * pow(y, 2) -
         p[6] * exp(-pow(y - p[1], 2));
}

/* The function to be minimized, f(x,y) in GSL format*/
double ex5_f (const gsl_vector *v, void *params)
{
  double x, y;
  double *p = (double *)params;

  x = gsl_vector_get(v, 0);
  y = gsl_vector_get(v, 1);

  return f(x, y);
}

/* The gradient of f, df = (df/dx, df/dy). */
void ex5_df (const gsl_vector *v, void *params,
       gsl_vector *df)
{
  double x, y;
  double *p = (double *)params;

  x = gsl_vector_get(v, 0);
  y = gsl_vector_get(v, 1);

  gsl_vector_set(df, 0, -2.0 * p[2] * (x - p[0]) * exp(-pow(x - p[0], 2)) +
                   2.0 * p[3] * x +
                   p[4] * y);
  gsl_vector_set(df, 1, 2.0 * p[5] * y -
                   2.0 * p[6] * (y - p[1]) * exp(-pow(y - p[1], 2)) +
                   p[4] * x);
}

/* Compute both f and df together. */
void ex5_fdf (const gsl_vector *x, void *params,
        double *f, gsl_vector *df)
{
  *f = ex5_f(x, params);
  ex5_df(x, params, df);
}

/* Generic gradient descent minimization algorithm */
int gradient (double x0, double y0, const gsl_multimin_fdfminimizer_type *T)
{
  size_t iter = 0;
  int status;

  // Type of minimization algorithm
  // const gsl_multimin_fdfminimizer_type *T;

  // Workspace for minimization
  gsl_multimin_fdfminimizer *s;

  // n-dimensional position vector for the minimization
  gsl_vector *x;

  // Generic structural form of the function to be minimized
  gsl_multimin_function_fdf my_func;

  my_func.n = 2;
  my_func.f = ex5_f;
  my_func.df = ex5_df;
  my_func.fdf = ex5_fdf;
  my_func.params = p;

  /* Starting point, x = (5,7) */
  x = gsl_vector_alloc (2);
  gsl_vector_set (x, 0, x0);
  gsl_vector_set (x, 1, y0);

  // Allocate the minimizer workspace
  s = gsl_multimin_fdfminimizer_alloc (T, 2);

  // Initialize the minimizer with the function, initial point, step size, and tolerance
  gsl_multimin_fdfminimizer_set (s, &my_func, x, 0.01, 1e-4);

  // Delete "xy.txt" if it exists, ignore error if it doesn't
  remove("xy.txt");

  do
    {
      iter++;
      // Perform one iteration of the minimization algorithm
      status = gsl_multimin_fdfminimizer_iterate (s);

      if (status)
        break;

      // Check if the norm of the gradient is smaller than the given tolerance
      status = gsl_multimin_test_gradient (s->gradient, 1e-3);

      if (status == GSL_SUCCESS)
        printf ("Minimum found at:\n");

      printf ("%5zu %.5f %.5f f() = %7.3f\n", iter,
              gsl_vector_get (s->x, 0),
              gsl_vector_get (s->x, 1),
              s->f);

      // Accumulate x and y in "xy.txt" for plotting the trajectory
      ofstream xy_file("xy.txt", ios::app);
      if (xy_file.is_open()) {
          xy_file << gsl_vector_get(s->x, 0) << " "
                  << gsl_vector_get(s->x, 1) << endl;
          xy_file.close();
      }
    }
  while (status == GSL_CONTINUE && iter < 100);

  gsl_multimin_fdfminimizer_free (s);
  gsl_vector_free (x);

  return 0;
}


/* Generic simplex minimization algorithm */
int simplex(double x0, double y0, const gsl_multimin_fminimizer_type *T)
{
  size_t iter = 0;
  int status;
  double size;

  // Type of minimization algorithm
  // const gsl_multimin_fminimizer_type *T; 

  // Workspace for minimization
  gsl_multimin_fminimizer *s;

  // step size vector and initial position vector
  gsl_vector *ss, *x;

  // Generic structural form of the function to be minimized
  gsl_multimin_function minex_func;

  minex_func.n = 2;
  minex_func.f = ex5_f;
  minex_func.params = p;

  /* Starting point */
  x = gsl_vector_alloc (2);
  gsl_vector_set (x, 0, x0);
  gsl_vector_set (x, 1, y0);

  // Set the type of minimization algorithm
  T = gsl_multimin_fminimizer_nmsimplex2;

  // Allocate the minimizer workspace
  s = gsl_multimin_fminimizer_alloc (T, 2);

  /* Set initial step sizes to 1 in all directions */
  ss = gsl_vector_alloc (2);
  gsl_vector_set_all (ss, 1.0);

  // Initialize the minimizer with the function, initial point and step size
  gsl_multimin_fminimizer_set (s, &minex_func, x, ss);

  // Delete "xy.txt" if it exists, ignore error if it doesn't
  remove("xy.txt");

  do
    {
      iter++;
      status = gsl_multimin_fminimizer_iterate(s);

      if (status)
        break;

      // Test if the minimizer specific characteristic size is smaller than a given threshold
      size = gsl_multimin_fminimizer_size (s);
      status = gsl_multimin_test_size (size, 1e-2);

      if (status == GSL_SUCCESS)
        {
          printf ("converged to minimum at\n");
        }

      printf ("%5zu %.5f %.5f f() = %7.3f size = %.3f\n",
              iter,
              gsl_vector_get (s->x, 0),
              gsl_vector_get (s->x, 1),
              s->fval, size);
              
      // Accumulate x and y in "xy.txt" for plotting the trajectory
      ofstream xy_file("xy.txt", ios::app);
      if (xy_file.is_open()) {
          xy_file << gsl_vector_get(s->x, 0) << " "
                  << gsl_vector_get(s->x, 1) << endl;
          xy_file.close();
      }

    }
  while (status == GSL_CONTINUE && iter < 100);

  gsl_vector_free(x);
  gsl_vector_free(ss);
  gsl_multimin_fminimizer_free (s);

  return status;
}

