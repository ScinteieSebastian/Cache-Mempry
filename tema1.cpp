#include <iostream>
#include <string.h>
#include <sstream>
#include <stdio.h>
#include <list>
#include <stdio.h>
#include <fstream>

using namespace std;

ifstream f1("ram.in");
ifstream f2("operations.in");
ifstream f5("ram.out");
ofstream f3("ram.out");
ofstream f4("cache.out");
//elem_info reprezinta procesele ce au o adresa si o data
template<typename Tkey, typename Tvalue>
    struct elem_info {
        Tkey key;
        Tvalue value;
        int dirty_bite;
        int date;
    };
      struct ram{
            int key;
            int value;
        };
// elementele continute de hashtable reprezentative pentru tipurile de memorie cache
    class Set {
        public:
            struct elem_info<int, int> way0;
            struct elem_info<int, int> way1;
            int date;

            Set()
            {
                way0.key = -1;
                way1.key = -1;
                way0.value = -1;
                way1.value = -1;
                date = 0;

            }
            ~Set()
            {

            }

            void put(int key, int value)
            {
                if(way0.key == -1 && way1.key == -1)
                {
                    way0.key = key;
                    way0.value = value;
                    date++;
                    way0.date = date;
                }
                else
                {
                    if(way0.key != -1 && way1.key == -1)
                    {
                        way1.key = key;
                        way1.value = value;
                        date++;
                        way1.date = date;
                    }
                    else
                    {
                        if(way0.key != -1 && way1.key != -1)
                        {
                            if(way0.date < way1.date)
                            {
                                way0.key = key;
                                way0.value = value;
                                date++;
                                way0.date = date;
                            }
                            else
                            {
                                way1.key = key;
                                way1.value = value;
                                date++;
                                way1.date = date;
                            }
                        }
                    }

                }
            }
            bool is_dirty(int key )
            {
                if((way0.key == key && way0.dirty_bite == 1|| (way1.key == key && way1.dirty_bite == 1)))
                {
                    return true;
                }
                else
                    return false;
            }
            void put_star(int key)
            {
                if(way0.key == key)
                {
                    way0.dirty_bite = 1;
                }
                if(way1.key == key)
                {
                    way1.dirty_bite = 1;
                }
            }
            void remove_star(int key)
            {
                 if(way0.key == key)
                {
                    way0.dirty_bite = 0;
                }
                if(way1.key == key)
                {
                    way1.dirty_bite = 0;
                }
            }
            void update(int key, int value)
            {
                if(way0.key == key)
                {
                    way0.value = value;
                    date++;
                    way0.date = date;
                }
                if(way1.key == key)
                {
                    way1.value = value;
                    date++;
                    way1.date = date;
                }
            }
            bool has_key(int key)
            {
                if(way0.key == key || way1.key == key)
                    return true;
                else
                    return false;

            }
            int get(int key)
            {
                if(way0.key == key)
                {
                    return way0.value;
                }
                else
                {
                    if(way1.key == key)
                    {
                        return way1.value;
                    }
                }
            }
            bool is_empty()
            {
                if(way0.key == -1 && way1.key == -1)
                    return true;
                else{
                        //cout<<"Aceasta adresa nu este empty"<<endl;
                        if(way0.key!=-1) //cout<<way0.value<<endl;
                        if(way1.key!=-1) //cout<<way1.value<<endl;
                        //cout<<"GAATA"<<endl;
                    return false;}
            }
            void print_set()
            {
                if(way0.key != -1)
                {
                    cout<<"Way0 : "<<"Key = "<<way0.key<<" "<<"Value = "<<way0.value<<"dirty = "<<way0.dirty_bite<<endl;
                }
                else
                    cout<<"Way0 : NULL"<<endl;
               if(way1.key != -1)
                {
                    cout<<"Way1 : "<<"Key = "<<way1.key<<" "<<"Value = "<<way1.value<<"dirty = "<<way1.dirty_bite<<endl;
                }
                else
                    cout<<"Way1 : NULL"<<endl;
            }
            void printf_set(int index)
            {
                if(way0.key != -1)
                {
                    cout<<index<<" "<<"0"<<" "<<way0.key<<" "<<way0.value<<" ";
                    if(way0.dirty_bite == 1)
                        cout<<"*"<<endl;
                    else
                        cout<<endl;
                }
                 if(way1.key != -1)
                {
                    cout<<index<<" "<<"1"<<" "<<way1.key<<" "<<way1.value<<" ";
                    if(way1.dirty_bite == 1)
                        cout<<"*"<<endl;
                    else
                        cout<<endl;
                }
            }
            bool is_occupate(int key)
            {
                if(way0.key != -1 && way1.key != -1)
                {
                    if(way0.key != key && way1.key != key)
                        return true;
                    else
                        return false;
                }
                else
                    return false;
            }

    };
 // hashtable folosit pentru reprezentarea memoriilor cache
 template<typename Tkey, typename Tvalue>
    class Hashtable {
        public:
            Set *H;
            int HMAX;
            unsigned int (*hash) (Tkey);

        
            Hashtable(int hmax, unsigned int (*h)(Tkey))
            {
            	HMAX = hmax;
            	hash = h;
            	H = new Set [HMAX];
            }
         	~Hashtable()
         	{
         		
         	}

            void put(Tkey key, Tvalue value)
            {
            	int index =  hash(key) % HMAX;
            	if(H[index].has_key(key))
                {
                    H[index].update(key, value);
                }
                else
                {
                    H[index].put(key, value);
                }

            }
            Tvalue get(Tkey key)
            {
            	int index = hash(key) % HMAX;
            	if(H[index].has_key(key))
                {
                    return H[index].get(key);

                }
                else
                {
                    cout<<"adresa nu exista in memorie"<<endl;
                }

            }
            Tvalue get_set(Tkey key)
            {
                int index = hash(key) % HMAX;
            	if(H[index].has_key(key))
                {
                    H[index].print_set();
                }
                else
                {
                   // cout<<"adresa nu exista in memorie"<<endl;
                }

            }
            bool has_key(Tkey key)
            {
                int index = hash(key) % HMAX;
            		if(H[index].has_key(key))
            		{
            			return true;
            		}
            		else
            			return false;

            }
            void print()
            {
                for(int i = 0; i< HMAX; i++)
                {
                    if(!H[i].is_empty())
                    {
                        H[i].print_set();
                    }
                }
            }
            void fprint()
            {
                 for(int i = 0; i< HMAX; i++)
                {
                    if(!H[i].is_empty())
                    {
                        H[i].printf_set(i);
                    }
                }
            }
            bool is_dirty(int key)
            {
                int index = hash(key) % HMAX;
                if(H[index].is_dirty(key))
                    return true;
                else
                    return false;
            }
            void put_star(int key)
            {

                int index = hash(key) % HMAX;
                H[index].put_star(key);
            }
            void remove_star(int key)
            {

                int index = hash(key) % HMAX;
                H[index].remove_star(key);
            }
            void print_file()
            {
                FILE *ff;
                ff=fopen("cache.out","a");
                fseek(ff,0,SEEK_SET);
                for (int i=0;i<HMAX;i++)
                    {
                        if (H[i].way0.key != -1 )
                        {
                            fprintf(ff,"%d 0 %d %d",i,H[i].way0.key,H[i].way0.value);
                            if(H[i].way0.dirty_bite == 1)
                                fprintf(ff," *");
                            fprintf(ff,"\n");
                        }

                        if (H[i].way1.key != -1)
                        {
                            fprintf(ff,"%d 1 %d %d",i,H[i].way1.key,H[i].way1.value);
                            if(H[i].way1.dirty_bite == 1)
                                fprintf(ff," *");
                            fprintf(ff,"\n");
                        }
                    }
               	fprintf(ff,"\n");
                fclose(ff);
			}
			 void print_file_L2()
            {
                FILE *ff;
                ff=fopen("cache.out","a");
                fseek(ff,0,SEEK_SET);
                for (int i=0;i<HMAX;i++)
                    {
                        if (H[i].way0.key != -1 )
                        {
                            fprintf(ff,"%d 0 %d %d",i,H[i].way0.key,H[i].way0.value);
                            if(H[i].way0.dirty_bite == 1)
                                fprintf(ff," *");
                            fprintf(ff,"\n");
                        }

                        if (H[i].way1.key != -1)
                        {
                            fprintf(ff,"%d 1 %d %d",i,H[i].way1.key,H[i].way1.value);
                            if(H[i].way1.dirty_bite == 1)
                                fprintf(ff," *");
                            fprintf(ff,"\n");
                        }
                    }
               	//fprintf(ff,"\n");
                fclose(ff);
			}
			bool is_occupate(int key)
			{
                int index = hash(key) % HMAX;
                if(!H[index].is_empty())
                {
                    if(H[index].is_occupate(key))
                    {cout<<key<<endl;;
                        return 1;}
                    else
                        return 0;
                }
                else
                    return 0;
			}
			void write_back(int key)
			{
            int index = hash(key) % HMAX;
            struct ram ram_file[100001];
            int kk = 0;
            f5.close();
            f5.open("ram.out");
            while(f5>>ram_file[kk].key)
            {
                f5>>ram_file[kk].value;
                kk++;
            }
            for(int i = 0;i<kk;i++)
            {
                if(ram_file[i].key == key)
                {
                    int value = H[index].get(key);
                    ram_file[i].value = value;

                }

			}
			FILE *ram;
            ram=fopen("ram.out","a");
            fseek(ram,0,SEEK_SET);
            for(int i = 0; i<kk-1;i++)
                {
                    fprintf(ram,"%010d %010d",ram_file[i].key,ram_file[i].value);
                    fprintf(ram,"\n");
                }
                fprintf(ram,"%010d %010d",ram_file[kk-1].key,ram_file[kk-1].value);

			}
};


void read(int core, class Hashtable<int,int> L11, class Hashtable<int,int> L12, class Hashtable<int ,int> L2,int key)
{
if(core == 0)
{
 if(L11.has_key(key) && !L11.is_dirty(key))
 {
           //cout<<"adresa se afla deja in L11"<<endl;

 }
 else
 {
     if(L2.has_key(key))
        {
            int value = L2.get(key);
            L11.put(key,value);
            L11.remove_star(key);

        }
     else
        {
            int a = 0;
            int b = 0;
            f1.close();
            f1.open("ram.in");
            while(f1>>a)
            {
                f1>>b;
                if(a == key)
                {
                    if(L2.is_occupate(a))
                    {
                        L2.write_back(a);
                    }
                    L2.put(a,b);
                    L11.put(a,b);
                    //cout<<"bine";

                    break;
                }
                //cout<<a[k]<<" "<<b[k]<<endl;
            }

        }

 }
}
 if(core == 1)
{
 if(L12.has_key(key) && !L12.is_dirty(key))
 {
     //cout<<"adresa se afla deja in L12"<<endl;

 }
 else
 {
     if(L2.has_key(key))
        {
            int value = L2.get(key);
            L12.put(key,value);
            L12.remove_star(key);

        }
     else
        {
            int a = 0;
            int b = 0;
            f1.close();
            f1.open("ram.in");
            while(f1>>a)
            {
                f1>>b;
                if(a == key)
                {
                     if(L2.is_occupate(a))
                    {
                        L2.write_back(a);
                    }
                    L2.put(a,b);
                    L12.put(a,b);


                    break;
                }
                //cout<<a[k]<<" "<<b[k]<<endl;

            }

        }

 }
}
}

void write(int core, class Hashtable<int,int> L11, class Hashtable<int,int> L12, class Hashtable<int ,int> L2,int key,int value)
{
    if(core == 0)
    {
        if(L11.has_key(key) && !L11.is_dirty(key))
        {
                    L11.put(key,value);
                     if(L2.is_occupate(key))
                    {
                        L2.write_back(key);
                    }
                    L2.put(key,value);
                    L12.put_star(key);


        }
        else
        {
            if(!L11.has_key(key) || L11.is_dirty(key))
            {
                if(L2.has_key(key))
                {
                     if(L2.is_occupate(key))
                    {
                        L2.write_back(key);
                    }
                    L2.put(key,value);
                    L11.put(key,value);
                    L12.put_star(key);
                    L11.remove_star(key);

                }
                else
                {
                     if(L2.is_occupate(key))
                    {
                        L2.write_back(key);
                    }
                    L2.put(key,value);
                    L11.put(key,value);
                    L11.remove_star(key);

                }
            }
        }

    }
    else
    {
        if(core == 1)
        {
            if(L12.has_key(key) && !L12.is_dirty(key))
        {
                    L12.put(key,value);
                     if(L2.is_occupate(key))
                    {
                        L2.write_back(key);
                    }
                    L2.put(key,value);
                    L11.put_star(key);
                    L12.remove_star(key);

        }
        else
        {
            if(!L12.has_key(key) || L12.is_dirty(key))
            {
                if(L2.has_key(key))
                {
                     if(L2.is_occupate(key))
                    {
                        L2.write_back(key);
                    }
                    L2.put(key,value);
                    L12.put(key,value);
                    L11.put_star(key);
                    L12.remove_star(key);

                }
                else
                {
                     if(L2.is_occupate(key))
                    {
                        L2.write_back(key);
                    }
                    L2.put(key,value);
                    L12.put(key,value);
                    L12.remove_star(key);

                }
            }
        }
    }
    }

}


int pow(int x,int nr){
	int p=1;
	while(nr>0)
	 {p=p*x;
	nr--;}
return p;
	}
unsigned int fhash(int key){
int v[100] = {0};
int k=0;
while(key!=0){
  v[k]=key%2;
 //cout<<v[i]<<endl;
  k++;
   key=key/2;
	}
int number = 0;
//for (int j=2;j<i;j++)
	//cout<<v[j];
	if (k>12) k=13;
for (int j=2;j<k;j++)
	number+=v[j]*pow(2,j-2);
return number;
}

unsigned int fhash2(int key)
{
int v[100] = {0};
int k=0;
while(key!=0){
  v[k]=key%2;
  k++;
  key=key/2;
	}
int number=0;
if(k>14) k=15;
for (int j=2;j<=k;j++)
	number+=v[j]*pow(2,j-2);
return number;
}
int main()
{
 Hashtable< int, int> L11 = Hashtable< int, int>(4096, fhash);
 Hashtable< int, int> L12 = Hashtable< int, int>(4096, fhash);
 Hashtable< int, int> L2 = Hashtable< int, int>( 16384, fhash2);
int key_r;
int value_r;
FILE *ram;
ram=fopen("ram.out","a");
fseek(ram,0,SEEK_SET);

f1.close();
f1.open("ram.in");
while(f1>>key_r)
{
    f1>>value_r;
    fprintf(ram,"%010d %010d",key_r,value_r);
    fprintf(ram,"\n");

}
f2.close();
f2.open("operations.in");
int core, key,value;
char operation;
int k = 0;
while(f2>>core)
{
    f2>>operation;
    f2>>key;
    if(operation  == 'w')
    {
        f2>>value;
    }
    if(operation == 'r')
    {
        read(core,L11,L12,L2,key);
    }
    if(operation == 'w')
    {
        write(core,L11,L12,L2,key ,value);
    }
}

L11.print_file();
L12.print_file();
L2.print_file_L2();
f1.close();
f2.close();
f3.close();
f4.close();
f5.close();

}
