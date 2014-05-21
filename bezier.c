#ifndef __BEZIER
#define __BEZIER

int originX(int x){
	return ((getmaxx()/2)+x);
}

int originY(int y){
	return ((getmaxy()/2)-y);
}

double Bezier(int n, int p[], double t){
	// cout << "Bezier(" << n << ", ";
	// for (int i=0; i<n; i++){
		// cout << p[i] << ", ";
	// }
	// cout << t << ");" <<endl;
	if (n==1){
		//cout << "done";
		return p[0];
	}
	else{
	int i;
	//cout << n << "--->";
	int *a = (int *) malloc ((n-1)*sizeof (int));
	int *b = (int *) malloc ((n-1)*sizeof (int));
	for (i=0; i<=n-2; i++){
		a[i] = p[i];
		//cout << a[i] << " ";
	}
	//cout << "        ";
	for (i=1; i<=n-1; i++){
		b[i-1] = p[i];
		//cout << b[i] << " ";
	}
	//cout << ">";
	int m = n-1;
	//cout << m << endl;
	double ret = ((1-t) * Bezier(m, a, t)) + (t * Bezier(m, b, t));
	return ret;
	}
}
 
void bezier (int x[], int y[], int n, int color)
{
    int i;
    double t;
 
    for (t = 0.0; t < 1.0; t += 0.0005)
    {
	/*double xt = pow (1-t, 3) * x[0] + 3 * t * pow (1-t, 2) * x[1] +
		    3 * pow (t, 2) * (1-t) * x[2] + pow (t, 3) * x[3];
 
	double yt = pow (1-t, 3) * y[0] + 3 * t * pow (1-t, 2) * y[1] +
		    3 * pow (t, 2) * (1-t) * y[2] + pow (t, 3) * y[3];*/
		double xt = Bezier(n, x, t);
		//cout << xt<< " ";
		double yt = Bezier(n, y, t);
 
		putpixel(originX((int) xt), originY((int) yt), color);
    }
 
    for (i=0; i<n; i++)
	putpixel (originX(x[i]), originY(y[i]), color);
	
    return;
}
 
#endif
