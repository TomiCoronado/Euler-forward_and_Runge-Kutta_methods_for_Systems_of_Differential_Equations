/*
Euler forward method vs RK2 method for Systems of Differential Equations.
Author: Tomas Coronado Gonzalez
Date: Augost 2020

IVP:    {  y1'(t) = -y2(t)
        {  y2'(t) = y1(t)
        {  y1(0) = 1
        {  y2(0) = 0

These are two explicit methods and, thus, they have a numerical 
inestability (solution -> infinity, with t -> infinity) if the step 
size is big. However, compared with implicit methods, these two are 
much easier to implement.
Runge-Kutta with two stages method (RK2) is a second-order method, while 
Euler forward method is a first-order method. For this reason, in order 
to obtain good solutions Euler forward method requires finer step sizes 
than RK2.
*/

#include<stdio.h>
#include<math.h>
#include<stdlib.h>

double f1 (double w1_fun, double w2_fun, double t_fun_w);        // y1'(t) = -y2(t) --> dy1/dt = f(y1,y2,t) = -y2(t) (ODE expressed in its normal form)
double f2 (double w1_fun, double w2_fun, double t_fun_w);        // y2'(t) = y1(t)  --> dy2/dt = f(y1,y2,t) =  y1(t) (ODE expressed in its normal form)
double f1_sol (double t_fun_sol);                                // Exact solution for y1
double f2_sol (double t_fun_sol);                                // Exact solution for y2                                                  

int main()
{
    FILE *pf;
    
    int n=1000;                                                  // Number of steps of the interval
    int j,k;
    
    double a = 0;                                                // Begining of the interval
    double b = 50;                                               // End of the interval             
    double h = (b-a)/n;                                          // Lengh of a subinterval
    
    double t[n+1];                                               // Time array
    t[0] = a;
    double y[2][n+1];                                            // Exact solution array
    y[0][0] = 1;
    y[1][0] = 0;

    // The next variables are the aproximate solution for each method:
    double w_expl[2][n+1];
    w_expl[0][0] = 1;
    w_expl[1][0] = 0;
    double w_RK2[2][n+1], k1, k2, l1, l2;
    w_RK2[0][0] = 1;
    w_RK2[1][0] = 0;

    for (j=1;j<n+1;j++)
    {
        t[j] = 0;
        
        y[0][j] = 1;
        y[1][j] = 0;
        
        w_expl[0][j] = 1;
        w_expl[1][j] = 0;
        
        w_RK2[0][j] = 1;
        w_RK2[1][j] = 0;
    }
    
    for (k=1;k<n+1;k++)              
    {
        t[k] = t[k-1] + h; 

        // Euler forward method:
        w_expl[0][k] = w_expl[0][k-1] + h*f1(w_expl[0][k-1],w_expl[1][k-1],t[k-1]);
        w_expl[1][k] = w_expl[1][k-1] + h*f2(w_expl[0][k-1],w_expl[1][k-1],t[k-1]);
        
        // Runge-Kutta with two stages (RK2):
        k1 = f1(w_RK2[0][k-1],w_RK2[1][k-1],t[k-1]);
        l1 = f2(w_RK2[0][k-1],w_RK2[1][k-1],t[k-1]);

        k2 = f1(w_RK2[0][k-1]+h*k1,w_RK2[1][k-1]+h*l1,t[k-1]);
        l2 = f2(w_RK2[0][k-1]+h*k1,w_RK2[1][k-1]+h*l1,t[k-1]);
        
        w_RK2[0][k]=w_RK2[0][k-1] + h*(0.5*k1+0.5*k2);
        w_RK2[1][k]=w_RK2[1][k-1] + h*(0.5*l1+0.5*l2);
        
        // Exact solution:
        y[0][k] = f1_sol(t[k]);
        y[1][k] = f2_sol(t[k]);

    }
    
    printf("Creating file...\n"); 

    // Open file:
    pf = fopen("output_P2.csv", "w");
    if (pf == NULL)
    {
        printf("Error: the file cannot be opened\n");
        exit(1);
    }
    else
    { 
        // Writting on the file:
        fprintf(pf, "time,w_expl_0,w_expl_1,w_RK2_0,w_RK2_1,exact_solution_0,exact_solution_1\n");
        for (j=0;j<n+1;j++)
        {
            fprintf(pf, "%f,%f,%f,%f,%f,%f,%f\n", t[j], w_expl[0][j], w_expl[1][j], w_RK2[0][j], w_RK2[1][j], y[0][j], y[1][j]);
        }
        // Close file:
        fclose(pf);
        printf("File with the solution (created and closed)\n");
    }
    if (ferror(pf))
    {
        printf("Error when creating the file\n");
        clearerr(pf);
    }
    
    return 0;
}

double f1 (double w1_fun, double w2_fun, double t_fun_w) {       // y1'(t) = -y2(t)
    double funcion_w;
    funcion_w = -w2_fun;

    return(funcion_w);
}

double f2 (double w1_fun, double w2_fun, double t_fun_w) {       // y2'(t) = y1(t)
    double funcion_w;
    funcion_w = w1_fun;

    return(funcion_w);
}

double f1_sol (double t_fun_sol) {
    double funcion_sol;
    funcion_sol = cos(t_fun_sol);

    return(funcion_sol);
}

double f2_sol (double t_fun_sol) {
    double funcion_sol;
    funcion_sol = sin(t_fun_sol);

    return(funcion_sol);
}





