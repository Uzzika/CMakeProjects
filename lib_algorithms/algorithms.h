// Copyright 2024 Dudchenko Olesya

#pragma once
#include <iostream>
#include <vector>
using namespace std;

string take_pol_body(std::string str)
{
    size_t ind = str.find_first_of('=');
    string ret = "";
    for (int i = ind + 1; i < str.size(); i++)
    {
        ret += str[i];
    }
    ret += '+';
    return ret;
}

class expect
{
public:
    expect() = default;

    void wrong_monom_Power(int pow, int max)  // Проверяет корректность 
    // значения степени монома
    {
        if (pow < 0 || pow > max)
        {
            cerr << "cerr: wrong monom power";
            exit(101);
        }  // Если pow меньше 0 или больше max, выводит сообщение об
        // ошибке и завершает программу с кодом 101
    }
    void wrong_monom_Xi(int xi, int xmax)
    {
        if (xi <= 0 || xi > xmax)
        {
            cerr << "cerr: wrong monom Xi";
            exit(102);
        }
    }
    void wrong_pol_K(int k)
    {
        if (k < 0)
        {
            cerr << "cerr: pol wrong number of vars";
            exit(202);
        }
    }
    bool check_pol_K(int k)
    {
        if (k < 0)
        {
            cerr << "cerr: pol wrong number of vars" << std::endl;
            return true;
        }
        return false;
    }
    void wrong_pol_N(int n)
    {
        if (n < 0)
        {
            cerr << "cerr: pol power < 0";
            exit(201);
        }
    }
    bool check_pol_N(int n)
    {
        if (n < 0)
        {
            cerr << "cerr: pol power < 0" << endl;
            return true;
        }
        return false;
    }
    bool type_check(char c)
    {
        if (c == 'i') return false;
        if (c == 'd') return false;
        cerr << "cerr: wrong type ?: " << c << endl;

        return true;
    }
    bool unexpect_sbl_for_pol_name(char s)
    {
        string check =
            "qwertyuiopasdfghjklzxcvbnm";
        check += "QWERTYUIOPASDFGHJKLZXCVBNM";
        check += "1234567890_";
        for (auto i : check)
        {
            if (i == s) return false;
        }
        cerr << "cerr: wrong polinom name ?:" << s;
        return true;
    }
    bool bodyparcer_unexpsym(char s, size_t locate)
    {
        for (int i = 0; i < locate; i++)
        {
            cerr << " ";
        }
        cerr << "^ - cerr: unexpected symbol for polinom: " << s << endl;
        return true;
    }
    bool parcer(char s, short* state, short* todo, size_t locate)
    {
        string numbers = "1234567890";

        switch (*state)
        {
        case 0:
        {
            if (s == 'x')
            {
                (*state) = 1;
                (*todo) = 1;
                return false;
            }
            for (auto i : numbers)
            {
                if (s == i)
                {
                    (*state) = 2;
                    (*todo) = 2;
                    return false;
                }
            }
            return bodyparcer_unexpsym(s, locate);
        }
        case 1:
        {
            for (auto i : numbers)
            {
                if (s == i)
                {
                    (*state) = 3;
                    (*todo) = 3;
                    return false;
                }
            }
            return bodyparcer_unexpsym(s, locate);
        }
        case 2:
        {
            if (s == 'x')
            {
                (*state) = 1;
                (*todo) = 5;
                return false;
            }
            if (s == '.')
            {
                (*state) = 5;
                (*todo) = 4;
                return false;
            }
            if (s == '+')
            {
                (*state) = 0;
                (*todo) = 9;
                return false;
            }
            for (auto i : numbers)
            {
                if (s == i)
                {
                    (*state) = 2;
                    (*todo) = 4;
                    return false;
                }
            }
            return bodyparcer_unexpsym(s, locate);
        }
        case 3:
        {
            if (s == '^')
            {
                (*state) = 4;
                (*todo) = -1;
                return false;
            }
            if (s == '+')
            {
                (*state) = 0;
                (*todo) = 7;
                return false;
            }
            if (s == 'x')
            {
                (*state) = 1;
                (*todo) = 7;
                return false;
            }
            return bodyparcer_unexpsym(s, locate);
        }
        case 4:
        {
            if (s == '+')
            {
                (*state) = 0;
                (*todo) = 8;
                return false;
            }
            if (s == 'x')
            {
                (*state) = 1;
                (*todo) = 8;
                return false;
            }
            for (auto i : numbers)
            {
                if (s == i)
                {
                    (*state) = 4;
                    (*todo) = 6;
                    return false;
                }
            }
            return bodyparcer_unexpsym(s, locate);
        }
        case 5:
        {
            if (s == 'x')
            {
                (*state) = 1;
                (*todo) = 5;
                return false;
            }
            if (s == '+')
            {
                (*state) = 0;
                (*todo) = 9;
                return false;
            }
            for (auto i : numbers)
            {
                if (s == i)
                {
                    (*state) = 5;
                    (*todo) = 4;
                    return false;
                }
            }
            return bodyparcer_unexpsym(s, locate);
        }
        default:
            cerr << "critical error: unkown parcer state";
            exit(999);
            break;
        }

    }
    // Проверяет, содержится ли имя полинома в пространстве имен полиномов
    bool PolNameSpaceCheck(vector<string> Polnamespace, string name)
    {
        for (auto i : Polnamespace)
        {
            if (name == i)
            {
                return true;
            }
        }
        return false;
    }

    ~expect() = default;
};