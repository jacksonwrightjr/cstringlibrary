// string_calculator.cpp
#include <iostream>
#include "my_string.h"
#include "./string_calculator.h"

using std::cout, std::endl;

unsigned int digit_to_decimal(char digit) {
    // TODO(student): implement
    int new_digit = digit - '0';
    if (new_digit < 0 || new_digit > 9) {
        throw std::invalid_argument("Digit out of range 0-9 (digit)");
    } else {
        return new_digit;
    }
}

char decimal_to_digit(unsigned int decimal) {
    // TODO(student): implement
    if (decimal > 9) {
        throw std::invalid_argument("Digit out of range 0-9 (decimal)");
    } else {
        return '0' + decimal;
    }
}

my_string trim_leading_zeros(my_string num) {
    // TODO(student): implement
    int i = 0;
    bool is_zero = true;
    if (num.at(0) == '-') {
        i++;
    }

    while (is_zero) {
        //bool x = num.at(i) == '0';
        //cout << "at value " << i << ", " << x << " value of num here is: " << num.at(i) << endl;

        if (num.at(i) == '0') {
            num.erase(i, 1);
        } else if (num.at(i) != '0') {
            is_zero = false;
        }
    }

    if (num.size() == 0 || (num[0] == '-' && num.size() == 1)) {
        num = "0";
    } 

    return num;
}

my_string add(my_string lhs, my_string rhs) {
    // TODO(student): implement

    bool both_neg = false;
    if (rhs.at(0) == '-' && lhs.at(0) == '-') {
        both_neg = true;
        rhs.erase(0, 1);
        lhs.erase(0, 1);
    } else if (rhs.at(0) == '-' && lhs.at(0) == '0') {
        both_neg = true;
        rhs.erase(0, 1);
    } else if (lhs.at(0) == '-' && rhs.at(0) == '0') {
        both_neg = true;
        lhs.erase(0, 1);
    } else if (lhs.at(0) == '-') {
        lhs.erase(0, 1);
        return subtract(rhs, lhs);
    } else if (rhs.at(0) == '-') {
        rhs.erase(0, 1);
        return subtract(lhs, rhs);
    }

    lhs = trim_leading_zeros(lhs);
    rhs = trim_leading_zeros(rhs);
    //cout << "lhs: " << lhs << endl << "rhs: " << rhs << endl;
    int overflow = 0;
    int left = 0;
    int rt = 0;
    int digit = 0;
    int zeros = 0;
    my_string builder_zeros;
    my_string result;

    //cout << "lhs size: " << lhs.size() << endl << "rhs size: " << rhs.size() << endl;

    if (rhs.size() > lhs.size()) {
        //cout << "pushing zeros into lhs" << endl;
        zeros = rhs.size() - lhs.size();
        for (int i = 0; i < zeros; i++) {
            builder_zeros.push_back('0');
        }
        //cout << "[ZERO STRING] " << builder_zeros << endl;
        lhs.insert(0, builder_zeros);
        //cout << "LHS AFTER ZEROS " << lhs << endl;
    } else if (lhs.size() > rhs.size()) {
        //cout << "pushing zeros into rhs" << endl;
        zeros = lhs.size() - rhs.size();
        for (int i = 0; i < zeros; i++) {
            builder_zeros.push_back('0');
        }
        rhs.insert(0, builder_zeros);
    }
    //cout << "RHS IS " << rhs << " LHS IS " << lhs << endl;

    while (lhs.size() != 0 || rhs.size() != 0) {
        //cout << "right index " << rhs.size() << endl;

        left = lhs.at(lhs.size() - 1) - '0';
        rt = rhs.at(rhs.size() - 1) - '0';
        //cout << "rhs at this point is " << rhs.at(rhs.size() - 1) << endl;

        digit = left + rt + overflow;
        //cout << "left is " << left << " and right is " << rt << endl;
        //cout << "digit = " << digit << endl;
        //cout << "digit string is " << to_string(digit) << endl;
        
        if (digit > 9) {
            overflow = 1;
            digit -= 10;
            result.insert(0, to_string(digit));
        } else {
            overflow = 0;
            result.insert(0, to_string(digit));
        }
        //cout << "result = " << result << endl;
        rhs.erase(rhs.size() - 1, 1);
        lhs.erase(lhs.size() - 1, 1);
    }
    if (overflow == 1) {
        result.insert(0, "1");
    }
    if (both_neg) {
        result.insert(0, "-");
    }
    return result;
}

my_string subtract(my_string lhs, my_string rhs) {
    // TODO(student): implement

    //cout << "[INIT] lhs " << lhs << endl << " rhs " << rhs << endl;

    rhs = trim_leading_zeros(rhs);
    lhs = trim_leading_zeros(lhs);
    my_string fill_zeros;
    int lmd_right;
    int lmd_left;
    my_string result;
    bool both_neg = false;
    bool same_num = false;

    if (rhs.size() == lhs.size()) {
        for (unsigned long i = 0; i < rhs.size(); i++) {
            // checking to see if they are the same number
            if (rhs.at(i) == lhs.at(i)) {
                same_num = true;
            } else {
                same_num = false;
                break;
            }
        }
    }

    if (same_num) {
        result = "0";
        return result;
    }

    // if both negative
    if (rhs.at(0) == '-' && lhs.at(0) == '-') {
        both_neg = true;
        lhs.erase(0, 1);
        rhs.erase(0, 1);

    } else if (rhs.at(0) == '-') { // if rhs negative
        rhs.erase(0, 1); // delete negative sign and kick to add
        return add(lhs, rhs);

    } else if (lhs.at(0) == '-') { // if lhs negative
        lhs.erase(0, 1); // delete negative sign and kick to add, then negate the answer
        result = add(lhs, rhs);
        result.insert(0, "-");

        return result;
    }

    // if the right number is longer than the left
    if (rhs.size() > lhs.size()) {
        int diff = rhs.size() - lhs.size();
        
        for (int a = 0; a < diff; a++) {
            fill_zeros.push_back('0');
        }
        
        // inserting zeros to the left if they are unequal in size
        lhs.insert(0, fill_zeros);
    //cout << "[INIT] lhs " << lhs << endl << " rhs " << rhs << endl;
    // if the left number is longer than the right
    } else if (lhs.size() > rhs.size()) {
        int diff = lhs.size() - rhs.size();

        for (int a = 0; a < diff; a++) {
            fill_zeros.push_back('0');
        }

        // inserting zeros again
        rhs.insert(0, fill_zeros);
        //cout << "[INIT] lhs " << lhs << endl << " rhs " << rhs << endl;
    }

    //cout << "[INIT] lhs " << lhs << endl << " rhs " << rhs << endl;

    // setting the leftmost digits of each number
    lmd_right = (rhs.at(0)) - '0';
    lmd_left = (lhs.at(0)) - '0';

    //cout << "right " << lmd_right << endl;
    //cout << "left " << lmd_left << endl;

    // if we need to perform an operation where rhs is bigger than lhs
    bool negate_ans = false;

    // if the leftmost digits are equal, iterate from left to right until you find a difference in lhs and rhs digits
    if (lmd_right == lmd_left) {

        for (size_t i = 0; i <= (lhs.size() - 1); i++) {
            //cout << "right " << lmd_right << " left " << lmd_left << endl;
            int r_dig = (rhs.at(i)) - '0';
            int l_dig = (lhs.at(i)) - '0';

                if (r_dig < l_dig) {
                    negate_ans = false;
                    break;
                } else if (r_dig > l_dig) {
                    negate_ans = true;
                    break;
                }
                //cout << "negate " << negate_ans << endl;
            }

    } else if (lmd_right > lmd_left) {
        negate_ans = true;
    }

    // todo: handle negative numbers and opposing signs. divert to add as needed
    
    if (negate_ans) {

        int top_dig = 0;
        int bot_dig = 0;
        int borrow = 0;
        int ans = 0;

        // begin subtraction
        for (int i = lhs.size() - 1; i >= 0; i--) {
            top_dig = (rhs.at(i)) - '0';
            bot_dig = (lhs.at(i)) - '0';

            //cout << "top " << top_dig << endl;
            //cout << "bottom " << bot_dig << endl;

            ans = (top_dig - borrow) - bot_dig;

            // if the bottom digit is larger than the top, we need to borrow from the left
            if (ans < 0) {
                ans += 10;
                borrow = 1;
            } else {
                borrow = 0;
            }

            // tack on the next digit to the final result and start over until loop ends
            //cout << "[ANS PUSH] " << ans << endl;
            result.insert(0, to_string(ans));
        }
    } else {
        int top_dig = 0;
        int bot_dig = 0;
        int borrow = 0;
        int ans = 0;

        // begin subtraction
        for (int i = lhs.size() - 1; i >= 0; i--) {
            //cout << "LHS actual = " << lhs << endl << "RHS actual = " << rhs << endl;
            //cout << "LHS IS " << lhs.at(i) << endl << "RHS IS " << rhs.at(i) << endl;
            top_dig = (lhs.at(i)) - '0';
            bot_dig = (rhs.at(i)) - '0';

            //cout << "top " << top_dig << endl;
            //cout << "bottom " << bot_dig << endl;

            ans = (top_dig - borrow) - bot_dig;

            // if the bottom digit is larger than the top, we need to borrow from the left
            if (ans < 0) {
                ans += 10;
                borrow = 1;
            } else {
                borrow = 0;
            }

            // tack on the next digit to the final result and start over until loop ends
            //cout << "[ANS PUSH] " << ans << endl;
            result.insert(0, to_string(ans));
            //cout << "inserted " << ans << endl;
        }
    }

    // todo: compute the final result
    result = trim_leading_zeros(result);
    
    if (both_neg) {

        if (result.at(0) == '0') {
            result.erase(0, 1);

        } else if (lmd_left < lmd_right) {
            return result;

        } else if (lmd_left == lmd_right) {
            for (size_t i = 0; i <= (lhs.size() - 1); i++) {
            //cout << "right " << lmd_right << " left " << lmd_left << endl;
            int r_dig = (rhs.at(i)) - '0';
            int l_dig = (lhs.at(i)) - '0';

                if (r_dig < l_dig) {
                    result.insert(0, "-");
                    return result;
                } else if (l_dig < r_dig) {
                    return result;
                }
                //cout << "negate " << negate_ans << endl;
            }
        } else {
            result.insert(0, "-");
        }
    } else if (negate_ans) {
        result.insert(0, "-");
    }

    return result;
}


my_string multiply(my_string lhs, my_string rhs) {
    // TODO(student): implement
   
    lhs = trim_leading_zeros(lhs);
    rhs = trim_leading_zeros(rhs);

    my_string result;
    my_string floater;

    // checking if left number is neg
    bool left_lower = false;
    if (lhs.at(0) == '-') {
       left_lower = true;
       lhs.erase(0, 1);
    }

    // checking if right number is neg
    bool rt_lower = false;
    if (rhs.at(0) == '-') {
       rt_lower = true;
       rhs.erase(0, 1);
    }

    // if only one number is negative, we negate the answer
    

    if (lhs.size() < rhs.size()) {
    
        floater = lhs;
        lhs = rhs;
        rhs = floater;
    
    }

    my_string floatSumRow;
    my_string floatSum = "0"; 
    int floatSumRowCount = 0;
    int carry = 0;

    for (int i = rhs.size() - 1; i >= 0; i--) {

        int bot_digit = rhs.at(i) - '0';

        for (int j = lhs.size() - 1; j >= 0; j--) {
            int top_digit = digit_to_decimal(lhs.at(j));
            int floatProd = (bot_digit * top_digit) + carry;

            carry = 0;

            if (floatProd < 10) {
                my_string floatSumDigit = to_string(floatProd);
                floatSumRow.insert(0, floatSumDigit);

            } else {

                if(j != 0) {

                    my_string floatSumDigit = to_string(floatProd % 10);
                    floatSumRow.insert(0, floatSumDigit);
                    carry = floatProd / 10;

                } else {

                    my_string floatSumDigit = to_string(floatProd);
                    floatSumRow.insert(0, floatSumDigit);

                }

            }
        }
        for (int i = 0; i < floatSumRowCount; i++) {
            floatSumRow.push_back('0');
        }

        floatSumRowCount++;
        floatSum = add(floatSumRow, floatSum);
        floatSumRow = "";
    }

    result.insert(0, floatSum);

    if( (left_lower && !rt_lower) || (!left_lower && rt_lower)) {

       result.insert(0, "-");
    
    }

    //cout << "result = " << result;

    return result;
}