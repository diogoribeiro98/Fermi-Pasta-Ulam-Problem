//================= FUP Problem  - Mana ================//
//											     		//
//				Code writen by Diogo Ribeiro			//
//					 MEFT(IST) n. 87311		     		//
//					    June 2018   					//
//														//
//======================================================//
//	This is the code to implement the Fermi-Pasta-Ulam
//	using the odeint library. It is based on the code
//	by Karsten Ahnert and Mario Mulansky presented in	
//	the odeint online documentation.
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

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <boost/numeric/odeint.hpp>	//Odeint library

#ifndef M_PI 
#define M_PI 3.1415927 
#endif

using namespace std;
using namespace boost::numeric::odeint;

/*Vector structure auxiliary*/
typedef vector< double > container;

// Odeint has a very specific way to work with ODE's.
// We first must define the system of linear equations
// this is done with the help of a structure:

/* FPU ODE's system*/

struct fpu_system
{
	//Potential coefficients
	const double k , alfa , beta ;
	const bool asteroids;
	
	//Initializer
	fpu_system(const double i_k = 1 , const double i_alfa = 0 , const double i_beta = 0 , bool i_asteroids = true) 
	:  k(i_k) , alfa(i_alfa) , beta(i_beta) , asteroids(i_asteroids){}
	
	//Ode's systems
	void operator() (const container &q , container &dpdt) const
	{
		//Variables
		size_t n = q.size();
		double ds;	
		double p_dot;
	
		//This first part make the ends of the string fixed
		//while the second one make the ends equal - just like
		//in an asteroids game(!!!)
	
		//First mass equation
		if(asteroids)
			ds = q[0]-q[n-1];		//1st spring displacement
		else
			ds = q[0]-0.0;
			
		dpdt[0] = -( ds + alfa*ds*ds + beta*ds*ds*ds);
		
		//Inner masses
		for( size_t i = 0 ; i < n-1 ; ++i)
		{
			ds = q[i+1] - q[i];
			p_dot = ( ds + alfa*ds*ds + beta*ds*ds*ds);
			dpdt[i] += p_dot;
			dpdt[i+1] = -p_dot;
		}
		
		//Last mass
		if(asteroids)
			ds = q[0]-q[n-1];		//1st spring displacement
		else
			ds = -q[n-1];
			
		dpdt[n-1] += ( ds + alfa*ds*ds + beta*ds*ds*ds);
	}
	
	//Fourier analysis
	void mode_energy( const container &q , const container &p , container &e ) const
    {
		size_t k = e.size();
		size_t n = q.size();
		for(int i=1 ; i < k+1 ; i++)
		{
			double ak = 0;
			double ak_dot = 0;
			e[i-1] = 0;
			for(int j=0 ; j < n; j++)
			{
				ak += q[j]*sin( M_PI * double( i )*j / double( n) );
				ak_dot += p[j]*sin( M_PI * double( i )*j / double( n) );
			}		
			e[i-1] += 0.5*ak_dot + 2*ak*ak*sin(M_PI*i/n)*sin(M_PI*i/n);
		}	
	}	
};

//Now that the ode's structure is constructed we need
//to create the function that shall be called to write
//the data to a file at regular intervals. Again, this 
//is, for convenience a structure ususally called 'Observer'

struct observer
{
	std::ofstream& m_file1;
	std::ofstream& m_file2;
	const fpu_system &m_fpu;
	size_t m_write_every;
	size_t m_count;
	size_t m_k;
	
	//Constructor
	observer( std::ofstream &file1 , std::ofstream &file2 , const fpu_system &f , size_t write_every = 100 , size_t k = 5)
	: m_file1(file1) , m_file2(file2) ,  m_fpu( f ) , m_write_every( write_every ) , m_k(k+1) , m_count( 0 ) {}
	
	//Write operator - is called every time
	template< class State>
	void operator()(const State &x , double t)
	{
		if( (m_count % m_write_every) == 0 )
		{
			container &q = x.first;
			container &p = x.second;
			container energy(m_k, 0.0);
			
			//Calculate mode energies
			m_fpu.mode_energy( q , p , energy);
			
			//Printing first fixed point
			m_file1 << t << '\t' << 0 << '\t' << 0 << '\t' << 0 << '\n' ;
			
			//Printing all points
			for( size_t i = 0 ; i < q.size() ; ++i)
			{
				m_file1 << t << '\t' << i+1 << '\t' << q[i] << '\t' << p[i] << '\n' ;
			}
			
			//Printing last fized point
			m_file1 << t << '\t' << q.size()+1 << '\t' << 0 << '\t' << 0 << "\n \n \n";
						
			//Print energy modes to second file
			m_file2 << t << '\t' ;

			for(size_t j = 0; j < m_k ; ++j)
			{
				m_file2 << '\t' <<  energy[j] ; 
			}
			m_file2 << '\n' ;	
		}
		++m_count;
	}
};

//We define some usefull auxiliary functions to 
//set up the initial conditions:

void set_normal_mode( container &q , int n , int k , double amp )
{	
	/*Initial conditions*/
	for(size_t i = 0 ; i < n; ++i )
	{
		q[i] = amp*sin( double( i + 1 )*k / double( n + 1) *M_PI );
	}
}

void add_normal_mode(container &q , int n , int k , double amp )
{	
	/*Initial conditions*/
	for(size_t i = 0 ; i < n; ++i )
	{
		q[i] += amp*sin( double( i + 1 )*k / double( n+1 ) *M_PI );
	}
}

void set_gaussian( container &q , int n , double a , double b , double m)
{	
	/*Initial conditions*/
	double c = m/8;
	for(size_t i = 0 ; i < n; ++i )
	{
		q[i] = a*exp( - (i - b)*(i - b)/(2*c*c) );
	}
}

void set_travelling_wave( container &q , container &p ,  int n ,int k, double amp , int i0 )
{	
	/*Initial conditions*/
	for(size_t i = i0 ; i < n+i0; ++i )
	{
		q[i] = amp*sin( double( (i-i0) + 1 )*k / double( n+1 ) *M_PI );
		p[i] = -amp*cos( double( (i-i0) + 1 )*k / double( n+1 ) *M_PI )*M_PI*k/ double(n+1)   ;
	}
}

void set_travelling_gaussian( container &q , container &p , int n , double a , double b , double m )
{
	/*Initial conditions*/
	double c = m/8;
	for(size_t i = 0 ; i < n; ++i )
	{
		q[i] = a*exp( - (i - b)*(i - b)/(2*c*c) );
		p[i] = a*exp( - (i - b)*(i - b)/(2*c*c) )*( i - b)/(c*c);
	}
}

void set_random_p(container &p , int n )
{
	/*Initial conditions*/
	for(size_t i = 0 ; i < n; ++i )
	{
		srand((unsigned)time(NULL)); 
		p[i] = rand()/(RAND_MAX + 1.0)-0.5;	
	}
}

//For the graphical representation the gnuplot script that
//goes along this code is to be used. With that in mind the
//is all stored in a single file in blocks (set of data separated
//by two empty lines) each one corresponding to a single time

int main( int argc , char** argv)
{
	/*Files to write*/
	std::ofstream f1;
	f1.open("data/pos_data.txt");
	std::ofstream f2;
	f2.open("data/ene_data.txt");
	
	/*Timer variables*/
	clock_t t;
	t = clock();
	
	/*Set up problem dimentions*/
	const size_t n = 32;
	container q(n , 0.0) , p(n , 0.0);
	
	//Bellow we have the set of the initial consitions 
	//functions. In order to understand better what each
	//one does (and you dont want do look at the code above)
	//just uncomment the refering line and play with the
	//parameters.
	//note : the code is not dummy-proof!
	
	/*Initial conditions*/
	
	/*Sinusoidal wave travelling to the right*/
	//set_travelling_wave( q, p , 500 , 1 , 0.5 ,100);
	
	/*Gaussian wave travelling to the right*/
	//set_travelling_gaussian(q , p , q.size() , 1 , 200 , 200);
	
	/*Still gaussian*/
	//set_gaussian( q , q.size() , 1 , 512 , 1024);
	
	/*Normal mode -Stacionary wave*/
	set_normal_mode( q , q.size() , 1 , 1);

	/*More standing waves*/
	//add_normal_mode( q , q.size() , 3 , 0.5);
	
	/*Random mommenta*/
	//set_random_p( p , p.size());

	/*time discretization*/
	const double dt = 0.1;

	//Odint has several methods of solving Ode's. For
	//this problem the Symplectic RKN McLachlan method
	//A full list of methods ca be found on the online
	//documentation.
	//We define now the method:
	
	typedef symplectic_rkn_sb3a_mclachlan< container> stepper_type;

	/*System ode's*/
	fpu_system fpu_instance( 1.0 , 0.25, 8.25 , false );
	
	//Now we use the integration function from Odint
	//The function uses equal intervals( const )
	
	integrate_const ( stepper_type() , fpu_instance , 
					  make_pair( boost::ref( q ) , boost::ref( p ) ) ,
					  0.0 , 1000.0 , dt , observer( f1 , f2 , fpu_instance , 5 , 5) );

	/*Close files*/
	f1.close();
	f2.close();

	/*Finish timer*/
	t = clock() - t;
	printf("Time taken: %f \n" , ((float)t)/CLOCKS_PER_SEC);
	return 0;
}














