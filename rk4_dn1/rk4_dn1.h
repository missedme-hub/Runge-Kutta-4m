#ifndef RK4_DN1_H
#define RK4_DN1_H

#include "linspace.h"
#include <vector>

using namespace std;
using std::vector;

vector< vector<double> > rk4_dn1( vector<double>(*dnx)(double, vector<double>),
		const double ti, const double step, const double tf, const vector<double> xi) {

	vector<double> step_t = steps(ti, step, tf); // ��ʱ��t��linspace.h��step�����ȷ�
	vector< vector<double> > xf;                 // ���

	const int n = xi.size();                     // �жϷ�����ά��

	for (size_t i=0; i != n; ++i) {              // ��Ϊn�в�����ֵ
		xf.push_back( vector<double>() );
		xf[i].push_back(xi[i]);
	}
	
	vector<double> x(n,0.0), dx(n,0.0), k1(n,0.0), k2(n,0.0), k3(n,0.0), k4(n,0.0), step_xf(n,0.0); // ��ʼ��
	step_xf=xi;

	for (size_t i=0; i+1 != step_t.size(); ++i) {             // step_xf���м�ֵ���xf
		
		// k1
		dx = dnx(step_t[i], step_xf);
		for (size_t j=0; j != n; ++j) {
			k1[j] = step*dx[j];
			x[j] = step_xf[j] + k1[j]/2.0;
		}

		// k2
		dx = dnx(step_t[i]+step/2.0, x);
		for (size_t j = 0; j != n; ++j) {
			k2[j] = step*dx[j];
			x[j] = step_xf[j] + k2[j]/2.0;
		}

		// k3
		dx = dnx(step_t[i]+step/2.0, x);
		for (size_t j = 0; j != n; ++j) {
			k3[j] = step*dx[j];
			x[j] = step_xf[j] + k3[j];
		}

		// k4 and result
		dx = dnx(step_t[i]+step, x);
		for (size_t j = 0; j != n; ++j) {
			k4[j] = step*dx[j];
		}

		// result
		for (size_t j = 0; j != n; ++j) {
			step_xf[j] += k1[j]/6.0+k2[j]/3.0+k3[j]/3.0+k4[j]/6.0;
			xf[j].push_back(step_xf[j]);
		}

	}

	return xf;

}

#endif
