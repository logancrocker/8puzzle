#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <cmath>
#include <ctime>
#include <string>
#include <sstream>
#include <iterator>

using namespace std;

class Node
{
    private:
        vector<vector<int> > state;
        int cost;
    public: 
        Node();
        Node(int cost);
        Node(vector<vector<int> > state, int cost);
        int get_cost();
        vector<vector<int> > get_state();
        void print();
        void expand(vector<Node*> &expanded, Node* last);
        void expand_misplaced(vector<Node*> &expanded, Node* last);
        void expand_manhattan(vector<Node*> &expanded, Node* last);
        vector<int> get_blank();
        vector<int> get_pos(int val);
        Node* move_right();
        Node* move_left();
        Node* move_up();    
        Node* move_down();  
        void set_cost(int new_cost);  
        int get_misplaced();
        int get_manhattan();
};

int Node::get_misplaced()
{
    vector<vector<int> > goal = {{1,2,3},
                                 {4,5,6},
                                 {7,8,0}};

    vector<vector<int> > v = this->state;
    int count = 0;
    for (unsigned i = 0; i < 3; i++)
    {
        for (unsigned j = 0; j < 3; j++)
        {
            if (v[i][j] != goal[i][j]) { count++; }
        }
    }
    return count;
}

int Node::get_manhattan()
{
    vector<vector<int> > goal = {{1,2,3},
                                 {4,5,6},
                                 {7,8,0}};

    int count = 0;
    vector<int> c(2);
    //for each value
    for (unsigned i = 1; i <= 8; i++)
    {
        c = this->get_pos(i);
        switch(i)
        {
            case 1:
                //1 should be at 0,0
                count += abs(0 - c[0]) + abs(0 - c[1]);
                break;
            case 2:
                //2 should be at 0,1
                count += abs(0-c[0]) + abs(1 - c[1]);
                break;
            case 3:
                //3 should be at 0,2
                count += abs(0 - c[0]) + abs(2 - c[1]);
                break;
            case 4:
                //4 should be at 1,0
                count += abs(1 - c[0]) + abs(0 - c[1]);
                break;
            case 5:
                //5 should be at 1,1
                count += abs(1 - c[0]) + abs(1 - c[1]);
                break;
            case 6:
                //6 should be at 1,2
                count += abs(1 - c[0]) + abs(2 - c[1]);
                break;
            case 7:
                //7 should be at 2,0
                count += abs(2 - c[0]) + abs(0 - c[1]);
                break;
            case 8:
                //8 should be at 2,1
                count += abs(2 - c[0]) + abs(1 - c[1]);
                break;
        }
    }
    return count;
}

void Node::set_cost(int new_cost)
{
    this->cost = new_cost;
}

void Node::expand(vector<Node*> &expanded, Node* last)
{
    Node* up = this->move_up();
    if ((up->get_state() != last->get_state()) && (up->get_state() != this->state)) 
    {
        expanded.push_back(up); 
    }
    Node* down = this->move_down();
    if ((down->get_state() != last->get_state()) && (down->get_state() != this->state))
    {
        expanded.push_back(down); 
    }
    Node* right = this->move_right();
    if ((right->get_state() != last->get_state()) && (right->get_state() != this->state)) 
    {
        expanded.push_back(right); 
    }
    Node* left = this->move_left();
    if ((left->get_state() != last->get_state()) && (left->get_state() != this->state))
    {
        expanded.push_back(left); 
    }
}

void Node::expand_misplaced(vector<Node*> &expanded, Node* last)
{
    //get the misplaced tile count for each child and add it to the cost
    Node* up = this->move_up();
    up->set_cost(up->get_cost()+up->get_misplaced());
    if ((up->get_state() != last->get_state()) && (up->get_state() != this->state)) 
    {
        expanded.push_back(up); 
    }
    Node* down = this->move_down();
    down->set_cost(down->get_cost()+down->get_misplaced());
    if ((down->get_state() != last->get_state()) && (down->get_state() != this->state))
    {
        expanded.push_back(down); 
    }
    Node* right = this->move_right();
    right->set_cost(right->get_cost()+right->get_misplaced());
    if ((right->get_state() != last->get_state()) && (right->get_state() != this->state)) 
    {
        expanded.push_back(right); 
    }
    Node* left = this->move_left();
    left->set_cost(left->get_cost()+left->get_misplaced());
    if ((left->get_state() != last->get_state()) && (left->get_state() != this->state))
    {
        expanded.push_back(left); 
    }
}

void Node::expand_manhattan(vector<Node*> &expanded, Node* last)
{
    //get the misplaced tile count for each child and add it to the cost
    Node* up = this->move_up();
    up->set_cost(up->get_cost()+up->get_manhattan());
    if ((up->get_state() != last->get_state()) && (up->get_state() != this->state)) 
    {
        expanded.push_back(up); 
    }
    Node* down = this->move_down();
    down->set_cost(down->get_cost()+down->get_manhattan());
    if ((down->get_state() != last->get_state()) && (down->get_state() != this->state))
    {
        expanded.push_back(down); 
    }
    Node* right = this->move_right();
    right->set_cost(right->get_cost()+right->get_manhattan());
    if ((right->get_state() != last->get_state()) && (right->get_state() != this->state)) 
    {
        expanded.push_back(right); 
    }
    Node* left = this->move_left();
    left->set_cost(left->get_cost()+left->get_manhattan());
    if ((left->get_state() != last->get_state()) && (left->get_state() != this->state))
    {
        expanded.push_back(left); 
    }
}

vector<int> Node::get_blank()
{
    vector<int> coords(2);
    for (unsigned i = 0; i < 3; i++)
    {
        for (unsigned j = 0; j < 3; j++)
        {
            if (this->state[i][j] == 0)
            {
                coords[0] = i;
                coords[1] = j;
            }
        }
    }
    return coords;
}

vector<int> Node::get_pos(int val)
{
    vector<int> coords(2);
    for (unsigned i = 0; i < 3; i++)
    {
        for (unsigned j = 0; j < 3; j++)
        {
            if (this->state[i][j] == val)
            {
                coords[0] = i;
                coords[1] = j;
            }
        }
    }
    return coords;
}

Node* Node::move_right()
{
    vector<vector<int> > ret_state = this->state;
    int ret_cost = this->cost + 1;
    vector<int> coords = this->get_blank();
    int r = coords[0];
    int c = coords[1];
    if (c < 2)
    {
        int tmp = ret_state[r][c+1];
        ret_state[r][c+1] = 0;
        ret_state[r][c] = tmp;
        Node* ret_node = new Node(ret_state, ret_cost);
        return ret_node;
    }
    Node* ret_node = new Node(ret_state, ret_cost);
    return ret_node;
}

Node* Node::move_left()
{
    vector<vector<int> > ret_state = this->state;
    int ret_cost = this->cost + 1;
    vector<int> coords = this->get_blank();
    int r = coords[0];
    int c = coords[1];
    if (c > 0)
    {
        int tmp = ret_state[r][c-1];
        ret_state[r][c-1] = 0;
        ret_state[r][c] = tmp;
        Node* ret_node = new Node(ret_state, ret_cost);
        return ret_node;
    }
    Node* ret_node = new Node(ret_state, ret_cost);
    return ret_node;
}

Node* Node::move_up()
{
    vector<vector<int> > ret_state = this->state;
    int ret_cost = this->cost + 1;
    vector<int> coords = this->get_blank();
    int r = coords[0];
    int c = coords[1];
    if (r > 0)
    {
        int tmp = ret_state[r-1][c];
        ret_state[r-1][c] = 0;
        ret_state[r][c] = tmp;
        Node* ret_node = new Node(ret_state, ret_cost);
        return ret_node;
    }
    Node* ret_node = new Node(ret_state, ret_cost);
    return ret_node;
}

Node* Node::move_down()
{
    vector<vector<int> > ret_state = this->state;
    int ret_cost = this->cost + 1;
    vector<int> coords = this->get_blank();
    int r = coords[0];
    int c = coords[1];
    if (r < 2)
    {
        int tmp = ret_state[r+1][c];
        ret_state[r+1][c] = 0;
        ret_state[r][c] = tmp;
        Node* ret_node = new Node(ret_state, ret_cost);
        return ret_node;
    }
    Node* ret_node = new Node(ret_state, ret_cost);
    return ret_node;
}

void Node::print()
{
    for (unsigned i = 0; i < 3; i++)
    {
        for (unsigned j = 0; j < 3; j++)
        {
            if (state[i][j] == 0) {cout << 'b';}
            else {cout << state[i][j];}
            cout << " ";
        }
        cout << endl;
    }
}

Node::Node()
{
    this->state = {{1,2,3},
                   {4,5,6},
                   {7,8,0}};
    this->cost = 0;
}

Node::Node(int cost)
{
    this->state = {{1,2,3},
                   {4,5,6},
                   {7,0,8}};
    this->cost = cost;
}

Node::Node(vector<vector<int> > state, int cost)
{
    this->state = state;
    this->cost = cost;
}

int Node::get_cost() { return this->cost; }

vector<vector<int> > Node::get_state() { return this->state; }

class compare_cost
{
    public:
        bool operator()(Node* a, Node* b)
        {
            return a->get_cost() > b->get_cost();
        }
};

void uniform_cost(Node* init)
{
    bool first = true;
    int nodes_expanded = 0;
    int max_q_size = 1;
    //g(n) is also the depth - 1
    int max_depth = 0;
    vector<vector<int> > goal = {{1,2,3},
                                 {4,5,6},
                                 {7,8,0}};

    //initialize q
    priority_queue<Node*, vector<Node*>, compare_cost> nodes;
    nodes.push(init);

    set<vector<vector<int> >> visited;

    Node* curr_node = NULL;
    //holds the child nodes so we can push to the queue
    vector<Node*> expanded;
    cout << "Expanding state" << endl;
    do
    {
        
        expanded.clear();
        if (nodes.empty()) { break; }
        
        //grab the top node
        curr_node = nodes.top();
        if (!first)
        {
            cout << "The best state to expand with a g(n) = " << curr_node->get_cost() << " is..." << endl;
        }
        //remove from queue
        nodes.pop();
        curr_node->print();  
        cout << endl;

        //check if we have reached the goal
        if (curr_node->get_state() == goal)
        {
            cout << endl << "Goal!!" << endl;
            //curr_node->print();
            cout << endl << endl;
            max_depth = curr_node->get_cost();
            break;
        }

        //here we expand curr_node and push results onto the stack
        if (!first)
        {
            cout << "\tExpanding this node..." << endl << endl;
        }
        nodes_expanded += 1;
        curr_node->expand(expanded, curr_node);
        for (unsigned i = 0; i < expanded.size(); i++)
        {
            if (visited.count(expanded[i]->get_state()) == 0)
            {
                nodes.push(expanded[i]);

            }
        }
        first = false;
        //check if q size is larger than before
        if (nodes.size() > max_q_size) { max_q_size = nodes.size(); }

        visited.insert(curr_node->get_state());

    } while(true);
    cout << "To solve this problem with the search algorithm expanded a total of " << nodes_expanded << " nodes." << endl;
    cout << "The maximum number of nodes in the queue at any one time was " << max_q_size << endl;
    cout << "The depth of the goal node was " << max_depth << endl;
}

void misplaced_tile(Node* init)
{
    bool first = true;
    int max_depth = 0;
    int max_q_size = 0;
    int nodes_expanded = 0;
    vector<vector<int> > goal = {{1,2,3},
                                 {4,5,6},
                                 {7,8,0}};

    //initialize q
    priority_queue<Node*, vector<Node*>, compare_cost> nodes;
    nodes.push(init);

    set<vector<vector<int> >> visited;

    Node* curr_node = NULL;
    //holds the child nodes so we can push to the queue
    vector<Node*> expanded;
    cout << "Expanding state" << endl;
    do
    {
        expanded.clear();
        if (nodes.empty()) { break; }
        
        //grab the top node
        curr_node = nodes.top();
        if (!first)
        {
            cout << "The best state to expand with a g(n) = " << curr_node->get_cost() - curr_node->get_misplaced() << " and h(n) = " << curr_node->get_misplaced() << " is..." << endl;
        }
        //remove from queue
        nodes.pop();
        curr_node->print();
        cout << endl;
        

        //check if we have reached the goal
        if (curr_node->get_state() == goal)
        {
            cout << "Goal!!" << endl;
            //curr_node->print();
            cout << endl << endl;
            max_depth = curr_node->get_cost();
            break;
        }

        //here we expand curr_node and push results onto the stack
        if (!first)
        {
            cout << "\tExpanding this node..." << endl << endl;
        }
        nodes_expanded += 1;
        curr_node->expand_misplaced(expanded, curr_node);
        for (unsigned i = 0; i < expanded.size(); i++)
        {
            if (visited.count(expanded[i]->get_state()) == 0)
            {
                nodes.push(expanded[i]);
            }
        }
        first = false;
        //check if q size is larger than before
        if (nodes.size() > max_q_size) { max_q_size = nodes.size(); }

        visited.insert(curr_node->get_state());

    } while(true);
    cout << "To solve this problem with the search algorithm expanded a total of " << nodes_expanded << " nodes." << endl;
    cout << "The maximum number of nodes in the queue at any one time was " << max_q_size << endl;
    cout << "The depth of the goal node was " << max_depth << endl;
}

void manhattan(Node* init)
{
    bool first = true;
    int max_depth = 0;
    int max_q_size = 0;
    int nodes_expanded = 0;
    vector<vector<int> > goal = {{1,2,3},
                                 {4,5,6},
                                 {7,8,0}};

    //initialize q
    priority_queue<Node*, vector<Node*>, compare_cost> nodes;
    nodes.push(init);

    set<vector<vector<int> >> visited;

    Node* curr_node = NULL;
    //holds the child nodes so we can push to the queue
    vector<Node*> expanded;
    cout << "Expanding state" << endl;
    do
    {
        expanded.clear();
        if (nodes.empty()) { break; }
        
        //grab the top node
        curr_node = nodes.top();
        //remove from queue
        if (!first)
        {
            cout << "The best state to expand with a g(n) = " << curr_node->get_cost() - curr_node->get_manhattan() << " and h(n) = " << curr_node->get_misplaced() << " is..." << endl;
        }
        nodes.pop();
        curr_node->print();
        cout << endl;
        

        //check if we have reached the goal
        if (curr_node->get_state() == goal)
        {
            cout << "Goal!!" << endl;
            //curr_node->print();
            cout << endl << endl;
            max_depth = curr_node->get_cost();
            break;
        }

        //here we expand curr_node and push results onto the stack
        if (!first)
        {
            cout << "\tExpanding this node..." << endl << endl;
        }
        nodes_expanded += 1;
        curr_node->expand_manhattan(expanded, curr_node);
        for (unsigned i = 0; i < expanded.size(); i++)
        {
            if (visited.count(expanded[i]->get_state()) == 0)
            {
                nodes.push(expanded[i]);
            }
        }
        first = false;
        if (nodes.size() > max_q_size) { max_q_size = nodes.size(); }

        visited.insert(curr_node->get_state());

    } while(true);
    cout << "To solve this problem with the search algorithm expanded a total of " << nodes_expanded << " nodes." << endl;
    cout << "The maximum number of nodes in the queue at any one time was " << max_q_size << endl;
    cout << "The depth of the goal node was " << max_depth << endl;
}

int main()
{
    clock_t start;
    double duration;
    //default puzzles
    vector<vector<int> > trivial = {{1,2,3},{4,5,6},{7,8,0}};
    vector<vector<int> > very_easy = {{1,2,3},{4,5,6},{7,0,8}};
    vector<vector<int> > easy = {{1,2,0},{4,5,3},{7,8,6}};
    vector<vector<int> > doable = {{0,1,2},{4,5,3},{7,8,6}};
    vector<vector<int> > oh_boy = {{8,7,1},{6,0,2},{5,4,3}};
    vector<vector<int> > impossible = {{1,2,3},{6,0,2},{5,4,3}};
    vector<vector<int> > v = {{8,1,3},{4,0,2},{7,6,5}};

    Node* init = NULL;

    int input;
    cout << "Welcome Logan's 8-puzzle solver!" << endl;
    cout << "Type \"1\" to use a default puzzle, or \"2\" to enter your own puzzle." << endl;
    cin >> input;
    cout << endl;
    string row1;
    string row2;
    string row3;
    cin.ignore();
    vector<vector<int> > user_input_board;
    vector<int> v1, v2, v3;
    stringstream s1, s2, s3;
    int val;
    bool skip = false;
    switch(input)
    {
        case 1:
            cout << "\t1. Trivial" << endl;
            cout << "\t2. Very Easy" << endl;
            cout << "\t3. Easy" << endl;
            cout << "\t4. Doable" << endl;
            cout << "\t5. Oh Boy" << endl;
            cout << "\t6. Impossible" << endl;
            cin >> input;
            break;
        case 2: 
            cout << "Enter your puzzle, use a zero to represent the blank" << endl;
            cout << "Enter the first row, use space or tabs between numbers\t";
            getline(cin, row1);
            cout << "Enter the second row, use space or tabs between numbers\t";
            getline(cin, row2);
            cout << "Enter the third row, use space or tabs between numbers\t";
            getline(cin, row3);
            s1 << row1;
            while(s1 >> val) { v1.push_back(val); }
            s2 << row2;
            while(s2 >> val) { v2.push_back(val); }
            s3 << row3;
            while(s3 >> val) { v3.push_back(val); }
            user_input_board.push_back(v1);
            user_input_board.push_back(v2);
            user_input_board.push_back(v3);
            init = new Node(user_input_board, 0);
            skip = true;
            break;
        default:
            cout << "Invalid entry" << endl;
            break;

    }
    //selecting default board
    if (!skip)
    {
        switch(input)
        {
            case 1:
                init = new Node(trivial, 0);
                break;
            case 2:
                init = new Node(very_easy, 0);
                break;
            case 3:
                init = new Node(easy, 0);
                break;
            case 4:
                init = new Node(doable, 0);
                break;
            case 5:
                init = new Node(oh_boy, 0);
                break;
            case 6:
                init = new Node(impossible, 0);
                break;    
            default:
                cout << "Invalid entry" << endl;
                break;
        }
    }
    cout << endl;
    cout << "Enter your choice of algorithm" << endl;
    cout << "\t1. Uniform Cost Search" << endl;
    cout << "\t2. A* with Misplaced Tile heuristic" << endl;
    cout << "\t3. A* with Manhattan distance heuristic" << endl;
    cin >> input;
    cout << endl;
    switch(input)
    {   
        case 1:
            uniform_cost(init);
            break;
        case 2:
            misplaced_tile(init);
            break;
        default:
            manhattan(init);
            break;
    }

    return 0;
}