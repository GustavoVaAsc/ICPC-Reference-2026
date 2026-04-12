mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#define ll long long

struct TreapNode{
    ll key, pr, sz;
    TreapNode *l, *r;
};

typedef TreapNode* Treap;

int getSize(Treap &t){
    return t ? t->sz : 0;
}

void updateSize(Treap &t){
    if (t) t->sz = 1 + getSize(t->l) + getSize(t->r);
}

void split(Treap& t, ll k, Treap &l, Treap  &r){
    if(not t) l = r = nullptr;

    else if(k < t->key){
        split(t->l,k,l, t->l);
        r = t;
        updateSize(r);
    }else{
        split(t->r,k,t->r,r);
        l = t;
        updateSize(l);
    }
}

void insert(Treap& t, Treap a){
    if(not t) t=a;
    else if(a->pr > t->pr){
        split(t, a->key, a->l, a->r);
        t = a;
    }else{
        if(a->key < t-> key) insert(t->l,a);
        else insert(t->r,a);
    }
    updateSize(t);
}

void merge(Treap &t, Treap l, Treap r){
    if(not l) t = r;
    else if(not r) t = l;

    else if(l->pr > r->pr){
        merge(l->r, l->r,r);
        t=l;
        updateSize(t);
    }else{
        merge(r->l,l,r->l);
        t=r;
        updateSize(t);
    }
}

void erase(Treap &t, ll k){
    if(not t) return;
    if(t->key == k) merge(t,t->l, t->r);
    
    else{
        if(k<t->key) erase(t->l,k);
        else erase(t->r, k);
    }
    updateSize(t);
}

bool find(Treap& t, ll k){
    if (not t) return false;
    if(t->key == k) return true;
    if(k<t->key) return find(t->l,k);
    return find(t->r,k);
}

void insertValue(Treap &t, ll k){
    if(not find(t,k)){
        Treap new_node = new TreapNode {k,rng(), 0,nullptr, nullptr};
        insert(t, new_node);
    }
}

ll getKth(Treap &t, int k){
    if(!t || k<=0 || k>getSize(t)) return 0;
    int leftSize = getSize(t->l);
    if(k == leftSize+1) return t->key;
    if(k <= leftSize) return getKth(t->l,k);
    return getKth(t->r, k-leftSize-1);
}
