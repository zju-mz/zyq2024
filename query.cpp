#include <bits/stdc++.h>
#include <openssl/sha.h>
using namespace std;

inline int toNum(char c){
    if(isdigit(c)) return c - '0';
    else return c - 'a' + 10;
}

class Trie{
private:
    struct Node{
        Node* ch[16];
        Node(){
            for(int i = 0; i < 16; i++)
                ch[i] = nullptr;
        }
    };
    Node *root;
    void clear(Node *cur){
        for(int i = 0; i < 16; i++)
            if(cur->ch[i]){
                clear(cur->ch[i]);
                cur->ch[i] = nullptr;
            }
        delete cur;
    }
public:
    Trie(){
        root = new Node;
    }
    ~Trie(){
        clear(root);
        root = nullptr;
    }
    void add(const string &s){
        Node *cur = root;
        for(int i = 0; i < s.size(); i++){
            int j = toNum(s[i]);
            if(cur->ch[j] == nullptr)
                cur->ch[j] = new Node;
            cur = cur->ch[j];
        }
    }
    bool check(const string &s) const{
        auto bytes_to_hex_string = [](const unsigned char* data, size_t len) {
            stringstream ss;
            for (size_t i = 0; i < len; ++i) {
                ss << std::hex << std::setw(2) << std::setfill('0') << (int)data[i];
            }
            return ss.str();
        };

        unsigned char hash[SHA256_DIGEST_LENGTH];
        SHA256_CTX sha256;
        SHA256_Init(&sha256);
        SHA256_Update(&sha256, s.c_str(), s.size());
        SHA256_Final(hash, &sha256);
        std::string hash_hex = bytes_to_hex_string(hash, sizeof(hash));

        Node *cur = root;
        for(int i = 0; i < hash_hex.size(); i++){
            int j = toNum(hash_hex[i]);
            if(cur->ch[j] == nullptr)
                return false;
            cur = cur->ch[j];
        }
        return true;
    }
};

const int grade[] = {0, 60, 90, 100, 110, 115};

int main(){
    ifstream fin("grades.txt");
    string input, mix;
    Trie trie;
    while(fin >> input)
        trie.add(input);
    cout << "Input your student ID (eg. 3230100001): " << endl;
    cin >> input;
    mix = input + '-';
    cout << "Input your name without space (eg-Chinese. CaiXukun) (eg-Foreigners. TaylorSwift): " << endl;
    cin >> input;
    mix += input;
    for(int i = 0; i < 6; i++){
        string qry = mix + '-' + to_string(grade[i]);
        if(trie.check(qry)){
            cout << "Your grade is: " << grade[i] << endl;
            return 0;
        }
    }
    cout << "No record." << endl;
    return 0;
}