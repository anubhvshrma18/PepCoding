#include <bits/stdc++.h>
using namespace std;

struct Node
{
    int data;
    Node *left;
    Node *right;
    Node(int val)
    {
        data = val;
        left = nullptr;
        right = nullptr;
    }
};

Node *construct(int *arr)
{
    Node *root = new Node(arr[0]);
    pair<Node *, int> p = {root, 1};

    stack<pair<Node *, int>> st;
    st.push(p);

    int idx = 1;
    while (!st.empty())
    {
        // pair<Node*,int> pe=st.top();
        if (st.top().second == 1)
        {
            st.top().second++;
            if (arr[idx] != -1)
            {
                st.top().first->left = new Node(arr[idx]);
                pair<Node *, int> lp = {st.top().first->left, 1};
                st.push(lp);
            }
            else
            {
                st.top().first->left = nullptr;
            }

            idx++;
        }
        else if (st.top().second == 2)
        {
            st.top().second++;
            if (arr[idx] != -1)
            {
                st.top().first->right = new Node(arr[idx]);
                pair<Node *, int> rp = {st.top().first->right, 1};
                st.push(rp);
            }
            else
            {
                st.top().first->right = nullptr;
            }
            idx++;
        }
        else
        {
            st.pop();
        }
    }
    return root;
}

void display(Node *node)
{
    if (node == nullptr)
    {
        return;
    }

    string str = " <- " + to_string(node->data) + " -> ";

    string left = (node->left == nullptr) ? "." : "" + to_string(node->left->data);
    string right = (node->right == nullptr) ? "." : "" + to_string(node->right->data);

    str = left + str + right;
    cout << str << endl;

    display(node->left);
    display(node->right);
}

void traversal(Node *root)
{
    string pre = "";
    string post = "";
    string in = "";
    stack<pair<Node *, int>> st;

    pair<Node *, int> p = {root, 0};
    st.push(p);
    while (st.size() > 0)
    {
        // pair<Node* , int> p=st.top();
        if (st.top().second == 0)
        {
            pre += to_string(st.top().first->data) + " ";
            st.top().second++;
            if (st.top().first->left != nullptr)
            {
                pair<Node *, int> x = {st.top().first->left, 0};
                st.push(x);
            }
        }
        else if (st.top().second == 1)
        {
            in += to_string(st.top().first->data) + " ";
            st.top().second++;
            if (st.top().first->right != nullptr)
            {
                pair<Node *, int> x = {st.top().first->right, 0};
                st.push(x);
            }
        }
        else
        {
            post += to_string(st.top().first->data) + " ";
            st.pop();
        }
    }

    cout << pre << "\n" << in << "\n" << post << endl;
}

int size(Node *root)
{
    if (root == nullptr)
    {
        return 0;
    }

    return size(root->left) + size(root->right) + 1;
}

int sum(Node *root)
{
    if (root == nullptr)
    {
        return 0;
    }

    int leftsum = sum(root->left);
    int rightsum = sum(root->right);

    return root->data + leftsum + rightsum;
}

int height(Node *root)
{
    if (root == nullptr)
    {
        return -1;
    }

    return max(height(root->left), height(root->right)) + 1;
}

int max(Node *root)
{
    if (root == nullptr)
    {
        return INT_MIN;
    }

    int leftmax = max(root->left);
    int rightmax = max(root->right);

    return max(root->data, max(leftmax, rightmax));
}

void levelOrder(Node *root)
{
    queue<Node *> q;
    q.push(root);
    while (q.size() > 0)
    {
        int n = q.size();
        for (int i = 0; i < n; i++)
        {
            cout << q.front()->data << " ";

            if (q.front()->left)
            {
                q.push(q.front()->left);
            }
            if (q.front()->right)
            {
                q.push(q.front()->right);
            }

            q.pop();
        }

        cout << endl;
    }
}

int main()
{
    int n;
    cin >> n;
    int v[n];
    for (int i = 0; i < n; i++)
    {
        string x;
        cin >> x;
        if (x == "n")
        {
            v[i] = -1;
        }
        else
        {
            v[i] = stoi(x);
        }
    }
    Node *root = construct(v);
    levelOrder(root);
}