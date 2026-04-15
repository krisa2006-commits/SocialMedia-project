#include <iostream>
#include <vector>
using namespace std;

class SocialMedia
{
    vector<string> users;
    vector<vector<string>> follow;
    vector<vector<string>> friends;
    vector<string> history;

public:
    int getUser(string name)
    {
        for (int i = 0; i < users.size(); i++)
        {
            if (users[i] == name)
                return i;
        }

        users.push_back(name);
        follow.push_back(vector<string>());
        friends.push_back(vector<string>());

        return users.size() - 1;
    }

    // ------------ FOLLOW ------------
    void followUser(string a, string b)
    {
        int y = getUser(a);

        follow[y].push_back(b);
        cout << a << " follows " << b << endl;
    }

    void unfollowUser(string a, string b)
    {
        int y = getUser(a);

        for (int i = 0; i < follow[y].size(); i++)
        {
            if (follow[y][i] == b)
            {
                follow[y].erase(follow[y].begin() + i);
                cout << a << " Unfollowed " << b << endl;
                break;
            }
        }

        cout << "Not found!" << endl;
    }

    void viewFollow(string a)
    {
        int y = getUser(a);

        cout << "Following: ";
        for (int i = 0; i < follow[y].size(); i++)
        {
            cout << follow[y][i] << " ";
        }

        cout << endl;
    }

    // ------------ FRIEND ------------
    void addFriend(string a, string b)
    {
        int y = getUser(a);
        int z = getUser(b);

        friends[y].push_back(b);
        friends[z].push_back(a);

        cout << a << " and " << b << " are now friends" << endl;
    }

    void removeFriend(string A, string B)
    {
        int i = getUser(A);

        int j = -1;
        for (int k = 0; k < users.size(); k++)
        {
            if (users[k] == B)
            {
                j = k;
                break;
            }
        }

        if (j == -1)
        {
            cout << "User not found!" << endl;
            return;
        }

        for (int k = 0; k < friends[i].size(); k++)
        {
            if (friends[i][k] == B)
            {
                friends[i].erase(friends[i].begin() + k);
                break;
            }
        }

        for (int k = 0; k < friends[j].size(); k++)
        {
            if (friends[j][k] == A)
            {
                friends[j].erase(friends[j].begin() + k);
                break;
            }
        }

        cout << "Friend removed!" << endl;
    }

    void viewFriend(string a)
    {
        int y = getUser(a);

        if (friends[y].empty())
        {
            cout << "No friends found!" << endl;
            return;
        }

        cout << "Friends: ";
        for (int i = 0; i < friends[y].size(); i++)
        {
            cout << friends[y][i] << " ";
        }
        cout << endl;
    }

    // ------------ DFS ------------
    void dfs(string start)
    {
        int y = getUser(start);
        vector<bool> visited(users.size(), false);
        dfsUnit(y, visited);
        cout << endl;
    }

    void dfsUnit(int node, vector<bool> &visited)
    {
        visited[node] = true;
        cout << users[node] << " ";

        for (int i = 0; i < friends[node].size(); i++)
        {
            string s = friends[node][i];
            int next = getUser(s);

            if (!visited[next])
            {
                dfsUnit(next, visited);
            }
        }
    }

    // ------------ HISTORY ------------
    void visit(string name)
    {
        history.push_back(name);
    }

    void showHistory()
    {
        cout << "History: ";
        for (int i = 0; i < history.size(); i++)
        {
            cout << history[i] << " ";
        }
        cout << endl;
    }
};

int main()
{
    SocialMedia s;
    int choice;
    string A, B;

    do
    {
        cout << "\n--------- SOCIAL MEDIA FRIEND SYSTEM ---------\n"
             << endl;

        cout << "----- FOLLOW SYSTEM (Directed) -----" << endl;
        cout << "1. Follow a User" << endl;
        cout << "2. Unfollow a User" << endl;
        cout << "3. View Followers / Following\n"
             << endl;

        cout << "----- FRIENDSHIP (Undirected+DFS) -----" << endl;
        cout << "4. Add Friend" << endl;
        cout << "5. Remove Friend" << endl;
        cout << "6. View Friends" << endl;
        cout << "7. DFS Traversal from User" << endl;
        cout << "8. Visit Profile\n"
             << endl;

        cout << "9. Exit\n"
             << endl;

        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter Names (A follows B): ";
            cin >> A >> B;
            s.followUser(A, B);
            break;

        case 2:
            cout << "Enter Names: ";
            cin >> A >> B;
            s.unfollowUser(A, B);
            break;

        case 3:
            cout << "Enter Name: ";
            cin >> A;
            s.viewFollow(A);
            break;

        case 4:
            cout << "Enter Names: ";
            cin >> A >> B;
            s.addFriend(A, B);
            break;

        case 5:
            cout << "Enter Names: ";
            cin >> A >> B;
            s.removeFriend(A, B);
            break;

        case 6:
            cout << "Enter Name: ";
            cin >> A;
            s.viewFriend(A);
            break;

        case 7:
            cout << "Enter Start Name: ";
            cin >> A;
            s.dfs(A);
            break;

        case 8:
            cout << "Enter Profile Name: ";
            cin >> A;
            s.visit(A);
            s.showHistory();
            break;

        case 9:
            cout << "Exiting Program....";
            break;

        default:
            cout << "Invalid choice!" << endl;
            break;
        }
    } while (choice != 9);
}