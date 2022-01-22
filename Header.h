//Name : Faraz Uddin Razi
//Assignment : 03
// Data Structures
//

#pragma once
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING 1;
#include<iostream>
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
using namespace std;

/*
These all classes along with their function definitions are for the sake of GTESTs that you are going to use to implement the assignment.
You can add more classes , member variables & member functions that supports your functionality.
*/

template<typename T>
struct AvlNode
{
    T data;
    T* path;
    AvlNode<T>* left = NULL;
    AvlNode<T>* right = NULL;
    int height;
    int num;
    AvlNode()
    {
        num = 0;
        path = NULL;
    }
    T getData()
    {
        return data;
    }

    void setData(T data)
    {
        this->data = data;
    }
    AvlNode<T>* getleft()
    {
        return this->left;
    }

    void setleft(AvlNode<T>* left)
    {
        this->left = left;
    }
    AvlNode<T>* getright()
    {
        return this->right;
    }

    void setright(AvlNode<T>* right)
    {
        this->right = right;
    }

    int getHeight()
    {
        return this->height;
    }

    void setHeight(int height)
    {
        this->height = height;
    }

};

template<typename T>
class AVLTree
{
    AvlNode<T>* root;
public:
    AVLTree()
    {
        root = NULL;
    }
    void insert(T data,T path) {
        AvlNode<T>* NewT = new AvlNode<T>;
        //T D(1, data[0]);
        NewT = root;
        root = Insert(data,path, NewT);
    }
    AvlNode<T>* Insert(T X,T path,AvlNode<T>* Tree) {

        if (Tree == NULL) { /* Create and return a one-AvlNode AVLTree */
            Tree = new AvlNode<T>;
            Tree->setData(X);
            T* p = new T[Tree->num+1];
            int i;
            for (i = 0; i < Tree->num; i++)
            {
                p[i] = Tree->path[i];
            }
            p[i] = path;
            Tree->path = p;
            Tree->setleft(NULL);
            Tree->setright(NULL);
            Tree->num++;
        }

        else if (X[0] < Tree->getData()[0]) {

            Tree->setleft(Insert(X,path,Tree->getleft()));

            if (height(Tree->left) - height(Tree->right) == 2)

                if (X[0]< Tree->left->getData()[0])

                    Tree = SingleRotateWithleft(Tree); // RR rotation

                else

                    Tree = DoubleRotateWithleft(Tree); // RL rotation

        }

        else if (X[0] > Tree->getData()[0]) {

            Tree->setright(Insert(X,path, Tree->getright()));
            if (height(Tree->right) - height(Tree->left) == 2)

                if (X[0] > Tree->right->getData()[0])

                    Tree = SingleRotateWithright(Tree); // LL rotation

                else

                    Tree = DoubleRotateWithright(Tree); // LR rotation
        } 
        else {
            T* p = new T[Tree->num + 1];
            int i;
            for (i = 0; i < Tree->num; i++)
            {
                p[i] = Tree->path[i];
            }
            p[i] = path;
            
            Tree->path = p;
            Tree->num++;
        }
        Tree->height = Max(height(Tree->left), height(Tree->right)) + 1;

        return Tree;
    }

    AvlNode<T>* SingleRotateWithleft(AvlNode<T>* K1) {

        AvlNode<T>* K2;

        K2 = K1->left; 

        K1->left = K2->right;
        
        K2->right = K1;

        K1->height = Max(height(K1->left), height(K1->right)) + 1;

        K2->height = Max(height(K2->left), K1->height) + 1;

        return K2; 

    }
    AvlNode<T>* DoubleRotateWithleft(AvlNode<T>* K3)
    {
        K3->left = SingleRotateWithright(K3->left);

        return SingleRotateWithleft(K3);
    }

    AvlNode<T>* SingleRotateWithright(AvlNode<T>* K1) {

        AvlNode<T>* K2;

        K2 = K1->right;

        K1->right = K2->left;

        K2->left = K1;

        K1->height = Max(height(K1->left), height(K1->right)) + 1;

        K2->height = Max(height(K2->right), K1->height) + 1;

        return K2; 

    }
    AvlNode<T>* DoubleRotateWithright(AvlNode<T>* K1)
    {
        K1->right = SingleRotateWithleft(K1->right);

        return SingleRotateWithright(K1);
    }
    
    int height(AvlNode<T>* P)
    {

        if (P == NULL)
            return -1;
        else
            return P->height;
    }
    int Max(int a, int b)
    {
        if (a > b)
            return a;
        else
            return b;
    }
    int height()
    {
        return getheight(root);
    }
    int getheight(AvlNode<T>* node)
    {
        if (node == NULL)
            return -1;
        else
        {
            int leftheight = getheight(node->left);
            int rightheight = getheight(node->right);
            if (leftheight > rightheight)
            {
                return leftheight + 1;
            }
            else
            {
                return rightheight + 1;
            }
        }

    }

    bool isBalanced()
    {
        if (getBalance(root) >= -1 || getBalance(root) <= 1)
            return true;
        else false;

    }
    int getBalance(AvlNode<T>* T)
    {
        if (T == NULL)
            return 0;
        return getheight(T->left) - getheight(T->right);
    }

    bool isEmpty()
    {
        return root == NULL;
    }

   

    
    /*~AVLTree()
    {
        deleteNodes(root);
    }
    void deleteNodes(AvlNode<T>* root)
    {
        if (root)
        {
            deleteNodes(root->getleft());
            deleteNodes(root->getright());
            delete root;
        }
    }*/
    ////Search File in AVL. It will return an array containing paths of the given file. will return NULL if no such file exist
    ////Check Test Case for better understanding of output
    T* searchFile(T filename) {
        T* path=NULL;
        getstrTree(root, filename, path);
       
        return path;
       
    }
    void getstrTree(AvlNode<T>* node,T filename,T*& path)
    {
        if (node)
        {
            int i = 0;
            while (i < node->num)
            {
                if (node->path[i].find(filename) !=string::npos)
                {
                    path = node->path;
                }
                i++;
            }
            getstrTree(node->left, filename,path);
            getstrTree(node->right, filename,path);
        }
    }
    ////This function returns string in format i.e. "J,D,O,A" after traversing AVL in levelOrder fashion
    ////Check Test Case for better understanding of output
    string levelOrderTraversal()
    {
        string str;
        PreOrder(root, str);
        return str;
    }
    ////This function returns string in format i.e. "J,D,O,A" after traversing AVL in preOrder fashion
    ////Check Test Case for better understanding of output
    string preorderTraversal()
    {
        string str;
        PreOrder(root, str);
        return str;
    }
    void PreOrder(AvlNode<T>* root, string& str)
    {
        if (root)
        {
            if (root->getData()[0] >= 97 && root->getData()[0] <= 122)
            {
                str += root->getData()[0] - 32;
            }
            else
            {
                str += root->getData()[0];
            }
            str += ",";

            PreOrder(root->getleft(), str);
            

            PreOrder(root->getright(), str);
        }
    }

    ////This function returns string in format i.e. "J,D,O,A" after traversing AVL in postOrder fashion
    ////Check Test Case for better understanding of output
    string postorderTraversal()
    {
        string str;
        PostOrder(root, str);
        return str;
    }
    void PostOrder(AvlNode<T>* root, string& str)
    {
        if (root)
        {

            PostOrder(root->getleft(), str);
            PostOrder(root->getright(), str);
            if (root->getData()[0] >= 97 && root->getData()[0] <= 122)
            {
                str += root->getData()[0] - 32;
            }
            else
            {
                str += root->getData()[0];
            }
            str += ",";
        }
    }


    

    ////This function returns string in format i.e. "J,D,O,A" after traversing AVL in inOrder fashion
    ////Check Test Case for better understanding of output
    string inorderTraversal() {
        string str;
        InOrder(root, str);
        return str;
    }
    void InOrder(AvlNode<T>* root, string& str)
    {
        if (root)
        {

            InOrder(root->getleft(), str);
            if (root->getData()[0] >= 97 && root->getData()[0] <= 122)
            {
                str += root->getData()[0] - 32;
            }
            else
            {
                str += root->getData()[0];
            }
            str += ",";
            InOrder(root->getright(), str);
            
        }
    }

};



template <typename T>
struct Node
{
    //Declare member variables and functions according to your logic
    T name;
    Node* parent=NULL;
    Node* child=NULL;
    Node* next=NULL;
    Node()
    {}
    Node(string& value, Node<T>* parent) {
        this->parent = parent;
        this->name = value;
    }

    Node* find(const std::string& entry)
    {
        Node* tmp = child;

        while (tmp && tmp->name != entry)
            tmp = tmp->next;

        return tmp;
    }
    Node<T>* lastChild()
    {
        Node<T>* nextChild = child, * child1 = NULL;

        while (nextChild != NULL)
        {
            child1 = nextChild;
            nextChild = nextChild->next;
        }

        return child1;
    }
    void addnew(string& value)
    {
        if (!child)
            child = new Node<T>(value, this);
        else
            lastChild()->next = new Node<T>(value, this);
    }
    
};
string getFilename(string str)
{
    int i = str.length();
    while (i > 0)
    {
        if (str[i] == '/')
        {
            break;
        }
        i--;
    }
    string retstr;
    while (str[i] != '\0')
    {
        
        retstr += str[i];
        i++;
    }
    return retstr;
}

bool add(string path, Node<string>* current)
{

    std::string nextFolder;
    size_t pos = path.find('/');
    nextFolder = (pos != std::string::npos) ? path.substr(0, pos) : "";
    if (nextFolder.length() > 0)
    {
        Node<string>* findedEntry;
        findedEntry = current->find(nextFolder);
        if (!findedEntry)
            return false;
        add(path.substr(pos + 1), findedEntry);
    }
    else
    {
        if (current->find(path) != NULL)
            return false;
        //convert path to name 
        current->addnew(getFilename(path));
    }

    return true;
}
//Remember :- You can add more classes that support your functionality

template <typename T>
class NaryTree {
    Node<T>* root;
    AVLTree<T> avl;
public:

    AVLTree<T> getAVL() {
        return avl;
    }

    //Create an N-ary tree and its corresponding AVl by taking path of root directory
    void CreateTree(T rootval) {
        string newRoot;
        int i = 2, l;
        fs::path p;
        root = new Node<T>;
        
        while (rootval[i] != '\0')
        {
            newRoot += rootval[i];
            i++;
        }
        add(newRoot, root);
        newRoot = "\0";
        for (auto& p1 : fs::recursive_directory_iterator(rootval))
        {

            p = p1;
            i = 2;
            
            while (p.generic_string()[i] != '\0')
            { 
                newRoot += p.generic_string()[i];
                i++;
            }
            l = newRoot.length();
            if (newRoot.find(".txt") == string::npos)
            {
                add(newRoot, root);
            } 
            newRoot = "\0";
        }
        for (auto& p1 : fs::recursive_directory_iterator(rootval))
        {

            p = p1;
            i = 2;

            while (p.generic_string()[i] != '\0')
            {
                newRoot += p.generic_string()[i];
                i++;
            }
            l = newRoot.length();
            if (newRoot.find(".txt") != string::npos)
            {
                add(newRoot, root);
                newRoot = "./" + newRoot;
                p = p.filename();
                //add to avl tree
                avl.insert(p.generic_string(),newRoot);
            }
            newRoot = "\0";
        }
    }

    ////Add a file to N-ary tree at a give path and store its path in AVL and returns true if successfully added
    bool addFile(T filepath, T filename) {
        return true;
    }

    ////Add a folder to N-ary tree at a give path and returns true if successfully added
    bool AddFolder(T folderpath, T foldername) {
        return true;
    }
    ////Delete a file from N-ary tree and its path from avl and returns true if successfully deleted
    ////Check Test Case for better understanding of output
    bool deleteFile(T filename) {
        return deleteF(root, filename);
    }
    bool deleteF(Node<T>* node, T filename)
    {
        if (node)
        {
            if (node->name == filename)
            {   
                Node<T>* prev = getnextNode(node);
                if (prev==node->parent)
                {
                    node->parent->child = node->next;
                }
                else
                {
                    prev->next = node->next;
                }
                delete node;
                return true;
            }
            deleteF(node->child, filename);
            deleteF(node->next, filename);
        }
        
    }
   
    Node<T>* getnextNode(Node<T>* node)
    {
        Node<T>* retNode=NULL;
        lastnext(node, root,retNode);
        if (!retNode)
            return node->parent;
        return retNode;            
    }
    void lastnext(Node<T>* nodeMatch,Node<T>* node, Node<T>* &retNode) {
        if (node)
        {
            if (node->next == nodeMatch)
            {
                retNode = node;
            }
            lastnext(nodeMatch, node->child, retNode);
            lastnext(nodeMatch, node->next, retNode);
           
        }
    }
    ////Delete a folder and all the files and folders from N-ary tree and path of files from avl and returns true if successfully deleted
    ////Check Test Case for better understanding of output
    bool DeleteFolder(T filename) {
        return deleteFol(root, filename);
    }
    bool deleteFol(Node<T>* node, T filename)
    {
        /*if (node)
        {
            if (node->name == filename)
            {

                Node<T>* prev = getnextNode(node);
                prev->next = node->next;
                delete node;
                return true;
            }
            deleteF(node->child, filename);
            deleteF(node->next, filename);
        }*/
        return true;

    }
    ////Merge two folders by moving all the files and folders of 2nd folder to first folder and update the paths in avl  and returns true if folders successfully merged
    ////Check Test Case for better understanding of output
    bool MergeFolder(T folder1, T folder2) {
        return true;
    }


    ////Display N-ary tree in treeform
    void DisplayTreeForm() {
    
        print(root->child, 0);
    
    }

    ////This function returns string in format i.e. "logs,powerLogs,timeUsageLog,voltageLogs,systemlog.txt" after traversing AVL in inOrder fashion
    ////Check Test Case for better understanding of output
    string inorderTraversal() {
        string str;
        inOrder(root->child,str);

        return str;

    }
    void inOrder(Node<T>* node,string& str)
    {
        if (node)
        {

            inOrder(node->child, str);
            //cout << node->name << ",";
            str += node->name;
            str += ',';
            inOrder(node->next,str);
            

        }
    }

    ////This function returns string in format i.e. "logs,powerLogs,timeUsageLog,voltageLogs,systemlog.txt" after traversing AVL in preOrder fashion
    ////Check Test Case for better understanding of output
    string preorderTraversal() {
        string str;
        preOrder(root->child, str);
        string retStr;
        int i = 0;
        int l = str.length();
        while (i<l-1)
        {

            retStr += str[i];
            i++;
        }
        return retStr;

    }
    void preOrder(Node<T>* node, string& str)
    {
        if (node)
        {

            str += node->name;
            str += ',';
            // cout << node->name << ",";
            preOrder(node->child, str);

            preOrder(node->next, str);

        }
    }
    ////This function returns string in format i.e. "logs,powerLogs,timeUsageLog,voltageLogs,systemlog.txt" after traversing AVL in levelOrder fashion
    ////Check Test Case for better understanding of output
    string levelOrderTraversal()
    {
        string str;
        levelOrder(root->child,str);
        int i = 0;
        int l = str.length();
        string retStr;
        while (i < l - 1)
        {

            retStr += str[i];
            i++;
        }
        return retStr;

    }

    void levelOrder(Node<T>* node,string &str)
    {
        if (node)
        {
            //cout << node->name << ",";
            str += node->name;
            str += ',';
            levelOrder(node->next, str);
            levelOrder(node->child,str);
            
        }
    }

    ////This function returns string in format i.e. "logs,powerLogs,timeUsageLog,voltageLogs,systemlog.txt" after traversing AVL in postOrder fashion
    ////Check Test Case for better understanding of output
    string postorderTraversal() {
        string str;
        postOrder(root->child, str);
        string retStr;
        int i = 0;
        int l = str.length();
        while (i < l - 1)
        {
            retStr += str[i];
            i++;
        }
        return retStr;
    }
    void postOrder(Node<T>* node, string& str)
    {
        if (node)
        {
            // cout << node->name << ",";
            postOrder(node->child, str);
            str += node->name;
            str += ',';
            postOrder(node->next, str);
        }
    }
    
    void print(Node<T>* node,int n)
    {
        if (node)
        {
            cout << "--" << node->name ;
            print(node->child,n+1);
            cout << endl;
            for (int i = 0; i < n; i++)
            {
                cout << "\t";
            }
            print(node->next,n);
            
            
        }
    }
    ////Returns size of a file 
    ////Check Test Case for better understanding of output
    int sizeFile(T filename) {
        
        
        int size=0;
        fs::path p =  filename;
        string str;
        fs::path p2;
        string path = root->child->name;
        for (auto& p1 : fs::recursive_directory_iterator(path))
        {
            p2 = p1;
            //cout << p.generic_string() << endl;
            //cout << p2.filename() << endl;
            p2 = p2.filename();
            
            if (p.generic_string().find(p2.generic_string())!=string::npos)
            {
                cout<<fs::file_size(p1);
                size = fs::file_size(p1);
            }
        }
        return size;
    }
    ////Returns size of a folder 
    ////Check Test Case for better understanding of output
    int sizeFolder(T foldername) {

        int size = 0;

        string str;
        int i = 2;

        fs::path p = foldername;
        while (p.generic_string()[i] != '\0')
        {
            str += p.generic_string()[i];
            i++;
        }
        p = str;
        fs::path p2;
        string path = root->child->name;
        for (auto& p1 : fs::recursive_directory_iterator(path))
        {
            p2 = p1;
            //cout << p.generic_string() << endl;
            //cout << p2.generic_string() << endl;
            //p2 = p2.filename();
            if (p.generic_string().compare(p2.generic_string())==0)
            {
                //cout << fs::file_size(p1);
                //size = fs::file_size(p1);
                for (auto& p3 : fs::recursive_directory_iterator(p1))
                {
                    if (!fs::is_directory(p3))
                    {
                        size = size + fs::file_size(p3);
                    }
                }
            }
        }
        return size;
    }


};