//#include "RDtree.h"
//int LineSS = 200;
//double Sc = 1.2;
//int R = 30;
//const int TreeSize = 13;
//
//
//RDnode::RDnode(bool flag, double value, int x1, int y1, string color, RDnode* parent, RDnode* r, RDnode* l)
//{
//	this->nextr = r;
//	this->nextl = l;
//	this->data = value;
//	this->color = color;
//	this->parent = parent;
//
//	circle.setRadius(R);
//	if (color == "black") {
//		circle.setFillColor(Color::Black);
//	}
//	if (color == "red") {
//		circle.setFillColor(Color::Red);
//	}
//	if (flag)
//	{
//		x = x1 + LineSS;
//		y = y1 + LineSS;
//	}
//
//	else
//	{
//		x = x1 - LineSS;
//		y = y1 + LineSS;
//	}
//
//	circle.setPosition(x, y);
//}
//
//void list::add(double value, RenderWindow& window, Text& txt)
//{
//	if (head == nullptr)
//	{
//		head = new RDnode(true, value, window.getSize().x / 2 - LineSS, 0 - LineSS, "black", nullptr);
//	}
//
//	else
//	{
//		RDnode* curr = head;
//		while (1)
//		{
//			if (value > curr->data)
//			{
//				if (curr->nextr == nullptr)
//				{
//					if (curr->nextl == nullptr)
//						LineSS /= Sc;
//					curr->nextr = new RDnode(true, value, curr->x, curr->y, "red", curr);
//					addbalance(curr->nextr, window, txt);
//					break;
//				}
//				else
//					curr = curr->nextr;
//			}
//
//			if (value < curr->data)
//			{
//				if (curr->nextl == nullptr)
//				{
//					if (curr->nextr == nullptr)
//						LineSS /= Sc;
//					curr->nextl = new RDnode(false, value, curr->x, curr->y, "red", curr);
//					addbalance(curr->nextl, window, txt);
//					break;
//				}
//				else
//					curr = curr->nextl;
//			}
//		}
//
//
//	}
//}
//
//void list::addbalance(RDnode* Insert, RenderWindow& window, Text& txt)
//{
//	while (Insert->parent->color == "red") {
//		auto grandparent = Insert->parent->parent;
//		auto uncle = head;
//		if (Insert->parent == grandparent->nextl) {
//			if (grandparent->nextr) { uncle = grandparent->nextr; }
//			if (uncle->color == "red") {
//				Insert->parent->color = "black";
//				uncle->color = "black";
//				grandparent->color = "red";
//				if (grandparent->data != head->data) { Insert = grandparent; }
//				else { break; }
//			}
//			else if (Insert = grandparent->nextl->nextr) {
//				leftrotate(Insert->parent);
//			}
//			else {
//				Insert->parent->color = "BLACK";
//				grandparent->color = "RED";
//				rightrotate(grandparent);
//				if (grandparent->data != head->data) { Insert = grandparent; }
//				else { break; }
//			}
//		}
//		else {
//			if (grandparent->nextl) { uncle = grandparent->nextl; }
//			if (uncle->color == "RED") {
//				Insert->parent->color = "BLACK";
//				uncle->color = "BLACK";
//				grandparent->color = "RED";
//				if (grandparent->data != head->data) { Insert = grandparent; }
//				else { break; }
//			}
//			else if (Insert == grandparent->nextr->nextl) {
//				rightrotate(Insert->parent);
//			}
//			else {
//				Insert->parent->color = "BLACK";
//				grandparent->color = "RED";
//				leftrotate(grandparent);
//				if (grandparent->data != head->data) { Insert = grandparent; }
//				else { break; }
//			}
//		}
//	}
//	head->color = "black";
//}
//
//void list::leftrotate(RDnode* Insert)
//{
//	RDnode* nw_node = new RDnode(true, 0, 0, 0, "red", nullptr);
//	if (Insert->nextr->nextl) { nw_node->nextr = Insert->nextr->nextl; }
//	nw_node->nextl = Insert->nextl;
//	nw_node->data = Insert->data;
//	nw_node->color = Insert->color;
//	Insert->data = Insert->nextr->data;
//	Insert->color = Insert->nextr->color;
//	Insert->nextl = nw_node;
//	if (nw_node->nextl) { nw_node->nextl->parent = nw_node; }
//	if (nw_node->nextr) { nw_node->nextr->parent = nw_node; }
//	nw_node->parent = Insert;
//	if (Insert->nextr->nextr) { Insert->nextr = Insert->nextr->nextr; }
//	else { Insert->nextr = nullptr; }
//	if (Insert->nextr) { Insert->nextr->parent = Insert; }
//}
//
//void list::rightrotate(RDnode* Insert)
//{
//	RDnode* nw_node = new RDnode(true, 0, 0, 0, "red", nullptr);
//	if (Insert->nextl->nextr) { nw_node->nextl = Insert->nextl->nextr; }
//	nw_node->nextr = Insert->nextr;
//	nw_node->data = Insert->data;
//	nw_node->color = Insert->color;
//
//	Insert->data = Insert->nextl->data;
//	Insert->color = Insert->nextl->color;
//	Insert->nextr = nw_node;
//
//	if (nw_node->nextl) { nw_node->nextl->parent = nw_node; }
//	if (nw_node->nextr) { nw_node->nextr->parent = nw_node; }
//
//	nw_node->parent = Insert;
//
//	if (Insert->nextl->nextl) { Insert->nextl = Insert->nextl->nextl; }
//	else { Insert->nextl = nullptr; }
//	if (Insert->nextl) { Insert->nextl->parent = Insert; }
//}
//
//void list::bfs(RDnode* head, RenderWindow& window, Text& txt)
//{
//	queue<RDnode*> q;
//
//	q.push(head);
//
//	int i = TreeSize;
//
//	while (i != 0) {
//		RDnode* tmp = q.front();
//		q.pop();
//		if (tmp->color == "black") {
//			tmp->circle.setFillColor(Color::Black);
//		}
//		else {
//			tmp->circle.setFillColor(Color::Red);
//		}
//
//		cout << tmp->data << endl;
//		if (tmp == head) {
//			window.draw(head->circle);
//			txt.setPosition(head->x + 20, head->y + 10);
//			txt.setString(to_string(head->data));
//			window.draw(txt);
//
//			if (head->nextr != nullptr) {
//				Vertex line[2] =
//				{
//					Vertex(Vector2f(head->x + R,head->y + R)),
//					Vertex(Vector2f(head->nextr->x + R,head->nextr->y + R))
//				};
//				line->color = Color::Green;
//				window.draw(line, 2, Lines);
//			}
//			if (head->nextl != nullptr) {
//				Vertex Line[2] =
//				{
//					Vertex(Vector2f(head->x + R,head->y + R)),
//					Vertex(Vector2f(head->nextl->x + R,head->nextl->y + R))
//				};
//				Line->color = Color::Green;
//				window.draw(Line, 2, Lines);
//			}
//
//		}
//		else {
//			window.draw(tmp->circle);
//			txt.setPosition(tmp->x + 20, tmp->y + 10);
//			txt.setString(to_string(tmp->data));
//			window.draw(txt);
//
//			if (tmp->nextr != nullptr) {
//				Vertex line[2] =
//				{
//					Vertex(Vector2f(tmp->x + R,tmp->y + R)),
//					Vertex(Vector2f(tmp->nextr->x + R,tmp->nextr->y + R))
//				};
//				line->color = Color::Green;
//				window.draw(line, 2, Lines);
//			}
//			if (tmp->nextl != nullptr) {
//				Vertex Line[2] =
//				{
//					Vertex(Vector2f(tmp->x + R,tmp->y + R)),
//					Vertex(Vector2f(tmp->nextl->x + R,tmp->nextl->y + R))
//				};
//				Line->color = Color::Green;
//				window.draw(Line, 2, Lines);
//			}
//
//		}
//
//
//		i--;
//		if (tmp->nextl) {
//			q.push(tmp->nextl);
//		}
//
//		if (tmp->nextr) {
//			q.push(tmp->nextr);
//		}
//	}
//}
//
//void rdtree()
//{
//	Font font;
//
//	font.loadFromFile("C:/WINDOWS/Fonts/arial.ttf");
//	Text txt("", font, 30);
//	list lst;
//
//	RenderWindow window(VideoMode(1900, 980), "BinaryTree");
//	window.clear(Color(30, 30, 30, 2));
//	double value;
//
//
//	for (int i = 0; i < TreeSize; i++)
//	{
//		value = rand();
//		lst.add(value, window, txt);
//	}
//
//	lst.bfs(lst.head, window, txt);
//	window.display();
//
//
//	while (window.isOpen())
//	{
//
//
//
//		Event event;
//		while (window.pollEvent(event))
//		{
//			if (event.type == Event::Closed)
//				window.close();
//		}
//
//	}
//}
#include "RDtree.h"
int LineSss = 200;
int width = 1900;
int height = 980;
double SCc = 1.2;
int Rad = 30;
const int TreesizE = 100000;
double timeBal = 0;

RDtree::RDtree() : head(nullptr) {}


node* RDtree::GetHead()
{
	return head; 
}


void RDtree::InsertNode(int stuff)
{
    if (head == nullptr) {
        head = new node();
        head->data = stuff;
        head->parent = nullptr;
        head->color = "BLACK";
    }
    else {
        node* curr = GetHead();
        node* newnode = new node();
        newnode->data = stuff;

        while (curr != nullptr) {
            if (curr->data > stuff) {
                if (curr->left == nullptr) {
                    curr->left = newnode;
                    newnode->color = "RED";
                    newnode->parent = curr;
                    break;
                }
                else { curr = curr->left; }
            }
            else {
                if (curr->right == nullptr) {
                    curr->right = newnode;
                    newnode->color = "RED";
                    newnode->parent = curr;
                    break;
                }
                else { curr = curr->right; }
            }
        }
        BalanceNode(newnode);
    }
}


void RDtree::BalanceNode(node* z)
{
    clock_t begin = clock();
    while (z->parent->color == "RED") {
        node* grandparent = z->parent->parent;
        node* uncle = GetHead();
        if (z->parent == grandparent->left) {
            if (grandparent->right) { uncle = grandparent->right; }
            if (uncle->color == "RED") {
                z->parent->color = "BLACK";
                uncle->color = "BLACK";
                grandparent->color = "RED";
                if (grandparent->data != head->data) { z = grandparent; }
                else { clock_t end = clock(); timeBal += ((double)(end - begin) / (CLOCKS_PER_SEC / 1000)); break; }
            }
            else if (z == grandparent->left->right) {
                LeftRotate(z->parent);
            }
            else {
                z->parent->color = "BLACK";
                grandparent->color = "RED";
                RightRotate(grandparent);
                if (grandparent->data != head->data) { z = grandparent; }
                else { clock_t end = clock(); timeBal += ((double)(end - begin) / (CLOCKS_PER_SEC / 1000)); break; }
            }
        }
        else {
            if (grandparent->left) { uncle = grandparent->left; }
            if (uncle->color == "RED") {
                z->parent->color = "BLACK";
                uncle->color = "BLACK";
                grandparent->color = "RED";
                if (grandparent->data != head->data) { z = grandparent; }
                else { clock_t end = clock(); timeBal += ((double)(end - begin) / (CLOCKS_PER_SEC / 1000)); break; }
            }
            else if (z == grandparent->right->left) {
                RightRotate(z->parent);
            }
            else {
                z->parent->color = "BLACK";
                grandparent->color = "RED";
                LeftRotate(grandparent);
                if (grandparent->data != head->data) { z = grandparent; }
                else { clock_t end = clock(); timeBal += ((double)(end - begin) / (CLOCKS_PER_SEC / 1000)); break; }
            }
        }
    }
    head->color = "BLACK";
}


void RDtree::LeftRotate(node* x)
{
    {
        node* nw_node = new node();
        if (x->right->left) { nw_node->right = x->right->left; }
        nw_node->left = x->left;
        nw_node->data = x->data;
        nw_node->color = x->color;
        x->data = x->right->data;
        x->color = x->right->color;
        x->left = nw_node;
        if (nw_node->left) { nw_node->left->parent = nw_node; }
        if (nw_node->right) { nw_node->right->parent = nw_node; }
        nw_node->parent = x;

        if (x->right->right) { x->right = x->right->right; }
        else { x->right = nullptr; }

        if (x->right) { x->right->parent = x; }
    }
}


void RDtree::RightRotate(node* x)
{
    {
        node* nw_node = new node();
        if (x->left->right) { nw_node->left = x->left->right; }
        nw_node->right = x->right;
        nw_node->data = x->data;
        nw_node->color = x->color;

        x->data = x->left->data;
        x->color = x->left->color;

        x->right = nw_node;
        if (nw_node->left) { nw_node->left->parent = nw_node; }
        if (nw_node->right) { nw_node->right->parent = nw_node; }
        nw_node->parent = x;

        if (x->left->left) { x->left = x->left->left; }
        else { x->left = nullptr; }

        if (x->left) { x->left->parent = x; }
    }
}


void RDtree::bfs(node* head, RenderWindow& window, Text& txt)
{
    queue<node*> q;

    q.push(head);

    int i = TreesizE;

    while (i != 0) {
            node* tmp = q.front();
            q.pop();
            tmp->circle.setRadius(30);
            if(tmp->color=="BLACK") tmp->circle.setFillColor(Color::Black);
            if (tmp->color == "RED") tmp->circle.setFillColor(Color::Red);

            //cout << tmp->data << endl;

            if (tmp == head) {
                head->circle.setPosition(width / 2, 1);
                window.draw(head->circle);
                txt.setPosition(width / 2 + 20, 7);
                txt.setString(to_string(head->data));
                window.draw(txt);
            }

            else {
                tmp->circle.setPosition(tmp->x, tmp->y);
                window.draw(tmp->circle);
                txt.setPosition(tmp->x + 20, tmp->y + 10);
                txt.setString(to_string(tmp->data));
                window.draw(txt);
            }


            i--;
            if (tmp->left) {
                LineSss /= SCc;
                tmp->left->x = tmp->x - LineSss;
                tmp->left->y = tmp->y + LineSss;
                q.push(tmp->left);
            }

            if (tmp->right) {
                LineSss /= SCc;
                tmp->right->x = tmp->x + LineSss;
                tmp->right->y = tmp->y + LineSss;
                q.push(tmp->right);
            }
        }

    while (!q.empty())
    {
        q.pop();
    }
    q.push(head);
    i = TreesizE;

    while (i != 0) {
        node* tmp = q.front();
        q.pop();
        //cout << tmp->data << endl;

        if (tmp == head) {

            Vertex line[2] =
            {
                Vertex(Vector2f(head->x + Rad,head->y + Rad)),
                Vertex(Vector2f(head->right->x + Rad,head->right->y + Rad))
            };
            line->color = Color::Green;
            window.draw(line, 2, Lines);

            Vertex Line[2] =
            {
                Vertex(Vector2f(head->x + Rad,head->y + Rad)),
                Vertex(Vector2f(head->left->x + Rad,head->left->y + Rad))
            };
            Line->color = Color::Green;
            window.draw(Line, 2, Lines);

        }

        else {

            if (tmp->right != nullptr) {
                Vertex line[2] =
                {
                    Vertex(Vector2f(tmp->x + Rad,tmp->y + Rad)),
                    Vertex(Vector2f(tmp->right->x + Rad,tmp->right->y + Rad))
                };
                line->color = Color::Green;
                window.draw(line, 2, Lines);
            }
            if (tmp->left != nullptr) {
                Vertex Line[2] =
                {
                    Vertex(Vector2f(tmp->x + Rad,tmp->y + Rad)),
                    Vertex(Vector2f(tmp->left->x + Rad,tmp->left->y + Rad))
                };
                Line->color = Color::Green;
                window.draw(Line, 2, Lines);
            }
        }


        i--;
        if (tmp->left) {
            q.push(tmp->left);
        }

        if (tmp->right) {
            q.push(tmp->right);
        }
    }

    }


int RDTree()
{
    Font font;

    font.loadFromFile("C:/WINDOWS/Fonts/arial.ttf");
    Text txt("", font, 30);
    RDtree lst;

    RenderWindow window(VideoMode(1900, 980), "BinaryTree");
    window.clear(Color(30, 30, 30, 2));
    double value;


    for (int i = 0; i < TreesizE; i++)
    {
        value = rand();
        lst.InsertNode(value);
    }

   lst.bfs(lst.GetHead(), window, txt);
   cout << endl << timeBal << endl;
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
    return 0;
}
