
#include <iostream>
#include <SFML/Graphics.hpp>
#include <queue>
#include <stack>

using namespace std;
using namespace sf;

int LineS = 200;
double sc = 1.2;
int R = 30;
const int TreeSize = 10;
int minTree = INT_MAX;
int maxTree = 0;




class node {
public:
	friend SFML_GRAPHICS_API CircleShape;
	friend SFML_GRAPHICS_API Vertex;

	int data;
	node* nextr;
	node* nextl;
	bool Visited;
	string An;
	CircleShape circle;

	int x;
	int y;

	node(bool flag, double value, int x1, int y1, node* r = nullptr, node* l = nullptr)
	{
		this->nextr = r;
		this->nextl = l;
		this->data = value;

		circle.setRadius(R);
		circle.setFillColor(Color::Green);

		if (flag)
		{
			x = x1 + LineS;
			y = y1 + LineS;
		}

		else
		{
			x = x1 - LineS;
			y = y1 + LineS;
		}

		circle.setPosition(x, y);

	}
};




class List {
public:
	node* head = nullptr;

	void add(double value, RenderWindow& window, Text& txt)
	{
		if (head == nullptr)
		{
			head = new node(true, value, window.getSize().x / 2 - LineS, 0 - LineS);
			window.draw(head->circle);
			txt.setPosition(head->x + 20, head->y + 10);
			txt.setString(to_string(head->data));
			window.draw(txt);
		}

		else
		{
			node* curr = head;
			while (1)
			{
				if (value > curr->data)
				{
					if (curr->nextr == nullptr)
					{
						if (curr->nextl == nullptr)
							LineS /= sc;
						curr->nextr = new node(true, value, curr->x, curr->y);
						Vertex line[2] =
						{
							Vertex(Vector2f(curr->x + R,curr->y + R)),
							Vertex(Vector2f(curr->nextr->x + R,curr->nextr->y + R))
						};
						line->color = Color::Green;
						window.draw(line, 2, Lines);
						window.draw(curr->nextr->circle);
						txt.setPosition(curr->nextr->x + 20, curr->nextr->y + 10);
						txt.setString(to_string(curr->nextr->data));
						window.draw(txt);

						break;
					}
					else
						curr = curr->nextr;
				}

				if (value < curr->data)
				{
					if (curr->nextl == nullptr)
					{
						if (curr->nextr == nullptr)
							LineS /= sc;
						curr->nextl = new node(false, value, curr->x, curr->y);
						Vertex line[2] =
						{
							Vertex(Vector2f(curr->x + R,curr->y + R)),
							Vertex(Vector2f(curr->nextl->x + R,curr->nextl->y + R))
						};
						line->color = Color::Green;
						window.draw(line, 2, Lines);
						window.draw(curr->nextl->circle);
						txt.setPosition(curr->nextl->x + 20, curr->nextl->y + 10);
						txt.setString(to_string(curr->nextl->data));
						window.draw(txt);

						break;
					}
					else
						curr = curr->nextl;
				}
			}
		}
	}




};




bool isOperator(char x) {
	switch (x) {
	case '+':
	case '-':
	case '/':
	case '*':
	case '^':
	case '%':
		return true;
	}
	return false;
}




bool isOperator2(char c)
{
	return (!isalpha(c) && !isdigit(c));
}




bool isOperand(char x)
{
	return (x >= 'a' && x <= 'z') ||
		(x >= 'A' && x <= 'Z');
}




int getPriority(char C)
{
	if (C == '-' || C == '+')
		return 1;
	else if (C == '*' || C == '/')
		return 2;
	else if (C == '^')
		return 3;
	return 0;
}




void preOrder(node* head) {
	if (!head) { return; }

	preOrder(head->nextl);
	preOrder(head->nextr);
	if (head->data) {
		if (head->data > maxTree) {
			maxTree = head->data;
		}
		cout << head->data << endl;
	}

}




void postOrder(node* head) {
	if (!head) { return; }

	if (head->data) {
		if (head->data < minTree) {
			minTree = head->data;
		}
		cout << head->data << endl;
	}
	postOrder(head->nextl);
	postOrder(head->nextr);

}




void inOrder(node* head) {
	if (!head) { return; }
	inOrder(head->nextl);
	if (head->data) { cout << head->data << endl; }
	inOrder(head->nextr);
}




void BFS(node* head) {

	queue<node*> q;

	q.push(head);

	int i = TreeSize;

	while (i != 0) {
		node* tmp = q.front();
		q.pop();
		cout << tmp->data << endl;
		i--;
		if (tmp->nextl) {
			q.push(tmp->nextl);
		}

		if (tmp->nextr) {
			q.push(tmp->nextr);
		}
	}

}




node* find(node* head, int key)
{
	if (head == NULL)
	{
		return NULL;
	}
	if (head->data == key)
	{
		return head;
	}

	if (key <= head->data)
	{

		if (head->nextl != NULL)
			return find(head->nextl, key);
		else
		{
			return NULL;
		}
	}
	else
	{

		if (head->nextr)
			return find(head->nextr, key);
		else
		{
			return NULL;
		}
	}
}




node* prev(node* head, int key)
{
	if (head == NULL)
	{
		return NULL;  
	}
	if (head->nextl->data == key)
	{
		return head; 
	}

	if (head->nextr->data == key)
	{
		return head; 
	}

	if (key <= head->data)
	{
		
		if (head->nextl != NULL)
			return prev(head->nextl, key); 
		else
		{
			return NULL; 
		}
	}
	else
	{
		
		if (head->nextr)
			return prev(head->nextr, key);
		else
		{
			return NULL; 
		}
	}
}




node* nextEl(node* head, int key,int flag) {
	if (head == NULL)
	{
		return NULL;
	}
	if (head->data == key)
	{
		if (flag == 0) {
			if (head->nextl != nullptr) {
				return head->nextl;
			}
		}
		if (flag == 1) {
			if (head->nextr != nullptr) {
				return head->nextr;
			}
		}
	}

	if (key <= head->data)
	{

		if (head->nextl != NULL)
			return nextEl(head->nextl, key,flag);
		else
		{
			return NULL;
		}
	}
	else
	{

		if (head->nextr)
			return nextEl(head->nextr, key,flag);
		else
		{
			return NULL;
		}
	}
}




node* DeleteNode(node * head, int val) {

		if (head == NULL)
			return head;

		if (val == head->data) {

			node* tmp;

			if (head->nextr == NULL)
				tmp = head->nextl;

			else {

				node* ptr = head->nextr;

				if (ptr->nextl == NULL) {
					ptr->nextl = head->nextl;
					tmp = ptr;
				}

				else {

					node* pmin = ptr->nextl;
					while (pmin->nextl != NULL) {
						ptr = pmin;
						pmin = ptr->nextl;
					}
					ptr->nextl = pmin->nextr;
					pmin->nextl = head->nextl;
					pmin->nextr = head->nextr;
					tmp = pmin;
				}

			}

			delete head;
			return tmp;
		}

		else if (val < head->data)
			head->nextl = DeleteNode(head->nextl, val);

		else
			head->nextr = DeleteNode(head->nextr, val);

		return head;
	}




string preToPost(string pre_exp)
{

	stack<string> s;
	int length = pre_exp.size();

	for (int i = length - 1; i >= 0; i--)
	{
		
		if (isOperator(pre_exp[i]))
		{
		
			string op1 = s.top();
			s.pop();
			string op2 = s.top();
			s.pop();

			
			string temp = op1 + op2 + pre_exp[i];

			
			s.push(temp);
		}

		
		else {

			
			s.push(string(1, pre_exp[i]));
		}
	}

	
	return s.top();
}




string preToInf(string pre_exp) {
	stack<string> s;


	int length = pre_exp.size();


	for (int i = length - 1; i >= 0; i--) {


		if (isOperator(pre_exp[i])) {


			string op1 = s.top();   s.pop();
			string op2 = s.top();   s.pop();


			string temp = "(" + op1 + pre_exp[i] + op2 + ")";


			s.push(temp);
		}


		else {


			s.push(string(1, pre_exp[i]));
		}
	}
	return s.top();
}




string infixToPostfix(string infix)
{
    infix = '(' + infix + ')';
    int l = infix.size();
    stack<char> char_stack;
    string output;
 
    for (int i = 0; i < l; i++) {
 
        
        if (isalpha(infix[i]) || isdigit(infix[i]))
            output += infix[i];
 
        
        else if (infix[i] == '(')
            char_stack.push('(');
 
        
        else if (infix[i] == ')') {
            while (char_stack.top() != '(') {
                output += char_stack.top();
                char_stack.pop();
            }
 
           
            char_stack.pop();
        }
 
        
        else
        {
            if (isOperator2(char_stack.top()))
            {
                if(infix[i] == '^')
                {
                      while (getPriority(infix[i]) <= getPriority(char_stack.top()))
                       {
                         output += char_stack.top();
                         char_stack.pop();
                       }
                     
                }
                else
                {
                    while (getPriority(infix[i]) < getPriority(char_stack.top()))
                       {
                         output += char_stack.top();
                         char_stack.pop();
                       }
                     
                }
 
                
                char_stack.push(infix[i]);
            }
        }
    }
      while(!char_stack.empty()){
          output += char_stack.top();
        char_stack.pop();
    }
    return output;
}
 



string infixToPrefix(string infix)
{

    int l = infix.size();
 
    
    reverse(infix.begin(), infix.end());
 
    
    for (int i = 0; i < l; i++) {
 
        if (infix[i] == '(') {
            infix[i] = ')';
        }
        else if (infix[i] == ')') {
            infix[i] = '(';
        }
    }
 
    string prefix = infixToPostfix(infix);
 
    
    reverse(prefix.begin(), prefix.end());
 
    return prefix;
}




string postToInf(string exp)
{
	stack<string> s;

	for (int i = 0; exp[i] != '\0'; i++)
	{
		
		if (isOperand(exp[i]))
		{
			string op(1, exp[i]);
			s.push(op);
		}

		
		else
		{
			string op1 = s.top();
			s.pop();
			string op2 = s.top();
			s.pop();
			s.push("(" + op2 + exp[i] +
				op1 + ")");
		}
	}

	
	return s.top();
}




string postToPre(string post_exp)
{
	stack<string> s;

	
	int length = post_exp.size();

	
	for (int i = 0; i < length; i++) {

		
		if (isOperator(post_exp[i])) {

			
			string op1 = s.top();
			s.pop();
			string op2 = s.top();
			s.pop();

			
			string temp = post_exp[i] + op2 + op1;

			
			s.push(temp);
		}

		
		else {

			
			s.push(string(1, post_exp[i]));
		}
	}

	string ans = "";
	while (!s.empty()) {
		ans += s.top();
		s.pop();
	}
	return ans;
}




int	main(){

		Font font;

		font.loadFromFile("C:/WINDOWS/Fonts/arial.ttf");
		Text txt("", font, 30);
		List lst;

		RenderWindow window(VideoMode(1900, 980), "BinaryTree");
		window.clear(Color(30, 30, 30, 2));
		double value;


		for (int i = 0; i < TreeSize; i++)
		{
			cin >> value;
			lst.add(value, window, txt);
		}


		window.display();
		while (window.isOpen())
		{
			Event event;
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed)
					window.close();
			}

		}


		cout << "Preorder: " << endl;
		preOrder(lst.head);


		cout << "PostOrder: " << endl;
		postOrder(lst.head);


		cout << "InOrder: " << endl;
		inOrder(lst.head);


		cout << "BFS: " << endl;
		BFS(lst.head);


		int key = 0;
		cout << endl << "Enter VALUE to find it in tree: " << endl;
		cin >> key;
		find(lst.head, key);


		cout << endl << "Max value in tree: " << maxTree << endl << "Min Value in tree: " << minTree << endl;


		cout << endl << "Previous element: ";;
		cout << prev(lst.head, key)->data << endl;


		lst.head = DeleteNode(lst.head, 6);


		node* nextL = nullptr;
		node* nextR = nullptr;
		nextL=nextEl(lst.head, key,0);
		nextR = nextEl(lst.head, key, 1);
		cout << "Next node's are: " << endl << "Left: " << nextL->data << endl << "Right:" << nextR->data << endl << endl;


		string s = "a+(f-b*c/(z-x)+y)/(a*r-k)";
		cout << "Infix: " << s << endl;
		cout << "infToPre:" << infixToPrefix(s) << endl;
		cout << "inftoPost: " << infixToPostfix(s) << endl << endl;


		s = "+a/+-f/*bc-zxy-*ark";
		cout << "Prefix: " << s << endl;
		cout << "preToInf: " << preToInf(s) << endl;
		cout << "preToPost: " << preToPost(s) << endl << endl;


		return 0;
	}
