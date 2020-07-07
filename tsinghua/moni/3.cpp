#ifndef _MINUS_OF_BIGINTGER_H
#define _MINUS_OF_BIGINTGER_H
/*
实现高精度存储, 比较和运算(加, 减, 乘, 除, 模, 绝对值)
这个高精度里面保存了
- 数字(v数组)
- 负数标志(is minus变量)
*/
#include<iostream>
#include<vector>

using namespace std;

struct BigIntger{
    bool is_minus;
    vector<int> v;

    // 将一个不合法的数等价变换成合法的数 
    BigIntger& change(){
        while(this->v.size() > 1 && this->v.back() == 0) // 前导0 
            this->v.pop_back();
        if(this->v.back() == 0 && this->v.size() == 1 && this->is_minus) // -0 
            this->is_minus = false;
        for(int i = 1; i < this->v.size(); i ++){ // 有数字超过10 
            this->v[i] += this->v[i - 1] / 10;
            this->v[i - 1] %= 10;
        }
        while(this->v.back() >= 10){ // 最高位有进位 
            this->v.push_back(this->v.back() / 10);
            this->v[this->v.size() - 2] %= 10;
        }
        return *this;
    }

    BigIntger& operator = (const BigIntger& b){
        this->is_minus = false;
        this->v.clear();
        this->is_minus = b.is_minus;
        for(int i = 0; i < b.v.size(); i ++)
            this->v.push_back(b.v[i]);
        return *this;
    }

    BigIntger& operator = (int x){
        this->is_minus = false, this->v.clear();
        if(x < 0){
            x = -x;
            this->is_minus = true;
        }
        while(x > 0){
            this->v.push_back(x % 10);
            x /= 10;
        }
        return *this;
    }
};

// 比较
bool operator < (const BigIntger a, const BigIntger b){
    int x = a.v.size(), y = b.v.size();
    if(a.is_minus != b.is_minus)
        return a.is_minus; 
    if(a.is_minus == false){
        if(x != y)
            return x < y;
        for(int i = x - 1; i >= 0; i --)
            if(a.v[i] != b.v[i])
                return a.v[i] < b.v[i];
        return false;
    }
    else{
        if(x != y)
            return x > y;
        for(int i = x - 1; i >= 0; i --)
            if(a.v[i] != b.v[i])
                return a.v[i] > b.v[i];
        return false;
    }
}

bool operator > (const BigIntger a, const BigIntger b){
    return (b < a);
}

bool operator == (const BigIntger a, const BigIntger b){
    return (!(a > b)) && (!(a < b));
}

bool operator <= (const BigIntger a, const BigIntger b){
    return (a < b) || (a == b);
}

bool operator >= (const BigIntger a, const BigIntger b){
    return (a > b) || (a == b);
}

bool operator != (const BigIntger a, const BigIntger b){
    return !(a == b);
}

// 绝对值函数 
BigIntger& abs(BigIntger x){
    BigIntger& y = x;
    y.is_minus = false;
    return y;
}

// input
istream& operator >> (istream& in, BigIntger& n){
    string s;
    in >> s;
    n.v.clear();
    n.is_minus = false;
    if(s[0] == '-')
        n.is_minus = true;
    for(int i = s.size() - 1; i >= (s[0] == '-'); i --)
        n.v.push_back(s[i] - '0');
    n.change();
    return in;
}

// output
ostream& operator << (ostream& out, BigIntger& n){
    n.change();
    int x = n.v.size();
    if(x == 0){
        out << x;
        return out;
    }
    if(n.is_minus == true)
        out << '-';
    for(int i = n.v.size() - 1; i >= 0; i --)
        out << n.v[i];
    return out;
}

// 加法 
BigIntger& operator += (BigIntger& a, BigIntger& b){
    a.change(), b.change();
    if(a.is_minus == b.is_minus){
        if(a.v.size() < b.v.size())
            a.v.resize(b.v.size());
        for(int i = 0; i < b.v.size(); i ++)
            a.v[i] = b.v[i] + a.v[i];
        return a.change();
    }
    else{
        BigIntger x = abs(a);
        BigIntger y = abs(b);
        if(x >= y){
            if(a.v.size() < b.v.size())
                a.v.resize(b.v.size());
            for(int i = 0; i < b.v.size(); i ++){
                while(a.v[i] < b.v[i]){
                    a.v[i + 1] --;
                    a.v[i] += 10;
                }
                a.v[i] = a.v[i] - b.v[i];
            }
            return a.change();
        }
        else{
            a.is_minus = !a.is_minus;
            if(a.v.size() < b.v.size())
                a.v.resize(b.v.size());
            for(int i = 0; i < a.v.size(); i ++){
                while(a.v[i] > b.v[i]){
                    a.v[i + 1] ++;
                    a.v[i] -= 10;
                }
                a.v[i] = b.v[i] - a.v[i];
            }
            return a.change();
        }
    }
}

BigIntger operator + (BigIntger a, BigIntger b){
    BigIntger c = a;
    c += b;
    return c;
}

// 减法 
BigIntger& operator -= (BigIntger& a, BigIntger b){
    BigIntger& c = b;
    c.is_minus = 1 - b.is_minus;
    a += c;
    return a;
}

BigIntger operator - (BigIntger a, BigIntger b){
    BigIntger c = a;
    c -= b;
    return c;
}

// 乘法 
BigIntger operator * (BigIntger &a, BigIntger &b){
    a.change(), b.change();
    BigIntger c;
    c.is_minus = a.is_minus ^ b.is_minus;
    c.v.resize(a.v.size() + b.v.size());
    for(int i = 0; i < a.v.size(); i ++)
        for(int j = 0; j < b.v.size(); j ++)
            c.v[i + j] += a.v[i] * b.v[j];
    c.change();
    return c;
}

BigIntger& operator *= (BigIntger& a, BigIntger& b){
    return a = a * b;
}

// 除法 
BigIntger operator / (BigIntger a, BigIntger b){
    BigIntger ans, now;
    ans.v.clear(), ans.is_minus = a.is_minus ^ b.is_minus;
    now.v.clear(), now.is_minus = false;
    for(int i = a.v.size() - 1; i >= 0; i --){
        now.v.push_back(a.v[i]);
        int d = 0;
        while(now >= b){
            now -= b;
            d ++;
        }
        ans.v.push_back(d);
    }
    ans.change();
    return ans;
}

BigIntger& operator /= (BigIntger& a, BigIntger b){
    return a = (a / b);
}

// mod 运算 
// BigIntger operator % (BigIntger a, BigIntger b){
//     return a - (a / b) * b;
// }

// BigIntger& operator %= (BigIntger& a, BigIntger b){
//     return a = (a % b);
// }

// 快速幂
BigIntger quick_pow(BigIntger a, int k){
    BigIntger ans, zero, one;
    ans.is_minus = false, zero.is_minus = false, one.is_minus = false;
    ans.v.clear(), zero.v.clear(), one.v.clear();
    ans.v.push_back(1), one.v.push_back(1);
    while(k > 0){
        if(k & 1){
            ans = ans * a;
        }
        a = a * a;
        k /= 2;
        // cout << ans << ' ' << a << ' ' << k << endl;
    }
    return ans;
}

#endif
// int main(){
//     BigIntger a,b,c;
//     cin>>a>>b;
//     c = a+b;
//     cout<<c<<endl;
//     return 0;
// }

//有时候之求解部分 所以不能计算全部 需要只计算500位
/*
#include<cmath>
//变形 + 高精度快速幂
int main(){
    int p;
    cin>>p;
    cout<<(int)(log10(2)*p+1)<<endl;
    //qmi
    BigIntger res,num;
    res = 1,num = 2;
    while(p){
        if(p&1) res*=num;
        p>>=1;
        num*=num;
    }
    // res = quick_pow(num,p);
    num = 1;
    res -= num;
    int cnt = 0;
    if(res.v.size()<500){
        for(int i=499;i>res.v.size()-1;i--){
            cout<<0;
            cnt++;
            if(cnt%50==0) cout<<endl;
        } 
        for(int i=res.v.size()-1;i>=0;i--){
            cout<<res.v[i];
            cnt++;
            if(cnt%50==0) cout<<endl;
        } 
    }else{
        for(int i=499;i>=0;i--){
            cout<<res.v[i];
            cnt++;
            if(cnt%50==0) cout<<endl;
        }
    }
    return 0;
}
*/
