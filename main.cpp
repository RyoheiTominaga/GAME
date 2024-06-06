#include"GameLib/Framework.h"
#include<fstream>
#include<iostream>
const int imageNum = 3;
using namespace std;
bool first = true;
int imageWight = 0;
int imageHeight = 0;
unsigned* image[imageNum] = {0};
int P_num();
int C_num();
void PlayGame(int Pnum,int Cnum);
//すみませんまだまだ途中です
namespace GameLib {
	void readFile(char** buffer, int* size, const char* filename);
	const char* GetFileName(int num);
	unsigned getUnsigned(const char*);
	
	void Framework::update() {
		int P_number = 0;
		int C_number = 0;
		if (first) {
			P_number = P_num();
			C_number = C_num();
			for (int i = 0;i < imageNum;++i) {
				char* buffer = 0;
				int size = 0;
				readFile(&buffer, &size,GetFileName(P_number) );
				imageHeight = getUnsigned(&(buffer[12]));
				imageWight = getUnsigned(&(buffer[16]));
				image[i] = new unsigned[imageWight * imageHeight];
				for (int j = 0;j < imageWight * imageHeight;++j) {
					image[i][j] = getUnsigned(&(buffer[128 + j * 4]));
				}
				delete[] buffer;
				
			}
			first = false;
		}
		unsigned* vram = videoMemory();
		unsigned windowWidth = width();
		//0:
		//1:
		//2:パー
		for (int i = 0;i < imageNum;++i) {
			for (int y = 0;y < imageHeight;++y) {
				for (int x = 0;x < imageWight;++x) {
					vram[y * windowWidth + x] = image[i][y * imageWight + x];
				}
			}
		}

		PlayGame(P_number,C_number);
		
		
	}
	void readFile(char** buffer, int* size, const char* filename) {
		ifstream in(filename, ifstream::binary);
		if (!in) {
			*buffer = 0;
			*size = 0;
		}
		else {
			in.seekg(0, ifstream::end);
			*size = static_cast<int>(in.tellg());
			in.seekg(0, ifstream::beg);
			*buffer = new char[*size];
			in.read(*buffer, *size);
		}
	}

	unsigned getUnsigned(const char* p) {
		const unsigned char* up;
		up = reinterpret_cast<const unsigned char*>(p);
		unsigned r = up[0];
		r |= up[1] << 8;
		r |= up[2] << 16;
		r |= up[3] << 24;
		return r;
	}
	const char* GetFileName(int num) {
		static char filename[256];
		snprintf(filename, sizeof(filename), "%02d.dds", num);
		cout << filename << endl;
		return filename;
	}
	
}
int P_num()//プレイヤーの決めた数字
{
	int num;
	cout << "グー:0\nチョキ:1\nパー:2\n";
	cin >> num;
	return num;
}
int C_num()//Cpが決めた数字
{
	srand((unsigned int)time(NULL));
	return rand() % 3;
}
bool Win(int P_N, int Cp_N)//プレイヤーが勝ったかどうか
{
	//0.グー1チョキ.2パー
	if (P_N == 0)//グー 
	{
		switch (Cp_N)
		{
		case 0:break;//あいこ
		case 1:return true;break;
		case 2:return false;break;
		}
	}
	else if (P_N == 1)//チョキ
	{
		switch (Cp_N)
		{
		case 0:return false;break;
		case 1:break;//あいこ
		case 2:return true;break;
		}
	}
	else//パー
	{
		switch (Cp_N)
		{
		case 0:return true;break;
		case 1:return false;break;
		case 2:break;//あいこ
		}
	}
}

void PlayGame(int Pnum,int Cnum) 
{
	bool win = Win(Pnum,Cnum);
	
	if (win) {
		cout << "プレイヤー勝利";
	}
	else if (!win){
		cout << "プレイヤーの負け";
	}
	else {
		//aiko
	}
	//ここでゲームの勝敗を決める
}
