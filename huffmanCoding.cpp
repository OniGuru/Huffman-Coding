#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
#include <cmath>


/////////////////////// Tree -> node //////////////////////
class Node
{
public:
    char c;
    int freq;
    Node *left, *right;
};


/////////////////// func for tree node ///////////////////
Node* getNode(char c, int freq, Node* left, Node* right)
{
    Node* t = new Node();
    t->c = c;
    t->freq = freq;
    t->left = left;
    t->right = right;

    return t;
}


///////// cmp object as to the order -> the heap /////////
class cmp
{
public:
    bool operator()(Node* left, Node* right)
    {
        // return through priority top most items first
        return left->freq > right->freq;
    }
};


///////////////// Huffman code to store /////////////////
void encode(Node* root, const std::string& str, std::unordered_map<char, std::string> &huffmanCode)
{
    // valid check
    if(!root)
        return;

    // if found
    if(!root->left && !root->right)
    {
        huffmanCode[root->c] = str;
        return; // ret to stop stack overflow
    }

    encode(root->left, str+"0", huffmanCode);
    encode(root->right, str+"1", huffmanCode);
}


/////////// Huffman -> decode the strings ///////////
std::string decode(Node* root, const std::string& s)
{
    std::string ans;
    Node* temp = root;
    for (char i : s)
    {
        if (i == '0')
        {
            temp = temp->left;
        }else
        {
            temp = temp->right;
        }
        if(!temp->left && !temp->right)
        {
            ans += temp->c;
            temp = root;
        }
    }
    return ans+'\n';
}


//////////// Use Huffman -> decode //////////////
void buildHuffman(const std::string& text)
{
    // Counts then stores freq in char
    std::unordered_map<char, int> freq;

    for(auto c:text)
    {
        freq[c]++;
    }

    // Create priority_queue for store leaves of tree
    std::priority_queue<Node*, std::vector<Node*>, cmp> tree;

    // Creating leaf node of each char in map -> root
    std::cout << "\nFrequency of each char in input string:\n";
    for(auto p : freq)
    {
        std::cout << p.first << " : " << p.second << std::endl;
        tree.push(getNode(p.first, p.second, nullptr, nullptr));
    }

    // Create tree
    while(tree.size() != 1)
    {
        Node* left = tree.top(); tree.pop();
        Node* right = tree.top(); tree.pop();

        // New node with left and right freq = sum of left && right
        int sum = left->freq + right->freq;
        tree.push(getNode(NULL, sum, left, right));
    }

    // Str ptr of root -> tree
    Node* root = tree.top();

    // Huffman tree -> str huffman -> in huffmanCode
    std::unordered_map<char, std::string> huffmanCode;
    encode(root, "", huffmanCode);

    std::cout << "\nHUFFMAN CODES ARE:\n" << std::endl;

    // Print code for each char
    for(const auto& p : huffmanCode)
    {
        std::cout<< p.first << " : " << p.second << std::endl;
    }
    std::cout << "\nOriginal string was: \n" << text << std::endl;

    // Appending code
    std::string res;
    for(char c : text)
    {
        res += huffmanCode[c];
    }
    std::cout << "\nEncoded string was: \n" << res <<std::endl;

    // Huffman -> decode
    std::cout << "\nDecoded string is : \n";
    std::string decodedStr = decode(root, res);
    std::cout << decodedStr << std::endl;

    // Finding compression ratio
    int org = 8*text.length();
    int conv = ceil(res.length()/8);
    double compressionRatio = (double)conv/org;
    std::cout << "String is compressed to " << compressionRatio * 100 << "% of the total size." << std::endl;

}




int main() {
    std::string str;
    std::getline(std::cin, str);

    buildHuffman(str);

    return 0;
}
