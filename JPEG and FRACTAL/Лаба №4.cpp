#include <iostream>
#include <SFML\Graphics.hpp>
#include <math.h>
#include <map>
#include <stack>
using namespace std;
using namespace sf;
const unsigned int W = 400;
const unsigned int H = 10;

int KoeffSjatie;
int RNG = 0;
int DomainSize = 0;
int RegionSize = 0;
int X1 = 0;
int Y1 = 0;




void PrintSprite(double** R, double** G, double** B, int x, int y, RenderWindow& window,int x1,int y1) {
	Uint8* pixels = new Uint8[x * y * 4];

	for (int i = 0; i < y * 4; i += 4) {
		for (int j = 0; j < x * 4; j += 4) {
			pixels[j + i * x] = R[i / 4][j / 4];
			pixels[j + 1 + i * x] = G[i / 4][j / 4];
			pixels[j + 2 + i * x] = B[i / 4][j / 4];
		}
	}
	sf::Texture Texture; Texture.create(x, y); Texture.update(pixels);
	sf::Sprite Sprite; Sprite.setTexture(Texture);
	Sprite.setPosition(x1, y1);
	window.draw(Sprite);

}


void RGBtoYCBCR(double** R, double** G, double** B, double** Y, double** Cb, double** Cr, int x, int y) {
	for (int i = 0; i < y; i++) {
		for (int j = 0; j < x; j++) {
			Y[i][j] = 0.299 * R[i][j] + 0.5870 * G[i][j] + 0.114 * B[i][j];
			Cb[i][j] = 128-0.1687 * R[i][j] - 0.3313 * G[i][j] + 0.5 * B[i][j];
			Cr[i][j] = 128+0.5 * R[i][j] - 0.4187 * G[i][j] - 0.0813 * B[i][j];
		}
	}
}


void YCBCRtoRGB(double** Y, double** Cb, double** Cr, double** R, double** G, double** B, int x, int y, RenderWindow& window) {

	for (int i = 0; i < y; i++) {
		for (int j = 0; j < x; j++) {
			R[i][j] = max(0.0, min(255.0, (Y[i][j] + 1.402 * (Cr[i][j] - 128))));
			G[i][j] = max(0.0, min(255.0, (Y[i][j] - 0.34414 * (Cb[i][j] - 128) - 0.71414 * (Cr[i][j] - 128))));
			B[i][j] = max(0.0, min(255.0, (Y[i][j] + 1.772 * (Cb[i][j] - 128))));
		}
	}
}


void YCBCRtoRGB(double** Y, double** Cb, double** Cr,int x, int y, RenderWindow& window) {
	static double** R;
	R = new double* [8];
	for (int i = 0; i < 8; i++) {
		R[i] = new double[8];
	}
	static double** G;
	G = new double* [8];
	for (int i = 0; i < 8; i++) {
		G[i] = new double[8];
	}
	static double** B;
	B = new double* [8];
	for (int i = 0; i < 8; i++) {
		B[i] = new double[8];
	}
	for (int i = 0; i < y; i++) {
		for (int j = 0; j < x; j++) {
			R[i][j] = max(0.0, min(255.0, (Y[i][j] + 1.402 * (Cr[i][j] - 128))));
			G[i][j] = max(0.0, min(255.0, (Y[i][j] - 0.34414 * (Cb[i][j] - 128) - 0.71414 * (Cr[i][j] - 128))));
			B[i][j] = max(0.0, min(255.0, (Y[i][j] + 1.772 * (Cb[i][j] - 128))));
		}
	}
	PrintSprite(R, G, B, 8, 8, window, X1, Y1);
}


void subsampling(double** Y, double** Cb, double** Cr, int x,int y) {
	for (int i = 0; i < y; i+=2) {
		for (int j = 0; j < x; j+=2) {
			Cb[i][j + 1] = Cb[i][j];
			Cb[i + 1][j] = Cb[i][j];
			Cb[i + 1][j + 1] = Cb[i][j];
			Cr[i][j + 1] = Cr[i][j];
			Cr[i + 1][j] = Cr[i][j];
			Cr[i + 1][j + 1] = Cr[i][j];
		}
	}
}


void idct(double** M,double** dctY, double** dctCb, double** dctCr,int x, int y, RenderWindow& window) {
	static double** buff;
	buff = new double* [8];
	for (int i = 0; i < 8; i++) {
		buff[i] = new double[8];
	}
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			buff[i][j] = 0;
		}
	}

	static double** buff1;
	buff1 = new double* [8];
	for (int i = 0; i < 8; i++) {
		buff1[i] = new double[8];
	}
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			buff1[i][j] = 0;
		}
	}

	static double** buff2;
	buff2 = new double* [8];
	for (int i = 0; i < 8; i++) {
		buff2[i] = new double[8];
	}
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			buff2[i][j] = 0;
		}
	}

	static double** Y;
	Y = new double* [8];
	for (int i = 0; i < 8; i++) {
		Y[i] = new double[8];
	}
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			Y[i][j] = 0;
		}
	}
	static double** Cb;
	Cb = new double* [8];
	for (int i = 0; i < 8; i++) {
		Cb[i] = new double[8];
	}
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			Cb[i][j] = 0;
		}
	}
	static double** Cr;
	Cr = new double* [8];
	for (int i = 0; i < 8; i++) {
		Cr[i] = new double[8];
	}
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			Cr[i][j] = 0;
		}
	}

	for (int row = 0; row < 8; row++) {
		for (int col = 0; col < 8; col++) {
			for (int inner = 0; inner < 8; inner++) {
				buff[row][col] += M[inner][row] * dctY[inner][col];
				buff1[row][col] += M[inner][row] * dctCb[inner][col];
				buff2[row][col] += M[inner][row] * dctCr[inner][col];

			}
		}
	}
	for (int row = 0; row < 8; row++) {
		for (int col = 0; col < 8; col++) {
			for (int inner = 0; inner < 8; inner++) {
				Y[row][col] += buff[row][inner] * M[inner][col];
				Cb[row][col] += buff1[row][inner] * M[inner][col];
				Cr[row][col] += buff2[row][inner] * M[inner][col];

			}
		}
	}
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			Y[i][j] +=128;
			Cb[i][j] += 128;
			Cr[i][j] += 128;
		}
	}
	static double** NU;
	NU = new double* [8];
	for (int i = 0; i < 8; i++) {
		NU[i] = new double[8];
	}
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			NU[i][j] = 0;
		}
	}

	YCBCRtoRGB(Y, Cb, Cr, 8, 8, window);
	//window.display();
}


void createMmatrix(double** M) {
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (i == 0)
				M[i][j] = sqrt(1.0 / 8.0);
			else
				M[i][j] = sqrt(2.0 / 8.0) * cos(((2 * j + 1) * i * 3.14) / 16);
		}
	}
}


void RLE(double** quant1, double** quant2, double** quant3) {
	std::map<int, double> tabl;
	string code="";
	double* buf[64];
	int curr = 0;
	for (int diff = 1 - 8; diff <= 8 - 1; diff++)
	{
		for (int i = 0; i < 8; i++)
		{
			int j = i - diff;

			if (j < 0 || j >= 8)
				continue;
			buf[curr++] = quant1[j, i];
		}
	}
	int countZero = 0;
	for (int i = 0; i < 64; i++) {
		if (*buf[i] == -0 or *buf[i] == 0) {
			countZero++;
		}
		else {
			code = code + '(' + to_string(countZero) + ',' + to_string(*buf[i]) + ')' + ' ';
			countZero = 0;
		}
	}
	for (int i = 0; i < code.length(); i++) {
		cout << code[i];
	}
	cout << endl << endl;

}


void quantization(double** dct, double** dct1, double** dct2) {
	static double** buff;
	buff = new double* [8];
	for (int i = 0; i < 8; i++) {
		buff[i] = new double[8];
	}
	/*плохая*/
	/*buff[0][0] = 3; buff[0][1] = 2; buff[0][2] = 2; buff[0][3] = 3; buff[0][4] = 5; buff[0][5] = 8; buff[0][6] = 10; buff[0][7] = 12;
	buff[1][0] = 2; buff[1][1] = 2; buff[1][2] = 3; buff[1][3] = 4; buff[1][4] = 5; buff[1][5] = 12; buff[1][6] = 12; buff[1][7] = 11;
	buff[2][0] = 3; buff[2][1] = 3; buff[2][2] = 3; buff[2][3] = 5; buff[2][4] = 8; buff[2][5] = 11; buff[2][6] = 14; buff[2][7] = 11;
	buff[3][0] = 3; buff[3][1] = 3; buff[3][2] = 4; buff[3][3] = 6; buff[3][4] = 10; buff[3][5] = 17; buff[3][6] = 16; buff[3][7] = 12;
	buff[4][0] = 4; buff[4][1] = 4; buff[4][2] = 7; buff[4][3] = 11; buff[4][4] = 14; buff[4][5] = 22; buff[4][6] = 21; buff[4][7] = 15;
	buff[5][0] = 5; buff[5][1] = 7; buff[5][2] = 11; buff[5][3] = 13; buff[5][4] = 16; buff[5][5] = 12; buff[5][6] = 23; buff[5][7] = 18;
	buff[6][0] = 10; buff[6][1] = 13; buff[6][2] = 16; buff[6][3] = 17; buff[6][4] = 21; buff[6][5] = 24; buff[6][6] = 24; buff[6][7] = 21;
	buff[7][0] = 14; buff[7][1] = 18; buff[7][2] = 19; buff[7][3] = 20; buff[7][4] = 22; buff[7][5] = 20; buff[7][6] = 20; buff[7][7] = 20;*/
	buff[0][0] = 80; buff[0][1] = 60; buff[0][2] = 50; buff[0][3] = 80; buff[0][4] = 120; buff[0][5] = 200; buff[0][6] = 255; buff[0][7] = 255;
	buff[1][0] = 55; buff[1][1] = 60; buff[1][2] = 70; buff[1][3] = 95; buff[1][4] = 130; buff[1][5] = 255; buff[1][6] = 255; buff[1][7] = 255;
	buff[2][0] = 70; buff[2][1] = 65; buff[2][2] = 80; buff[2][3] = 120; buff[2][4] = 200; buff[2][5] = 255; buff[2][6] = 255; buff[2][7] = 255;
	buff[3][0] = 70; buff[3][1] = 85; buff[3][2] = 110; buff[3][3] = 145; buff[3][4] = 255; buff[3][5] = 255; buff[3][6] = 255; buff[3][7] = 255;
	buff[4][0] = 90; buff[4][1] = 110; buff[4][2] = 185; buff[4][3] = 255; buff[4][4] = 255; buff[4][5] = 255; buff[4][6] = 255; buff[4][7] = 255;
	buff[5][0] = 120; buff[5][1] = 175; buff[5][2] = 255; buff[5][3] = 255; buff[5][4] = 255; buff[5][5] = 255; buff[5][6] = 255; buff[5][7] = 255;
	buff[6][0] = 245; buff[6][1] = 255; buff[6][2] = 255; buff[6][3] = 255; buff[6][4] = 255; buff[6][5] = 255; buff[6][6] = 255; buff[6][7] = 255;
	buff[7][0] = 255; buff[7][1] = 255; buff[7][2] = 255; buff[7][3] = 255; buff[7][4] = 255; buff[7][5] = 255; buff[7][6] = 255; buff[7][7] = 255;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			buff[i][j] *= KoeffSjatie;
		}
	}

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			dct[i][j] = round(dct[i][j] / buff[i][j]);
			dct1[i][j] = round(dct1[i][j] / buff[i][j]);
			dct2[i][j] = round(dct2[i][j] / buff[i][j]);

		}
	}




}


void dequantization(double** quant, double** quant1, double** quant2) {
	static double** buff;
	buff = new double* [8];
	for (int i = 0; i < 8; i++) {
		buff[i] = new double[8];
	}
	/*хорошая*/
	/*buff[0][0] = 3; buff[0][1] = 2; buff[0][2] = 2; buff[0][3] = 3; buff[0][4] = 5; buff[0][5] = 8; buff[0][6] = 10; buff[0][7] = 12;
	buff[1][0] = 2; buff[1][1] = 2; buff[1][2] = 3; buff[1][3] = 4; buff[1][4] = 5; buff[1][5] = 12; buff[1][6] = 12; buff[1][7] = 11;
	buff[2][0] = 3; buff[2][1] = 3; buff[2][2] = 3; buff[2][3] = 5; buff[2][4] = 8; buff[2][5] = 11; buff[2][6] = 14; buff[2][7] = 11;
	buff[3][0] = 3; buff[3][1] = 3; buff[3][2] = 4; buff[3][3] = 6; buff[3][4] = 10; buff[3][5] = 17; buff[3][6] = 16; buff[3][7] = 12;
	buff[4][0] = 4; buff[4][1] = 4; buff[4][2] = 7; buff[4][3] = 11; buff[4][4] = 14; buff[4][5] = 22; buff[4][6] = 21; buff[4][7] = 15;
	buff[5][0] = 5; buff[5][1] = 7; buff[5][2] = 11; buff[5][3] = 13; buff[5][4] = 16; buff[5][5] = 12; buff[5][6] = 23; buff[5][7] = 18;
	buff[6][0] = 10; buff[6][1] = 13; buff[6][2] = 16; buff[6][3] = 17; buff[6][4] = 21; buff[6][5] = 24; buff[6][6] = 24; buff[6][7] = 21;
	buff[7][0] = 14; buff[7][1] = 18; buff[7][2] = 19; buff[7][3] = 20; buff[7][4] = 22; buff[7][5] = 20; buff[7][6] = 20; buff[7][7] = 20;*/
	buff[0][0] = 80; buff[0][1] = 60; buff[0][2] = 50; buff[0][3] = 80; buff[0][4] = 120; buff[0][5] = 200; buff[0][6] = 255; buff[0][7] = 255;
	buff[1][0] = 55; buff[1][1] = 60; buff[1][2] = 70; buff[1][3] = 95; buff[1][4] = 130; buff[1][5] = 255; buff[1][6] = 255; buff[1][7] = 255;
	buff[2][0] = 70; buff[2][1] = 65; buff[2][2] = 80; buff[2][3] = 120; buff[2][4] = 200; buff[2][5] = 255; buff[2][6] = 255; buff[2][7] = 255;
	buff[3][0] = 70; buff[3][1] = 85; buff[3][2] = 110; buff[3][3] = 145; buff[3][4] = 255; buff[3][5] = 255; buff[3][6] = 255; buff[3][7] = 255;
	buff[4][0] = 90; buff[4][1] = 110; buff[4][2] = 185; buff[4][3] = 255; buff[4][4] = 255; buff[4][5] = 255; buff[4][6] = 255; buff[4][7] = 255;
	buff[5][0] = 120; buff[5][1] = 175; buff[5][2] = 255; buff[5][3] = 255; buff[5][4] = 255; buff[5][5] = 255; buff[5][6] = 255; buff[5][7] = 255;
	buff[6][0] = 245; buff[6][1] = 255; buff[6][2] = 255; buff[6][3] = 255; buff[6][4] = 255; buff[6][5] = 255; buff[6][6] = 255; buff[6][7] = 255;
	buff[7][0] = 255; buff[7][1] = 255; buff[7][2] = 255; buff[7][3] = 255; buff[7][4] = 255; buff[7][5] = 255; buff[7][6] = 255; buff[7][7] = 255;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			buff[i][j] *= KoeffSjatie;
		}
	}



	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			quant[i][j] = quant[i][j] * buff[i][j];
			quant1[i][j] = quant1[i][j] * buff[i][j];
			quant2[i][j] = quant2[i][j] * buff[i][j];

		}
	}
}


void dct(double** Y,double** Cb,double** Cr,double** M,int x, int y, RenderWindow& window) {
	static double** buff;
	buff = new double* [8];
	for (int i = 0; i < 8; i++) {
		buff[i] = new double[8];
	}
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			buff[i][j] = 0;
		}
	}

	static double** buff1;
	buff1 = new double* [8];
	for (int i = 0; i < 8; i++) {
		buff1[i] = new double[8];
	}
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			buff1[i][j] = 0;
		}
	}

	static double** buff2;
	buff2 = new double* [8];
	for (int i = 0; i < 8; i++) {
		buff2[i] = new double[8];
	}
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			buff2[i][j] = 0;
		}
	}

	static double** T;
	T = new double* [8];
	for (int i = 0; i < 8; i++) {
		T[i] = new double[8];
	}
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			T[i][j] = 0;
		}
	}
	static double** T1;
	T1 = new double* [8];
	for (int i = 0; i < 8; i++) {
		T1[i] = new double[8];
	}
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			T1[i][j] = 0;
		}
	}

	static double** T2;
	T2 = new double* [8];
	for (int i = 0; i < 8; i++) {
		T2[i] = new double[8];
	}
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			T2[i][j] = 0;
		}
	}

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			Y[i][j] -= 128;
			Cb[i][j] -= 128;
			Cr[i][j] -= 128;

		}
	}

	for (int row = 0; row < 8; row++) {
		for (int col = 0; col < 8; col++) {
			for (int inner = 0; inner < 8; inner++) {
				buff[row][col] += M[row][inner] * Y[inner][col];
				buff1[row][col] += M[row][inner] * Cb[inner][col];
				buff2[row][col] += M[row][inner] * Cr[inner][col];

			}
		}
	}
	for (int row = 0; row < 8; row++) {
		for (int col = 0; col < 8; col++) {
			for (int inner = 0; inner < 8; inner++) {
				T[row][col] += buff[row][inner] * M[col][inner];
				T1[row][col] += buff1[row][inner] * M[col][inner];
				T2[row][col] += buff2[row][inner] * M[col][inner];

			}
		}
	}

	quantization(T,T1,T2);
	//RLE(T, T1, T2);
	dequantization(T,T1,T2);
	idct(M,T,T1,T2, 8, 8, window);

}


void rot90(double** urot,int N) {
	for (int i = 0; i < N / 2; i++) {
		for (int j = i; j < N - i - 1; j++) {
			int temp = urot[i][j];
			urot[i][j] = urot[N - 1 - j][i];
			urot[N - 1 - j][i] = urot[N - 1 - i][N - 1 - j];
			urot[N - 1 - i][N - 1 - j] = urot[j][N - 1 - i];
			urot[j][N - 1 - i] = temp;
		}
	}
}


void gorizSwap(double** urot,int N)
{

	/*int row = 0;

	
	for (int j = 0; j < n; j++) {

		stack<int> s;
		int i = row, k = j;
		while (i < n && k >= 0)
			s.push(urot[i++][k--]);

		
		i = row, k = j;
		while (i < n && k >= 0) {
			urot[i++][k--] = s.top();
			s.pop();
		}
	}

	int column = n - 1;
	for (int j = 1; j < n; j++) {

		stack<int> s;
		int i = j, k = column;
		while (i < n && k >= 0)
			s.push(urot[i++][k--]);


		i = j;
		k = column;
		while (i < n && k >= 0) {
			urot[i++][k--] = s.top();
			s.pop();
		}
	}*/

	int t, m = N / 2;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < m; ++j) {
			t = urot[i][j];
			urot[i][j] = urot[i][N - 1 - j];
			urot[i][N - 1 - j] = t;
		}
	}

}


void matrixcomp(double** buff,double** comp) {
	
	int p = 0; int l = 0;
	for (int i = 0; i < RegionSize; i++) {
		for (int j = 0; j < RegionSize; j++) {
			buff[i][j] = (comp[l][p] + comp[l + 1][p + 1] + comp[l + 1][p] + comp[l][p + 1]) / 4;
			p += 2;
		}
		p = 0; l += 2;
	}

}


double sumRD(double** region, double** domain) {
	double sum = 0;
	for (int i = 0; i < RegionSize; i++) {
		for (int j = 0; j < RegionSize; j++) {
			sum += region[i][j] * domain[i][j];
		}
	}
	return sum;
}


double sumR(double** region) {
	double sum = 0;
	for (int i = 0; i < RegionSize; i++) {
		for (int j = 0; j < RegionSize; j++) {
			sum += region[i][j];
		}
	}
	return sum;
}


double sumR2(double** region) {
	double sum = 0;
	for (int i = 0; i < RegionSize; i++) {
		for (int j = 0; j < RegionSize; j++) {
			sum += region[i][j]* region[i][j];
		}
	}
	return sum;
}


double sumD(double** domain) {
	double sum = 0;
	for (int i = 0; i < RegionSize; i++) {
		for (int j = 0; j < RegionSize; j++) {
			sum += domain[i][j];
		}
	}
	return sum;
}


double sumD2(double** domain) {
	double sum = 0;
	for (int i = 0; i < RegionSize; i++) {
		for (int j = 0; j < RegionSize; j++) {
			sum += domain[i][j]*domain[i][j];
		}
	}
	return sum;
}


double koeffcontr(double** region, double** domain) {
	double contr = 0;
	double sumDD = sumD(domain);
	contr = (DomainSize * (sumRD(region,domain))-sumR(region)*sumDD)/(DomainSize*sumD2(domain)-pow(sumDD,2));
	return contr;
}


double koeffbright(double** region, double** domain) {
	double contr = 0;
	contr = 1.0/RegionSize*(sumR(region) - koeffcontr(region, domain)*sumD(domain));
	return contr;
}


double findQ(double** region, double** domain, double sigma, double s) {
	double Q = 0;
	for (int i = 0; i < RegionSize; i++) {
		for (int j = 0; j < RegionSize; j++) {
			Q += pow(((sigma * domain[i][j] + s) - region[i][j]),2);
		}
	}
	return Q;
}


double minQ(double** region, double** domain,double Q,double** preobM,int dx,int dy, int rx,int countRot,int countZerk,double sigma,double s) {
	double mimiQ = findQ(region, domain,sigma,s);
	if (mimiQ < Q) {
		Q = mimiQ;
		preobM[rx][0] = Q;
		preobM[rx][1] = dx;
		preobM[rx][2] = dy;
		preobM[rx][3] = countZerk;
		preobM[rx][4] = countRot;
		preobM[rx][5] = sigma;
		preobM[rx][6] = s;
	}
	return Q;
}


void findminQ(double** region, double** domain,double miniQ, double** preobM, int dx, int dy, int rx) {
	/*if (minQ(region, domain, miniQ, preobM, dx, dy, rx, 0, 0, koeffbright(region, domain), koeffcontr(region, domain)) >=preobM[rx][0]) {
		return;
	}*/
	for (int i = 0; i < 4; i++) {
		rot90(domain, RegionSize);
		miniQ = minQ(region, domain, miniQ, preobM, dx, dy, rx, i, 0, koeffbright(region, domain), koeffcontr(region, domain));
	}
	gorizSwap(domain, RegionSize);
	for (int i = 0; i < 4; i++) {
		rot90(domain, RegionSize);
		miniQ = minQ(region, domain, miniQ, preobM, dx, dy, rx, i, 1, koeffbright(region, domain), koeffcontr(region, domain));
	}
	cout << miniQ << endl;
}


int main()
{
	sf::RenderWindow window(sf::VideoMode(1300, 1100), "Picture"); window.clear((sf::Color(30, 30, 30, 2)));
	cout << "Enter koeffcompressed: "; cin >> KoeffSjatie; cout << endl;
	if (KoeffSjatie == 1) {
		DomainSize = 16;
		RegionSize = 8;
		RNG = 10;
	}
	else if (KoeffSjatie == 2) {
		DomainSize = 32;
		RegionSize = 16;
		RNG = 10;
	}
	else if (KoeffSjatie == 3) {
		DomainSize = 64;
		RegionSize = 32;
		RNG = 15;
	}
	else if (KoeffSjatie == 4) {
		DomainSize = 128;
		RegionSize = 64;
		RNG = 1000;
	}

	
	sf::Image Image1; Image1.loadFromFile("lips.png");
	
		
	static double **R;
	R = new double* [Image1.getSize().y];
	for (int i = 0; i < Image1.getSize().y; i++) {
		R[i] = new double[Image1.getSize().x];
	}
	static double** G;
	G = new double* [Image1.getSize().y];
	for (int i = 0; i < Image1.getSize().y; i++) {
		G[i] = new double[Image1.getSize().x];
	}
	static double** B;
	B = new double* [Image1.getSize().y];
	for (int i = 0; i < Image1.getSize().y; i++) {
		B[i] = new double[Image1.getSize().x];
	}

	for (int i = 0; i < Image1.getSize().y; i++) {
		for (int j = 0; j < Image1.getSize().x; j++) {
			R[i][j] = (double)Image1.getPixel(j, i).r;
			G[i][j] = (double)Image1.getPixel(j, i).g;
			B[i][j] = (double)Image1.getPixel(j, i).b;
		}
	}
	
	static double** Y;
	Y = new double* [Image1.getSize().y];
	for (int i = 0; i < Image1.getSize().y; i++) {
		Y[i] = new double[Image1.getSize().x];
	}

	static double** Cb;
	Cb = new double* [Image1.getSize().y];
	for (int i = 0; i < Image1.getSize().y; i++) {
		Cb[i] = new double[Image1.getSize().x];
	}

	static double** Cr;
	Cr = new double* [Image1.getSize().y];
	for (int i = 0; i < Image1.getSize().y; i++) {
		Cr[i] = new double[Image1.getSize().x];
	}

	RGBtoYCBCR(R, G, B, Y, Cb, Cr, Image1.getSize().x, Image1.getSize().y);
	subsampling(Y, Cb, Cr, Image1.getSize().x, Image1.getSize().y);

	static double** M;
	M = new double* [8];
	for (int i = 0; i < 8; i++) {
		M[i] = new double[8];
	}
	createMmatrix(M);
	static double** Y8;
	Y8 = new double* [8];
	for (int i = 0; i < 8; i++) {
		Y8[i] = new double[8];
	}
	static double** Сb8;
	Сb8 = new double* [8];
	for (int i = 0; i < 8; i++) {
		Сb8[i] = new double[8];
	}
	static double** Cr8;
	Cr8 = new double* [8];
	for (int i = 0; i < 8; i++) {
		Cr8[i] = new double[8];
	}

	int y = 0; int x = 0;
	for (y = 0; y < Image1.getSize().y;) {
		for (x = 0; x < Image1.getSize().x;) {
			for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 8; j++) {
					Y8[i][j] = Y[i+y][j+x];
					Cr8[i][j] = Cr[i + y][j + x];
					Сb8[i][j] = Cb[i + y][j + x];
				}
			}
			
			dct(Y8, Сb8, Cr8,M, 8, 8, window);
			x += 8; X1 += 8;
		}
		y += 8; x = 0; Y1 += 8; X1 = 0;
	}

	
	Y1 = 0; X1 = 0;
	/*фрактальное сжатие*/
	Image Image2; Image2.loadFromFile("lips.png");
	Texture texture2; texture2.loadFromImage(Image2);
	Sprite sprite2; sprite2.setTexture(texture2);

	static double** Frac;
	Frac = new double* [Image2.getSize().y];
	for (int i = 0; i < Image2.getSize().y; i++) {
		Frac[i] = new double[Image2.getSize().x];
	}

	for (int i = 0; i < Image2.getSize().y; i++) {
		for (int j = 0; j < Image2.getSize().x; j++) {
			Frac[i][j] = (double)Image2.getPixel(j, i).r;
		}
	}



	static double** preobM;
	preobM = new double* [Image2.getSize().y * Image2.getSize().y /(RegionSize * RegionSize)];
	for (int i = 0; i < Image2.getSize().y * Image2.getSize().y / (RegionSize * RegionSize); i++) {
		preobM[i] = new double[7];
	}
	for (int i = 0; i < Image2.getSize().y * Image2.getSize().y / (RegionSize * RegionSize); i++) {
		preobM[i][0] = INT_MAX;
	}
	static double** D32;
	D32 = new double* [DomainSize];
	for (int i = 0; i < DomainSize; i++) {
		D32[i] = new double[DomainSize];
	}
	static double** R16;
	R16 = new double* [RegionSize];
	for (int i = 0; i < RegionSize; i++) {
		R16[i] = new double[RegionSize];
	}

	static double** compD;
	compD = new double* [RegionSize];
	for (int i = 0; i < RegionSize; i++) {
		compD[i] = new double[RegionSize];
	}
	int nomerregiona = 0;
	for (int k = 0; k < Image2.getSize().y; k+= RegionSize) {
		for (int l = 0; l < Image2.getSize().x; l += RegionSize) {

			for (int i = 0; i < RegionSize; i++) {
				for (int j = 0; j < RegionSize; j++) {
					R16[i][j] = Frac[i+k][j+l];
				}
			}

			for (int m = 0; m < Image2.getSize().y; m += DomainSize) {
				for (int n = 0; n < Image2.getSize().x; n += DomainSize) {

					for (int i = 0; i < DomainSize; i++) {
						for (int j = 0; j < DomainSize; j++) {
							D32[i][j] = Frac[i+m][j+n];
						}
					}

					

					matrixcomp(compD, D32);
					findminQ(R16, compD, preobM[nomerregiona][0],preobM, n, m, nomerregiona);

				}
			}
			cout << nomerregiona << endl;
			nomerregiona++;
		}

	}


	for (int i = 0; i < Image2.getSize().y * Image2.getSize().y / (RegionSize * RegionSize); i++){
		for (int j = 0; j < 7; j++) {
			cout << preobM[i][j] << ' ';
		}
		cout << endl;
	}

	static double** biff;
	biff = new double* [DomainSize];
	for (int i = 0; i < DomainSize; i++) {
		biff[i] = new double[DomainSize];
	}
	static double** Ynew;
	Ynew = new double* [Image2.getSize().y];
	for (int i = 0; i < Image2.getSize().y; i++) {
		Ynew[i] = new double[Image2.getSize().x];
	}
	for (RNG = 0; RNG < 5; RNG++) {
		X1 = 0; Y1 = 0;
		if (RNG > 0) {
			for (int U = 0; U < Image2.getSize().y; U++) {
				for (int R = 0; R < Image2.getSize().x; R++) {
					Frac[U][R] = Ynew[U][R];
				}
			}
		}
		for (int k = 0; k < Image2.getSize().y * Image2.getSize().y / (RegionSize * RegionSize); k++) {

			for (int i = 0; i < DomainSize; i++) {
				for (int j = 0; j < DomainSize; j++) {
					biff[i][j] = Frac[(int)preobM[k][1] + i][(int)preobM[k][2] + j];
				}
			}

			//matrixcomp(compD, biff);

			for (int i = 0; i < preobM[k][3]; i++) {
				gorizSwap(biff, DomainSize);
			}
			for (int i = 0; i < preobM[k][4]; i++) {
				rot90(biff, DomainSize);
			}
			

			for (int i = 0; i < DomainSize; i++) {
				for (int j = 0; j < DomainSize; j++) {
					biff[i][j] = max(0.0, min(255.0, preobM[k][6] * biff[i][j]) + preobM[k][5]);
				}
			}
			matrixcomp(compD, biff);
			for (int i = Y1; i < Y1 + RegionSize; i++) {
				for (int j = X1; j < X1 + RegionSize; j++) {
					Ynew[i][j] = compD[i - Y1][j - X1];
				}
			}


			X1 += RegionSize;
			if (X1 == Image2.getSize().x) {
				X1 = 0;
				Y1 += RegionSize;
			}

		}
	}
	PrintSprite(Ynew, Ynew, Ynew, Image2.getSize().x, Image2.getSize().y, window, 641,0);
	
	window.display();



	while (window.isOpen())
	{

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

	}
}