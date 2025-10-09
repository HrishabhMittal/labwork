#include "stack.hpp"
#include <cctype>
#include <cmath>
#include <iostream>
#include <map>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <string>
std::map<char,int> priority_map{
    {'^',0},{'*',1},{'/',1},{'+',2},{'-',2}
};
std::string in_to_post(const std::string& expr) {
    Stack<std::string,100> exprs;
    Stack<char,100> ops;
    int paren_count=0;
    for (char i:expr) {
        if (i==' ') continue;
        if (std::isalpha(i)) {
            std::string s;
            s+=i;
            exprs.push_back(s);
        } else {
            if (i=='(') {
                ops.push_back(i);
                paren_count++;
            } else if (i==')') {
                if (paren_count<=0) throw std::runtime_error("invalid expr (parenthesis)");
                paren_count--;
                while (ops.peek()!='(') {
                    auto x=exprs.pop_back();
                    exprs.peek()+=x;
                    exprs.peek()+=ops.pop_back();
                }
                ops.pop_back();
            } else if (priority_map.count(i)) {
                while (!ops.is_empty() && ops.peek()!='(' && priority_map[ops.peek()]<=priority_map[i]) {
                    auto x=exprs.pop_back();
                    exprs.peek()+=x;
                    exprs.peek()+=ops.pop_back();
                }
                ops.push_back(i);
            } else {
                throw std::runtime_error(std::string("unknown ops in expr")+i);
            }
        }
    }
    while (!ops.is_empty()) {
        auto x=exprs.pop_back();
        exprs.peek()+=x;
        exprs.peek()+=ops.pop_back();
    }
    auto out=exprs.pop_back();
    if (!exprs.is_empty()) throw std::runtime_error("incomplete expression");
    return out;
}

std::string post_to_pre(const std::string& expr) {
    Stack<std::string,100> exprs;
    for (char i:expr) {
        if (i==' ') continue;
        if (std::isalpha(i)) {
            std::string s;
            s+=i;
            exprs.push_back(s);
        } else {
            auto x=exprs.pop_back();
            exprs.peek()=i+exprs.peek()+x;
        }
    }
    return exprs.pop_back();
}

std::string pre_to_in(const std::string& expr) {
    Stack<std::string,100> exprs;
    for (int it=expr.size()-1;it>=0;it--) {
        char i = expr[it];
        if (i == ' ') continue;
        if (std::isalpha(i)) {
            std::string s;
            s += i;
            exprs.push_back(s);
        } else {
            auto left = exprs.pop_back();
            auto right = exprs.pop_back();
            std::string combined = "(" + left + i + right + ")";
            exprs.push_back(combined);
        }
    }
    return exprs.pop_back();
}
bool running=true;
void takeAll(std::stringstream& ss,std::string& str) {
    std::string temp;
    str="";
    while (ss>>temp) {
        str+=temp;
    }

}
float eval(const std::string& cm) {
    std::stringstream ss;
    ss<<cm;
    std::string cmd;
    ss>>cmd;
    static std::map<char,int> vars;
    if (cmd=="exit") {
        running=0;
        std::cout<<"exiting with code ";
        return 0;
    }
    std::string ogcmd;
    if (cmd.size()>2&&isalpha(cmd[0])&&cmd[1]=='=') {
        vars[cmd[0]]=std::stoi(cmd.substr(2,cmd.size()));
        std::cout<<"set "<<cmd[0]<<" equal to ";
        return vars[cmd[0]];
    } else if (cmd=="pre") {
        takeAll(ss,cmd);
        ogcmd=cmd;
        cmd=in_to_post(pre_to_in(cmd));
    } else if (cmd=="post") {
        takeAll(ss,cmd);
        ogcmd=cmd;
    } else if (cmd=="in") {
        takeAll(ss,cmd);
        ogcmd=cmd;
        cmd=in_to_post(cmd);
    } else {
        throw std::runtime_error("invalid command: "+cmd);
    }
    Stack<float,100> vals;
    for (char i:cmd) {
        if (isalpha(i)) {
            if (vars.count(i)) {
                vals.push_back(vars[i]);
            } else {
                throw std::runtime_error("variable not defined");
            }
        } else {
            auto y=vals.pop_back();
            auto x=vals.pop_back();
            if (i=='+') x+=y;
            else if (i=='-') x-=y;
            else if (i=='/') x/=y;
            else if (i=='*') x*=y;
            else if (i=='^') x=std::pow(x,y);
            else {
                throw std::runtime_error(std::string("invalid operator: ")+i);
            }
            vals.push_back(x);
        }
    }
    std::cout<<"expression "<<ogcmd<<" evaluates to: ";
    return vals.pop_back();
}
float eval() {
    static std::map<char,int> vars;
    std::string cmd;
    std::cin>>cmd;
    if (cmd=="exit") {
        running=0;
        std::cout<<"exiting with code ";
        return 0;
    }
    std::string ogcmd;
    if (cmd.size()>2&&isalpha(cmd[0])&&cmd[1]=='=') {
        vars[cmd[0]]=std::stoi(cmd.substr(2,cmd.size()));
        std::cout<<"set "<<cmd[0]<<" equal to ";
        return vars[cmd[0]];
    } else if (cmd=="pre") {
        std::cin>>cmd;
        ogcmd=cmd;
        cmd=in_to_post(pre_to_in(cmd));
    } else if (cmd=="post") {
        std::cin>>cmd;
        ogcmd=cmd;
    } else if (cmd=="in") {
        std::cin>>cmd;
        ogcmd=cmd;
        cmd=in_to_post(cmd);
    } else {
        throw std::runtime_error("invalid command: "+cmd);
    }
    Stack<float,100> vals;
    for (char i:cmd) {
        if (isalpha(i)) {
            if (vars.count(i)) {
                vals.push_back(vars[i]);
            } else {
                throw std::runtime_error("variable not defined");
            }
        } else {
            auto y=vals.pop_back();
            auto x=vals.pop_back();
            if (i=='+') x+=y;
            else if (i=='-') x-=y;
            else if (i=='/') x/=y;
            else if (i=='*') x*=y;
            else if (i=='^') x=std::pow(x,y);
            else {
                throw std::runtime_error(std::string("invalid operator: ")+i);
            }
            vals.push_back(x);
        }
    }
    std::cout<<"expression "<<ogcmd<<" evaluates to: ";
    return vals.pop_back();
}
int main(int argc,char**argv) {
    if (argc==2&&argv[1]==std::string("interactive")) {
        while (running) {
            std::cout<<"> ";
            std::cout<<eval()<<std::endl;
        }
    } else {
        std::cout<<eval("A=2");
        std::cout<<std::endl;
        std::cout<<eval("B=3");
        std::cout<<std::endl;
        std::cout<<eval("C=10");
        std::cout<<std::endl;
        std::cout<<eval("D=8");
        std::cout<<std::endl;
        std::cout<<eval("E=4");
        std::cout<<std::endl;
        std::cout<<eval("F=5");
        std::cout<<std::endl;
        std::cout<<eval("G=2");
        std::cout<<std::endl;
        std::cout<<eval("H=2");
        std::cout<<std::endl;
        std::cout<<eval("I=2");
        std::cout<<std::endl;
        std::cout<<eval("J=1");
        std::cout<<std::endl;
        std::cout<<eval("in ((A^B)*(C-D/E)+F)/(G*(H^I-J))");
        std::cout<<std::endl;
        std::cout<<eval("pre /+*^AB-C/DEF*G-^HIJ");
        std::cout<<std::endl;
        std::cout<<eval("post AB^CDE/-*F+GHI^J-*/");
        std::cout<<std::endl;
    }
}
