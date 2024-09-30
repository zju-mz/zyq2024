#include <iostream>
#include <cstring>

class Chicken
{
    private:
        int age = 24;
        char *name = nullptr;
    public:
        Chicken(){};
        Chicken(int _age) : age(_age) {};
        Chicken(int _age, const char *_name) : age(_age) 
        {
            int len = strlen(_name) + 1;
            name = new char[len];
            for (int i = 0; i < len; i++)
                name[i] = _name[i];
        };
        Chicken(const Chicken &other) : age(other.age)
        {
            if (other.name != nullptr)
            {
                int len = strlen(other.name) + 1;
                name = new char[len];
                for (int i = 0;i < len; i++)
                {
                    name[i] = other.name[i];
                }
            }
            else{
                name = nullptr;
            }
        }
        ~Chicken() //析构函数
        {
            if (name != nullptr)
                delete[] name;
        }
        void setAge(int _age)
        {
            age = _age;
        }
        void setName(const char *_name)
        {
            if(name != nullptr)
                delete[] name;
            int len = strlen(_name) + 1;
            name = new char[len];
            for (int i = 0; i < len; i++)
                name[i] = _name[i];
        }

        const char *getName() const
        {
            return name;
        }

        const int &getAge() const
        {
            return age;
        }

        Chicken &operator=(const Chicken &other)
        {
            if (this != &other){
                age=other.age;
                if (name != nullptr)
                {
                    delete[] name;
                }
                if (other.name != nullptr)
                {
                    int len = strlen(other.name) +1;
                    name= new char[len];
                    for (int i=0;i<len;i++)
                    {
                        name[i] = other.name[i];
                    }
                }
                else
                {
                    name = nullptr;
                }
            }
            return *this;
        }
};

int main(){
    auto print = [](const Chicken &c){
        std::cout << "Hi, everyone! My name is " << c.getName()
                  << ", I am " << c.getAge() << " years old." << std::endl;
    };Chicken c(24, "Kunkun");
    print(c);
    
    Chicken d;
    d = c;    
    print(d); // 测试【赋值运算符】是否正确，能正确输出给 20 分    
    
    Chicken a = c;    
    print(a); // 测试【赋值构造函数】是否正确，能正确输出给 20 分    
    
    c.setName("Xukun Cai");    
    print(c);    
    print(a);    
    print(d); // 测试是否为【深度复制】，本行与上两行能正确输出给 20 分    
    
    Chicken b;    
    b = d = c;    
    print(b);    
    print(d); // 测试【连续赋值】功能，本行与上一行能正确输出给 20 分
    return 0;
}