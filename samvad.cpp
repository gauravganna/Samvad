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
#define back1 COLOR(15,15,15)			//dark background
#define back2 COLOR(25,25,25)
#define fore COLOR (255,255,255)
#define fore2 COLOR (255,255,255)
#define tint COLOR (23,123,15)
#define acc_add "acc.dat"
#define data_add "database.dat"


void inbox(hybrid& all);//Controls & Handles inbox's Clicks and inbox for a list 'all'			
void create_account();	//Crea
void background();		//Sets a background Color
void title_bar();		//Creates the Title Bar
void update(hybrid& all);	//Rechecks for messages from the database file
int error();				//Checks and waits till the user clicks on the close Button for the error box
void error(string,string);	//Prints an error box with 1st string on titlebar and 2nd on the dialog box
void login(hybrid& all,string,string);	//Checks for a username and password and inserts msgs in a;;
void login(hybrid& all);	//creates the login page, takes input and calls the other login function to verify
void send(hybrid& all);		//used to send msgs. creates a new object msg, takes input and writes to the database
void inbox(hybrid& all,int index);	//this one prints the inbox layout, prints all msgs from serial no. 'index' to 'index+10'
void login_box(hybrid& all,short no_of_boxes,int height,int width,int end_x,int end_y);//Main menu after login
void create_layout();	//creates layout for sending msg
void input_msg(string &to,string &subject,string &msg);	//takes input for sending msg then calls send to do the backend work
void read_msg(msg&);		//prints msg in a display view
void search_msg(hybrid &all);	//searchs in 'all' and creates a temp hybrid list and calls inbox for the same.

user current;			//curent logged in user detailss
int unread=0;			//no. unreads for currrent user
long long pos=0;		//last read position used when update() is called so that it does not re-check for new msgs in the area already checked once.

int main() {
	intro();
	initCanvas("intro",1280,720);
	background();
	title_bar();
	
	while(true)	{
		hybrid msgs;
    	login(msgs);
    }
	return 0;
}

void background() {
    Rectangle r(640,360,1280,720);
    r.setFill(1);
    r.setColor(back2);
    r.imprint();
}

void title_bar() {
	int h=40 , m=20, r=10;
	Rectangle bar(640,h/2,1280,h);
	bar.setColor(tint);
	bar.setFill(1);
	bar.imprint();
	if(current.id==" ")
		return;
	if(current.id!="\0") {
		Text(1220-(textWidth(current.Name+"[  ]")/2),2*h/3,current.Name).setColor(fore).imprint();
		Text(1230-r,2*h/3,unread).setColor(fore).imprint();
		Circle(1230-r,2*h/3,r).setColor(fore).imprint();
		Text(1230-(textWidth("Signed in as:")/2),h/4, "Signed in as:").setColor(fore).imprint();
	}
	else	
		Text(1220-(textWidth("Not Signed in")/2),h/3, "Not Signed in").setColor(fore).imprint();
}

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

//user_id, password verification remaining
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
    Text(550,200,"User ID :").setColor(fore).imprint();
    Text(550,260,"Password :").setColor(fore).imprint();
    Text(550,320,"Confirm Password :").setColor(fore).imprint();
    Text(550,380,"Phone No. :").setColor(fore).imprint();
    Text(550,440,"Name :").setColor(fore).imprint();
    Rectangle UserName(700,200,160,30);   UserName.setColor(fore);
    Rectangle PassWord(700,260,160,30);   PassWord.setColor(fore);
    Rectangle Confirm(700,320,160,30);   Confirm.setColor(fore);
    Rectangle Phone(700,380,160,30);   Phone.setColor(fore);
    Rectangle Name(700,440,160,30);   Name.setColor(fore);
    Rectangle Submit(775,500,100,30);   Submit.setColor(fore);
    Text(775,500,"Submit").setColor(fore).imprint();
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
            Text(625+textWidth(s1)/2,200,s1).setColor(fore).imprint();
            Text(625+textWidth(Encrypted_Password)/2,260,Encrypted_Password).setColor(fore).imprint();
            Text(625+textWidth(Encrypted_Password2)/2,320,Encrypted_Password2).setColor(fore).imprint();
            Text(625+textWidth(s4)/2,380,s4).setColor(fore).imprint();
            Text(625+textWidth(s5)/2,440,s5).setColor(fore).imprint();          
        }
        if(checkEvent(event) && keyPressEvent(event)) {
            char c = charFromEvent(event);
             
            if(i==1) {
                if(c == backspace) {
                    a = textWidth(s1[s1.length()-2]);
                    s1 = cut_string(s1);
                    Rectangle r(625 + textWidth(s1) + a/2,200,a,30);
                    r.setColor(back2);
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
                Text(625+textWidth(s1)/2,200,s1).setColor(fore).imprint();
            }
            if(i==2) {
                if(c == backspace) {
                    s2 = cut_string(s2);
                    Encrypted_Password = cut_string(Encrypted_Password);
                    Rectangle r(625 + textWidth(Encrypted_Password) + textWidth("*")/2,260,textWidth("*"),30);
                    r.setColor(back2);
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
                Text(625+textWidth(Encrypted_Password)/2,260,Encrypted_Password).setColor(fore).imprint();
            }
            if(i==3) {
                if(c == backspace) {
                    s3 = cut_string(s3);
                    Encrypted_Password2 = cut_string(Encrypted_Password2);
                    Rectangle r(625 + textWidth(Encrypted_Password2) + textWidth("*")/2,320,textWidth("*"),30);
                    r.setColor(back2);
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
                Text (625+textWidth(Encrypted_Password2)/2,320,Encrypted_Password2).setColor(fore).imprint();
            }
            if(i==4) {
                if(c == backspace) {
                    a = textWidth(s1[s1.length()-2]);
                    s4 = cut_string(s4);
                    Rectangle r(625 + textWidth(s4) + a/2,380,a,30);
                    r.setColor(back2);
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
                Text(625+textWidth(s4)/2,380,s4).setColor(fore).imprint();
            }
            if(i==5) {
            	
                if(c == backspace) {
                    a = textWidth(s1[s1.length()-2]);
                    s5 = cut_string(s5);
                    Rectangle r(625 + textWidth(s5) + a/2,440,a,30);
                    r.setColor(back2);
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
                Text(625+textWidth(s5)/2,440,s5).setColor(fore).imprint();
            }
        }
    }
    //Password Verification remaining #ganna
    user b(s1,s2,s5,s4);
    usr u;
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
    Text(550,300,"User Name :").setColor(fore).imprint();
    Text(550,360,"Password  :").setColor(fore).imprint();
    Rectangle UserName(700,300,150,30);   UserName.setColor(fore);  // UserName.setFill(true);
    Rectangle PassWord(700,360,150,30);   PassWord.setColor(fore);  // PassWord.setFill(true);
    Rectangle LoginBox(575,440,100,30);   LoginBox.setColor(fore);   // LoginBox.setFill(true);
    Rectangle r4(708,440,110,30);           r4.setColor(fore);       // r4.setFill(true);
    Text(575,440,"LOGIN").setColor(fore).imprint();
    Text(708,440,"New User??").setColor(fore).imprint();
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

        //}
        if(checkEvent(event) && keyPressEvent(event)) {
            char c = charFromEvent(event);
            if(i==1) {
                if(c == backspace){
                    a = textWidth(s1[s1.length()-2]);
                    s1 = cut_string(s1);
                    Rectangle r(627 + textWidth(s1) + a/2,300,a,30);
                    r.setColor(back2);
                    r.setFill(true);
                    r.imprint();
                }
                else{
                    if(s1.length() < 16)
                        s1 = s1 + c;
                }
                Text(627+textWidth(s1)/2,300,s1).setColor(fore).imprint();
            }
            if(i==2) {
                if(c == backspace) {
                    s2 = cut_string(s2);
                    Encrypted_Password = cut_string(Encrypted_Password);
                    Rectangle r(627 + textWidth(Encrypted_Password) + textWidth("*")/2,360,textWidth("*"),30);
                    r.setColor(back2);
                    r.setFill(true);
                    r.imprint();
                }
                else {
                    if(s2.length()<16) {
                        s2 = s2 + c;
                        Encrypted_Password = Encrypted_Password + '*';
                    }
                }
                Text(627+textWidth(Encrypted_Password)/2,360,Encrypted_Password).setColor(fore).imprint();
            }
          
            if(i==4);{
				
            }
        }

    }
    login(s1,s2,all);    
}

void login_box(hybrid& all,short no_of_boxes=5,int height=40,int width=180,int end_x=550,int end_y=200) {
	closeCanvas();
	initCanvas("Menu",1280,720);
	background(); title_bar();
	
    int space_between_boxes = 20;
		while(true)	{
//General :        Rectangle(end_x + width/2,end_y + i*space_between_boxes + (2*i+1)*(height/2),width,height).imprint();
        Rectangle r1(end_x + width/2,end_y + 1*(height/2),width,height);
        r1.setColor(fore);
        r1.imprint();
        Text(end_x + width/2,end_y + 1*(height/2),"COMPOSE").setColor(fore).imprint();
        Rectangle r2(end_x + width/2,end_y + space_between_boxes + 3*(height/2),width,height);
        r2.setColor(fore);
        r2.imprint();
        Text(end_x + width/2,end_y + space_between_boxes + 3*(height/2),"INBOX").setColor(fore).imprint();
        Rectangle r3(end_x + width/2,end_y + 2*space_between_boxes + 5*(height/2),width,height);
        r3.setColor(fore);
        r3.imprint();
        Text(end_x + width/2,end_y + 2*space_between_boxes + 5*(height/2),"SIGN OUT").setColor(fore).imprint();
        Rectangle r4(end_x + width/2,end_y + 3*space_between_boxes + 7*(height/2),width,height);
        r4.setColor(fore);
        r4.imprint();
        Text(end_x + width/2,end_y + 3*space_between_boxes + 7*(height/2),"EXIT").setColor(fore).imprint();
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
   	ToBox.setColor(fore);
    ToBox.imprint();
    Rectangle SubjectBox (720,170,1040,30);
    SubjectBox.setColor(fore);
    SubjectBox.imprint();
    Rectangle MsgBox (700,440,1100,430);
    MsgBox.setColor(fore);
    MsgBox.imprint();
    Rectangle Send (320,690,110,35);
    Send.setColor(fore);
    Send.setFill(true);
    Send.imprint();

    Text (75,120,"To :").setColor(fore).imprint();
    Text (75,170,"Subject :").setColor(fore).imprint();
    Text (75,250,"Sandesh :").setColor(fore).imprint();
    Text (320,690,"SEND").setColor(back1).imprint();
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
                    r.setColor(back2);
                    r.setFill(true);
                    r.imprint();
                }
                else {
                    if(to.length() < 16)
                        to = to + c;
                }
                Text(202+textWidth(to)/2,120,to).setColor(fore).imprint();
            }
            if(i==2) {
                if(c == backspace) {
                    int a = textWidth(subject[subject.length()-1]);
                    subject = cut_string(subject);
                    Rectangle r(202 + textWidth(subject) + a/2,170,a,28);
                    r.setColor(back2);
                    r.setFill(true);
                    r.imprint();
                }
                else {
                    if(subject.length() < 100)
                        subject = subject + c;
                }
                Text(202+textWidth(subject)/2,170,subject).setColor(fore).imprint();
            }

            if(i==3) {
                if(msg.length()%150 == 0 )  line_number++;
                if(c == backspace) {
                    int a = textWidth(dummy[dummy.length()-1]);
                    msg = cut_string(msg);
                    dummy = cut_string(dummy);
                    Rectangle r(154 + textWidth(dummy) + a/2,220 + 30*line_number,a,28);
                    if(dummy.length() == 0)  line_number--;
                    r.setColor(back2);
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
                Text(155+textWidth(dummy)/2,220 + 30*line_number,dummy).setColor(fore).imprint();
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
		return;
	}
}

void inbox(hybrid& all) {
    int size=all.size();
    int i=0;
    int no_pages=size/10;
    int x=0,y=0,p;
    Rectangle next(1150,150,100,30);
    next.setColor(fore);
    Text Nt(1150,150,"Next");
    Nt.setColor(fore);
    Rectangle prev(1150,200,100,30);
    prev.setColor(fore);
    Text Pv(1150,200,"Prev");
    Pv.setColor(fore);
    Rectangle close(1150,300,100,30);
    close.setColor(fore);
    Text Cl(1150,300,"Close");
    Cl.setColor(fore);
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
       	else if(x>70 && x<1000 && y>172 && y<622)	{
       		int ind=(y-172)/45;
       		read_msg(all[ind]->key);
       		inbox(all,i);
       	}
  
    }
    return;
}


void inbox(hybrid& all,int index) {
	closeCanvas();
	initCanvas("Inbox",1280,720);
	background();
	title_bar();
	Rectangle r(550,375,975,510);
	r.setFill(1);
	r.setColor(back1);
	r.imprint();
	int i=index,y=45;
	string s;
	Text(100,150,"Sr.no").setColor(fore).imprint();
	Text(200,150,"Date").setColor(fore).imprint();
	Text(400,150,"From").setColor(fore).imprint();
	Text(500+textWidth("Body")/2,150,"Body").setColor(fore).imprint();
	Text(1000,150,"Read").setColor(fore).imprint();
	while(i<index+10 && i<all.size() ) {
		Text(100,150+y,i).setColor(fore).imprint();
		Text(200,150+y,all[i]->key.date).setColor(fore).imprint();
		Text(400,150+y,all[i]->key.from).setColor(fore).imprint();
		s=all[i]->key.body;
		if(s.length()>40)
			Text(500+textWidth(s.substr(0,40))/2,150+y,s.substr(0,40)).setColor(fore).imprint();
		else
			Text(500+textWidth(s)/2,150+y,s).setColor(fore).imprint();
		Text(1000,150+y,all[i]->key.read_flag?"Yes":"No").setColor(fore).imprint();
		i++;
		y=y+45;
	}
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
	r.setColor(fore);
	r.setFill(1);
	
	r.imprint();
	Rectangle r2(640,360,418,w-2);
	r2.setColor(back1);
	r2.setFill(1);

	r2.imprint();
	Rectangle r3(640,360-w/2,420,40);
	r3.setColor(tint);
	r3.setFill(1);

	r3.imprint();
	Text(640,360-w/2,a).setColor(fore).imprint();
	Text(640,360,s).setColor(fore).imprint();
	Rectangle xbut(450,360-w/2,40,40);
	xbut.setColor(red);
	xbut.setFill(1);

	xbut.imprint();
	int m=8;
	Line(450-m,360-w/2-m,450+m,360-w/2+m).setColor(back1).imprint();
	Line(450+m,360-w/2-m,450-m,360-w/2+m).setColor(back1).imprint();
}

void display(string from,string body){
	Text (75,120,"From :").setColor(fore).imprint();
    Text (75,170,"Subject :").setColor(fore).imprint();
    Text (75,250,"Sandesh :").setColor(fore).imprint();
    string subject,linespliter;
    int line_number = 0;
    for(int i=0;i<body.length();i++){
        if(body[i] == ':'){
            body = body.substr(i+1,body.length()-i-1);
            break;
        }
        subject = subject + body[i];
    }
    Text(204 + textWidth(from)/2,120,from).setColor(fore).imprint();
    Text(204 + textWidth(subject)/2,170,subject).setColor(fore).imprint();
    while(body!=""){
        if(body.length()>150){
            linespliter = body.substr(0,150);
            body = body.substr(150,body.length()-150);
            Text(650,250 + 30*line_number,linespliter).setColor(fore).imprint();
        }
        else{
            linespliter = body;
            Text(170 + textWidth(body)/2 ,250 + 30*line_number,linespliter).setColor(fore).imprint();
            body = "";
        }

        line_number++;
    }
}

void read_msg(msg &m)	{
	closeCanvas();
	initCanvas("Message",1280,720);
	background();
	title_bar();	
	display(m.from,m.body);	
	Rectangle Back (320,690,110,35);
    Back.setColor(fore);
    Back.imprint();
    Text (320,690,"BACK").setColor(fore).imprint();
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
	
	


