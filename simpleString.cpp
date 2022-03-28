#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

#include "simpleString.h"

#ifndef _MSC_FULL_VER // if not Visual Studio Compiler
    #warning "Klasa jest do zaimplementowania. Instrukcja w pliku naglowkowym"
#else
    #pragma message ("Klasa jest do zaimplementowania. Instrukcja w pliku naglowkowym")
#endif

std::size_t SimpleString::instances_ = 0;

SimpleString::SimpleString() {
    data_ =  new char[1];
    data_[0] = '\0';
    capacity_ = 0;
    size_ = 0;
    instances_ += 1;
}


SimpleString::SimpleString(char* data) {
    data_ = new char[strlen(data)];
    strcpy(data_,data);
    size_ = strlen(data_);
    capacity_ = size_;
    instances_ += 1;
}


SimpleString::SimpleString(const SimpleString &data) {
    data_ = new char[strlen(data.data_)];
    strcpy(data_, data.data_);
    size_ = strlen(data_);
    capacity_ = size_;
    instances_ += 1;
}


SimpleString::SimpleString(const char *const string) {
    data_ = new char[strlen(string)];
    strcpy(data_,string);
    size_ = strlen(data_);
    capacity_ = size_;
    instances_+= 1;
}


void SimpleString::assign(const char *new_text) {
    delete data_;
    data_ = new char[strlen(new_text)];
    strcpy(data_,new_text);
    size_ = strlen(data_);
    capacity_ = size_;
}


void SimpleString::append(const SimpleString &string) {
    strcat(this->data_, string.data_);
    size_ = (strlen(this->data_));
    capacity_ = size_;
}


bool SimpleString::equal_to(const SimpleString &array2, bool case_sensitive)const {
        if(case_sensitive) {
            int i;
            bool flag = false;
            i = 0;
            while (this->data_[i] == array2.data_[i] && flag == 0) {
                if (this->data_[i] == '\0' || array2.data_[i] == '\0') {
                    flag = true;
                }
                i++;
            }

            return flag;
        }
        else{
            int i;
            bool flag = false;
            i = 0;
            while ((this->data_[i] == array2.data_[i] ||this->data_[i] == (array2.data_[i] ^ 32)) && flag == 0) {
                if (this->data_[i] == '\0' || array2.data_[i] == '\0') {
                    flag = true;
                }
                i++;
            }
            return flag;
        }
}


