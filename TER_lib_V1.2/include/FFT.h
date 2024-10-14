#include ".\include\image.h"

template<typename T>
void directFFT(const v2_0::Image<T>& realIn, const v2_0::Image<T>& imagIn, v2_0::Image<T>& realOut, v2_0::Image<T>& imagOut);

template<typename T>
void inverseFFT(const v2_0::Image<T>& realIn, const v2_0::Image<T>& imagIn, v2_0::Image<T>& realOut, v2_0::Image<T>& imagOut);


/*************************************************************************
 *       FOURN : Fast Fourier Transform (from Numerical Recipes)         *
 *************************************************************************/
#define SWAP(a,b) tempr=(a);(a)=(b);(b)=tempr

void fourn(double* data,int* nn,int ndim,int isign)
{
	int i1,i2,i3,i2rev,i3rev,ip1,ip2,ip3,ifp1,ifp2;
	int ibit,idim,k1,k2,n,nprev,nrem,ntot;
	double tempi,tempr;
	double theta,wi,wpi,wpr,wr,wtemp;

	ntot=1;
	for (idim=1;idim<=ndim;idim++)
		ntot *= nn[idim];
	nprev=1;
	for (idim=ndim;idim>=1;idim--) {
		n=nn[idim];
		nrem=ntot/(n*nprev);
		ip1=nprev << 1;
		ip2=ip1*n;
		ip3=ip2*nrem;
		i2rev=1;
		for (i2=1;i2<=ip2;i2+=ip1) {
			if (i2 < i2rev) {
				for (i1=i2;i1<=i2+ip1-2;i1+=2) {
					for (i3=i1;i3<=ip3;i3+=ip2) {
						i3rev=i2rev+i3-i2;
						SWAP(data[i3],data[i3rev]);
						SWAP(data[i3+1],data[i3rev+1]);
					}
				}
			}
			ibit=ip2 >> 1;
			while (ibit >= ip1 && i2rev > ibit) {
				i2rev -= ibit;
				ibit >>= 1;
			}
			i2rev += ibit;
		}
		ifp1=ip1;
		while (ifp1 < ip2) {
			ifp2=ifp1 << 1;
			theta=isign*6.28318530717959/(ifp2/ip1);
			wtemp=sin(0.5*theta);
			wpr = -2.0*wtemp*wtemp;
			wpi=sin(theta);
			wr=1.0;
			wi=0.0;
			for (i3=1;i3<=ifp1;i3+=ip1) {
				for (i1=i3;i1<=i3+ip1-2;i1+=2) {
					for (i2=i1;i2<=ip3;i2+=ifp2) {
						k1=i2;
						k2=k1+ifp1;
						tempr=wr*data[k2]-wi*data[k2+1];
						tempi=wr*data[k2+1]+wi*data[k2];
						data[k2]=data[k1]-tempr;
						data[k2+1]=data[k1+1]-tempi;
						data[k1] += tempr;
						data[k1+1] += tempi;
					}
				}
				wr=(wtemp=wr)*wpr-wi*wpi+wr;
				wi=wi*wpr+wtemp*wpi+wi;
			}
			ifp1=ifp2;
		}
		nprev *= n;
	}
}

#undef SWAP


/***********************************************
 *       Direct Fast Fourier Transform         *
 ***********************************************/

template<typename T>
void directFFT(const v2_0::Image<T>& realIn, const v2_0::Image<T>& imagIn, v2_0::Image<T>& realOut, v2_0::Image<T>& imagOut)
{
	int NN[3] = { 0, realIn.getWidth(), realIn.getHeight() };
	int dim = NN[1] * NN[2], n = 2;

	double * tmp = new double[2 * dim + 1];
	
	// Real image filling
	int k = 0;
	for (int i{ 0 }; i < realIn.getWidth(); ++i)
		for (int j{ 0 }; j < realIn.getHeight(); ++j)
			tmp[++k] = realIn(i, j);

	// Imaginary image filling
	for (int i{ 0 }; i < realIn.getWidth(); ++i)
		for (int j{ 0 }; j < realIn.getHeight(); ++j)
			tmp[++k] = imagIn(i, j);

	// Direct Fourier Transform
	fourn(tmp, NN, n, 1);

	for (int j{ 0 }; j < NN[2]; ++j) 
		for (int i{ 0 }; i < NN[1]; ++i)
		{
			int ind = i + j * NN[1];
			int i0 = (i+NN[1]/2)%NN[1], j0 = (j+NN[2]/2)%NN[2];
			realOut(i0,j0) = static_cast<T>(tmp[2*ind+1]/dim);
			imagOut(i0,j0) = static_cast<T>(tmp[2*ind+2]/dim);
		}

    delete [] tmp;
}


/***********************************************
 *       Inverse Fast Fourier Transform        *
 ***********************************************/

template<typename T>
void inverseFFT(const v2_0::Image<T>& realIn, const v2_0::Image<T>& imagIn, v2_0::Image<T>& realOut, v2_0::Image<T>& imagOut)
{
	int NN[3] = { 0, realIn.getWidth(), realIn.getHeight() };
	int dim = NN[1] * NN[2], n = 2;

	double * tmp = new double[2 * dim + 1];
	
	for (int j{ 0 }; j < NN[2]; ++j) 
		for (int i{ 0 }; i < NN[1]; ++i)
		{
			int ind = i + j * NN[1];
			int i0 = (i+NN[1]/2)%NN[1], j0 = (j+NN[2]/2)%NN[2];
			tmp[2*ind+1] = realIn(i0,j0);
			tmp[2*ind+2] = imagIn(i0,j0);
		}

	// Inverse Fourier Transform
	fourn(tmp,NN,n,-1);

	// Filling of real image
	int k = 0;
	for (int i{ 0 }; i < realOut.getWidth(); ++i)
		for (int j{ 0 }; j < realOut.getHeight(); ++j)
			realOut(i, j) = static_cast<T>(tmp[++k]);

	// Filling of imaginary image
	for (int i{ 0 }; i < imagOut.getWidth(); ++i)
		for (int j{ 0 }; j < imagOut.getHeight(); ++j)
			imagOut(i, j) = static_cast<T>(tmp[++k]);

	delete [] tmp;
}
