#include<simplecpp>
#include<fstream>

struct theme	{
Color back1;// COLOR(15,15,15)			//dark background
Color back2;// COLOR(25,25,25)
Color fore;// COLOR (255,255,255)
Color fore2;// COLOR (255,255,255)
Color tint;// COLOR (23,123,15)

};
	

int main()	{
	ofstream mf;
	mf.open("themes.dat",ios::out|ios::binary);
	int r,g,b;
	theme t;
	int i=0;
	while(i<13)	{
		cin>>r>>g>>b;
		t.back1=COLOR(r,g,b);
		cout<<r<<' '<<g<<' '<<b<<'\n';
		cin>>r>>g>>b;
		t.back2=COLOR(r,g,b);
		cout<<r<<' '<<g<<' '<<b<<'\n';
		cin>>r>>g>>b;
		t.fore=COLOR(r,g,b);
		cout<<r<<' '<<g<<' '<<b<<'\n';
		cin>>r>>g>>b;
		t.fore2=COLOR(r,g,b);
		cout<<r<<' '<<g<<' '<<b<<'\n';
		cin>>r>>g>>b;
		t.tint=COLOR(r,g,b);
		cout<<r<<' '<<g<<' '<<b<<"\n\n";
		mf.write((char*)&t,sizeof(t));
		i++;
	}
	mf.close();
}
