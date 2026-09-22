#include <iostream>
#include <string>
#include <cctype>
using namespace std;
bool isPalindrome(const string& text) {
    int start = 0;
    int end = text.length() - 1;
    while (start < end) {
        // skipping symbols 
        while (start < end && !isalnum(text[start])) {
            start++;
        }
        while (start < end && !isalnum(text[end])) {
            end--;
        }
        if (tolower(text[start]) != tolower(text[end])) {
            return false;
        }

        start++;
        end--;
    }
    return true;
}

int main() {
    string input;
    cout << "Enter a string: ";
    getline(cin, input);

    // checking palindrome
    if (isPalindrome(input)) {
        cout << "\"" << input << "\" is a palindrome." << endl;
    } else {
        cout << "\"" << input << "\" is not a palindrome." << endl;
    }

    return 0;
}
