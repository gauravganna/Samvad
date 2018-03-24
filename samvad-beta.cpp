#include<simplecpp>
#include<fstream>
#include<ctime>
#include<vector>
#include"data.cpp"
#include"hybrid.h"
#include"intro.cpp"
#define red COLOR(225,0,0)
#define blue COLOR(0,255,0)
#define green COLOR(0,0,255)

#define acc_add "acc.dat"
#define data_add "database.dat"
#define theme_add "themes.dat"


void inbox(hybrid& all);//Controls & Handles inbox's Clicks and inbox for a list 'all'			
void create_account();	//Crea
void background();		//Sets a background Color
void title_bar();		//Creates the Title Bar
void get_theme();		//Reads the Theme Data from file for Shuffling
void shuffle();			//Changes Theme after every login
void update(hybrid& all);	//Rechecks for messages from the database file
int error();				//Checks and waits till the user clicks on the close Button for the error box
void error(string,string);	//Prints an error box with 1st string on titlebar and 2nd on the dialog box
void login(hybrid& all,string,string);	//Checks for a username and password and inserts msgs in a;;
void login(hybrid& all);	//creates the login page, takes input and calls the other login function to verify
void send(hybrid& all);		//used to send msgs. creates a new object msg, takes input and writes to the database
void inbox(hybrid& all,size_t index);	//this one prints the inbox layout, prints all msgs from serial no. 'index' to 'index+10'
void login_box(hybrid& all,short no_of_boxes,int height,int width,int end_x,int end_y);//Main menu after login
void create_layout();	//creates layout for sending msg
void input_msg(string &to,string &subject,string &msg);	//takes input for sending msg then calls send to do the backend work
void read_msg(msg&);		//prints msg in a display view
void search_msg(hybrid &all);	//searchs in 'all' and creates a temp hybrid list and calls inbox for the same.

//GLOBAL VARIABLES
user current;
int unread=0;
long long pos=0;
size_t t_i=0;

vector <theme> themes;

//MAIN FUNCTION
int main() {
	intro();
	initCanvas("intro",1280,720);
	get_theme();
	background();
	title_bar();
	
	while(true)	{
		hybrid msgs;
    	login(msgs);
		shuffle();    
	}
	return 0;
}

//Sets a background for the entire Canvas
void background() {
    Rectangle r(640,360,1280,720);
    r.setFill(1);
    r.setColor(themes[t_i].back2);
    r.imprint();
}

//Creates the default bar for every screen
void title_bar() {
	int h=40 , r=10;
	Rectangle bar(640,h/2,1280,h);
	bar.setColor(themes[t_i].tint);
	bar.setFill(1);
	bar.imprint();
	if(current.id==" ")
		return;
	if(current.id!="\0") {
		Text(1220-(textWidth(current.Name+"[  ]")/2),2*h/3,current.Name).setColor(themes[t_i].fore2).imprint();
		Text(1230-r,2*h/3,unread).setColor(themes[t_i].fore).imprint();
		Circle(1230-r,2*h/3,r).setColor(themes[t_i].fore).imprint();
		Text(1230-(textWidth("Signed in as:")/2),h/4, "Signed in as:").setColor(themes[t_i].fore2).imprint();
	}
	else	
		Text(1220-(textWidth("Not Signed in")/2),h/3, "Not Signed in").setColor(themes[t_i].fore2).imprint();
}

void get_theme(){
	
	ifstream th;
	theme t;
	th.open("themes.dat",ios::in);
	if(!th)	{
		t.back1=COLOR(15,15,15);
		t.back2=COLOR(25,25,25);
		t.fore=COLOR(255,255,255);
		t.fore2=COLOR(255,255,255);
		t.tint=COLOR(23,123,15);
		themes.push_back(t);
		themes.push_back(t);
		return;
	}	
	while(th){
		th.read((char*)&t,sizeof(t));
		themes.push_back(t);
	}
	th.close();
}
	

void shuffle(){
	t_i=(++t_i)%themes.size();
}




//Scans and checks for new mails
void update(hybrid& all) {
	ifstream mf;
	mf.open(data_add,ios::in|ios::binary);
	if(!mf) {
		error("An Error Occured","UNABLE TO CONNECT TO DATABASE. TRY LATER");
		if(error()) {
			background();
			return;
		}
	}
	msg_data md;
	mf.seekg(pos,ios::beg);
	mf.read((char*)&md,sizeof(md));
	while(mf) {
		msg m(md);
		if(m.to==current.id) {
			all.insert(msg(m));
			if(m.read_flag==0)	unread++;
		}
		mf.read((char*)&md,sizeof(md));
		pos=mf.tellg();
	}
	mf.close();
}

//creates the new User Page
void create_account() {
	start:
	closeCanvas();
	initCanvas("Create Account",1280,720);
	background();
	title_bar(); 
    int i=0,x=0,y=0,a=0;
    string s1,s2,s3,s4,s5,Encrypted_Password,Encrypted_Password2;
    const char backspace = 8;
    
    layout:
    Text(550,200,"User ID :").setColor(themes[t_i].fore).imprint();
    Text(550,260,"Password :").setColor(themes[t_i].fore).imprint();
    Text(550,320,"Confirm Password :").setColor(themes[t_i].fore).imprint();
    Text(550,380,"Phone No. :").setColor(themes[t_i].fore).imprint();
    Text(550,440,"Name :").setColor(themes[t_i].fore).imprint();
    Rectangle UserName(700,200,160,30);   UserName.setColor(themes[t_i].fore);
    Rectangle PassWord(700,260,160,30);   PassWord.setColor(themes[t_i].fore);
    Rectangle Confirm(700,320,160,30);   Confirm.setColor(themes[t_i].fore);
    Rectangle Phone(700,380,160,30);   Phone.setColor(themes[t_i].fore);
    Rectangle Name(700,440,160,30);   Name.setColor(themes[t_i].fore);
    Rectangle Submit(775,500,100,30);   Submit.setColor(themes[t_i].fore);
    Text(775,500,"Submit").setColor(themes[t_i].fore).imprint();
    UserName.imprint();PassWord.imprint();Confirm.imprint();Name.imprint();Phone.imprint(); Submit.imprint();

    while( x<725 || x>825 || y<485 || y>515 ) {
        XEvent event;
        if(mouseButtonPressEvent(event)) {
            x = event.xbutton.x; y = event.xbutton.y;
            if( (x>625 && x<775) && (y>185 && y<215) )          i=1;
            else if( (x>625 && x<775) && (y>245 && y<275) )     i=2;
            else if( (x>625 && x<775) && (y>305 && y<335) )     i=3;
            else if( (x>625 && x<775) && (y>365 && y<395) )     i=4;
            else if( (x>625 && x<775) && (y>425 && y<455) )     i=5;
            else if( (x>725 && x<825) && (y>485 && y<515) )     i=6;
            else i=0;
            Text(625+textWidth(s1)/2,200,s1).setColor(themes[t_i].fore).imprint();
            Text(625+textWidth(Encrypted_Password)/2,260,Encrypted_Password).setColor(themes[t_i].fore).imprint();
            Text(625+textWidth(Encrypted_Password2)/2,320,Encrypted_Password2).setColor(themes[t_i].fore).imprint();
            Text(625+textWidth(s4)/2,380,s4).setColor(themes[t_i].fore).imprint();
            Text(625+textWidth(s5)/2,440,s5).setColor(themes[t_i].fore).imprint();          
        }
        if(checkEvent(event) && keyPressEvent(event)) {
            char c = charFromEvent(event);
             
            if(i==1) {
                if(c == backspace) {
                    a = textWidth(s1[s1.length()-2]);
                    s1 = cut_string(s1);
                    Rectangle r(625 + textWidth(s1) + a/2,200,a,30);
                    r.setColor(themes[t_i].back2);
                    r.setFill(true);
                    r.imprint();
                }
                else {
                    if(s1.length() < 16)
                        s1 = s1 + c;
                    else {
                        error("error", "word limit cannot exceed 16,try again");
                        if(error())
                        {	background();
                       		title_bar();
                       		goto layout;
                       	}
                    }
                }
                Text(625+textWidth(s1)/2,200,s1).setColor(themes[t_i].fore).imprint();
            }
            if(i==2) {
                if(c == backspace) {
                    s2 = cut_string(s2);
                    Encrypted_Password = cut_string(Encrypted_Password);
                    Rectangle r(625 + textWidth(Encrypted_Password) + textWidth("*")/2,260,textWidth("*"),30);
                    r.setColor(themes[t_i].back2);
                    r.setFill(true);
                    r.imprint();
                }
                else {
                    if(s2.length()<16) {
                        s2 = s2 + c;
                        Encrypted_Password = Encrypted_Password + '*';
                    }
                    else {
                        error("error", "word limit cannot exceed 16,try again");
                        if(error())
                        {	background();
                        	title_bar();
                        	goto layout;
                        }
                   	}
                }
                Text(625+textWidth(Encrypted_Password)/2,260,Encrypted_Password).setColor(themes[t_i].fore).imprint();
            }
            if(i==3) {
                if(c == backspace) {
                    s3 = cut_string(s3);
                    Encrypted_Password2 = cut_string(Encrypted_Password2);
                    Rectangle r(625 + textWidth(Encrypted_Password2) + textWidth("*")/2,320,textWidth("*"),30);
                    r.setColor(themes[t_i].back2);
                    r.setFill(true);
                    r.imprint();
                }
                else {
                    if(s3.length()<16) {
                        s3 = s3 + c;
                        Encrypted_Password2 = Encrypted_Password2 + '*';
                    }
                    else {
                        error("error", "word limit cannot exceed 16,try again");
                        if(error())
                        {	background();
                        	title_bar();
                        	goto layout;
                        }
                   	}
                }
                Text (625+textWidth(Encrypted_Password2)/2,320,Encrypted_Password2).setColor(themes[t_i].fore).imprint();
            }
            if(i==4) {
                if(c == backspace) {
                    a = textWidth(s1[s1.length()-2]);
                    s4 = cut_string(s4);
                    Rectangle r(625 + textWidth(s4) + a/2,380,a,30);
                    r.setColor(themes[t_i].back2);
                    r.setFill(true);
                    r.imprint();
                }
                else {
                    if(s4.length() < 16)
                        s4 = s4 + c;
                    else {
                        error("error", "word limit cannot exceed 16,try again");
                        if(error())
                        {	background();
                        	title_bar();
                        	goto layout;
                        }
                   	}
                }
                Text(625+textWidth(s4)/2,380,s4).setColor(themes[t_i].fore).imprint();
            }
            if(i==5) {
            	
                if(c == backspace) {
                    a = textWidth(s1[s1.length()-2]);
                    s5 = cut_string(s5);
                    Rectangle r(625 + textWidth(s5) + a/2,440,a,30);
                    r.setColor(themes[t_i].back2);
                    r.setFill(true);
                    r.imprint();
                    
                }
                else {
                    if(s5.length() < 16)
                        s5 = s5 + c;
                    else {
                        error("error", "word limit cannot exceed 16,try again");
                        if(error()) {	
                        	background();
                        	title_bar();
                        	goto layout;
                        }
                   	}
                        
                }
                Text(625+textWidth(s5)/2,440,s5).setColor(themes[t_i].fore).imprint();
            }
        }
    }
	if(s2!=s3) {
		error("Error!!!", "Passwords do not match!!!");
		if(error())	{
			goto start;
		}
	}
	usr u;
	/*char id[17];
	strcpy(s1,id);
	ifstream in;
	in.open(acc_add,ios::binary|ios::in);
	in.read((char*)&u, sizeof(u));
	while(in)	{
		if(strcmp(id,u.id))	{
			error("Error","User ID Already Exists!!!");
			in.close();
			if(error())	{
				goto start;
			}
		else
			in.read((char*)&u, sizeof(u));
		}
	}*/
	user b(s1,s2,s5,s4);
    u.create(b);
    ofstream mf;
    mf.open(acc_add,ios::out|ios::binary|ios::app);
    if(!mf)	{
    	error("Error Occured","Unable to Connect to Database");
    	if(error())
    		goto start;
    	}
    mf.write((char*)&u,sizeof(u));
    mf.close();
  	return;
}

//Login Verification Fn. verfies inputdata with database
void login(string i,string pas, hybrid& all) {
	closeCanvas();
	initCanvas("verfiying", 1280,720);
	char id[17], pass[17];
	strcpy(i,id);
	strcpy(pas,pass);
	
	background();
	title_bar();
	ifstream mf(acc_add,ios::in|ios::binary);
	if(!mf)	{
		error("Error Occured","Login Credentials don't match/exist on our Database");
		if(error())
			return;
	}
	usr u; bool f=1;

	mf.read((char*)&u,sizeof(u));
	while(mf && f==1)	{
		if(strcmp(id,u.id) && strcmp(pass,u.pass)) {
			f=0;
			current.create(u);
			break;
		}
		mf.read((char*)&u,sizeof(u));
	}
	mf.close();
	  	
    if(f==0) {
    	closeCanvas();
    	initCanvas("User",1280,720);
    	background(); title_bar();
    	error("Success", "Signed in Successfully");
    	update(all);
    	if(error())
   			login_box(all,5,40,180,550,200);    
    }
    else {
    	error("Error Occurred","Invalid Credentials!!! Try Again.");
    	if(error())
    		return;
    }
    error("Sucess!!!","Sucessfully Signed out!!!");
    if(error())
    	return;
}

//Login Box(LOGIN PAGE)
void login(hybrid& all) {
	closeCanvas();
	initCanvas("Login",1280,720);
	background();
	title_bar();
    string s1,s2,Encrypted_Password;          //s1 -> string to store the UserName.  s2-> string to store the Password(original).   Encrypted_Password-> string to store and display Password on Screen.
    const char backspace = 8;
    int i=0,a=0;
    Text(550,300,"User Name :").setColor(themes[t_i].fore).imprint();
    Text(550,360,"Password  :").setColor(themes[t_i].fore).imprint();
    Rectangle UserName(700,300,150,30);   UserName.setColor(themes[t_i].fore);  // UserName.setFill(true);
    Rectangle PassWord(700,360,150,30);   PassWord.setColor(themes[t_i].fore);  // PassWord.setFill(true);
    Rectangle LoginBox(575,440,100,30);   LoginBox.setColor(themes[t_i].fore);   // LoginBox.setFill(true);
    Rectangle r4(708,440,110,30);           r4.setColor(themes[t_i].fore);       // r4.setFill(true);
    Text(575,440,"LOGIN").setColor(themes[t_i].fore).imprint();
    Text(708,440,"New User??").setColor(themes[t_i].fore).imprint();
    int x=0,y=0;
	int getc=getClick();
	x=getc/65536;
	y=getc%65536;
	if((x>655 && x<745) && (y>425 && y<455)) 
		return create_account();
    while(x<535 || x>625 || y<425 || y>455) {
        XEvent event;
        if(mouseButtonPressEvent(event)) {
            x = event.xbutton.x; y = event.xbutton.y;	}
            if( (x>625 && x<775) && (y>285 && y<315) )          i=1;
            else if( (x>625 && x<775) && (y>345 && y<375) )     i=2;
            else if( (x>535 && x<625) && (y>425 && y<455) )     i=3;
            else if( (x>655 && x<745) && (y>425 && y<455) )     i=4;
            else i=0;

        if(checkEvent(event) && keyPressEvent(event)) {
            char c = charFromEvent(event);
            if(i==1) {
                if(c == backspace){
                    a = textWidth(s1[s1.length()-2]);
                    s1 = cut_string(s1);
                    Rectangle r(627 + textWidth(s1) + a/2,300,a,30);
                    r.setColor(themes[t_i].back2);
                    r.setFill(true);
                    r.imprint();
                }
                else{
                    if(s1.length() < 16)
                        s1 = s1 + c;
                }
                Text(627+textWidth(s1)/2,300,s1).setColor(themes[t_i].fore).imprint();
            }
            if(i==2) {
                if(c == backspace) {
                    s2 = cut_string(s2);
                    Encrypted_Password = cut_string(Encrypted_Password);
                    Rectangle r(627 + textWidth(Encrypted_Password) + textWidth("*")/2,360,textWidth("*"),30);
                    r.setColor(themes[t_i].back2);
                    r.setFill(true);
                    r.imprint();
                }
                else {
                    if(s2.length()<16) {
                        s2 = s2 + c;
                        Encrypted_Password = Encrypted_Password + '*';
                    }
                }
                Text(627+textWidth(Encrypted_Password)/2,360,Encrypted_Password).setColor(themes[t_i].fore).imprint();
            }
          
            if(i==4);{
				
            }
        }

    }
    login(s1,s2,all);    
}

//Menu Page the one after login
void login_box(hybrid& all,short no_of_boxes=5,int height=40,int width=180,int end_x=550,int end_y=200) {
	closeCanvas();
	initCanvas("Menu",1280,720);
	background(); title_bar();
	
    int space_between_boxes = 20;
		while(true)	{
//General :        Rectangle(end_x + width/2,end_y + i*space_between_boxes + (2*i+1)*(height/2),width,height).imprint();
        Rectangle r1(end_x + width/2,end_y + 1*(height/2),width,height);
        r1.setColor(themes[t_i].fore);
        r1.imprint();
        Text(end_x + width/2,end_y + 1*(height/2),"COMPOSE").setColor(themes[t_i].fore).imprint();
        Rectangle r2(end_x + width/2,end_y + space_between_boxes + 3*(height/2),width,height);
        r2.setColor(themes[t_i].fore);
        r2.imprint();
        Text(end_x + width/2,end_y + space_between_boxes + 3*(height/2),"INBOX").setColor(themes[t_i].fore).imprint();
        Rectangle r3(end_x + width/2,end_y + 2*space_between_boxes + 5*(height/2),width,height);
        r3.setColor(themes[t_i].fore);
        r3.imprint();
        Text(end_x + width/2,end_y + 2*space_between_boxes + 5*(height/2),"SIGN OUT").setColor(themes[t_i].fore).imprint();
        Rectangle r4(end_x + width/2,end_y + 3*space_between_boxes + 7*(height/2),width,height);
        r4.setColor(themes[t_i].fore);
        r4.imprint();
        Text(end_x + width/2,end_y + 3*space_between_boxes + 7*(height/2),"EXIT").setColor(themes[t_i].fore).imprint();
       		update(all);
       		title_bar();
        	int v = getClick();
        	int xco = v/65536,yco = v%65536;
        	if(xco >= end_x && xco <= (end_x +width)) {
            	if(yco - end_y > 0 && yco - end_y < height)  send(all);
            	if(yco - end_y >height + 20 && yco - end_y < 2*height+20)    {inbox(all); closeCanvas();
	initCanvas("Menu",1280,720);
	background(); title_bar(); }
            	if(yco - end_y >2*height+40 && yco - end_y < 3*height+40) {  current.reset();unread=0,pos=0; return;}
            	if(yco - end_y >3*height+60 && yco - end_y < 4*height+60)    std::exit(0);
        	}
		}
}

void create_layout() {
    Rectangle ToBox (720,120,1040,30);
   	ToBox.setColor(themes[t_i].fore);
    ToBox.imprint();
    Rectangle SubjectBox (720,170,1040,30);
    SubjectBox.setColor(themes[t_i].fore);
    SubjectBox.imprint();
    Rectangle MsgBox (700,440,1100,430);
    MsgBox.setColor(themes[t_i].fore);
    MsgBox.imprint();
    Rectangle Send (320,690,110,35);
    Send.setColor(themes[t_i].fore);
    Send.setFill(true);
    Send.imprint();

    Text (75,120,"To :").setColor(themes[t_i].fore).imprint();
    Text (75,170,"Subject :").setColor(themes[t_i].fore).imprint();
    Text (75,250,"Sandesh :").setColor(themes[t_i].fore).imprint();
    Text (320,690,"SEND").setColor(themes[t_i].back1).imprint();
}

void input_msg(string &to,string &subject,string &msg) {
    int x=0,y=0,i=0,line_number=0,enterno=0;
    string dummy;
    const char backspace = 8;
    const char tab = 9; 
    const char enter = 13;
    while(x<265 || x>375 || y<672 || y>707) {
        XEvent event;
        if(mouseButtonPressEvent(event)) {
            x = event.xbutton.x; y = event.xbutton.y;
            if( (x>200 && x<1240) && (y>105 && y<135) )         i=1;
            else if( (x>200 && x<1240) && (y>155 && y<185) )    i=2;
            else if( (x>150 && x<1250) && (y>225 && y<655) )    i=3;
            else if( (x>265 && x<375) && (y>672 && y<707) )     i=4;
            else i=0;

        }
        if(checkEvent(event) && keyPressEvent(event)) {
            char c = charFromEvent(event);
            if(c==tab) {
                if(i<5)  i++;
            }
            if(i==4) {
                if(to.length()==0);  //error
                if(msg.length()==0); //error
                if(to.length()!=0 && msg.length()!=0)     return;
            }
            if(i==1) {
                if(c == backspace) {
                    int a = textWidth(to[to.length()-1]);
                    to = cut_string(to);
                    Rectangle r(202 + textWidth(to) + a/2,120,a,28);
                    r.setColor(themes[t_i].back2);
                    r.setFill(true);
                    r.imprint();
                }
                else {
                    if(to.length() < 16)
                        to = to + c;
                }
                Text(202+textWidth(to)/2,120,to).setColor(themes[t_i].fore).imprint();
            }
            if(i==2) {
                if(c == backspace) {
                    int a = textWidth(subject[subject.length()-1]);
                    subject = cut_string(subject);
                    Rectangle r(202 + textWidth(subject) + a/2,170,a,28);
                    r.setColor(themes[t_i].back2);
                    r.setFill(true);
                    r.imprint();
                }
                else {
                    if(subject.length() < 100)
                        subject = subject + c;
                }
                Text(202+textWidth(subject)/2,170,subject).setColor(themes[t_i].fore).imprint();
            }

            if(i==3) {
                if(msg.length()%150 == 0 )  line_number++;
                if(c == backspace) {
                    int a = textWidth(dummy[dummy.length()-1]);
                    msg = cut_string(msg);
                    dummy = cut_string(dummy);
                    Rectangle r(154 + textWidth(dummy) + a/2,220 + 30*line_number,a,28);
                    if(dummy.length() == 0)  line_number--;
                    r.setColor(themes[t_i].back2);
                    r.setFill(true);
                    r.imprint();
                }
                else {
                    if(msg.length() < 500)
                        msg = msg + c;
                    if(c == enter){
                        line_number++;   dummy = "";    enterno++; }
                    else
                        dummy = msg.substr(msg.length() - msg.length()%150,msg.length()%150);

                }
                Text(155+textWidth(dummy)/2,220 + 30*line_number,dummy).setColor(themes[t_i].fore).imprint();
            }
        }
    }
}

void send(hybrid& all) {
	ofstream mf;
	mf.open(data_add,ios::out|ios::binary|ios::app);
	if(!mf)	{
		error("An Error Occured", "SENDING FAILED");
		if(error())
			login_box(all,5,40,180,550,200);
	}
	closeCanvas();
	initCanvas("Compose",1280,720);
	background();
	title_bar();
	create_layout();
	string to,sub,ms;
	input_msg(to,sub,ms);
	sub=sub + " : ";
	ms=sub+ms;
	msg_data m;
	m.create(gettime(),current.id,to,ms,0);
	mf.write((char*)&m,sizeof(msg_data));
	mf.close();
	closeCanvas();
	initCanvas("Compose",1280,720);
	background();
	title_bar();
	error("Success!!", "Message Submitted Successfully");
	if(error())	{
		login_box(all,5,40,180,550,200);
	}
}


void inbox(hybrid& all,size_t index) {
	closeCanvas();
	initCanvas("Inbox",1280,720);
	background();
	title_bar();
	Rectangle r(550,375,975,510);
	r.setFill(1);
	r.setColor(themes[t_i].back1);
	r.imprint();
	size_t i=index;
	int y=45;
	string s;
	Text(100,150,"Sr.no").setColor(themes[t_i].fore).imprint();
	Text(200,150,"Date").setColor(themes[t_i].fore).imprint();
	Text(400,150,"From").setColor(themes[t_i].fore).imprint();
	Text(500+textWidth("Body")/2,150,"Body").setColor(themes[t_i].fore).imprint();
	Text(1000,150,"Read").setColor(themes[t_i].fore).imprint();
	while(i<index+10 && i<all.size() ) {
		Text(100,150+y,i).setColor(themes[t_i].fore).imprint();
		Text(200,150+y,all[i]->key.date).setColor(themes[t_i].fore).imprint();
		Text(400,150+y,all[i]->key.from).setColor(themes[t_i].fore).imprint();
		s=all[i]->key.body;
		if(s.length()>40)
			Text(500+textWidth(s.substr(0,40))/2,150+y,s.substr(0,40)).setColor(themes[t_i].fore).imprint();
		else
			Text(500+textWidth(s)/2,150+y,s).setColor(themes[t_i].fore).imprint();
		Text(1000,150+y,all[i]->key.read_flag).setColor(themes[t_i].fore).imprint();
		i++;
		y=y+45;
	}
}

void inbox(hybrid& all) {
    int size=all.size();
    int i=0;
    int no_pages=size/10;
    int x=0,y=0,p;
    Rectangle next(1150,150,100,30);
    next.setColor(themes[t_i].fore);
    Text Nt(1150,150,"Next");
    Nt.setColor(themes[t_i].fore);
    Rectangle prev(1150,200,100,30);
    prev.setColor(themes[t_i].fore);
    Text Pv(1150,200,"Prev");
    Pv.setColor(themes[t_i].fore);
    Rectangle close(1150,300,100,30);
    Rectangle Searc(1150,250,100,30);
    Searc.setColor(themes[t_i].fore);
    Text t(1150,250,"Search");
    t.setColor(themes[t_i].fore);
    close.setColor(themes[t_i].fore);
    Text Cl(1150,300,"Close");
    Cl.setColor(themes[t_i].fore);
    inbox(all,0);
    close.imprint();
    Cl.imprint();
    if(i<no_pages)
    	next.imprint(),Nt.imprint();
    while(x<1100 || x>1200 || y<285 || y>315) {
    	if(i>0)
    		prev.imprint(),Pv.imprint();
    	if(i<no_pages)
    		next.imprint(),Nt.imprint();
    	close.imprint(),Cl.imprint();
    	Searc.imprint(); t.imprint();
        p=getClick();
        x=p/65536; y=p%65536;
        if(x>1100 && x<1200 && y>135 && y<165) {
            if(i<no_pages) {
            i++;
            inbox(all,(i*10));
            }
        }
        else if(x>1100 && x<1200 && y>185 && y<215) {
            if(i>0) {
            i--;
            inbox(all,(i*10));
            }
        }
        else if(x>1100 && x<1200 && y>235 && y<265)	{
        	search_msg(all);
       	}
       	else if(x>70 && x<1000 && y>172 && y<622)	{
       		int ind=(y-172)/45;
       		read_msg(all[ind]->key);
       		inbox(all,i);
       	}
  
    }
    return;
}



int error()	{
	int x,y,p;
	p=getClick();
	x=p/65536; y=p%65536;
	while(!(x<470 && x>430 && y<330 && y>290)) {
		p=getClick();
		x=p/65536; y=p%65536;
	}
	return 1;
}

void error(string a,string s) {
	int w=100;
	Rectangle r(640,360,420,w);
	r.setColor(themes[t_i].fore);
	r.setFill(1);
	
	r.imprint();
	Rectangle r2(640,360,418,w-2);
	r2.setColor(themes[t_i].back1);
	r2.setFill(1);

	r2.imprint();
	Rectangle r3(640,360-w/2,420,40);
	r3.setColor(themes[t_i].tint);
	r3.setFill(1);

	r3.imprint();
	Text(640,360-w/2,a).setColor(themes[t_i].fore2).imprint();
	Text(640,360,s).setColor(themes[t_i].fore).imprint();
	Rectangle xbut(450,360-w/2,40,40);
	xbut.setColor(red);
	xbut.setFill(1);

	xbut.imprint();
	int m=8;
	Line(450-m,360-w/2-m,450+m,360-w/2+m).setColor(themes[t_i].back1).imprint();
	Line(450+m,360-w/2-m,450-m,360-w/2+m).setColor(themes[t_i].back1).imprint();
}

void display(string from,string body){
	Text (75,120,"From :").setColor(themes[t_i].fore).imprint();
    Text (75,170,"Subject :").setColor(themes[t_i].fore).imprint();
    Text (75,250,"Sandesh :").setColor(themes[t_i].fore).imprint();
    string subject,linespliter;
    int line_number = 0;
    for(size_t i=0;i<body.length();i++){
        if(body[i] == ':'){
            body = body.substr(i+1,body.length()-i-1);
            break;
        }
        subject = subject + body[i];
    }
    Text(204 + textWidth(from)/2,120,from).setColor(themes[t_i].fore).imprint();
    Text(204 + textWidth(subject)/2,170,subject).setColor(themes[t_i].fore).imprint();
    while(body!=""){
        if(body.length()>150){
            linespliter = body.substr(0,150);
            body = body.substr(150,body.length()-150);
            Text(650,250 + 30*line_number,linespliter).setColor(themes[t_i].fore).imprint();
        }
        else{
            linespliter = body;
            Text(170 + textWidth(body)/2 ,250 + 30*line_number,linespliter).setColor(themes[t_i].fore).imprint();
            body = "";
        }

        line_number++;
    }
}

void search_msg(hybrid &all) {
	closeCanvas();
	initCanvas("Search",1280,720);
	background();
	title_bar();
    int i=0,x=0,y=0,a=0;
    string s1;
    const char backspace = 8;
    Text(550,320,"Search here :").setColor(themes[t_i].fore).imprint();
    Rectangle search(700,320,160,30);   search.setColor(themes[t_i].fore);
    Rectangle Submit(650,400,100,30);   Submit.setColor(themes[t_i].fore);
    Submit.imprint();
    Text(650,400,"Submit").setColor(themes[t_i].fore).imprint();
    while(true) {
    XEvent event;
    if(mouseButtonPressEvent(event)){
        x = event.xbutton.x; y = event.xbutton.y;
        if( (x>625 && x<775) && (y>305 && y<335) )     i=1;
        else if( (x>600 && x<700) && (y>385 && y<415) )     break;
        else i=0;
    }
    if(checkEvent(event) && keyPressEvent(event)){
        char c = charFromEvent(event);
             
        if(i==1) {
             if(c == backspace) {
                 a = textWidth(s1[s1.length()-2]);
                 s1 = cut_string(s1);
                 Rectangle r(625 + textWidth(s1) + a/2,320,a,30);
                 r.setColor(themes[t_i].back1);
                 r.setFill(true);
                 r.imprint(); 
             }
        else {
             if(s1.length() < 16)
                 s1 = s1 + c;
         }
         Text (625+textWidth(s1)/2,320,s1).setColor(themes[t_i].fore).imprint();
         }
    }
    }
    hybrid h=all.search(s1);
    inbox(h);
}


void read_msg(msg &m)	{
	closeCanvas();
	initCanvas("Message",1280,720);
	background();
	title_bar();	
	display(m.from,m.body);	
	Rectangle Back (320,690,110,35);
    Back.setColor(themes[t_i].fore);
    Back.imprint();
    Text (320,690,"BACK").setColor(themes[t_i].fore).imprint();
    fstream mf;
    mf.open(data_add,ios::in|ios::out|ios::binary);
    if(!mf)	{
    	error("Error Occurred!!!", "Unable to Connect Database!!!");
    	if(error())
    		return;
    }
    msg_data temp;
    mf.read((char*)&temp,sizeof(temp));
    while(mf)	{
    	msg b(temp);
    	if(b==m)	{
    		temp.read_flag=1;
    		mf.seekp(mf.tellg()-sizeof(msg_data),ios::beg);
    		mf.write((char*)&temp,sizeof(temp));
    		break;
    	}
    mf.read((char*)&temp,sizeof(temp));
    }
    mf.close();
    if(m.read_flag==0)	{
    	unread--;
    	m.read_flag=1;
    }
    int x,y,p;
    p=getClick();
    x=p/65536; y=p%65536;
    while(!(x>265 && x<375 && y>672 && y<708))	{
    	p=getClick();
    	x=p/65536; y=p%65536;
    }
    return;
}
	
	


