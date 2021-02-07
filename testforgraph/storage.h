#ifndef STORAGE_H
#define STORAGE_H

template <class Type>
    class Storage
{
private:
    int top;
    Type *s;
public:

Storage() {
    s = new Type[top];
    top = 0;
}

void add(Type var)
{

        Type *a=new Type[top+1];
        for(int i=0;i<top;i++) a[i]=s[i];
        a[top]= var;
        top++;
        delete []s;
        s = a;

}

void remove(int p) {
    delete s[p];

    if(top>0)
    {
        Type *a=new Type[top-1];
         int j=0;
         for(int i=0;i<top;i++) {

            if(i!= p)
            {
                a[j]=s[i];
                j++;
            }
         }
            delete[]s;
            s = a;
            top--;
     }

}


    Type& get(int p) {
        return s[p];
    }

    int Count() {
        return top;
    }

    void Sort()
    {
        int tmp;
            for(int i = 0; i < top-1; ++i)
            {
                for(int j = 0; j < top-1; ++j)
                {
                    if (s[j + 1] < s[j])
                    {
                        tmp = s[j + 1];
                        s[j + 1] = s[j];
                        s[j] = tmp;
                    }
                }
            }
    }

    ~Storage()
    {
        delete []s;
    }

};

#endif // STORAGE_H
