#include<simplecpp>
#include<fstream>
#include <canvas.h>

using namespace std;
struct point {
   	unsigned char r;
	unsigned char g;
	unsigned char b;
};


void intro() {
	initCanvas("SAMVAD",1280,720);
	ifstream mf;
	mf.open("intro.dat",ios::in|ios::binary);
	if(!mf) cout<<"error"; 	
	point a;
	cout<<'a';

	int x=8;
	for(int i=0; i<100; i++) {
		for(int j=0; j<177; j++) {
			mf.read((char*)&a,sizeof(a));
			if(a.g<100)
				continue;
			Rectangle r(j*x,i*x,1*x,1*x);
			r.setColor(COLOR(a.r,a.g,a.b));
			r.setFill(1);
			r.imprint();
		}
	}
	mf.close();
	wait(0.5);
	closeCanvas();
}
