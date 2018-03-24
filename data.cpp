#include<simplecpp>
#include"lib.cpp"

struct msg;

struct msg_data {
	char date[17];
	char from[17];
	char to[17];
	char body[600];
	bool read_flag;
		
	void create(string, string, string, string, bool);
	void create(msg);
	
};

struct msg {
	string date;
    string from;
    string to;
    string body;
    bool read_flag;
	
	msg(string, string, string, string, bool);
    msg(msg_data a);
    
    bool operator==(const msg&);    
    void create(msg_data);
};

struct usr;
struct user {
    string id;
    string pass;
    string Name;
    string ph_no;
    
    user& operator=(const user& u);
    user(string, string, string, string);
   
   	void create(usr); 
   	void reset();
   
};


struct usr {
	char id[17];
	char pass[17];
	char Name[17];
	char ph_no[17];
	
	void create(user);

};

struct theme	{
Color back1;// COLOR(15,15,15)			//dark background
Color back2;// COLOR(25,25,25)
Color fore;// COLOR (255,255,255)
Color fore2;// COLOR (255,255,255)
Color tint;// COLOR (23,123,15)
};


void msg::create(msg_data m) {
	strcpy(m.date,date);
	strcpy(m.to,to);
	strcpy(m.from,from);
	strcpy(m.body,body);
}

msg::msg(string s1=" ", string s2=" ", string s3=" ", string s4=" ", bool r=0) {
	date=s1;
	from=s2;
	to=s3;
	body=s4;
	read_flag=r;
}  

void msg_data::create(string s1=" ", string s2=" ", string s3=" ", string s4=" ", bool r=0) {
	strcpy(s1,date);
	strcpy(s2,from);
	strcpy(s3,to);
	strcpy(s4,body);	
	read_flag=r;
}     
    
msg:: msg(msg_data a) {
	date=a.date;
	from=a.from;
	to=a.to;
	body=a.body;
	read_flag=a.read_flag;
}

void msg_data::create(msg m) {
	strcpy(m.date,date);
	strcpy(m.to,to);
	strcpy(m.from,from);
	strcpy(m.body,body);
}

bool msg::operator==(const msg& m){
	if(m.from==from)	{
		if(m.to==to)	{
			if(m.date==date)	{
				if(m.read_flag==read_flag)
					return 1;
				}
			}
		}
	return 0;
}	
	
void user::create(usr a) {
    strcpy(a.id,id);
    strcpy(a.pass,pass);
    strcpy(a.Name,Name);
    strcpy(a.ph_no,ph_no);
}
   
user& user::operator=(const user& u) {
    id=u.id;
    pass=u.pass;
    Name=u.Name;
    ph_no=u.ph_no;
    return *this; 
}

    
user::user(string i="\0", string p="\0", string N=" ", string ph="0") {
    id=i;
    pass=p;
    Name=N;
    ph_no=ph;
}

void user::reset() {
	id="\0";
	pass="\0";
	Name="\0";
	ph_no="\0";
}
  
void usr::create(user a) {
	strcpy(a.id,id);
	strcpy(a.pass,pass);
    strcpy(a.Name,Name);
    strcpy(a.ph_no,ph_no);
} 




