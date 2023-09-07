#include<iostream>

using namespace std;

#define bool int
#define True 1
#define TRUE 1
#define true 1
#define FALSE 0
#define false 0
#define False 0

template<class T>
class TMList
{
public :
virtual void add(T data,bool *success)=0;
virtual void insertAt(int index,T data,bool *success)=0;
virtual T removeAt(int index,bool *success)=0;
virtual void update(int index,T data,bool *success)=0;
virtual T get(int index,bool *success) const=0;
virtual void removeAll()=0;
virtual void clear()=0;
virtual int getSize() const=0;
virtual void display()=0;
};

//************************************************************
template<class T>
class Iterator 
{
private : 
Iterator *iterator;
public :

Iterator()
{
this->iterator=NULL;
}

Iterator(Iterator *iterator)
{
this->iterator=iterator;
}

Iterator(const Iterator &other)
{
this->iterator=other.iterator;
}

virtual int hasMoreElements()
{
if(this->iterator!=NULL)this->iterator->hasMoreElements();
}
virtual T next()
{
if(this->iterator!=NULL)this->iterator->next();
}
};

template<class T>
class Iterable
{
public :
virtual Iterator<T> getIterator()=0;
};

template<class T>
class TMForwardList : public TMList<T>, public Iterable<T>
{
private:
class Node
{
public :
T data;
Node *next;
};

public:

class TMForwardListIterator : public Iterator<T>
{
private:
Node *ptr;
public:

void init(Node *ptr)
{
this->ptr=ptr;
}

int hasMoreElements()
{
if(this->ptr!=NULL) return true;
return false;
}

T next()
{
T num=this->ptr->data;
this->ptr=this->ptr->next;
return num;
}
};
private: 
TMForwardListIterator tmForwardListIterator;
public:

Iterator<T> getIterator()
{
tmForwardListIterator.init(this->start);
return Iterator<T>(&tmForwardListIterator);
}

int size;
Node *start;
Node *end;
TMForwardList();
TMForwardList(int bufferSize);
TMForwardList(const TMForwardList &other);
TMForwardList(const TMList<T> &other);
TMForwardList & operator=(const TMForwardList &other);
TMForwardList & operator=(const TMList<T> &other);
void operator+=(const TMForwardList & other);
void operator+=(const TMList<T> & other);
T operator[](int index);
TMForwardList operator+(const TMForwardList &other);
virtual ~TMForwardList();
void display();
void add(T data,bool *success);
void insertAt(int index,T data,bool *success);
T removeAt(int index,bool *success);
void update(int index,T data,bool *success);
T get(int index,bool *success) const;
void removeAll();
void clear();
int getSize() const;
};

template<class T>
TMForwardList<T>::TMForwardList()
{
this->size=0;
this->start=NULL;
end==NULL;
}
template<class T>
TMForwardList<T>::TMForwardList(int bufferSize)
{
size=0;
start=NULL;
end==NULL;
}

template<class T>
TMForwardList<T>::TMForwardList(const TMList<T> &other)
{
this->size=0;
this->start=NULL;
end==NULL;
int succ;
for(int i=0;i<other.getSize();i++)this->add(other.get(i,&succ),&succ);
}

template<class T>
TMForwardList<T>::TMForwardList(const TMForwardList<T> & other)
{
this->size=0;
this->start=NULL;
end==NULL;
int succ;
for(int i=0;i<other.size;i++) this->add(other.get(i,&succ),&succ);
}

template<class T>
TMForwardList<T> & TMForwardList<T>::operator=(const TMList<T> & other)
{
int succ;
this->clear();
for(int i=0;i<other.getSize();i++)this->add(other.get(i,&succ),&succ);
return *this;
}

template<class T>
TMForwardList<T> & TMForwardList<T>::operator=(const TMForwardList<T> & other)
{
int succ;
this->clear();
for(int i=0;i<other.size;i++) this->add(other.get(i,&succ),&succ);
return *this;
}

template<class T>
void TMForwardList<T>::operator+=(const TMList<T> & other)
{
int succ;
for(int i=0;i<other.getSize();i++) this->add(other.get(i,&succ),&succ);
}

template<class T>
void TMForwardList<T>::operator+=(const TMForwardList<T> &other)
{
int succ;
for(int i=0;i<other.size;i++) this->add(other.get(i,&succ),&succ);
}

template<class T>
T TMForwardList<T>::operator[](int index)
{ 
Node *p1;
if(index<0 && index>size)
{
cout<<"Invalid Entry"<<endl;
return 0;
}
if(index==0)
{
return start->data;
}
else
{
int x=0;
p1=start;
while(x<index && p1)
{
p1=p1->next;
x++;
}
if(!p1)
{
cout<<"Invalid Entry"<<endl;
return 0;
}
}
return p1->data;
}

template<class T>
TMForwardList<T> TMForwardList<T>::operator+(const TMForwardList<T> &other)
{
TMForwardList<T> k;
k+=(*this);
k+=other;
return k;
}

template<class T>
TMForwardList<T>::~TMForwardList()
{
Node *a;
while(this->start)
{
a=this->start;
this->start=this->start->next;
delete []a;
}
this->size=0;
this->start=NULL;
this->end=NULL;
}

template<class T>
void TMForwardList<T>::add(T data,bool *success)
{
Node *a;
if(success)*success=false;
a=new Node();
if(a==NULL)
{
return;
}
a->data=data;
a->next=NULL;
if(start==NULL)
{
start=a;
}
else
{
end->next=a;
}
end=a;
size++;
if(success)*success=true;
}

template<class T>
void TMForwardList<T>::insertAt(int index,T data,bool *success)
{
Node *a,*p1,*p2;
if(success)*success=false;
if(index>size)return;
a=new Node();
if(a==NULL)return;
a->data=data;
a->next=NULL;
if(index<=0)
{
a->next=start;
start=a;
size++;
if(success)*success=true;
return;
}
int x=0;
p1=start;
while(x<index && p1)
{
p2=p1;
p1=p1->next;
x++;
}
if(p1==NULL)
{
end->next=a;
size++;
if(success)*success=true;
return;
}
p2->next=a;
a->next=p1;
size++;
if(success)*success=true;
}

template<class T>
T TMForwardList<T>::removeAt(int index,bool *success)
{
T num;
if(success)*success=false;
Node *a,*p1,*p2;
p1=start;
int x=0;
if(index<0 || index>size)
{
if(success)*success=false;
return 0;
}
if(index==0)
{
start=start->next;
num=p1->data;
free(p1);
size--;
if(success)*success=true;
return num;
}
while(x<index && p1)
{
p2=p1;
p1=p1->next;
x++;
}
if(!p1)
{
return 0;
}
p2->next=p1->next;
num=p1->data;
free(p1);
size--;
if(success)*success=true;
return num;
}

template<class T>
void TMForwardList<T>::update(int index,T data,bool *success)
{
if(success)*success=false;
Node *p1,*p2;
p1=start;
int x=0;
if(index==0)
{
start->data=data;
}
else
{
while(p1 && x<index)
{
p2=p1;
p1=p1->next;
x++;
}
}
if(!p1)return;
p1->data=data;
if(success)*success=true;
}

template<class T>
T TMForwardList<T>::get(int index,bool *success) const
{
if(success)*success=false;
Node *p1;
p1=start;
if(index==0)
{
return start->data;
}
else
{
int x=0;
while(x<index && p1)
{
p1=p1->next;
x++;
}
if(p1==NULL)return 0;
}
if(success)*success=true;
return p1->data;
}

template<class T>
void TMForwardList<T>::removeAll()
{
if(size==0)return;
Node *a,*p1;
p1=start;
while(p1)
{
a=p1;
p1=p1->next;
delete []a;
}
size=0;
start=NULL;
end=NULL;
}

template<class T>
void TMForwardList<T>::clear()
{
if(size==0)return;
Node *a,*p1;
p1=start;
while(p1)
{
a=p1;
p1=p1->next;
delete []a;
}
size=0;
start=NULL;
end=NULL;
}

template<class T>
int TMForwardList<T>::getSize() const
{
return size;
}

template<class T>
void TMForwardList<T>::display()
{
if(size==0)
{
cout<<"No Data"<<endl;
return;
}
int x=0;
Node *a;
a=start;
cout<<"**********"<<endl;
while(a)
{
cout<<a->data<<endl;
a=a->next;
}
cout<<"**********"<<endl;
}

//************************************************************ TMTwoWayList ***************************************************************

template<class T>
class TMTwoWayList :public TMList<T>
{

public:
class Node2
{
public :
T data;
Node2 *previous;
Node2 *next;
};
int size;
Node2 *start;
Node2 *end;

class TMTwoWayListIterator : public Iterator<T>
{
private:
Node2 *ptr;
public:

void init(Node2 *ptr)
{
this->ptr=ptr;
}

int hasMoreElements()
{
if(this->ptr!=NULL) return true;
return false;
}

T next()
{
T num=this->ptr->data;
this->ptr=this->ptr->next;
return num;
}
};
private: 
TMTwoWayListIterator tmTwoWayListIterator;
public:

Iterator<T> getIterator()
{
tmTwoWayListIterator.init(this->start);
return Iterator<T>(&tmTwoWayListIterator);
}

TMTwoWayList();
TMTwoWayList(T &data);
TMTwoWayList(const TMTwoWayList &other);
TMTwoWayList & operator=(TMTwoWayList &other);
void operator+=(TMTwoWayList & other);
T operator[](int index);
//void operator+();
virtual ~TMTwoWayList();
void display();
void add(T data,bool *success);
void insertAt(int index,T data,bool *success);
T removeAt(int index,bool *success);
void update(int index,T data,bool *success);
T get(int index,bool *success)const;
void removeAll();
void clear();
int getSize() const;
};

template<class T>
TMTwoWayList<T>::TMTwoWayList()
{
size=0;
start=NULL;
end==NULL;
}

template<class T>
TMTwoWayList<T>::TMTwoWayList(T &data)
{
int success;
TMTwoWayList::add(data,&success);
}

template<class T>
TMTwoWayList<T>::TMTwoWayList(const TMTwoWayList<T> &other)
{
size=other.size;
start=other.start;
end=other.end;
}

template<class T>
TMTwoWayList<T> & TMTwoWayList<T>::operator=(TMTwoWayList<T> & other)
{
size=other.size;
start=other.start;
end=other.end;
return *this;
}

template<class T>
void TMTwoWayList<T>::operator+=(TMTwoWayList<T> &other)
{
end->next=other.start;
other.start->previous=end;
end=other.end;
size=size+other.size;
}

template<class T>
T TMTwoWayList<T>::operator[](int index)
{ 
Node2 *p1;

if(index<0 && index>size)
{
cout<<"Invalid Entry"<<endl;
return 0;
}
if(index==0)
{
return start->data;
}
else
{
int x=0;
p1=start;
while(x<index && p1)
{
p1=p1->next;
x++;
}
if(!p1)
{
cout<<"Invalid Entry"<<endl;
return 0;
}
}
return p1->data;
}
//void TMTwoWayList::operator+()
//{
//}

template<class T>
TMTwoWayList<T>::~TMTwoWayList()
{
Node2 *p,*a;
a=start;
while(a)
{
p=a;
free(p);
a=a->next;
}
size=0;
start=NULL;
end=NULL;
}

template<class T>
void TMTwoWayList<T>::add(T data,bool *success)
{
Node2 *a;
if(success)*success=false;
a=new Node2();
if(a==NULL)
{
if(success)*success=false;
return;
}
a->data=data;
a->next=NULL;
a->previous=NULL;
if(start==NULL)
{
start=a;
}
else
{
end->next=a;
a->previous=end;
}
end=a;
size++;
if(success)*success=true;
}

template<class T>
void TMTwoWayList<T>::insertAt(int index,T data,bool *success)
{
Node2 *a,*p1;
if(success)*success=false;
if(index>size)return;
a=new Node2();
if(a==NULL)return;
a->data=data;
a->previous=NULL;
a->next=NULL;
if(index<=0)
{
a->next=start;
start=a;
size++;
if(success)*success=true;
return;
}
int x=0;
p1=start;
while(x<index && p1)
{
p1=p1->next;
x++;
}
if(p1==NULL)
{
end->next=a;
a->previous=end;
end=a;
size++;
if(success)*success=true;
return;
}
a->next=p1;
a->previous=p1->previous;
p1->previous->next=a;
p1->previous=a;
size++;
if(success)*success=true;
}

template<class T>
T TMTwoWayList<T>::removeAt(int index,bool *success)
{
T num;
if(success)*success=false;
Node2 *a,*p1;
p1=start;
int x=0;
if(index<0 && index>size)
{
if(success)*success=false;
return 0;
}
if(index==0)
{
start=start->next;
start->previous=NULL;
num=p1->data;
free(p1);
size--;
if(success)*success=true;
return num;
}
while(x<index && p1)
{
p1=p1->next;
x++;
}
if(!p1)
{
return 0;
}
p1->previous->next=p1->next;
p1->next->previous=p1->previous;
num=p1->data;
free(p1);
size--;
if(success)*success=true;
return num;
}
template<class T>
void TMTwoWayList<T>::update(int index,T data,bool *success)
{
if(success)*success=false;
Node2 *p1;
p1=start;
int x=0;
if(index==0)
{
start->data=data;
}
else
{
while(p1 && x<index)
{
p1=p1->next;
x++;
}
}
if(!p1)return;
p1->data=data;
if(success)*success=true;
}

template<class T>
T TMTwoWayList<T>::get(int index,bool *success) const
{
if(success)*success=false;
Node2 *p1;
p1=start;
if(index==0)
{
return start->data;
}
else
{
int x=0;
while(x<index && p1)
{
p1=p1->next;
x++;
}
if(!p1)return 0;
}
return p1->data;
if(success)*success=true;
}

template<class T>
void TMTwoWayList<T>::removeAll()
{
if(size==0)return;
Node2 *a,*p1;
p1=start;
while(p1)
{
a=p1;
p1=p1->next;
delete a;
}
size=0;
start=NULL;
end=NULL;
}

template<class T>
void TMTwoWayList<T>::clear()
{
if(size==0)return;
Node2 *a,*p1;
p1=start;
while(p1)
{
a=p1;
p1=p1->next;
delete a;
}
size=0;
start=NULL;
end=NULL;
}

template<class T>
int TMTwoWayList<T>::getSize() const
{
return size;
}

template<class T>
void TMTwoWayList<T>::display()
{
if(size==0)
{
cout<<"No data"<<endl;
return;
}
int x=0;
Node2 *a;
a=start;
cout<<"Display from TMArrayList"<<endl;
while(a)
{
cout<<a->data<<endl;
a=a->next;
}
}

//******************************************************************* TMArrayList **************************************************************************

template<class T>
class TMArrayList : public TMList<T>
{
private:
char a;
T **ptr;
int size,capacity;
int addRows();
public:
TMArrayList();
TMArrayList(int bufferSize);
TMArrayList(const TMList<T> & other);
TMArrayList(const TMArrayList & other);
TMArrayList & operator=(const TMList<T> &other);
TMArrayList & operator=(const TMArrayList &other);
void operator+=(const TMList<T> & other);
void operator+=(const TMArrayList & other);
T operator[](int index);
//TMArrayList operator+(const TMArrayList & other);
~TMArrayList();
void display();
void add(T data,bool *success);
void insertAt(int index,T data,bool *success);
T removeAt(int index,bool *success);
void update(int index,T data,bool *success);
T get(int index,bool *success) const;
void removeAll();
void clear();
int getSize() const;
};



template<class T>
TMArrayList<T>::TMArrayList()
{
this->size=0;
ptr=new T *[10];
ptr[0]=new T[10];
this->capacity=10;
this->a=0;
}

template<class T>
TMArrayList<T>::TMArrayList(int bufferSize)
{
if(bufferSize<=0)
{
this->size=0;
this->ptr=new T *[10];
this->ptr[0]=new T [10];
this->capacity=10;
this->a=0;
}
else
{
int rows,numberOfPointers;
rows=bufferSize/10;
if(bufferSize%10!=0) rows++;
numberOfPointers=rows+(10-(rows%10));
this->ptr=new T *[numberOfPointers];
for(int e=0;e<rows;e++) this->ptr[e]=new T[10];
this->capacity=rows*10;
this->size=0;
this->a=0;
}
}

template<class T>
TMArrayList<T>::TMArrayList(const TMList<T> & other)
{
this->size=0;
this->ptr=new T *[10];
this->ptr[0]=new T [10];
this->capacity=10;
this->a=0;
bool succ;
for(int e=0;e<other.getSize();e++)
{
this->add(other.get(e,&succ),&succ);
}
} 

template<class T>
TMArrayList<T>::TMArrayList(const TMArrayList<T> & other)
{
int bufferSize=other.size;
if(bufferSize<=0)
{
this->size=0;
this->ptr=new T *[10];
this->ptr[0]=new T[10];
this->capacity=10;
this->a=0;
}
else
{
int rows,numberOfPointers;
rows=bufferSize/10;
if(bufferSize%10!=0) rows++;
numberOfPointers=rows+(10-(rows%10));
this->ptr=new T *[numberOfPointers];
for(int e=0;e<rows;e++) this->ptr[e]=new T[10];
this->capacity=rows*10;
this->size=0;
this->a=0;
}
bool succ;
for(int e=0;e<other.size;e++)
{
this->add(other.get(e,&succ),&succ);
}
}

template<class T>
TMArrayList<T> & TMArrayList<T>::operator=(const TMList<T> &other)
{
bool succ;
this->clear();
for(int i=0;i<other.getSize();i++)this->add(other.get(i,&succ),&succ);
}

template<class T>
TMArrayList<T> & TMArrayList<T>::operator=(const TMArrayList<T> &other)
{
if(other.a==0)
{
this->clear();
bool succ;
for(int e=0;e<other.size;e++)
{
this->add(other.get(e,&succ),&succ);
}
}
else
{
int rows=this->capacity/10;
int j;
for(j=0;j<rows;j++)
{
delete[] this->ptr[j];
}
delete [] this->ptr;
this->ptr=other.ptr;
this->capacity=other.capacity;
this->size=other.size;
}
return *this;
}

template<class T>
void TMArrayList<T>::operator+=(const TMList<T> & other)
{
bool succ;
for(int i=0;i<other.getSize();i++) this->add(other.get(i,&succ),&succ);
}

template<class T>
void TMArrayList<T>::operator+=(const TMArrayList<T> & other)
{
bool succ;
for(int e=0;e<other.size;e++)this->add(other.get(e,&succ),&succ);
}

template<class T>
T TMArrayList<T>::operator[](int index)
{
bool succ;
T data=this->get(index,&succ);
if(succ) return data;
return NULL;
}

/* TMArrayList TMArrayList::operator+(const TMArrayList & other)
{
TMArrayList k;
k.a=1;
bool succ;
for(int e=0;e<this->size;e++)k.add(this->get(e,&succ),&succ);
for(int e=0;e<other.size;e++)k.add(other.get(e,&succ),&succ);
return k;
} */

template<class T>
TMArrayList<T>::~TMArrayList()
{
if(this->a==0)
{
int rows=this->capacity/10;
for(int e=0;e<rows;e++)
{
delete []this->ptr[e];
}
delete []this->ptr;
}
}

template<class T>
int TMArrayList<T>::addRows()
{
int rows;
rows=this->capacity/10;
if(this->capacity%100==0)
{
T **tmp=new T *[rows+10];
for(int e=0;e<rows;e++)
{
tmp[e]=ptr[e];
}
this->ptr=tmp;
}
this->ptr[rows]=new T [10];
this->capacity=this->capacity+10;
}

template<class T>
void TMArrayList<T>::display()
{
cout<<"**********"<<endl;
for(int i=0;i<size;i++)
{
int a=i/10;
int b=i%10;
cout<<this->ptr[a][b]<<endl;
}
cout<<"**********"<<endl;
}

template<class T>
void TMArrayList<T>::add(T data,bool *success)
{
if(success)*success=false;
if(this->size==this->capacity)
{
if(!addRows())return;
}
int rowIndex,columnIndex;
rowIndex=size/10;
columnIndex=size%10;
this->ptr[rowIndex][columnIndex]=data;
this->size++;
if(success)*success=true;
}

template<class T>
T TMArrayList<T>::removeAt(int index,bool *success)
{
if(success)*success=false;
if(index<0 || index>this->size)return NULL;
bool succ;
T data=this->get(index,&succ);
int j;
int op=this->size-2;
j=index;
while(j<=op)
{
this->update(j,this->get(j+1,&succ),&succ);
j++;
}
this->size--;
if(success)*success=true;
return data;
}

template<class T>
void TMArrayList<T>::insertAt(int index,T data,bool *success)
{
if(success)*success=false;
if(index<0 || index>this->size)return;
if(index==this->size)
{
this->add(data,success);
return;
}
int succ;
T k;
k=this->get(this->size-1,&succ);
this->add(k,&succ);
int j;
j=this->size-3;
while(j>=index)
{
this->update(j+1,this->get(j,&succ),&succ);
j--;
}
this->update(index,data,&succ);
if(success)*success=true;
}

template<class T>
void TMArrayList<T>::update(int index,T data,bool *success)
{
if(success)*success=false;
if(index<0 || index>this->size) return;
int rowIndex=index/10;
int columnIndex=index%10;
this->ptr[rowIndex][columnIndex]=data;
if(success)*success=true;
}

template<class T>
T TMArrayList<T>::get(int index,bool *success) const
{
if(success)*success=false;
if(index<0 || index>=this->size) return false;
int rowIndex,columnIndex;
rowIndex=index/10;
columnIndex=index%10;
if(success)*success=true;
return this->ptr[rowIndex][columnIndex];
}

template<class T>
void TMArrayList<T>::removeAll()
{
this->size=0;
}

template<class T>
void TMArrayList<T>::clear()
{
this->size=0;
}

template<class T>
int TMArrayList<T>::getSize() const
{
return this->size;
}

int main()
{
int succ;
TMArrayList<char *> a;
//TMArrayList<char> a;
a.add("Raghav",&succ);
a.add("Smriti",&succ);
a.add("Yash",&succ);
a.add("Raj",&succ);
a.add("Rahul",&succ);
a.add("Preeti",&succ);
a.add("Lakhan",&succ);
a.display();
/*
Iterator<char *> iter=a.getIterator();
while(iter.hasMoreElements())
{
cout<<iter.next()<<endl;
}
*/
return 0;
}