#include <iostream>
#include <SFML\Graphics.hpp>
#include <math.h>
#include <map>
#include <stack>
#include <fstream>
using namespace std;
using namespace sf;
const unsigned int W = 400;
const unsigned int H = 10;
int X1 = 0;
int Y1 = 0;
int levelHaar = 0;
double StepQ = 0.0;
void PrintSprite(double** R, double** G, double** B, int x, int y, RenderWindow& window, int x1, int y1) {
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
			Cb[i][j] = 128 - 0.1687 * R[i][j] - 0.3313 * G[i][j] + 0.5 * B[i][j];
			Cr[i][j] = 128 + 0.5 * R[i][j] - 0.4187 * G[i][j] - 0.0813 * B[i][j];
		}
	}
}


void YCBCRtoRGB(double** Y, double** Cb, double** Cr, int x, int y, RenderWindow& window) {
	static double** R;
	R = new double* [y];
	for (int i = 0; i < y; i++) {
		R[i] = new double[x];
	}
	static double** G;
	G = new double* [y];
	for (int i = 0; i < y; i++) {
		G[i] = new double[x];
	}
	static double** B;
	B = new double* [y];
	for (int i = 0; i < y; i++) {
		B[i] = new double[x];
	}
	for (int i = 0; i < y; i++) {
		for (int j = 0; j < x; j++) {
			R[i][j] = max(0.0, min(255.0, (Y[i][j] + 1.402 * (Cr[i][j] - 128))));
			G[i][j] = max(0.0, min(255.0, (Y[i][j] - 0.34414 * (Cb[i][j] - 128) - 0.71414 * (Cr[i][j] - 128))));
			B[i][j] = max(0.0, min(255.0, (Y[i][j] + 1.772 * (Cb[i][j] - 128))));
		}
	}
}


void subsampling(double** Y, double** Cb, double** Cr, int x, int y) {
	for (int i = 0; i < y; i += 2) {
		for (int j = 0; j < x; j += 2) {
			Cb[i][j + 1] = Cb[i][j];
			Cb[i + 1][j] = Cb[i][j];
			Cb[i + 1][j + 1] = Cb[i][j];
			Cr[i][j + 1] = Cr[i][j];
			Cr[i + 1][j] = Cr[i][j];
			Cr[i + 1][j + 1] = Cr[i][j];
		}
	}
}


string ZigZagPassage(double** matrixHaar)
{
	string code = "";
	int curr = 0;
	int j = 0; int i = 0;
	code += to_string((int)floor(matrixHaar[j][i]));
	for (int k = 0; k < 640*640; k++)
	{
		if (j == 0 && i == 0)
		{
			i++;
			code += to_string((int)floor(matrixHaar[j][i]));
		}
		if (j == 0)
		{
			while (i != 0)
			{
				j++;
				i--;
				code += to_string((int)floor(matrixHaar[j][i]));
			}
			if (j != 7)
			{
				code += to_string((int)floor(matrixHaar[j + 1][0]));
				j++;
			}
		}
		if (i == 0)
		{
			while (j != 0)
			{
				j--;
				i++;
				code += to_string((int)floor(matrixHaar[j][i]));
			}
			if (i != 7)
			{
				code += to_string((int)floor(matrixHaar[0][i + 1]));
				i++;
			}
		}
		if (j == 7)
		{
			while (i != 7)
			{
				j--;
				i++;
				code += to_string((int)floor(matrixHaar[j][i]));
			}
			if (i != 0)
			{
				code += to_string((int)floor(matrixHaar[j - 1][7]));
				j--;
			}
		}
		if (i == 7)
		{
			while (j != 7)
			{
				j++;
				i--;
				code += to_string((int)floor(matrixHaar[j][i]));
			}
			if (i != 0)
			{
				code += to_string((int)floor(matrixHaar[7][i - 1]));
				i--;
			}
		}
	}
	return code;
}


//void Matrix2str(double** matrixHaar, string& Y)
//{
//	int y = 0, x = 0, temp = 0, y_size = 640 - 1, x_size = 640 - 1;
//	bool direction = false;
//
//	Y += to_string((int)matrixHaar[y][x]); Y += " ";
//
//	while (1)
//	{
//		if (y == 0 && x < x_size) {
//			x++;
//			Y += to_string((int)matrixHaar[y][x]); Y += " ";
//			direction = false;
//		}
//		else if (y < y_size && x == x_size) {
//			y++;
//			Y += to_string((int)matrixHaar[y][x]); Y += " ";
//			direction = false;
//		}
//		else if (x == 0 && y < y_size) {
//			y++;
//			Y += to_string((int)matrixHaar[y][x]); Y += " ";
//			direction = true;
//		}
//		else if (x == 0 && y == y_size) {
//			x++;
//			Y += to_string((int)matrixHaar[y][x]); Y += " ";
//			direction = true;
//		}
//		else if (x < x_size && y == y_size) {
//			x++;
//			Y += to_string((int)matrixHaar[y][x]); Y += " ";
//			direction = true;
//		}
//
//		if (x == y_size && y == y_size) break;
//
//		if (!direction)
//		{
//			temp = x;
//			for (int i = 0; i < temp; i++)
//			{
//				x--; y++;
//				Y += to_string((int)matrixHaar[y][x]); Y += " ";
//				if (y > y_size - 1 || x == 0) break;
//			}
//		}
//		else
//		{
//			temp = y;
//			for (int i = 0; i < temp; i++)
//			{
//				x++; y--;
//				Y += to_string((int)matrixHaar[y][x]); Y += " ";
//				if (x > x_size - 1 || y == 0) break;
//			}
//		}
//	}
//
//}


void Matrix2str(double** matrixHaar, string& Y)
{
	int y = 0, x = 0, temp = 0, y_size = 640/pow(2,levelHaar) - 1, x_size = 640 / pow(2, levelHaar) - 1;
	bool direction = false;

	Y += to_string((int)matrixHaar[y][x]); Y += " ";
	while (1)
	{
		if (y == 0 && x < x_size) x++,
			Y += to_string((int)matrixHaar[y][x]),
			Y += " ",
			direction = false;
		else if (y < y_size && x == x_size) y++,
			Y += to_string((int)matrixHaar[y][x]),
			Y += " ",
			direction = false;
		else if (x == 0 && y < y_size) y++,
			Y += to_string((int)matrixHaar[y][x]),
			Y += " ",
			direction = true;
		else if (x == 0 && y == y_size) x++,
			Y += to_string((int)matrixHaar[y][x]),
			Y += " ",
			direction = true;
		else if (x < x_size && y == y_size) x++,
			Y += to_string((int)matrixHaar[y][x]),
			Y += " ",
			direction = true;

		if (x == y_size && y == y_size) break;

		if (!direction)
		{
			temp = x;
			for (int i = 0; i < temp; i++)
			{
				x--; y++;
				Y += to_string((int)matrixHaar[y][x]);
				Y += " ";
				if (y > y_size - 1 || x == 0)  break;
			}
		}
		else
		{
			temp = y;
			for (int i = 0; i < temp; i++)
			{
				x++; y--;
				Y += to_string((int)matrixHaar[y][x]);
				Y += " ";
				if (x > x_size - 1 || y == 0) break;
			}
		}
	}
	/*cout << Y.length();
	system("pause");*/
}



void str2Matrix(double** matrixHaar, string& code)
{
	int y = 0, x = 0, temp = 0, y_size = 640 / pow(2, levelHaar) - 1, x_size = 640 / pow(2, levelHaar) - 1;
	bool direction = false;
	int curr = 0;
	string tmp = "";
	while (code[curr] != ' ') {
		tmp += code[curr]; curr++;
	}
	curr++;
	matrixHaar[y][x] = stod(tmp); tmp = "";
	while (1)
	{
		if (y == 0 && x < x_size) {
			x++;
			while (code[curr] != ' ') {
				tmp += code[curr]; curr++;
			}
			curr++;
			matrixHaar[y][x] = stod(tmp); tmp = "";
			direction = false;
		}
		else if (y < y_size && x == x_size) {
			y++;
			while (code[curr] != ' ') {
				tmp += code[curr]; curr++;
			}
			curr++;
			matrixHaar[y][x] = stod(tmp); tmp = "";
			direction = false;
		}
		else if (x == 0 && y < y_size) {
			y++;
			while (code[curr] != ' ') {
				tmp += code[curr]; curr++;
			}
			curr++;
			matrixHaar[y][x] = stod(tmp); tmp = "";
			direction = true;
		}
		else if (x == 0 && y == y_size) {
			x++;
			while (code[curr] != ' ') {
				tmp += code[curr]; curr++;
			}
			curr++;
			matrixHaar[y][x] = stod(tmp); tmp = "";
			direction = true;
		}
		else if (x < x_size && y == y_size) {
			x++;
			while (code[curr] != ' ') {
				tmp += code[curr]; curr++;
			}
			curr++;
			matrixHaar[y][x] = stod(tmp); tmp = "";
			direction = true;
		}

		if (x == y_size && y == y_size) break;

		if (!direction)
		{
			temp = x;
			for (int i = 0; i < temp; i++)
			{
				x--; y++;
				while (code[curr] != ' ') {
					tmp += code[curr]; curr++;
				}
				curr++;
				matrixHaar[y][x] = stod(tmp); tmp = "";
				if (y > y_size - 1 || x == 0) break;
			}
		}
		else
		{
			temp = y;
			for (int i = 0; i < temp; i++)
			{
				x++; y--;
				while (code[curr] != ' ') {
					tmp += code[curr]; curr++;
				}
				curr++;
				matrixHaar[y][x] = stod(tmp); tmp = "";
				if (x > x_size - 1 || y == 0) break;
			}
		}
	}

}


string RLE(string text)
{
	string result = "";
	int count = 0;
	string tmp = "";

	for (int i = 0; i < text.length(); i++)
	{
		while (text[i]!= ' ')
		{
			tmp += text[i]; i++;
		}
		if (tmp == "0" || tmp=="-0") {
			count++;
			tmp = "";
		}
		else {
			result += (char)count;
			
			result += (char)stoi(tmp);

			count = 0;
			tmp = "";
		}
	}
	return result;
}


string RLEdecode(string code)
{
	int size = 0, size2 = 0; int Y = 0; int X = 0;
	string result = ""; int countZero = 0;
	for (int i = 0; i < code.length(); i++) {
		if (i % 2 == 0) {
			int TMP = code[i];
			countZero = TMP;

			for (int j = 0; j < countZero; j++) {
				result += "0"; result += " ";
			}
		}
		if (i % 2 == 1) {
			int TMP = code[i];
			result += to_string(TMP); result += " ";
		}
	}
	return result;
}


void quantization(double** MatrixHaar) {	
	cout << "Enter the quantization coefficient: ";
	cin >> StepQ;
	int y = 0; int x = 0;
	for (y = 0; y < 640; y++) {
		for (x = 0; x < 640; x++) {
			MatrixHaar[y][x] = MatrixHaar[y][x] / StepQ;
		}
	}
}


void dequantization(double** MatrixHaar) {	
	int y = 0; int x = 0;
	for (y = 0; y < 640; y++) {
		for (x = 0; x < 640; x++) {
			MatrixHaar[y][x] = MatrixHaar[y][x] * StepQ;
		}
	}
}


void HaarTransform(double** LL,double** Y, int x, int y, RenderWindow& window) {
	static double** LLbuff;
	LLbuff = new double* [y];
	for (int i = 0; i < y; i++) {
		LLbuff[i] = new double[x];
	}
	for (int i = 0; i < y; i++) {
		for (int j = 0; j < x; j++)
		{
			LLbuff[i][j] = Y[i][j];
		}
	}
	
	for (int i = 0; i < y; i++) {
		for (int j = 0; j < x; j += 2)
		{
			LL[i][j/2] = (LLbuff[i][j] + LLbuff[i][j + 1]) / 2.0;
		}
	}

	for (int i = 0; i < y; i++) {
		for (int j = 0; j < x; j += 2)
		{
			LL[i][j/2 + x / 2] = (LLbuff[i][j] - LLbuff[i][j + 1]) / 2.0;
		}
	}


	for (int i = 0; i < y; i++) {
		for (int j = 0; j < x; j++)
		{
			LLbuff[i][j] = LL[i][j];
		}
	}

	for (int i = 0; i < y; i++) {
		for (int j = 0; j < x; j += 2)
		{
			LL[j / 2][i] = (LL[j][i] + LL[j+1][i]) / 2.0;
		}
	}

	for (int i = 0; i < y; i++) {
		for (int j = 0; j < x; j += 2)
		{
			LL[j / 2 + x / 2][i] = (LLbuff[j][i] - LLbuff[j+1][i]) / 2.0;
		}
	}
}


void IhaarTransform(double** PmatrixHaar,double** FmatrixHaar, RenderWindow& window, int x, int y) {
	static double** LLbuff3;
	LLbuff3 = new double* [y];
	for (int i = 0; i < y; i++) {
		LLbuff3[i] = new double[x];
	}
	for (int i = 0; i < y; i++) {
		for (int j = 0; j < x; j++)
		{
			LLbuff3[i][j] = PmatrixHaar[i][j];
		}
	}
	for (int i = 0; i < y; i++) {
		for (int j = 0; j < (x - 1); j++)
		{
			FmatrixHaar[j][i] = LLbuff3[j / 2][i] + LLbuff3[j / 2 + x / 2][i];
			FmatrixHaar[j + 1][i] = LLbuff3[j / 2][i] - LLbuff3[j / 2 + x / 2][i];
		}
	}
	static double** LLbuff2;
	LLbuff2 = new double* [y];
	for (int i = 0; i < y; i++) {
		LLbuff2[i] = new double[x];
	}
	for (int i = 0; i < y; i++) {
		for (int j = 0; j < x; j++)
		{
			LLbuff2[i][j] = FmatrixHaar[i][j];
		}
	}
	for (int i = 0; i < y; i++) {
		for (int j = 0; j < x; j++)
		{
			FmatrixHaar[i][j] = LLbuff2[i][j / 2] + LLbuff2[i][j / 2 + x / 2];
			FmatrixHaar[i][j + 1] = LLbuff2[i][j / 2] - LLbuff2[i][j / 2 + x / 2];
		}
	}

}


int main()
{
	ofstream output("RLE().txt");
	ofstream output2("RLEDECODE.txt");


	sf::RenderWindow window(sf::VideoMode(1980, 1080), "Picture"); window.clear((sf::Color(30, 30, 30, 2)));
	sf::Image Image1; Image1.loadFromFile("lips.png");

	static double** R;
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

	static double** matrixHaar;
	matrixHaar = new double* [Image1.getSize().y];
	for (int i = 0; i < Image1.getSize().y; i++) {
		matrixHaar[i] = new double[Image1.getSize().x];
	}

	static double** ImatrixHaar;
	ImatrixHaar = new double* [Image1.getSize().y];
	for (int i = 0; i < Image1.getSize().y; i++) {
		ImatrixHaar[i] = new double[Image1.getSize().x];
	}

	static double** ImatrixHaar2;
	ImatrixHaar2 = new double* [Image1.getSize().y];
	for (int i = 0; i < Image1.getSize().y; i++) {
		ImatrixHaar2[i] = new double[Image1.getSize().x];
	}

	for (int i = 0; i < Image1.getSize().y; i++) {
		for (int j = 0; j < Image1.getSize().x; j++) {
			R[i][j] = (double)Image1.getPixel(j, i).r;
			G[i][j] = (double)Image1.getPixel(j, i).g;
			B[i][j] = (double)Image1.getPixel(j, i).b;
		}
	}


	RGBtoYCBCR(R, G, B, Y, Cb, Cr, Image1.getSize().x, Image1.getSize().y);

	subsampling(Y, Cb, Cr, Image1.getSize().x, Image1.getSize().y);

	PrintSprite(Y, Y, Y, Image1.getSize().x, Image1.getSize().y, window, 0, 0);
	
	

	
	/*Преобразоавние Хаара*/
	cout << "Enter level of Haar transformation: ";
	cin >> levelHaar;
	for (int i = 0; i < levelHaar; i++) {
		if (i == 0) {
			HaarTransform(matrixHaar, Y, Image1.getSize().x / pow(2, i), Image1.getSize().y / pow(2, i), window);
		}
		else {
			HaarTransform(matrixHaar, matrixHaar, Image1.getSize().x / pow(2, i), Image1.getSize().y / pow(2, i), window);

		}
	}
	PrintSprite(matrixHaar, matrixHaar, matrixHaar, Image1.getSize().x, Image1.getSize().y, window, 641, 0);




	
	quantization(matrixHaar);
	string code = "";
	Matrix2str(matrixHaar, code);
	output << code;

	code = RLE(code);

	

	string encode = "";
	encode = RLEdecode(code);
	output2 << encode;
	str2Matrix(matrixHaar, encode);
	dequantization(matrixHaar);

	
	for (int i = 0; i < Image1.getSize().y; i++) {
		for (int j = 0; j < Image1.getSize().x; j++) {
			ImatrixHaar[i][j] = matrixHaar[i][j];
		}
	}
	for (int i = levelHaar; i > 0; i--) {
		if (i == levelHaar) {
			IhaarTransform(matrixHaar, ImatrixHaar, window, Image1.getSize().x / pow(2, levelHaar) * pow(2, levelHaar - i + 1), Image1.getSize().y / pow(2, levelHaar) * pow(2, levelHaar - i + 1));
		}
		else {
			IhaarTransform(ImatrixHaar, ImatrixHaar, window, Image1.getSize().x / pow(2, levelHaar) * pow(2, levelHaar - i + 1), Image1.getSize().y / pow(2, levelHaar) * pow(2, levelHaar - i + 1));
		}
	}
	

	PrintSprite(ImatrixHaar, ImatrixHaar, ImatrixHaar, Image1.getSize().x, Image1.getSize().y, window, 1281, 0);
	


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
