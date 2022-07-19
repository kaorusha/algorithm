# ifndef KARATSUBA_H_
# define KARATSUBA_H_
# include <string>
# include <iostream>
# include <algorithm>
/**
 * @brief https://en.wikipedia.org/wiki/Karatsuba_algorithm
 * call multiplication() after construction
 */
class Karatsuba {
private:
    bool positive = true;
    std::string num1;
    std::string num2;
    // split string with lower digit of given length
    void split (std::string& input, int& len, std::string& h, std::string& l) {
        auto total = input.length();
        h = input.substr(0, total - len);
        l = input.substr(total - len, len);
    }
    // add two numbers, leading zeros are not accepted
    std::string add (std::string num1, std::string num2) {
        if (num1[0] == '-' && num2[0] != '-') return subtract(num2, num1);
        if (num1[0] != '-' && num2[0] == '-') return subtract(num1, num2);
        bool negative = false;
        if (num1[0] == '-' && num2[0] == '-') negative = true; 
        // two positive numbers
        std::string ans;
        std::reverse(num1.begin(), num1.end());
        std::reverse(num2.begin(), num2.end());
        int carry = 0;
        int n1 = num1.length();
        int n2 = num2.length();
        for (int i = 0; i < std::max(n1,n2); ++i) {
            if (i < n1) carry += (num1[i] - '0');
            if (i < n2) carry += (num2[i] - '0');
            ans += std::to_string(carry % 10);
            carry /= 10;
        }
        if (carry > 0) ans += std::to_string(carry);
        if (negative) ans += '-';
        std::reverse(ans.begin(), ans.end());
        return ans;
    }
    // return true if num1 >= num2; constraint: accept positive numbers
    bool greater (std::string& num1, std::string& num2) {
        int n1 = num1.length();
        int n2 = num2.length();
        if (n1 > n2) return true;
        else if (n1 == n2) {
            for (int i = 0; i < n1; ++i) {
                if (num1[i] > num2[i]) return true;
                else if (num1[i] == num2[i]) continue;
                else return false;
            }
            // identical
            return true;
        }
        else return false;
    }
    // return num1 - num2, constraint: accept positive numbers
    std::string subtract (std::string num1, std::string num2) {
        std::string ans;
        bool negative = false;
        if (!greater(num1, num2)) {
            num1.swap(num2);
            negative = true;
        }
        std::reverse(num1.begin(), num1.end());
        std::reverse(num2.begin(), num2.end());
        int carry = 0;
        int n1 = num1.length();
        int n2 = num2.length();
        for (int i = 0; i < n1; ++i) {
            carry += (num1[i] - '0');
            if (i < n2) carry -= (num2[i] - '0');
            if (carry >= 0) {
                ans += std::to_string(carry);
                carry = 0;
            } else {
                ans += std::to_string(carry + 10);
                carry = -1;
            }    
        }
        while (ans.back() == '0') ans.pop_back();
        if (negative) ans += '-';
        std::reverse(ans.begin(), ans.end());
        return ans;
    }
public:
    // constructor, pre-process string, remove leading negative sign 
    Karatsuba(std::string& s1, std::string& s2){
        if (s1[0] == '-') {
            if (s2[0] != '-') positive = false;
            this->num1 = s1.substr(1);
        } else this->num1 = s1;

        if (s2[0] == '-') {
            if (num1[0] != '-') positive = false;
            this->num2 = s2.substr(1);
        } else this->num2 = s2;
    }
    std::string multiplication () {
        std::string ans = karatsuba(this->num1, this->num2);
        if (!positive) ans.insert(ans.begin(), '-'); 
        return ans;
    }
    // order O(n^2), constraint: accept positive numbers
    std::string grade_school (std::string num1, std::string num2) {
        if (num1 == "0" || num2 == "0") return "0";
        std::string ans = "0";
        for (int i = num1.length() - 1; i >= 0; --i) {
            std::string sum = "0";
            for (int j = 0; j < num2.length(); ++j) {
                if (sum != "0") sum += '0';
                sum = add(sum, std::to_string((num1[i] - '0') * (num2[j] - '0')));
            }
            for (int k = num1.length() - 1; k > i; --k) sum += '0';
            ans = add(ans, sum);
        }
        return ans;
    }
    // order O(n*log(n)), constraint: accept positive numbers
    std::string karatsuba (std::string num1, std::string num2) {
        if (num1.length() < 2 || num2.length() < 2) return grade_school(num1, num2);
            
        /* Calculates the size of the numbers. */
        int m = std::min(num1.length(), num2.length());
        int m2 = m / 2;

        /* Split the digit sequences in the middle. */
        std::string h1, l1, h2, l2;
        split(num1, m2, h1, l1);
        split(num2, m2, h2, l2);

        /* 3 recursive calls made to numbers approximately half the size. */
        auto z0 = karatsuba (l1, l2);
        auto z1 = karatsuba (add(l1, h1), add(l2, h2));
        auto z2 = karatsuba (h1, h2);
        auto temp = subtract(z1, add(z2,z0));

        return add(add(z2 + std::string(m2 * 2,'0'), temp + std::string(m2, '0')), z0);
    }
};
# endif /* KARATSUBA_H_ */