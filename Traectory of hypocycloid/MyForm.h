#pragma once
#include "windows.h"
#include "math.h"
#include <vector>
namespace Traectory {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::ColorDialog^ colorDialog1;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::ColorDialog^ colorDialog2;
	private: System::Windows::Forms::ColorDialog^ colorDialog3;
	private: System::Windows::Forms::Button^ button4;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::GroupBox^ groupBox2;
	private: System::Windows::Forms::RadioButton^ dot;
	private: System::Windows::Forms::RadioButton^ lineLine;
	private: System::Windows::Forms::RadioButton^ radioButton1;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::CheckBox^ checkBox1;
	private: System::Windows::Forms::TextBox^ textBox3;
	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::TextBox^ textBox4;
	private: System::Windows::Forms::Label^ label8;
	private: System::Windows::Forms::GroupBox^ groupBox1;
	private: System::Windows::Forms::RadioButton^ left;
	private: System::Windows::Forms::RadioButton^ right;
	private: System::Windows::Forms::GroupBox^ groupBox3;
	private: System::Windows::Forms::RadioButton^ downRight;
	private: System::Windows::Forms::RadioButton^ upRight;
	private: System::Windows::Forms::RadioButton^ center;
	private: System::Windows::Forms::RadioButton^ downLeft;
	private: System::Windows::Forms::RadioButton^ upLeft;
	private: System::Windows::Forms::TextBox^ textBox5;
	private: System::Windows::Forms::Label^ label9;
	private: System::Windows::Forms::PictureBox^ pictureBox2;
	private: System::Windows::Forms::Label^ label10;
		   //array <Point>^ points;
	protected:

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->colorDialog1 = (gcnew System::Windows::Forms::ColorDialog());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->colorDialog2 = (gcnew System::Windows::Forms::ColorDialog());
			this->colorDialog3 = (gcnew System::Windows::Forms::ColorDialog());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->dot = (gcnew System::Windows::Forms::RadioButton());
			this->lineLine = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton1 = (gcnew System::Windows::Forms::RadioButton());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->left = (gcnew System::Windows::Forms::RadioButton());
			this->right = (gcnew System::Windows::Forms::RadioButton());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->downRight = (gcnew System::Windows::Forms::RadioButton());
			this->upRight = (gcnew System::Windows::Forms::RadioButton());
			this->center = (gcnew System::Windows::Forms::RadioButton());
			this->downLeft = (gcnew System::Windows::Forms::RadioButton());
			this->upLeft = (gcnew System::Windows::Forms::RadioButton());
			this->textBox5 = (gcnew System::Windows::Forms::TextBox());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->label10 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->groupBox2->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->groupBox3->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->pictureBox1->Location = System::Drawing::Point(12, 12);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(387, 389);
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(531, 269);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 1;
			this->button1->Text = L"Start";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(405, 31);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(75, 23);
			this->button2->TabIndex = 2;
			this->button2->Text = L"Color";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(405, 114);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(75, 23);
			this->button3->TabIndex = 3;
			this->button3->Text = L"Color";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(424, 15);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(26, 13);
			this->label1->TabIndex = 4;
			this->label1->Text = L"Star";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(416, 98);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(52, 13);
			this->label2->TabIndex = 5;
			this->label2->Text = L"Traectory";
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(405, 73);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(75, 23);
			this->button4->TabIndex = 6;
			this->button4->Text = L"Color";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &MyForm::button4_Click);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(424, 57);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(44, 13);
			this->label3->TabIndex = 7;
			this->label3->Text = L"Contour";
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(531, 31);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(100, 20);
			this->textBox1->TabIndex = 8;
			this->textBox1->Text = L"2";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(528, 12);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(61, 13);
			this->label4->TabIndex = 9;
			this->label4->Text = L"Width (star)";
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(531, 73);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(100, 20);
			this->textBox2->TabIndex = 10;
			this->textBox2->Text = L"2";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(528, 57);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(85, 13);
			this->label5->TabIndex = 11;
			this->label5->Text = L"Width (traectory)";
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->dot);
			this->groupBox2->Controls->Add(this->lineLine);
			this->groupBox2->Controls->Add(this->radioButton1);
			this->groupBox2->Location = System::Drawing::Point(531, 114);
			this->groupBox2->Margin = System::Windows::Forms::Padding(2);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Padding = System::Windows::Forms::Padding(2);
			this->groupBox2->Size = System::Drawing::Size(63, 81);
			this->groupBox2->TabIndex = 28;
			this->groupBox2->TabStop = false;
			this->groupBox2->Enter += gcnew System::EventHandler(this, &MyForm::groupBox2_Enter);
			// 
			// dot
			// 
			this->dot->AutoSize = true;
			this->dot->Location = System::Drawing::Point(4, 52);
			this->dot->Margin = System::Windows::Forms::Padding(2);
			this->dot->Name = L"dot";
			this->dot->Size = System::Drawing::Size(73, 17);
			this->dot->TabIndex = 2;
			this->dot->Text = L". . . . . . . . ";
			this->dot->UseVisualStyleBackColor = true;
			this->dot->CheckedChanged += gcnew System::EventHandler(this, &MyForm::dot_CheckedChanged);
			// 
			// lineLine
			// 
			this->lineLine->AutoSize = true;
			this->lineLine->Location = System::Drawing::Point(4, 31);
			this->lineLine->Margin = System::Windows::Forms::Padding(2);
			this->lineLine->Name = L"lineLine";
			this->lineLine->Size = System::Drawing::Size(64, 17);
			this->lineLine->TabIndex = 1;
			this->lineLine->Text = L"- - - - - - -";
			this->lineLine->UseVisualStyleBackColor = true;
			this->lineLine->CheckedChanged += gcnew System::EventHandler(this, &MyForm::lineLine_CheckedChanged);
			// 
			// radioButton1
			// 
			this->radioButton1->AutoSize = true;
			this->radioButton1->Checked = true;
			this->radioButton1->Location = System::Drawing::Point(4, 10);
			this->radioButton1->Margin = System::Windows::Forms::Padding(2);
			this->radioButton1->Name = L"radioButton1";
			this->radioButton1->Size = System::Drawing::Size(64, 17);
			this->radioButton1->TabIndex = 0;
			this->radioButton1->TabStop = true;
			this->radioButton1->Text = L"-------------";
			this->radioButton1->UseVisualStyleBackColor = true;
			this->radioButton1->CheckedChanged += gcnew System::EventHandler(this, &MyForm::radioButton1_CheckedChanged);
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(532, 98);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(62, 13);
			this->label6->TabIndex = 29;
			this->label6->Text = L"Type of line";
			// 
			// checkBox1
			// 
			this->checkBox1->AutoSize = true;
			this->checkBox1->Location = System::Drawing::Point(410, 139);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(52, 17);
			this->checkBox1->TabIndex = 30;
			this->checkBox1->Text = L"Pulse";
			this->checkBox1->UseVisualStyleBackColor = true;
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(405, 175);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(100, 20);
			this->textBox3->TabIndex = 31;
			this->textBox3->Text = L"12";
			this->textBox3->TextChanged += gcnew System::EventHandler(this, &MyForm::textBox3_TextChanged);
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(407, 159);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(98, 13);
			this->label7->TabIndex = 32;
			this->label7->Text = L"Speed of animation";
			this->label7->Click += gcnew System::EventHandler(this, &MyForm::label7_Click);
			// 
			// textBox4
			// 
			this->textBox4->Location = System::Drawing::Point(637, 31);
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(100, 20);
			this->textBox4->TabIndex = 33;
			this->textBox4->Text = L"1";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(634, 12);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(95, 13);
			this->label8->TabIndex = 34;
			this->label8->Text = L"Count of animation";
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->left);
			this->groupBox1->Controls->Add(this->right);
			this->groupBox1->Location = System::Drawing::Point(637, 63);
			this->groupBox1->Margin = System::Windows::Forms::Padding(2);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Padding = System::Windows::Forms::Padding(2);
			this->groupBox1->Size = System::Drawing::Size(153, 78);
			this->groupBox1->TabIndex = 35;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Direction of movement";
			// 
			// left
			// 
			this->left->AutoSize = true;
			this->left->Location = System::Drawing::Point(4, 46);
			this->left->Margin = System::Windows::Forms::Padding(2);
			this->left->Name = L"left";
			this->left->Size = System::Drawing::Size(109, 17);
			this->left->TabIndex = 1;
			this->left->TabStop = true;
			this->left->Text = L"Counterclockwise";
			this->left->UseVisualStyleBackColor = true;
			this->left->CheckedChanged += gcnew System::EventHandler(this, &MyForm::left_CheckedChanged);
			// 
			// right
			// 
			this->right->AutoSize = true;
			this->right->Checked = true;
			this->right->Location = System::Drawing::Point(4, 25);
			this->right->Margin = System::Windows::Forms::Padding(2);
			this->right->Name = L"right";
			this->right->Size = System::Drawing::Size(73, 17);
			this->right->TabIndex = 0;
			this->right->TabStop = true;
			this->right->Text = L"Clockwise";
			this->right->UseVisualStyleBackColor = true;
			this->right->CheckedChanged += gcnew System::EventHandler(this, &MyForm::right_CheckedChanged);
			// 
			// groupBox3
			// 
			this->groupBox3->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->groupBox3->Controls->Add(this->downRight);
			this->groupBox3->Controls->Add(this->upRight);
			this->groupBox3->Controls->Add(this->center);
			this->groupBox3->Controls->Add(this->downLeft);
			this->groupBox3->Controls->Add(this->upLeft);
			this->groupBox3->Location = System::Drawing::Point(637, 159);
			this->groupBox3->Margin = System::Windows::Forms::Padding(2);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Padding = System::Windows::Forms::Padding(2);
			this->groupBox3->Size = System::Drawing::Size(170, 133);
			this->groupBox3->TabIndex = 36;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"Touch point";
			// 
			// downRight
			// 
			this->downRight->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->downRight->AutoSize = true;
			this->downRight->Location = System::Drawing::Point(79, 96);
			this->downRight->Margin = System::Windows::Forms::Padding(2);
			this->downRight->Name = L"downRight";
			this->downRight->Size = System::Drawing::Size(14, 13);
			this->downRight->TabIndex = 4;
			this->downRight->UseVisualStyleBackColor = true;
			this->downRight->CheckedChanged += gcnew System::EventHandler(this, &MyForm::downRight_CheckedChanged);
			// 
			// upRight
			// 
			this->upRight->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->upRight->AutoSize = true;
			this->upRight->Location = System::Drawing::Point(108, 70);
			this->upRight->Margin = System::Windows::Forms::Padding(2);
			this->upRight->Name = L"upRight";
			this->upRight->Size = System::Drawing::Size(14, 13);
			this->upRight->TabIndex = 3;
			this->upRight->UseVisualStyleBackColor = true;
			// 
			// center
			// 
			this->center->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->center->AutoSize = true;
			this->center->Checked = true;
			this->center->Location = System::Drawing::Point(79, 70);
			this->center->Margin = System::Windows::Forms::Padding(2);
			this->center->Name = L"center";
			this->center->Size = System::Drawing::Size(14, 13);
			this->center->TabIndex = 2;
			this->center->TabStop = true;
			this->center->UseVisualStyleBackColor = true;
			this->center->CheckedChanged += gcnew System::EventHandler(this, &MyForm::center_CheckedChanged);
			// 
			// downLeft
			// 
			this->downLeft->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->downLeft->AutoSize = true;
			this->downLeft->Location = System::Drawing::Point(79, 44);
			this->downLeft->Margin = System::Windows::Forms::Padding(2);
			this->downLeft->Name = L"downLeft";
			this->downLeft->Size = System::Drawing::Size(14, 13);
			this->downLeft->TabIndex = 1;
			this->downLeft->UseVisualStyleBackColor = true;
			// 
			// upLeft
			// 
			this->upLeft->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->upLeft->AutoSize = true;
			this->upLeft->Location = System::Drawing::Point(50, 70);
			this->upLeft->Margin = System::Windows::Forms::Padding(2);
			this->upLeft->Name = L"upLeft";
			this->upLeft->Size = System::Drawing::Size(14, 13);
			this->upLeft->TabIndex = 0;
			this->upLeft->UseVisualStyleBackColor = true;
			this->upLeft->CheckedChanged += gcnew System::EventHandler(this, &MyForm::upLeft_CheckedChanged);
			// 
			// textBox5
			// 
			this->textBox5->Location = System::Drawing::Point(405, 214);
			this->textBox5->Name = L"textBox5";
			this->textBox5->Size = System::Drawing::Size(100, 20);
			this->textBox5->TabIndex = 37;
			this->textBox5->Text = L"1";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(402, 198);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(110, 13);
			this->label9->TabIndex = 38;
			this->label9->Text = L"Number of revolutions";
			// 
			// pictureBox2
			// 
			this->pictureBox2->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox2.BackgroundImage")));
			this->pictureBox2->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureBox2->Location = System::Drawing::Point(419, 329);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(142, 116);
			this->pictureBox2->TabIndex = 39;
			this->pictureBox2->TabStop = false;
			this->pictureBox2->Click += gcnew System::EventHandler(this, &MyForm::pictureBox2_Click);
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(424, 313);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(51, 13);
			this->label10->TabIndex = 40;
			this->label10->Text = L"Condition";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(922, 470);
			this->Controls->Add(this->label10);
			this->Controls->Add(this->pictureBox2);
			this->Controls->Add(this->label9);
			this->Controls->Add(this->textBox5);
			this->Controls->Add(this->groupBox3);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->label8);
			this->Controls->Add(this->textBox4);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->textBox3);
			this->Controls->Add(this->checkBox1);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->pictureBox1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->groupBox3->ResumeLayout(false);
			this->groupBox3->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: void Paint_Graphic(int cX, int cY, int r2, int x, int y, array<Point>^ p)
	{
		Graphics^ Графика = pictureBox1->CreateGraphics();
		Графика->Clear(BackColor);
		Pen^ PZv = gcnew Pen(colorDialog2->Color,Convert::ToInt32(textBox2->Text));
		Графика->DrawLine(PZv, cX, 0, cX, cY * 2);
		Графика->DrawLine(PZv, 0, cY, cX*2, cY);
		if (lineLine->Checked)
			PZv->DashStyle = System::Drawing::Drawing2D::DashStyle::Dash;
		if (dot->Checked)
			PZv->DashStyle = System::Drawing::Drawing2D::DashStyle::Dot;
		Графика->DrawLines(PZv, p); // траектория
	}

	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
		
	}
	
	public: System::Void Paint_Zvezda(array<Point>^ p,Graphics^ g) {
		Pen^ PZv = gcnew Pen(colorDialog3->Color,Convert::ToInt32(textBox1->Text));
		if (lineLine->Checked)
			PZv->DashStyle = System::Drawing::Drawing2D::DashStyle::Dash;
		if (dot->Checked)
			PZv->DashStyle = System::Drawing::Drawing2D::DashStyle::Dot;
		SolidBrush^ Brush = gcnew SolidBrush(colorDialog1->Color);
		g->FillPolygon(Brush, p);
		g->DrawLines(PZv, p);
	}

	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		int repeat = Convert::ToInt32(textBox4->Text);
		int touchPointX, touchPointY;
		if (center->Checked) { touchPointX = 0; touchPointY = 0; }
		if (upLeft->Checked) { touchPointX = 40; touchPointY = 0; }
		if (upRight->Checked) { touchPointX = -40; touchPointY = 0; }
		if (downRight->Checked) { touchPointX = 0; touchPointY = 40; }
		if (downLeft->Checked) { touchPointX = 0; touchPointY = -40; }


		while (repeat--) {
			double LastT{}, angle{};
			double Step = 0.1;
			if (right->Checked) {
				LastT = 6.3; angle = 0;
			}
			if (left->Checked) {
				LastT = 0; angle = 6.3;
			}
			double x, y, x1, y1;
			int cX = 160, cY = 150;
			int R2 = 90;
			int k = 4;
			int R1 = int(R2 / k);
			int i = 0;
			array<Point>^ p;
			p = gcnew array<Point>(64);
			int curent_p = 0;
			bool rise = false;
			double predX = 0; double predY = 0;
			if (right->Checked) {
				while (angle <= LastT)
				{
					x = R1 * (k - 1) * (cos(angle) + cos((k - 1) * angle) / (k - 1));
					y = R1 * (k - 1) * (sin(angle) - sin((k - 1) * angle) / (k - 1));
					p[i] = Drawing::Point(cX + x, cY + y);
					Paint_Graphic(cX, cY, R2, x, y, p);

					double alpha = 0;
					array<Point>^ points;
					points = gcnew array<Point>(9);
					double a = alpha, da = 3.14 / 4, l;
					double R = 10, r = 40;
					if (checkBox1->Checked) {
						if (curent_p == 11) {
							curent_p--;
							rise = true;
						}
						if (curent_p == 0) {
							rise = false;
						}
						R = R / curent_p; r = r / curent_p;
					}
					for (int k = 0; k < 9; k++)
					{
						if (k % 2 == 0) l = r;
						else { l = R; }
						points[k] = Drawing::Point(x + cX-touchPointX + l * cos(a), y + cY-touchPointY + l * sin(a));
						double x1_new = ((points[k].X - cX - x) * cos(angle*Convert::ToInt32(textBox5->Text)) - (points[k].Y - cY - y) * sin(angle* Convert::ToInt32(textBox5->Text)))+ cX + x;
						double y1_new = ((points[k].X - cX - x) * sin(angle* Convert::ToInt32(textBox5->Text)) + (points[k].Y - cY - y) * cos(angle* Convert::ToInt32(textBox5->Text)))+ cY + y;
						points[k].X= x1_new;
						points[k].Y = y1_new;
						predX = cX;
						predY = cY;

						a += da;
					}
					Graphics^ Zv = pictureBox1->CreateGraphics();
					Paint_Zvezda(points, Zv);
					if (rise)
						curent_p--;
					else
						curent_p++;
					angle += Step;
					::Sleep(Convert::ToInt32(textBox3->Text));
					i++;
				}
			}
			if (left->Checked) {
				while (angle >= LastT)
				{
					x = R1 * (k - 1) * (cos(angle) + cos((k - 1) * angle) / (k - 1));
					y = R1 * (k - 1) * (sin(angle) - sin((k - 1) * angle) / (k - 1));
					p[i] = Drawing::Point(cX + x, cY + y);
					Paint_Graphic(cX, cY, R2, x, y, p);

					double alpha = 0;
					array<Point>^ points;
					points = gcnew array<Point>(9);
					double a = alpha, da = 3.14 / 4, l;
					double R = 10, r = 40;
					if (checkBox1->Checked) {
						if (curent_p == 11) {
							curent_p--;
							rise = true;
						}
						if (curent_p == 0) {
							rise = false;
						}
						R = R / curent_p; r = r / curent_p;
					}
					for (int k = 0; k < 9; k++)
					{
						if (k % 2 == 0) l = r;
						else { l = R; }
						points[k] = Drawing::Point(x + cX - touchPointX + l * cos(a), y + cY - touchPointY + l * sin(a));
						double x1_new = ((points[k].X - cX - x) * cos(angle * Convert::ToInt32(textBox5->Text)) - (points[k].Y - cY - y) * sin(angle * Convert::ToInt32(textBox5->Text))) + cX + x;
						double y1_new = ((points[k].X - cX - x) * sin(angle * Convert::ToInt32(textBox5->Text)) + (points[k].Y - cY - y) * cos(angle * Convert::ToInt32(textBox5->Text))) + cY + y;
						points[k].X = x1_new;
						points[k].Y = y1_new;
						predX = cX;
						predY = cY;

						a += da;
					}
					Graphics^ Zv = pictureBox1->CreateGraphics();
					Paint_Zvezda(points, Zv);
					if (rise)
						curent_p--;
					else
						curent_p++;
					angle -= Step;
					::Sleep(Convert::ToInt32(textBox3->Text));
					i++;
				}
			}
		}
	}

	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
		this->colorDialog1->ShowDialog();
	}
	private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
		this->colorDialog2->ShowDialog();
	}
	private: System::Void button4_Click(System::Object^ sender, System::EventArgs^ e) {
		this->colorDialog3->ShowDialog();
	}
	private: System::Void groupBox2_Enter(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void radioButton1_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void lineLine_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void dot_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label7_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void textBox3_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void right_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void left_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void upLeft_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void center_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void downRight_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void pictureBox2_Click(System::Object^ sender, System::EventArgs^ e) {
	}
};
}
