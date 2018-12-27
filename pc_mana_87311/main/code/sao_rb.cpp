//==================== SAO - Mana ======================//
//											     		//
//				Code writen by Diogo Ribeiro			//
//					 MEFT(IST) n. 87311		     		//
//					    June 2018   					//
//														//
//======================================================//
//	This is the code to implement the Simple anharmonic
// oscilator and generate its pointcaré map. It is used 
// to study the relation of the nonlinear terms and the 
// chaotic behaviour observed.
//======================================================//
//	To get the report explaining the implemntation and 
//	studying the problem, please send an email to:
//		
//			diogo.c.ribeir@tecnico.ulisboa.pt
//
//	The code was writen as part of the computational
//	project for professor João Seixas and Hugo Terças
//======================================================//
//======================================================//

/*Libs*/
#include <iostream>	//input output library
#include <fstream>	//file inout put
#include <numeric>	//some c++ algorithms
#include <cmath>	//Mathematical functions
#include <vector>	//C++ vector library
#include <time.h>   //clock_t, clock, CLOCKS_PER_SEC

#include <boost/numeric/odeint.hpp>	//Odeint library

#ifndef M_PI 
#define M_PI 3.1415927 
#endif

using namespace std;
using namespace boost::numeric::odeint;

/*Vector structure auxiliary*/
typedef vector< double > container;

/* FPU ODE's system*/
struct fpu_system
{
	//Potential coefficients
	const double alfa , beta ;
	
	//Initializer
	fpu_system(const double i_alfa = 0 , const double i_beta = 0) :  alfa(i_alfa) , beta(i_beta) {}
	
	//Ode's systems
	void operator() (const container &q , container &dpdt ) const
	{
		//Variables
		size_t n = q.size();
		double ds;	
		double p_dot;
		
		//Equation of motion
		ds = q[0];		//Spring displacement
		dpdt[0] = -( ds + alfa*ds*ds + beta*ds*ds*ds);
	}
};

/*Observer function and file writer*/
struct observer
{
	std::ofstream& m_file1;
	const fpu_system &m_fpu;
	size_t m_write_every;
	size_t m_count;
	
	//Constructor
	observer( std::ofstream &file1 , const fpu_system &f , size_t write_every = 100 )
	: m_file1(file1) ,  m_fpu( f ) , m_write_every( write_every ) , m_count( 0 ) {}
	
	//Write operator - is called every time
	template< class State>
	void operator()(const State &x , double t)
	{
		if( (m_count % m_write_every) == 0 )
		{
			container &q = x.first;
			container &p = x.second;
			
			m_file1 << t << '\t' << q[0] << '\t' << p[0] << '\n' ;
		}
		++m_count;
	}
};

/*Main functions*/
int main( int argc , char** argv)
{
	/*Files to write*/
	std::ofstream f1;
	f1.open("data/pointcare_map.txt");
	
	/*Timer variables*/
	clock_t t;
	t = clock();
	
	/*Set up problem dimentions*/
	container q(1 , 0.0) , p(1 , 0.0);
	
	/*time discretization*/
	const double dt = 0.01;

	/*Diferential method to solve ODE*/
	typedef symplectic_rkn_sb3a_mclachlan< container> stepper_type;
	
	/*Iteration Cycle to generate pointcaré map*/
	
	double dp  = 0.2 , dq = 0.2;		//Position and momenta diferential
	double alfa = 1.4 , beta = 0.3;		//Problem Parameters

	for(int j = 0 ; j < 300 ; j++)
	{
		for(int i = 0 ; i < 200 ; i++)
		{
			q[0] = -6.2 + j*dp;
			p[0] = -3.2 + i*dp;	
			
			/*System ode's*/
			fpu_system fpu_instance(alfa, beta);
			
			integrate_const ( stepper_type() , fpu_instance , 
						  make_pair( boost::ref( q ) , boost::ref( p ) ) ,
						  0.0 , 1.5 , dt , observer( f1 , fpu_instance , 10 ) );
			f1 << "\n \n";			
		}
	}

	/*Close files*/
	f1.close();

	/*Finish timer*/
	t = clock() - t;
	printf(" Time of simulation: %f \n" , ((float)t)/CLOCKS_PER_SEC);
	
	return 0;
}















