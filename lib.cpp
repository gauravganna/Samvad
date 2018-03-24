#include<simplecpp>
#include <ctime>


void strcpy(char a[], string& b);
void strcpy(string& b, char a[]); 

void strcpy( string& b,char a[]) {
	size_t i=0;
	while(i<b.length()) {	
		a[i]=b[i];
		i++;
	}
	a[i]='\0';
}

void strcpy(char a[], string& b) {
	int i=0;
	while(a[i]!='\0') {	
		b=b+a[i];
		i++;
	}
}



 
bool strcmp(char s1[], char s2[]) {
	int i=0;
	while(s1[i]!='\0' && s2[i]!='\0') {
		if(s1[i]!=s2[i])
			return 0;
		i++;
	}
	if(s1[i]=='\0' && s2[i]=='\0')
		return 1;
	return 0;
}


string cut_string(string s) {        //Function that trims the last character of a string if string is non empty else do nothing.
    if(s.length() == 0) return s;
    return s.substr(0,s.length()-1);
}

string gettime() {
   	time_t now = time(0);            // current date/time based on current system
   	string time = ctime(&now);       // convert now to string form
   	string t[5];
   	int j=0;
   	for(size_t i=0;i<time.length();i++) {
        if(time[i]== ' ')   j++;
		else   t[j] = t[j] + time[i];
   	}

   	t[3] = t[3].substr(0,t[3].length()-3);
   	t[4] = t[4].substr(0,t[4].length()-1);
   	string month_in_no = t[1];


   	if(t[1] == "Jan" )    month_in_no = "01";
    else if(t[1] == "Feb" )    month_in_no = "02";
    else if(t[1] == "Mar" )    month_in_no = "03";
    else if(t[1] == "Apr" )    month_in_no = "04";
    else if(t[1] == "May" )    month_in_no = "05";
    else if(t[1] == "Jun" )    month_in_no = "06";
    else if(t[1] == "Jul" )    month_in_no = "07";
    else if(t[1] == "Aug" )    month_in_no = "08";
    else if(t[1] == "Sep" )    month_in_no = "09";
    else if(t[1] == "Oct" )    month_in_no = "10";
    else if(t[1] == "Nov" )    month_in_no = "11";
    else if(t[1] == "Dec" )    month_in_no = "12";


    string date;
    date = t[2] + "/" + month_in_no + "/" + t[4] + " " + t[3];
    return date;

}



