//
// Created by anranzhai on 2020/3/29.
//
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <array>
#include <unordered_map>
#include <set>
using namespace std;
//递归超出时间限制
bool findW(std::string &word,int index,std::vector<std::pair<int,int>> &gone,const std::vector<std::vector<char>>& board,int row,int col){
    if(index==word.size()){
        return true;
    }
    if(row<board.size()-1 && board[row+1][col]==word[index] && std::find(gone.begin(),gone.end(),std::pair<int,int>(row+1,col))==gone.end()){
        gone.emplace_back(row+1,col);
        if(findW(word,index+1,gone,board,row+1,col))
            return true;
        else
            gone.pop_back();
    }
    if(row>0 && board[row-1][col]==word[index] && std::find(gone.begin(),gone.end(),std::pair<int,int>(row-1,col))==gone.end()){
        gone.emplace_back(row-1,col);
        if(findW(word,index+1,gone,board,row-1,col))
            return true;
        else
            gone.pop_back();
    }
    if(col<board[0].size()-1 && board[row][col+1]==word[index] && std::find(gone.begin(),gone.end(),std::pair<int,int>(row,col+1))==gone.end()){
        gone.emplace_back(row,col+1);
        if(findW(word,index+1,gone,board,row,col+1))
            return true;
        else
            gone.pop_back();
    }
    if(col>0 && board[row][col-1]==word[index] && std::find(gone.begin(),gone.end(),std::pair<int,int>(row,col-1))==gone.end()){
        gone.emplace_back(row,col-1);
        if(findW(word,index+1,gone,board,row,col-1))
            return true;
        else
            gone.pop_back();
    }
    return false;
}
std::vector<std::string> findWs(std::vector<std::vector<char>>& board, std::vector<std::string>& words) {
    if(board.size()==0 || words.size()==0) return std::vector<std::string>();
    std::vector<std::string> ret;
    for(auto word:words){
        bool isFind= false;
        for(int row=0;row<board.size();row++){
            if(std::find(board[row].begin(),board[row].end(),word[0])==board[row].end())
                continue;
            else{
                for(int col=0;col<board[row].size();col++){
                    if(word[0]==board[row][col]){
                        std::vector<std::pair<int,int>> gone{std::pair<int,int>(row,col)};
                        if(findW(word,1,gone,board,row,col)){
                            ret.emplace_back(word);
                            isFind=true;
                            break;
                        }
                    }
                }
            }
            if(isFind)break;
        }
    }
    std::sort(ret.begin(),ret.end());
    return ret;
}

//Trie树
struct TreeNode{
    std::string word="";
    std::unordered_map<char,TreeNode*> next;
};
void backtracking(int row,int col,TreeNode* treeNode,std::vector<std::vector<char>>& board,std::vector<std::string> &ret){
    char letter=board[row][col];
    TreeNode* cur=treeNode->next[letter];
    if(cur->word != ""){
        ret.emplace_back(cur->word);
        //查到之后就把words设为“”,避免重复
        cur->word="";
    }
    //保证同一个单词不重复访问board的同一位置
    board[row][col] = '#';

    // explore neighbor cells in around-clock directions: up, right, down, left
    std::array<int,4> rowOffset{-1, 0, 1, 0};
    std::array<int,4> colOffset{0, 1, 0, -1};
    for (int i = 0; i < 4; ++i) {
        int newRow = row + rowOffset[i];
        int newCol = col + colOffset[i];
        if (newRow < 0 || newRow >= board.size() || newCol < 0 || newCol >= board[0].size() || board[newRow][newCol]=='#') {
            continue;
        }
        if (cur->next.count(board[newRow][newCol])!=0) {
            backtracking(newRow, newCol, cur,board,ret);
        }
    }

    // End of EXPLORATION, restore the original letter in the board.
    board[row][col] = letter;
    if(cur->next.empty())
        treeNode->next.erase(letter);

}
std::vector<std::string> findWords(std::vector<std::vector<char>>& board, std::vector<std::string>& words) {
    TreeNode* treeNode=new TreeNode;
    for(auto word:words){
        TreeNode* cur=treeNode;
        for(int i=0;i<word.size();i++){
            if(cur->next.count(word[i])==0)
                cur->next[word[i]]=new TreeNode;
            cur=cur->next[word[i]];
        }
        cur->word=word;
    }
    std::vector<std::string> ret;
    for(int i=0;i<board.size();i++){
        for(int j=0;j<board[0].size();j++){
            if(treeNode->next.count(board[i][j])!=0){
                backtracking(i, j, treeNode,board,ret);
            }
        }
    }
    std::sort(ret.begin(),ret.end());
    return ret;
}


class TrieNode{
public:
    TrieNode():isEnd(false),path(0){
        //memset只能填int值，注意指针数组初始化分配空间
        //# include <string.h>//memset是c函数
        //void *memset(void *s, int c, unsigned long n);
        memset(children,0,sizeof(children));
    }
    //不能是private，外部需要直接调用，或者设置成private并对每个操作定义对应函数
    bool isEnd;
    int path;
    TrieNode* children[26];
};
class Trie {
public:
    /** Initialize your data structure here. */
    Trie() {
        root=new TrieNode();
    }

    /** Inserts a word into the trie. */
    void insert(string word) {
        TrieNode* node=root;
        for(int i=0;i<word.size();i++){
            int index=word[i]-'a';
            if(node->children[index]==0)
                node->children[index]=new TrieNode();
            node->children[index]->path++;
            node=node->children[index];
        }
        node->isEnd=true;
    }

    //添加hasPrefix避免后两个函数包含重复代码
    TrieNode* hasPrefix(string prefix) {
        TrieNode* node=root;
        for(auto w:prefix){
            int index=w-'a';
            if(node->children[index]==0)
                return nullptr;
            else
                node=node->children[index];
        }
        return node;
    }

    /** Returns if the word is in the trie. */
    bool search(string word) {
        TrieNode* node=hasPrefix(word);
        return node==nullptr?false:node->isEnd;
    }

    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        TrieNode* node=hasPrefix(prefix);
        return node!=nullptr;
    }
    TrieNode* root;
};
class Solution {
public:
    vector<string> ret;
    array<int,4> row{-1,0,1,0};
    array<int,4> col{0,1,0,-1};
    void dfs(vector<vector<char>>& board,vector<vector<bool>>& visited,int i,int j,TrieNode* curnode,string path){
        if(curnode->isEnd){
            ret.push_back(path);
            //避免重复获取同一个string
            curnode->isEnd=false;
        }

        for(int k=0;k<4;k++){
            int newrow=i+row[k];
            int newcol=j+col[k];
            if(newrow<0 || newrow>=board.size() || newcol<0 || newcol>=board[0].size() || visited[newrow][newcol])
                continue;
            int index=board[newrow][newcol]-'a';
            if(curnode->children[index]!=nullptr){
                visited[newrow][newcol]=true;
                dfs(board,visited,newrow,newcol,curnode->children[index],path+board[newrow][newcol]);
                visited[newrow][newcol]= false;
            }
        }
    }

    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        if(board.size()==0)
            return vector<string>();
        Trie* trie=new Trie();
        for(auto s:words)
            trie->insert(s);
        vector<vector<bool>> visited(board.size(),vector<bool>(board[0].size(),false));
        for(int i=0;i<board.size();i++){
            for(int j=0;j<board[0].size();j++){
                int index=board[i][j]-'a';
                if(trie->root->children[index]!= nullptr){
                    visited[i][j]=true;
                    string s(1,board[i][j]);
                    dfs(board,visited,i,j,trie->root->children[index],s);
                    visited[i][j]=false;
                }
            }
        }
        return ret;
    }
};

int main(){
    Solution solution;
    std::vector<std::vector<char>> vec{{'a','a','a','a'},{'a','a','a','a'},{'a','a','a','a'},{'a','a','a','a'},{'b','c','d','e'},{'f','g','h','i'},{'j','k','l','m'},{'n','o','p','q'},{'r','s','t','u'},{'v','w','x','y'},{'z','z','z','z'}};
    std::vector<std::string> str{"aaaaaaaaaaaaaaaa","aaaaaaaaaaaaaaab","aaaaaaaaaaaaaaac","aaaaaaaaaaaaaaad","aaaaaaaaaaaaaaae","aaaaaaaaaaaaaaaf","aaaaaaaaaaaaaaag","aaaaaaaaaaaaaaah","aaaaaaaaaaaaaaai","aaaaaaaaaaaaaaaj","aaaaaaaaaaaaaaak","aaaaaaaaaaaaaaal","aaaaaaaaaaaaaaam","aaaaaaaaaaaaaaan","aaaaaaaaaaaaaaao","aaaaaaaaaaaaaaap","aaaaaaaaaaaaaaaq","aaaaaaaaaaaaaaar","aaaaaaaaaaaaaaas","aaaaaaaaaaaaaaat","aaaaaaaaaaaaaaau","aaaaaaaaaaaaaaav","aaaaaaaaaaaaaaaw","aaaaaaaaaaaaaaax","aaaaaaaaaaaaaaay","aaaaaaaaaaaaaaaz","aaaaaaaaaaaaaaba","aaaaaaaaaaaaaabb","aaaaaaaaaaaaaabc","aaaaaaaaaaaaaabd","aaaaaaaaaaaaaabe","aaaaaaaaaaaaaabf","aaaaaaaaaaaaaabg","aaaaaaaaaaaaaabh","aaaaaaaaaaaaaabi","aaaaaaaaaaaaaabj","aaaaaaaaaaaaaabk","aaaaaaaaaaaaaabl","aaaaaaaaaaaaaabm","aaaaaaaaaaaaaabn","aaaaaaaaaaaaaabo","aaaaaaaaaaaaaabp","aaaaaaaaaaaaaabq","aaaaaaaaaaaaaabr","aaaaaaaaaaaaaabs","aaaaaaaaaaaaaabt","aaaaaaaaaaaaaabu","aaaaaaaaaaaaaabv","aaaaaaaaaaaaaabw","aaaaaaaaaaaaaabx","aaaaaaaaaaaaaaby","aaaaaaaaaaaaaabz","aaaaaaaaaaaaaaca","aaaaaaaaaaaaaacb","aaaaaaaaaaaaaacc","aaaaaaaaaaaaaacd","aaaaaaaaaaaaaace","aaaaaaaaaaaaaacf","aaaaaaaaaaaaaacg","aaaaaaaaaaaaaach","aaaaaaaaaaaaaaci","aaaaaaaaaaaaaacj","aaaaaaaaaaaaaack","aaaaaaaaaaaaaacl","aaaaaaaaaaaaaacm","aaaaaaaaaaaaaacn","aaaaaaaaaaaaaaco","aaaaaaaaaaaaaacp","aaaaaaaaaaaaaacq","aaaaaaaaaaaaaacr","aaaaaaaaaaaaaacs","aaaaaaaaaaaaaact","aaaaaaaaaaaaaacu","aaaaaaaaaaaaaacv","aaaaaaaaaaaaaacw","aaaaaaaaaaaaaacx","aaaaaaaaaaaaaacy","aaaaaaaaaaaaaacz","aaaaaaaaaaaaaada","aaaaaaaaaaaaaadb","aaaaaaaaaaaaaadc","aaaaaaaaaaaaaadd","aaaaaaaaaaaaaade","aaaaaaaaaaaaaadf","aaaaaaaaaaaaaadg","aaaaaaaaaaaaaadh","aaaaaaaaaaaaaadi","aaaaaaaaaaaaaadj","aaaaaaaaaaaaaadk","aaaaaaaaaaaaaadl","aaaaaaaaaaaaaadm","aaaaaaaaaaaaaadn","aaaaaaaaaaaaaado","aaaaaaaaaaaaaadp","aaaaaaaaaaaaaadq","aaaaaaaaaaaaaadr","aaaaaaaaaaaaaads","aaaaaaaaaaaaaadt","aaaaaaaaaaaaaadu","aaaaaaaaaaaaaadv","aaaaaaaaaaaaaadw","aaaaaaaaaaaaaadx","aaaaaaaaaaaaaady","aaaaaaaaaaaaaadz","aaaaaaaaaaaaaaea","aaaaaaaaaaaaaaeb","aaaaaaaaaaaaaaec","aaaaaaaaaaaaaaed","aaaaaaaaaaaaaaee","aaaaaaaaaaaaaaef","aaaaaaaaaaaaaaeg","aaaaaaaaaaaaaaeh","aaaaaaaaaaaaaaei","aaaaaaaaaaaaaaej","aaaaaaaaaaaaaaek","aaaaaaaaaaaaaael","aaaaaaaaaaaaaaem","aaaaaaaaaaaaaaen","aaaaaaaaaaaaaaeo","aaaaaaaaaaaaaaep","aaaaaaaaaaaaaaeq","aaaaaaaaaaaaaaer","aaaaaaaaaaaaaaes","aaaaaaaaaaaaaaet","aaaaaaaaaaaaaaeu","aaaaaaaaaaaaaaev","aaaaaaaaaaaaaaew","aaaaaaaaaaaaaaex","aaaaaaaaaaaaaaey","aaaaaaaaaaaaaaez","aaaaaaaaaaaaaafa","aaaaaaaaaaaaaafb","aaaaaaaaaaaaaafc","aaaaaaaaaaaaaafd","aaaaaaaaaaaaaafe","aaaaaaaaaaaaaaff","aaaaaaaaaaaaaafg","aaaaaaaaaaaaaafh","aaaaaaaaaaaaaafi","aaaaaaaaaaaaaafj","aaaaaaaaaaaaaafk","aaaaaaaaaaaaaafl","aaaaaaaaaaaaaafm","aaaaaaaaaaaaaafn","aaaaaaaaaaaaaafo","aaaaaaaaaaaaaafp","aaaaaaaaaaaaaafq","aaaaaaaaaaaaaafr","aaaaaaaaaaaaaafs","aaaaaaaaaaaaaaft","aaaaaaaaaaaaaafu","aaaaaaaaaaaaaafv","aaaaaaaaaaaaaafw","aaaaaaaaaaaaaafx","aaaaaaaaaaaaaafy","aaaaaaaaaaaaaafz","aaaaaaaaaaaaaaga","aaaaaaaaaaaaaagb","aaaaaaaaaaaaaagc","aaaaaaaaaaaaaagd","aaaaaaaaaaaaaage","aaaaaaaaaaaaaagf","aaaaaaaaaaaaaagg","aaaaaaaaaaaaaagh","aaaaaaaaaaaaaagi","aaaaaaaaaaaaaagj","aaaaaaaaaaaaaagk","aaaaaaaaaaaaaagl","aaaaaaaaaaaaaagm","aaaaaaaaaaaaaagn","aaaaaaaaaaaaaago","aaaaaaaaaaaaaagp","aaaaaaaaaaaaaagq","aaaaaaaaaaaaaagr","aaaaaaaaaaaaaags","aaaaaaaaaaaaaagt","aaaaaaaaaaaaaagu","aaaaaaaaaaaaaagv","aaaaaaaaaaaaaagw","aaaaaaaaaaaaaagx","aaaaaaaaaaaaaagy","aaaaaaaaaaaaaagz","aaaaaaaaaaaaaaha","aaaaaaaaaaaaaahb","aaaaaaaaaaaaaahc","aaaaaaaaaaaaaahd","aaaaaaaaaaaaaahe","aaaaaaaaaaaaaahf","aaaaaaaaaaaaaahg","aaaaaaaaaaaaaahh","aaaaaaaaaaaaaahi","aaaaaaaaaaaaaahj","aaaaaaaaaaaaaahk","aaaaaaaaaaaaaahl","aaaaaaaaaaaaaahm","aaaaaaaaaaaaaahn","aaaaaaaaaaaaaaho","aaaaaaaaaaaaaahp","aaaaaaaaaaaaaahq","aaaaaaaaaaaaaahr","aaaaaaaaaaaaaahs","aaaaaaaaaaaaaaht","aaaaaaaaaaaaaahu","aaaaaaaaaaaaaahv","aaaaaaaaaaaaaahw","aaaaaaaaaaaaaahx","aaaaaaaaaaaaaahy","aaaaaaaaaaaaaahz","aaaaaaaaaaaaaaia","aaaaaaaaaaaaaaib","aaaaaaaaaaaaaaic","aaaaaaaaaaaaaaid","aaaaaaaaaaaaaaie","aaaaaaaaaaaaaaif","aaaaaaaaaaaaaaig","aaaaaaaaaaaaaaih","aaaaaaaaaaaaaaii","aaaaaaaaaaaaaaij","aaaaaaaaaaaaaaik","aaaaaaaaaaaaaail","aaaaaaaaaaaaaaim","aaaaaaaaaaaaaain","aaaaaaaaaaaaaaio","aaaaaaaaaaaaaaip","aaaaaaaaaaaaaaiq","aaaaaaaaaaaaaair","aaaaaaaaaaaaaais","aaaaaaaaaaaaaait","aaaaaaaaaaaaaaiu","aaaaaaaaaaaaaaiv","aaaaaaaaaaaaaaiw","aaaaaaaaaaaaaaix","aaaaaaaaaaaaaaiy","aaaaaaaaaaaaaaiz","aaaaaaaaaaaaaaja","aaaaaaaaaaaaaajb","aaaaaaaaaaaaaajc","aaaaaaaaaaaaaajd","aaaaaaaaaaaaaaje","aaaaaaaaaaaaaajf","aaaaaaaaaaaaaajg","aaaaaaaaaaaaaajh","aaaaaaaaaaaaaaji","aaaaaaaaaaaaaajj","aaaaaaaaaaaaaajk","aaaaaaaaaaaaaajl","aaaaaaaaaaaaaajm","aaaaaaaaaaaaaajn","aaaaaaaaaaaaaajo","aaaaaaaaaaaaaajp","aaaaaaaaaaaaaajq","aaaaaaaaaaaaaajr","aaaaaaaaaaaaaajs","aaaaaaaaaaaaaajt","aaaaaaaaaaaaaaju","aaaaaaaaaaaaaajv","aaaaaaaaaaaaaajw","aaaaaaaaaaaaaajx","aaaaaaaaaaaaaajy","aaaaaaaaaaaaaajz","aaaaaaaaaaaaaaka","aaaaaaaaaaaaaakb","aaaaaaaaaaaaaakc","aaaaaaaaaaaaaakd","aaaaaaaaaaaaaake","aaaaaaaaaaaaaakf","aaaaaaaaaaaaaakg","aaaaaaaaaaaaaakh","aaaaaaaaaaaaaaki","aaaaaaaaaaaaaakj","aaaaaaaaaaaaaakk","aaaaaaaaaaaaaakl","aaaaaaaaaaaaaakm","aaaaaaaaaaaaaakn","aaaaaaaaaaaaaako","aaaaaaaaaaaaaakp","aaaaaaaaaaaaaakq","aaaaaaaaaaaaaakr","aaaaaaaaaaaaaaks","aaaaaaaaaaaaaakt","aaaaaaaaaaaaaaku","aaaaaaaaaaaaaakv","aaaaaaaaaaaaaakw","aaaaaaaaaaaaaakx","aaaaaaaaaaaaaaky","aaaaaaaaaaaaaakz","aaaaaaaaaaaaaala","aaaaaaaaaaaaaalb","aaaaaaaaaaaaaalc","aaaaaaaaaaaaaald","aaaaaaaaaaaaaale","aaaaaaaaaaaaaalf","aaaaaaaaaaaaaalg","aaaaaaaaaaaaaalh","aaaaaaaaaaaaaali","aaaaaaaaaaaaaalj","aaaaaaaaaaaaaalk","aaaaaaaaaaaaaall","aaaaaaaaaaaaaalm","aaaaaaaaaaaaaaln","aaaaaaaaaaaaaalo","aaaaaaaaaaaaaalp","aaaaaaaaaaaaaalq","aaaaaaaaaaaaaalr","aaaaaaaaaaaaaals","aaaaaaaaaaaaaalt","aaaaaaaaaaaaaalu","aaaaaaaaaaaaaalv","aaaaaaaaaaaaaalw","aaaaaaaaaaaaaalx","aaaaaaaaaaaaaaly","aaaaaaaaaaaaaalz","aaaaaaaaaaaaaama","aaaaaaaaaaaaaamb","aaaaaaaaaaaaaamc","aaaaaaaaaaaaaamd","aaaaaaaaaaaaaame","aaaaaaaaaaaaaamf","aaaaaaaaaaaaaamg","aaaaaaaaaaaaaamh","aaaaaaaaaaaaaami","aaaaaaaaaaaaaamj","aaaaaaaaaaaaaamk","aaaaaaaaaaaaaaml","aaaaaaaaaaaaaamm","aaaaaaaaaaaaaamn","aaaaaaaaaaaaaamo","aaaaaaaaaaaaaamp","aaaaaaaaaaaaaamq","aaaaaaaaaaaaaamr","aaaaaaaaaaaaaams","aaaaaaaaaaaaaamt","aaaaaaaaaaaaaamu","aaaaaaaaaaaaaamv","aaaaaaaaaaaaaamw","aaaaaaaaaaaaaamx","aaaaaaaaaaaaaamy","aaaaaaaaaaaaaamz","aaaaaaaaaaaaaana","aaaaaaaaaaaaaanb","aaaaaaaaaaaaaanc","aaaaaaaaaaaaaand","aaaaaaaaaaaaaane","aaaaaaaaaaaaaanf","aaaaaaaaaaaaaang","aaaaaaaaaaaaaanh","aaaaaaaaaaaaaani","aaaaaaaaaaaaaanj","aaaaaaaaaaaaaank","aaaaaaaaaaaaaanl","aaaaaaaaaaaaaanm","aaaaaaaaaaaaaann","aaaaaaaaaaaaaano","aaaaaaaaaaaaaanp","aaaaaaaaaaaaaanq","aaaaaaaaaaaaaanr","aaaaaaaaaaaaaans","aaaaaaaaaaaaaant","aaaaaaaaaaaaaanu","aaaaaaaaaaaaaanv","aaaaaaaaaaaaaanw","aaaaaaaaaaaaaanx","aaaaaaaaaaaaaany","aaaaaaaaaaaaaanz","aaaaaaaaaaaaaaoa","aaaaaaaaaaaaaaob","aaaaaaaaaaaaaaoc","aaaaaaaaaaaaaaod","aaaaaaaaaaaaaaoe","aaaaaaaaaaaaaaof","aaaaaaaaaaaaaaog","aaaaaaaaaaaaaaoh","aaaaaaaaaaaaaaoi","aaaaaaaaaaaaaaoj","aaaaaaaaaaaaaaok","aaaaaaaaaaaaaaol","aaaaaaaaaaaaaaom","aaaaaaaaaaaaaaon","aaaaaaaaaaaaaaoo","aaaaaaaaaaaaaaop","aaaaaaaaaaaaaaoq","aaaaaaaaaaaaaaor","aaaaaaaaaaaaaaos","aaaaaaaaaaaaaaot","aaaaaaaaaaaaaaou","aaaaaaaaaaaaaaov","aaaaaaaaaaaaaaow","aaaaaaaaaaaaaaox","aaaaaaaaaaaaaaoy","aaaaaaaaaaaaaaoz","aaaaaaaaaaaaaapa","aaaaaaaaaaaaaapb","aaaaaaaaaaaaaapc","aaaaaaaaaaaaaapd","aaaaaaaaaaaaaape","aaaaaaaaaaaaaapf","aaaaaaaaaaaaaapg","aaaaaaaaaaaaaaph","aaaaaaaaaaaaaapi","aaaaaaaaaaaaaapj","aaaaaaaaaaaaaapk","aaaaaaaaaaaaaapl","aaaaaaaaaaaaaapm","aaaaaaaaaaaaaapn","aaaaaaaaaaaaaapo","aaaaaaaaaaaaaapp","aaaaaaaaaaaaaapq","aaaaaaaaaaaaaapr","aaaaaaaaaaaaaaps","aaaaaaaaaaaaaapt","aaaaaaaaaaaaaapu","aaaaaaaaaaaaaapv","aaaaaaaaaaaaaapw","aaaaaaaaaaaaaapx","aaaaaaaaaaaaaapy","aaaaaaaaaaaaaapz","aaaaaaaaaaaaaaqa","aaaaaaaaaaaaaaqb","aaaaaaaaaaaaaaqc","aaaaaaaaaaaaaaqd","aaaaaaaaaaaaaaqe","aaaaaaaaaaaaaaqf","aaaaaaaaaaaaaaqg","aaaaaaaaaaaaaaqh","aaaaaaaaaaaaaaqi","aaaaaaaaaaaaaaqj","aaaaaaaaaaaaaaqk","aaaaaaaaaaaaaaql","aaaaaaaaaaaaaaqm","aaaaaaaaaaaaaaqn","aaaaaaaaaaaaaaqo","aaaaaaaaaaaaaaqp","aaaaaaaaaaaaaaqq","aaaaaaaaaaaaaaqr","aaaaaaaaaaaaaaqs","aaaaaaaaaaaaaaqt","aaaaaaaaaaaaaaqu","aaaaaaaaaaaaaaqv","aaaaaaaaaaaaaaqw","aaaaaaaaaaaaaaqx","aaaaaaaaaaaaaaqy","aaaaaaaaaaaaaaqz","aaaaaaaaaaaaaara","aaaaaaaaaaaaaarb","aaaaaaaaaaaaaarc","aaaaaaaaaaaaaard","aaaaaaaaaaaaaare","aaaaaaaaaaaaaarf","aaaaaaaaaaaaaarg","aaaaaaaaaaaaaarh","aaaaaaaaaaaaaari","aaaaaaaaaaaaaarj","aaaaaaaaaaaaaark","aaaaaaaaaaaaaarl","aaaaaaaaaaaaaarm","aaaaaaaaaaaaaarn","aaaaaaaaaaaaaaro","aaaaaaaaaaaaaarp","aaaaaaaaaaaaaarq","aaaaaaaaaaaaaarr","aaaaaaaaaaaaaars","aaaaaaaaaaaaaart","aaaaaaaaaaaaaaru","aaaaaaaaaaaaaarv","aaaaaaaaaaaaaarw","aaaaaaaaaaaaaarx","aaaaaaaaaaaaaary","aaaaaaaaaaaaaarz","aaaaaaaaaaaaaasa","aaaaaaaaaaaaaasb","aaaaaaaaaaaaaasc","aaaaaaaaaaaaaasd","aaaaaaaaaaaaaase","aaaaaaaaaaaaaasf","aaaaaaaaaaaaaasg","aaaaaaaaaaaaaash","aaaaaaaaaaaaaasi","aaaaaaaaaaaaaasj","aaaaaaaaaaaaaask","aaaaaaaaaaaaaasl","aaaaaaaaaaaaaasm","aaaaaaaaaaaaaasn","aaaaaaaaaaaaaaso","aaaaaaaaaaaaaasp","aaaaaaaaaaaaaasq","aaaaaaaaaaaaaasr","aaaaaaaaaaaaaass","aaaaaaaaaaaaaast","aaaaaaaaaaaaaasu","aaaaaaaaaaaaaasv","aaaaaaaaaaaaaasw","aaaaaaaaaaaaaasx","aaaaaaaaaaaaaasy","aaaaaaaaaaaaaasz","aaaaaaaaaaaaaata","aaaaaaaaaaaaaatb","aaaaaaaaaaaaaatc","aaaaaaaaaaaaaatd","aaaaaaaaaaaaaate","aaaaaaaaaaaaaatf","aaaaaaaaaaaaaatg","aaaaaaaaaaaaaath","aaaaaaaaaaaaaati","aaaaaaaaaaaaaatj","aaaaaaaaaaaaaatk","aaaaaaaaaaaaaatl","aaaaaaaaaaaaaatm","aaaaaaaaaaaaaatn","aaaaaaaaaaaaaato","aaaaaaaaaaaaaatp","aaaaaaaaaaaaaatq","aaaaaaaaaaaaaatr","aaaaaaaaaaaaaats","aaaaaaaaaaaaaatt","aaaaaaaaaaaaaatu","aaaaaaaaaaaaaatv","aaaaaaaaaaaaaatw","aaaaaaaaaaaaaatx","aaaaaaaaaaaaaaty","aaaaaaaaaaaaaatz","aaaaaaaaaaaaaaua","aaaaaaaaaaaaaaub","aaaaaaaaaaaaaauc","aaaaaaaaaaaaaaud","aaaaaaaaaaaaaaue","aaaaaaaaaaaaaauf","aaaaaaaaaaaaaaug","aaaaaaaaaaaaaauh","aaaaaaaaaaaaaaui","aaaaaaaaaaaaaauj","aaaaaaaaaaaaaauk","aaaaaaaaaaaaaaul","aaaaaaaaaaaaaaum","aaaaaaaaaaaaaaun","aaaaaaaaaaaaaauo","aaaaaaaaaaaaaaup","aaaaaaaaaaaaaauq","aaaaaaaaaaaaaaur","aaaaaaaaaaaaaaus","aaaaaaaaaaaaaaut","aaaaaaaaaaaaaauu","aaaaaaaaaaaaaauv","aaaaaaaaaaaaaauw","aaaaaaaaaaaaaaux","aaaaaaaaaaaaaauy","aaaaaaaaaaaaaauz","aaaaaaaaaaaaaava","aaaaaaaaaaaaaavb","aaaaaaaaaaaaaavc","aaaaaaaaaaaaaavd","aaaaaaaaaaaaaave","aaaaaaaaaaaaaavf","aaaaaaaaaaaaaavg","aaaaaaaaaaaaaavh","aaaaaaaaaaaaaavi","aaaaaaaaaaaaaavj","aaaaaaaaaaaaaavk","aaaaaaaaaaaaaavl","aaaaaaaaaaaaaavm","aaaaaaaaaaaaaavn","aaaaaaaaaaaaaavo","aaaaaaaaaaaaaavp","aaaaaaaaaaaaaavq","aaaaaaaaaaaaaavr","aaaaaaaaaaaaaavs","aaaaaaaaaaaaaavt","aaaaaaaaaaaaaavu","aaaaaaaaaaaaaavv","aaaaaaaaaaaaaavw","aaaaaaaaaaaaaavx","aaaaaaaaaaaaaavy","aaaaaaaaaaaaaavz","aaaaaaaaaaaaaawa","aaaaaaaaaaaaaawb","aaaaaaaaaaaaaawc","aaaaaaaaaaaaaawd","aaaaaaaaaaaaaawe","aaaaaaaaaaaaaawf","aaaaaaaaaaaaaawg","aaaaaaaaaaaaaawh","aaaaaaaaaaaaaawi","aaaaaaaaaaaaaawj","aaaaaaaaaaaaaawk","aaaaaaaaaaaaaawl","aaaaaaaaaaaaaawm","aaaaaaaaaaaaaawn","aaaaaaaaaaaaaawo","aaaaaaaaaaaaaawp","aaaaaaaaaaaaaawq","aaaaaaaaaaaaaawr","aaaaaaaaaaaaaaws","aaaaaaaaaaaaaawt","aaaaaaaaaaaaaawu","aaaaaaaaaaaaaawv","aaaaaaaaaaaaaaww","aaaaaaaaaaaaaawx","aaaaaaaaaaaaaawy","aaaaaaaaaaaaaawz","aaaaaaaaaaaaaaxa","aaaaaaaaaaaaaaxb","aaaaaaaaaaaaaaxc","aaaaaaaaaaaaaaxd","aaaaaaaaaaaaaaxe","aaaaaaaaaaaaaaxf","aaaaaaaaaaaaaaxg","aaaaaaaaaaaaaaxh","aaaaaaaaaaaaaaxi","aaaaaaaaaaaaaaxj","aaaaaaaaaaaaaaxk","aaaaaaaaaaaaaaxl","aaaaaaaaaaaaaaxm","aaaaaaaaaaaaaaxn","aaaaaaaaaaaaaaxo","aaaaaaaaaaaaaaxp","aaaaaaaaaaaaaaxq","aaaaaaaaaaaaaaxr","aaaaaaaaaaaaaaxs","aaaaaaaaaaaaaaxt","aaaaaaaaaaaaaaxu","aaaaaaaaaaaaaaxv","aaaaaaaaaaaaaaxw","aaaaaaaaaaaaaaxx","aaaaaaaaaaaaaaxy","aaaaaaaaaaaaaaxz","aaaaaaaaaaaaaaya","aaaaaaaaaaaaaayb","aaaaaaaaaaaaaayc","aaaaaaaaaaaaaayd","aaaaaaaaaaaaaaye","aaaaaaaaaaaaaayf","aaaaaaaaaaaaaayg","aaaaaaaaaaaaaayh","aaaaaaaaaaaaaayi","aaaaaaaaaaaaaayj","aaaaaaaaaaaaaayk","aaaaaaaaaaaaaayl","aaaaaaaaaaaaaaym","aaaaaaaaaaaaaayn","aaaaaaaaaaaaaayo","aaaaaaaaaaaaaayp","aaaaaaaaaaaaaayq","aaaaaaaaaaaaaayr","aaaaaaaaaaaaaays","aaaaaaaaaaaaaayt","aaaaaaaaaaaaaayu","aaaaaaaaaaaaaayv","aaaaaaaaaaaaaayw","aaaaaaaaaaaaaayx","aaaaaaaaaaaaaayy","aaaaaaaaaaaaaayz","aaaaaaaaaaaaaaza","aaaaaaaaaaaaaazb","aaaaaaaaaaaaaazc","aaaaaaaaaaaaaazd","aaaaaaaaaaaaaaze","aaaaaaaaaaaaaazf","aaaaaaaaaaaaaazg","aaaaaaaaaaaaaazh","aaaaaaaaaaaaaazi","aaaaaaaaaaaaaazj","aaaaaaaaaaaaaazk","aaaaaaaaaaaaaazl","aaaaaaaaaaaaaazm","aaaaaaaaaaaaaazn","aaaaaaaaaaaaaazo","aaaaaaaaaaaaaazp","aaaaaaaaaaaaaazq","aaaaaaaaaaaaaazr","aaaaaaaaaaaaaazs","aaaaaaaaaaaaaazt","aaaaaaaaaaaaaazu","aaaaaaaaaaaaaazv","aaaaaaaaaaaaaazw","aaaaaaaaaaaaaazx","aaaaaaaaaaaaaazy","aaaaaaaaaaaaaazz"};
    std::vector<std::string> s{"aaaaaaaaaaaaaazz"};
//    vector<string> words = {"oath","pea","eat","rain"};
//    vector<vector<char>>   board =
//            {{'o','a','a','n'},
//            {'e','t','a','e'},
//                {'i','h','k','r'},
//                    {'i','f','l','v'}};
//    std::vector<std::string> ret=solution.findWords(board,words);
    vector<string> ret=findWords(vec,str);
    for(auto word:ret){
        std::cout<<word<<' ';
    }
}