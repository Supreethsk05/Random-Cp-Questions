#include <iostream>
#include <string>

using namespace std;

bool is_vowel(char c) {
    c = tolower(c);
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

char correct_letter(char c, int shift) {
    if (isalpha(c)) {
        char base = isupper(c) ? 'A' : 'a';
        return (char)(((c - base - shift + 26) % 26) + base);
    }
    return c;
}

string correct_text(const string &text) {
    string corrected;
    for (size_t i = 0; i < text.length(); ++i) {
        char c = text[i];
        if (i < text.length() - 1 && is_vowel(text[i + 1])) {
            if (c == 'g' || c == 'G') c = 'a';
            if (c == 'p' || c == 'P') c = 'z';
        } else {
            if (c == 's' || c == 'S') c = 'a';
            if (c == 'k' || c == 'K') c = 'z';
        }
        corrected += correct_letter(c, 3);
    }
    return corrected;
}

int main() {
    string text;
    getline(cin, text);

    string corrected_text = correct_text(text);
    cout << corrected_text << endl;

    return 0;
}
