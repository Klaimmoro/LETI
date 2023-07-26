#include "AVLtree.h"
int LineSs = 200;
int Width = 1900;
int Height = 980;
double SC = 1.2;
int Ra = 30;
const int Treesize = 4000;
double TimeBal = 0;
//
//
//NodeAVL::NodeAVL(bool flag, double value, int x1, int y1, NodeAVL* r, NodeAVL* l, int Koeff)
//{
//	this->nextr = r;
//	this->nextl = l;
//	this->data = value;
//	this->Koeff = Koeff;
//	circle.setRadius(R);
//	circle.setFillColor(Color::Green);
//
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
//
//void treeAVL::add(double value,RenderWindow& window, Text& txt)
//{
//	if (head == nullptr)
//	{
//		head = new NodeAVL(true, value, window.getSize().x / 2 - LineSS, 0 - LineSS);
//		addBalance(head, window, txt);
//	}
//
//	else
//	{
//		NodeAVL* curr = head;
//		while (1)
//		{
//			if (value > curr->data)
//			{
//				if (curr->nextr == nullptr)
//				{
//					if (curr->nextl == nullptr)
//						LineSS /= Sc;
//					curr->nextr = new NodeAVL(true, value, curr->x, curr->y);
//					addBalance(curr, window, txt);
//					break;
//				}
//				else
//					addBalance(curr, window, txt);
//					curr = curr->nextr;
//			}
//
//			if (value < curr->data)
//			{
//				if (curr->nextl == nullptr)
//				{
//					if (curr->nextr == nullptr)
//						LineSS /= Sc;
//					curr->nextl = new NodeAVL(false, value, curr->x, curr->y);
//					addBalance(curr, window, txt);
//					break;
//				}
//				else
//					addBalance(curr, window, txt);
//					curr = curr->nextl;
//			}
//
//
//		}
//
//
//
//
//	}
//}
//
//
//NodeAVL* treeAVL::addBalance(NodeAVL* Insert, RenderWindow& window, Text& txt)
//{
//	fixheight(Insert);
//	if (bfactor(Insert) == 2)
//	{
//		if (bfactor(Insert->nextr) < 0)
//			Insert->nextr = RightRotate(Insert->nextr);
//		//cout << "Balanced node: " << Insert->data << ' ' << Insert->Koeff << endl;
//		return LeftRotate(Insert);
//	}
//	if (bfactor(Insert) == -2)
//	{
//		if (bfactor(Insert->nextl) > 0)
//			Insert->nextl = LeftRotate(Insert->nextl);
//		//cout << "Balanced node: " << Insert->data << ' ' << Insert->Koeff << endl;
//
//		return RightRotate(Insert);
//	}
//	//cout << "Notbalanced node: " << Insert->data << ' ' << Insert->Koeff << endl;
//	return Insert; 
//}
//
//
//void treeAVL::fixheight(NodeAVL* p)
//{
//	int hl = height(p->nextl);
//
//	int hr = height(p->nextr);
//
//	p->Koeff = hr - hl;
//
//}
//
//
//int treeAVL::height(NodeAVL* p)
//{
//	int b = 0;
//	if (p != nullptr) { return p->Koeff; }
//	else { return b; }
//}
//
//
//int treeAVL::bfactor(NodeAVL* p)
//{
//	return height(p->nextr) - height(p->nextl);
//}
//
//
//NodeAVL* treeAVL::LeftRotate(NodeAVL* Insert)
//{
//	NodeAVL* p = Insert->nextr;
//	Insert->nextr = p->nextl;
//	p->nextl = Insert;
//	fixheight(Insert);
//	fixheight(p);
//	return p;
//
//}
//
//
//NodeAVL* treeAVL::RightRotate(NodeAVL* Insert)
//{
//	NodeAVL* q = Insert->nextl;
//	Insert->nextl = q->nextr;
//	q->nextr = Insert;
//	fixheight(Insert);
//	fixheight(q);
//	return q;
//}
//
//
//void treeAVL::BFS(NodeAVL* head, RenderWindow& window, Text& txt) {
//
//	queue<NodeAVL*> q;
//
//	q.push(head);
//
//	int i = TreeSize;
//
//	while (i != 0) {
//		NodeAVL* tmp = q.front();
//		q.pop();
//		cout << tmp->data << endl;
//
//	/*	if (tmp == head) {
//			window.draw(head->circle);
//			txt.setPosition(head->x + 20, head->y + 10);
//			txt.setString(to_string(head->data));
//			window.draw(txt);
//			txt.setPosition(head->x + 20, head->y -15);
//			txt.setString(to_string(int(head->Koeff)));
//			window.draw(txt);
//		}
//
//		else {
//			window.draw(tmp->circle);
//			txt.setPosition(tmp->x + 20, tmp->y + 10);
//			txt.setString(to_string(tmp->data));
//			window.draw(txt);
//			txt.setPosition(tmp->x + 20, tmp->y - 15);
//			txt.setString(to_string(int(tmp->Koeff)));
//			window.draw(txt);
//
//		}*/
//
//
//		i--;
//		if (tmp->nextl) {
//			cout << "left";
//			q.push(tmp->nextl);
//		}
//
//		if (tmp->nextr) {
//			cout << "right";
//			q.push(tmp->nextr);
//		}
//	}
//
//
//
//}
//
//
//void AVLtree() {
//	Font font;
//
//	font.loadFromFile("C:/WINDOWS/Fonts/arial.ttf");
//	Text txt("", font, 30);
//	treeAVL lst;
//
//	RenderWindow window(VideoMode(1900, 980), "BinaryTree");
//	window.clear(Color(30, 30, 30, 2));
//	double value;
//
//
//	for (int i = 0; i < TreeSize; i++)
//	{
//		cin >> value;
//		lst.add(value,window, txt);
//	}
//	cout << lst.head->data << endl;
//	cout << lst.head->nextl->data << " " << lst.head->nextr->data << endl;
//	//cout << "     " << lst.head->nextr->nextl->data << " " << lst.head->nextr->nextr->data << endl;
//	//lst.BFS(lst.head, window, txt);
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


AVLnode::AVLnode(int k)
{
	data = k; left = right = 0; height = 1; 

	circle.setRadius(Ra);
	circle.setFillColor(Color::Green);
}


int height(AVLnode* p)
{
	return p ? p->height : 0;
}


int bfactor(AVLnode* p)
{
	return height(p->right) - height(p->left);
}


void fixheight(AVLnode* p)
{
	int hl = height(p->left);
	int hr = height(p->right);
	p->height = (hl > hr ? hl : hr) + 1;
}


AVLnode* rotateright(AVLnode* p)
{
	AVLnode* q = p->left;
	p->left = q->right;
	q->right = p;
	fixheight(p);
	fixheight(q);
	return q;
}


AVLnode* rotateleft(AVLnode* q)
{
	AVLnode* p = q->right;
	q->right = p->left;
	p->left = q;
	fixheight(q);
	fixheight(p);
	return p;
}


AVLnode* balance(AVLnode* p)
{
	clock_t begin = clock();
	fixheight(p);
	if (bfactor(p) == 2)
	{
		if (bfactor(p->right) < 0)
			p->right = rotateright(p->right);
		clock_t end = clock();
		TimeBal += ((double)(end - begin) / (CLOCKS_PER_SEC / 1000));
		return rotateleft(p);
	}
	if (bfactor(p) == -2)
	{
		if (bfactor(p->left) > 0)
			p->left = rotateleft(p->left);
		clock_t end = clock();
		TimeBal += ((double)(end - begin) / (CLOCKS_PER_SEC / 1000));
		return rotateright(p);
	}
	clock_t end = clock();
	TimeBal += ((double)(end - begin) / (CLOCKS_PER_SEC / 1000));
	return p;
}


AVLnode* insert(AVLnode* p, int k)
{

	if (!p) return new AVLnode(k);

	if (k < p->data) {
		p->left = insert(p->left, k);
	}

	else {
		p->right = insert(p->right, k);
	}

	return balance(p);
}


void BFS(AVLnode* head, RenderWindow& window, Text& txt) {

	queue<AVLnode*> q;

	q.push(head);

	int i = Treesize;

	while (i != 0) {
		AVLnode* tmp = q.front();
		q.pop();
		//cout << tmp->key << endl;

		if (tmp == head) {
			head->circle.setPosition(Width/2,1);
			window.draw(head->circle);
			txt.setPosition(Width/2+20,7);
			txt.setString(to_string(head->data));
			window.draw(txt);
			txt.setPosition(20, -15);
			txt.setString(to_string(int(head->height)));
			window.draw(txt);
		}

		else {
			tmp->circle.setPosition(tmp->x, tmp->y);
			window.draw(tmp->circle);
			txt.setPosition(tmp->x + 20, tmp->y + 10);
			txt.setString(to_string(tmp->data));
			window.draw(txt);
			txt.setPosition(tmp->x + 20, tmp->y - 15);
			txt.setString(to_string(int(tmp->height)));
			window.draw(txt);
		}


		i--;
		if (tmp->left) {
			LineSs /= SC;
			tmp->left->x = tmp->x - LineSs;
			tmp->left->y = tmp->y + LineSs;
			q.push(tmp->left);
		}

		if (tmp->right) {
			LineSs /= SC;
			tmp->right->x = tmp->x + LineSs;
			tmp->right->y = tmp->y + LineSs;
			q.push(tmp->right);
		}
	}


	while (!q.empty())
	{
		q.pop();
	}
	q.push(head);
	i = Treesize;

	while (i != 0) {
		AVLnode* tmp = q.front();
		q.pop();
		//cout << tmp->data << endl;

		if (tmp == head) {

			Vertex line[2] =
			{
				Vertex(Vector2f(head->x + Ra,head->y + Ra)),
				Vertex(Vector2f(head->right->x + Ra,head->right->y + Ra))
			};
			line->color = Color::Green;
			window.draw(line, 2, Lines);

			Vertex Line[2] =
			{
				Vertex(Vector2f(head->x + Ra,head->y + Ra)),
				Vertex(Vector2f(head->left->x + Ra,head->left->y + Ra))
			};
			Line->color = Color::Green;
			window.draw(Line, 2, Lines);

		}

		else {
			
			if (tmp->right != nullptr) {
				Vertex line[2] =
				{
					Vertex(Vector2f(tmp->x + Ra,tmp->y + Ra)),
					Vertex(Vector2f(tmp->right->x + Ra,tmp->right->y + Ra))
				};
				line->color = Color::Green;
				window.draw(line, 2, Lines);
			}
			if (tmp->left != nullptr) {
				Vertex Line[2] =
				{
					Vertex(Vector2f(tmp->x + Ra,tmp->y + Ra)),
					Vertex(Vector2f(tmp->left->x + Ra,tmp->left->y + Ra))
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


void AVLtree() {
	Font font;
	font.loadFromFile("C:/WINDOWS/Fonts/arial.ttf");
	Text txt("", font, 30);
	AVLnode* AVltree=nullptr;

	RenderWindow window(VideoMode(Width, Height), "BinaryTree");
	window.clear(Color(30, 30, 30, 2));
	double value;


	for (int i = 0; i < Treesize; i++)
	{
		value = rand();
		AVltree=insert(AVltree,value);
	}
	cout << endl << "Time bal: " << TimeBal << endl;
	BFS(AVltree,window,txt);
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
}
