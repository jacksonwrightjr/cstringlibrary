// my_string.cpp
#include <iostream>
#include <limits>
#include "my_string.h"
#include "my_sstream.h"

// TODO(student): define all necessary my_string methods
// NOTE: some methods suggested here may not be required for you.
//       if you don't need a method, then you are not required to implement it
// NOTE: some methods not suggested here may be required for you.
//       if you need a method, then you are required to implement it (or re-engineer your solution to no longer need the method).

// my_string methods


// constructors
//   default (done for you.  you're welcome.)
my_string::my_string() : _data(new char[1]{0}), _capacity(1), _size(0) {}


//  **************************** rule of "3" ****************************

//     ******* my_string copy constructor *******

my_string::my_string(const my_string& other) : _data(other._data), _capacity(other._capacity), _size(other._size) {

    // allocate memory
    _data = new char[other._capacity];

    // assign size and capacity
    _capacity = other._capacity;
    _size = other._size;

    // copy data to newly allocated char array
    for(size_t i = 0; i < _capacity; i++) {
        _data[i] = other._data[i];
    }
    
}


//     ******* my_string copy assignment *******

my_string& my_string::operator=(const my_string& rhs) {

    // check if the data being copied is itself
    if (_data != rhs._data) {
        _capacity = rhs._capacity;
        _size = rhs._size;

        // loop through the rhs data array and copy values to new data array
        for (size_t i = 0; i < rhs._capacity; i++) {
            _data[i] = rhs._data[i];
        }

    }

    return *this;
}

//     destructor

my_string::~my_string() { 

    // deallocate memory and set capacity and size to 0
    delete [] _data;
    _capacity = 0;
    _size = 0;

}

//   c-string copy constructor

my_string::my_string(const char* other) : _data(new char[1]{0}), _capacity(1), _size(0) {

    // find dimensions of character array capacity and how filled it is
    size_t i = 0;
    while (other[i] != '\0') {
        i++;
    }

    _size = i;
    _capacity = _size;

    // allocate memory
    _data = new char[_capacity];

    for (size_t i = 0; i < _capacity; i++) {
        _data[i] = other[i];
    }

}

// **************************** helper ****************************


// **************************** element access ****************************

//   ******* at *******
char& my_string::at(size_type pos) {

    return _data[pos];

}

// ******* at for c-string *******
const char& my_string::at(size_type pos) const {

    return _data[pos];

}

//   front

//   ******* operator[] *******
const char& my_string::operator[](size_type index) const {

    return _data[index];

}

char& my_string::operator[](size_type index) {

    return _data[index];

}

// capacity

//   ******* empty *******
bool my_string::empty() const {

    if (_size == 0) {
        return true;
    } else {
        return false;
    }

}

//   ******* size *******
size_t my_string::size() const {

    return _size;

}


// **************************** operations ****************************
//   concatenation
//     my_string + my_string (non-member, friend)
//     my_string + c-string (non-member, friend)
//     my_string + char (non-member, friend)
//     c-string + my_string (non-member, friend)
//     char + my_string (non-member, friend)
//     my_string += my_string
//     my_string += c-string
//     my_string += char

// **************************** search ****************************
//   find

// **************************** non-member functions ****************************
//   relational operators

//     ******* my_string == my_string *******

bool operator==(const my_string& lhs, const my_string& rhs) {
    bool isEqual = true;

    // if the my_strings are not equal in size, they cannot be equal. return false immediately
    if (lhs.size() != rhs.size()) {
        return false;
    }

    // loop through the two given strings' _data arrays. if any portion is not equal, exit the loop and return false
    for (size_t i = 0; i < lhs.size(); i++) {

        if (lhs._data[i] != rhs._data[i]) {
            return false;
        }

    }

    return isEqual;
}

//     ******* my_string == c-string *******
bool operator==(const my_string& lhs, const char* rhs) {

    bool isEqual = true;

    // loop through the _data member of lhs and the char array rhs to check for equality. exit on inequality and return false
    for (size_t i = 0; i < lhs.size(); i++) {

        if (lhs._data[i] != rhs[i]) {
            return false;
        }

    }

    return isEqual;
}


//   **************************** stream operators ****************************

//     ******* ostream instertion operator *******
std::ostream& operator<<(std::ostream& os, const my_string& str) {

    for (size_t i = 0; i < str.size(); i++) {
        os << str.at(i);
    }

    return os;
}

//     ******* istream extraction operator *******
std::istream& operator>>(std::istream& os, my_string& str) {

    for (size_t i = 0; i < str.size(); i++) {

        if (str.at(i) == ' ') {
            break;
        }

        os >> str.at(i);
    }

    return os;
}

//     getline
//   numeric conversions
//     *to_string

my_string to_string(int value) {

    // initialize object to return
    my_string x;

    char y;

    char first;
    char second;

    if (value / 10 != 0) {

        first = (value / 10) + '0';
        second = (value % 10) + '0';

        x.push_back(first);
        x.push_back(second);

    } else {

        //std::cout << "[TO STRING] value is " << value << std::endl;
        y = value + '0';
        //std::cout << "[TO STRING 2] value is " << y << std::endl;
        x.push_back(y);
    }
    
    return x;

}

// **************************** other necessary functions ****************************

//   ******* insert *******
void my_string::insert(size_t pos, my_string x) {
    
    //std::cout << "This is x: " << x << std::endl;
    

    // create new char array to store the string with inserted input, adding the capacity of x to the capacity of the total capacity so as not to overflow
    char* goodData = new char[x._capacity + _capacity];


    // if pos is zero it made the function break
    if (pos == 0) {

        for (size_t e = x._size; e < _size + x._size; e++) {
            goodData[e] = _data[e - x._size];
        }

        for (size_t c = 0; c < x._size; c++ /* lol */) {
            goodData[c] = x._data[c];
        }

        _data = new char[_capacity + x._capacity];

        for (size_t d = 0; d < _size + x._size; d++) {
            //std::cout<< x._data[d] << std::endl;
            _data[d] = goodData[d];
        }
        
        _capacity += x._capacity;
        _size += x._size;

        delete [] goodData;

    } else {
        // loop to copy data before inserting string
        for (size_t i = 0; i < pos; i++) {
            //std::cout << "ran first loop" << std::endl;
            goodData[i] = _data[i];
        }
        // copy data from inserted string into new string
        for (size_t j = pos; j <= x._size + pos; j++) {
            //std::cout << "ran top loop" << std::endl;
            //std::cout << "X DATA " << x[j-pos] << std::endl;
            goodData[j] = x._data[j - pos];
        }
        // copy the rest of the remaining data to the new string
        for (size_t a = pos + x._size; a < _size; a++) {
            //std::cout << "ran mid loop" << std::endl;
            goodData[a] = _data[a - x._size];
        }

        // create new data array
        _data = new char[_capacity + x._capacity];

        for (size_t b = 0; b < _size + x._size; b++) {
            //std::cout << "ran final loop" << std::endl;
            //std::cout << "RAW DATA " << goodData[b] << std::endl;
            _data[b] = goodData[b];
        }

        _capacity += x._capacity;
        _size += x._size;

        delete [] goodData;
    }

}

// ******* erase *******
void my_string::erase(int pos, size_t length) {

    // loop through the length of specified erase
    for (size_t i = 0; i < length; i++) {

        // for each character to erase, we bump the rest of the characters to the right of "pos" one index to the left
        for (size_t i = pos; i < _size; i++) {

            _data[i] = _data[i + 1];

        }
    
    }
    _size -= length;
    _capacity -= length;

}

// ******* push_back *******
void my_string::push_back(char x) {

    //std::cout << "[PUSH BACK] pushing in " << x << std::endl;
    _data[_size] = x;
    _size++;
    _capacity++;

}

// my_istringstream methods

/*

my_istringstream::my_istringstream(const my_string& str) : _str(str), idx(0), state_fail(false), state_eof(str.empty()) {}

void my_istringstream::eat_whitespaces() {
    while (idx < _str.size() && isspace(_str[idx])) {
        idx++;
    }
}

my_istringstream& my_istringstream::operator>>(my_string& str) {
    eat_whitespaces();
    if (eof()) {
        state_fail = true;
    }
    if (fail()) {
        return *this;
    }
    my_string s;
    while (idx < _str.size() && !isspace(_str[idx])) {
        s += _str[idx++];
    }
    if (idx == _str.size()) {
        state_eof = true;
    }
    str = s;
    return *this;
}

my_istringstream& my_istringstream::operator>>(char& c) {
    eat_whitespaces();
    if (eof()) {
        state_fail = true;
    }
    if (fail()) {
        return *this;
    }
    if (idx < _str.size()) {
        c = _str[idx++];
    }
    if (idx == _str.size()) {
        state_eof = true;
    }
    return *this;
}

bool my_istringstream::good() const { return !(state_fail || state_eof); }
bool my_istringstream::fail() const { return state_fail; }
bool my_istringstream::eof() const { return state_eof; }

*/

// TODO(student): define other my_istringstream methods, if any
/*
int main() {
    my_string x = "505";
    x.erase(1, 1);
    std::cout << x << std::endl;
}
*/