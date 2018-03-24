
struct node	{
  	node*left;
    node*right;
    msg key;

    node(msg v) {
 	   left=NULL;
       right=NULL;
       key=v;
	}
};


struct hybrid {
    vector <node*> root;

    hybrid(const hybrid&);
    void push(msg);
    void insert(msg);
    void push_back(msg);
    hybrid search(const string);
    node*& operator[](int n) {
        return root[n];
    }
    size_t size() {
    	return root.size();
    }
	hybrid() {
	}
	~hybrid()	{
		for(size_t i=0; i<root.size(); i++	)
			delete root[i];
	}
};


void hybrid::push_back(msg m)	{
	node *ptr=new node(m);
	root.push_back(ptr);
}


void hybrid::insert(msg v) {
    if(root.size()==0) {
      	node* ptr=new node(v);
        root.push_back(ptr);
        return;
	}
    node *ptr=root.front(),*p;
    while(ptr!=NULL) {
        p=ptr;
        if(v.from<ptr->key.from)
        ptr=ptr->left;
        else
	        ptr=ptr->right;
   	}
    ptr=new node(v);
    root.push_back(ptr);
    if(v.from<p->key.from)
      	p->left=root.back();
    else
        p->right=root[root.size()-1];
}

void find(string s,node * ptr, hybrid& a){
    if(ptr == NULL) return;
    if(ptr->key.from.find(s) == 0)     a.push_back(ptr->key);
    if(ptr->right!= NULL &&(ptr->right->key.from.find(s) ==0 || ptr->right->key.from < s)  )   find(s,ptr->right,a);
    if(ptr->left!= NULL && (ptr->left->key.from.find(s) == 0 || ptr->left->key.from > s)   )   find(s,ptr->left,a);

}

hybrid hybrid::search(string s) {
	hybrid a;
	node *ptr=root.front();
	find(s,ptr,a);
	return a;
}

