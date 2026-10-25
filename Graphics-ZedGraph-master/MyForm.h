#pragma once
#include <math.h>

namespace Graph {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Collections::Generic;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace ZedGraph;

	// ============================================================
	//   КЛАСС FormTask2 — отдельное окно с 3 графиками
	// ============================================================
	public ref class FormTask2 : public System::Windows::Forms::Form
	{
	public:
		FormTask2(array<double>^ xs, array<double>^ us, array<double>^ vs)
		{
			InitializeComponent();
			DrawGraphs(xs, us, vs);
		}

	private:
		ZedGraph::ZedGraphControl^ zg_u;
		ZedGraph::ZedGraphControl^ zg_v;
		ZedGraph::ZedGraphControl^ zg_phase;
		System::ComponentModel::IContainer^ components;

		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->zg_u = (gcnew ZedGraph::ZedGraphControl());
			this->zg_v = (gcnew ZedGraph::ZedGraphControl());
			this->zg_phase = (gcnew ZedGraph::ZedGraphControl());
			this->SuspendLayout();

			this->zg_u->Location = System::Drawing::Point(12, 12);
			this->zg_u->Size = System::Drawing::Size(760, 250);
			this->zg_u->TabIndex = 0;

			this->zg_v->Location = System::Drawing::Point(12, 270);
			this->zg_v->Size = System::Drawing::Size(760, 250);
			this->zg_v->TabIndex = 1;

			this->zg_phase->Location = System::Drawing::Point(12, 528);
			this->zg_phase->Size = System::Drawing::Size(760, 250);
			this->zg_phase->TabIndex = 2;

			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(790, 795);
			this->Controls->Add(this->zg_u);
			this->Controls->Add(this->zg_v);
			this->Controls->Add(this->zg_phase);
			this->Name = L"FormTask2";
			this->Text = L"Задача №2: u(x), u'(x), фазовый портрет";
			this->ResumeLayout(false);
		}

		void DrawGraphs(array<double>^ xs, array<double>^ us, array<double>^ vs)
		{
			// --- 1. u(x) ---
			GraphPane^ p1 = zg_u->GraphPane;
			p1->CurveList->Clear();
			PointPairList^ listU = gcnew PointPairList();
			for (int k = 0; k < xs->Length; k++)
				listU->Add(xs[k], us[k]);
			LineItem^ c1 = p1->AddCurve("u(x)", listU, Color::Blue, SymbolType::None);
			c1->Line->Width = 1.5f;
			p1->XAxis->Title->Text = "x";
			p1->YAxis->Title->Text = "u";
			p1->Title->Text = "Решение u(x)";
			zg_u->AxisChange();
			zg_u->Invalidate();

			// --- 2. u'(x) ---
			GraphPane^ p2 = zg_v->GraphPane;
			p2->CurveList->Clear();
			PointPairList^ listV = gcnew PointPairList();
			for (int k = 0; k < xs->Length; k++)
				listV->Add(xs[k], vs[k]);
			LineItem^ c2 = p2->AddCurve("u'(x)", listV, Color::Green, SymbolType::None);
			c2->Line->Width = 1.5f;
			p2->XAxis->Title->Text = "x";
			p2->YAxis->Title->Text = "u'";
			p2->Title->Text = "Производная u'(x)";
			zg_v->AxisChange();
			zg_v->Invalidate();

			// --- 3. Фазовый портрет ---
			GraphPane^ p3 = zg_phase->GraphPane;
			p3->CurveList->Clear();
			PointPairList^ listPhase = gcnew PointPairList();
			for (int k = 0; k < xs->Length; k++)
				listPhase->Add(us[k], vs[k]);
			LineItem^ c3 = p3->AddCurve("u'(u)", listPhase, Color::Red, SymbolType::None);
			c3->Line->Width = 1.5f;
			p3->XAxis->Title->Text = "u";
			p3->YAxis->Title->Text = "u'";
			p3->Title->Text = "Фазовый портрет";
			zg_phase->AxisChange();
			zg_phase->Invalidate();
		}
	};

	// ============================================================
	//   КЛАСС MyForm — основное окно
	// ============================================================
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
		}

	protected:
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private: ZedGraph::ZedGraphControl^ zedGraphControl1;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::DataGridView^ dataGridView1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ col_i;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ col_xi;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ col_vi;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ col_v2i;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ col_diff;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ col_olp;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ col_hi;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ col_C1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ col_C2;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ col_ui;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ col_err;

	private: System::Windows::Forms::Label^ lbl_X0;
	private: System::Windows::Forms::TextBox^ tb_X0;
	private: System::Windows::Forms::Label^ lbl_Xend;
	private: System::Windows::Forms::TextBox^ tb_Xend;
	private: System::Windows::Forms::Label^ lbl_U0;
	private: System::Windows::Forms::TextBox^ tb_U0;
	private: System::Windows::Forms::Label^ lbl_H0;
	private: System::Windows::Forms::TextBox^ tb_H0;
	private: System::Windows::Forms::Label^ lbl_Eps;
	private: System::Windows::Forms::TextBox^ tb_Eps;
	private: System::Windows::Forms::Label^ lbl_Nmax;
	private: System::Windows::Forms::TextBox^ tb_Nmax;

	private: System::Windows::Forms::RadioButton^ rb_Fixed;
	private: System::Windows::Forms::RadioButton^ rb_Adaptive;

	private: System::Windows::Forms::TextBox^ tb_Stats;
	private: System::Windows::Forms::Label^ lbl_Stats;

	private: System::Windows::Forms::ComboBox^ cb_Task;
	private: int currentTask;

	private: System::Windows::Forms::Label^ lbl_V0;
	private: System::Windows::Forms::TextBox^ tb_V0;
	private: System::Windows::Forms::Label^ lbl_A;
	private: System::Windows::Forms::TextBox^ tb_A;
	private: System::Windows::Forms::Label^ lbl_B;
	private: System::Windows::Forms::TextBox^ tb_B;
	private: System::Windows::Forms::Label^ lbl_C;
	private: System::Windows::Forms::TextBox^ tb_C;

	protected:
	private: System::ComponentModel::IContainer^ components;

#pragma region Windows Form Designer generated code
		   void InitializeComponent(void)
		   {
			   this->components = (gcnew System::ComponentModel::Container());
			   this->zedGraphControl1 = (gcnew ZedGraph::ZedGraphControl());
			   this->button1 = (gcnew System::Windows::Forms::Button());
			   this->button2 = (gcnew System::Windows::Forms::Button());
			   this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			   this->col_i = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			   this->col_xi = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			   this->col_vi = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			   this->col_v2i = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			   this->col_diff = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			   this->col_olp = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			   this->col_hi = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			   this->col_C1 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			   this->col_C2 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			   this->col_ui = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			   this->col_err = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			   this->lbl_X0 = (gcnew System::Windows::Forms::Label());
			   this->tb_X0 = (gcnew System::Windows::Forms::TextBox());
			   this->lbl_Xend = (gcnew System::Windows::Forms::Label());
			   this->tb_Xend = (gcnew System::Windows::Forms::TextBox());
			   this->lbl_U0 = (gcnew System::Windows::Forms::Label());
			   this->tb_U0 = (gcnew System::Windows::Forms::TextBox());
			   this->lbl_H0 = (gcnew System::Windows::Forms::Label());
			   this->tb_H0 = (gcnew System::Windows::Forms::TextBox());
			   this->lbl_Eps = (gcnew System::Windows::Forms::Label());
			   this->tb_Eps = (gcnew System::Windows::Forms::TextBox());
			   this->lbl_Nmax = (gcnew System::Windows::Forms::Label());
			   this->tb_Nmax = (gcnew System::Windows::Forms::TextBox());
			   this->lbl_V0 = (gcnew System::Windows::Forms::Label());
			   this->tb_V0 = (gcnew System::Windows::Forms::TextBox());
			   this->lbl_A = (gcnew System::Windows::Forms::Label());
			   this->tb_A = (gcnew System::Windows::Forms::TextBox());
			   this->lbl_B = (gcnew System::Windows::Forms::Label());
			   this->tb_B = (gcnew System::Windows::Forms::TextBox());
			   this->lbl_C = (gcnew System::Windows::Forms::Label());
			   this->tb_C = (gcnew System::Windows::Forms::TextBox());
			   this->cb_Task = (gcnew System::Windows::Forms::ComboBox());
			   this->rb_Fixed = (gcnew System::Windows::Forms::RadioButton());
			   this->rb_Adaptive = (gcnew System::Windows::Forms::RadioButton());
			   this->tb_Stats = (gcnew System::Windows::Forms::TextBox());
			   this->lbl_Stats = (gcnew System::Windows::Forms::Label());
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
			   this->SuspendLayout();

			   // zedGraphControl1
			   this->zedGraphControl1->Location = System::Drawing::Point(12, 12);
			   this->zedGraphControl1->Name = L"zedGraphControl1";
			   this->zedGraphControl1->Size = System::Drawing::Size(560, 400);
			   this->zedGraphControl1->TabIndex = 0;

			   // button1
			   this->button1->Location = System::Drawing::Point(881, 454);
			   this->button1->Size = System::Drawing::Size(120, 30);
			   this->button1->TabIndex = 16;
			   this->button1->Text = L"Решить";
			   this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);

			   // button2
			   this->button2->Location = System::Drawing::Point(1038, 454);
			   this->button2->Size = System::Drawing::Size(120, 30);
			   this->button2->TabIndex = 17;
			   this->button2->Text = L"Очистить";
			   this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);

			   // dataGridView1
			   this->dataGridView1->AllowUserToAddRows = false;
			   this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			   this->dataGridView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(11) {
				   this->col_i, this->col_xi, this->col_vi, this->col_v2i,
					   this->col_diff, this->col_olp, this->col_hi,
					   this->col_C1, this->col_C2, this->col_ui, this->col_err
			   });
			   this->dataGridView1->Location = System::Drawing::Point(585, 12);
			   this->dataGridView1->ReadOnly = true;
			   this->dataGridView1->RowHeadersVisible = false;
			   this->dataGridView1->Size = System::Drawing::Size(600, 400);
			   this->dataGridView1->TabIndex = 1;

			   this->col_i->HeaderText = L"i";           this->col_i->Width = 40;
			   this->col_xi->HeaderText = L"xi";         this->col_xi->Width = 70;
			   this->col_vi->HeaderText = L"vi";         this->col_vi->Width = 80;
			   this->col_v2i->HeaderText = L"v2i";       this->col_v2i->Width = 80;
			   this->col_diff->HeaderText = L"vi-v2i";   this->col_diff->Width = 80;
			   this->col_olp->HeaderText = L"ОЛП";       this->col_olp->Width = 80;
			   this->col_hi->HeaderText = L"hi";         this->col_hi->Width = 60;
			   this->col_C1->HeaderText = L"C1";         this->col_C1->Width = 50;
			   this->col_C2->HeaderText = L"C2";         this->col_C2->Width = 50;
			   this->col_ui->HeaderText = L"ui";         this->col_ui->Width = 80;
			   this->col_err->HeaderText = L"|ui-vi|";   this->col_err->Width = 80;

			   // lbl_X0
			   this->lbl_X0->Location = System::Drawing::Point(12, 454);
			   this->lbl_X0->Size = System::Drawing::Size(100, 23);
			   this->lbl_X0->Text = L"X0";
			   // tb_X0
			   this->tb_X0->Location = System::Drawing::Point(118, 454);
			   this->tb_X0->Size = System::Drawing::Size(60, 20);
			   this->tb_X0->Text = L"0";
			   // lbl_Xend
			   this->lbl_Xend->Location = System::Drawing::Point(204, 451);
			   this->lbl_Xend->Size = System::Drawing::Size(100, 23);
			   this->lbl_Xend->Text = L"X_end";
			   // tb_Xend
			   this->tb_Xend->Location = System::Drawing::Point(310, 451);
			   this->tb_Xend->Size = System::Drawing::Size(60, 20);
			   this->tb_Xend->Text = L"1";
			   // lbl_U0
			   this->lbl_U0->Location = System::Drawing::Point(401, 448);
			   this->lbl_U0->Size = System::Drawing::Size(100, 23);
			   this->lbl_U0->Text = L"U0";
			   // tb_U0
			   this->tb_U0->Location = System::Drawing::Point(520, 454);
			   this->tb_U0->Size = System::Drawing::Size(60, 20);
			   this->tb_U0->Text = L"0";
			   // lbl_H0
			   this->lbl_H0->Location = System::Drawing::Point(12, 491);
			   this->lbl_H0->Size = System::Drawing::Size(100, 23);
			   this->lbl_H0->Text = L"H0";
			   // tb_H0
			   this->tb_H0->Location = System::Drawing::Point(118, 488);
			   this->tb_H0->Size = System::Drawing::Size(60, 20);
			   this->tb_H0->Text = L"0,1";
			   // lbl_Eps
			   this->lbl_Eps->Location = System::Drawing::Point(204, 488);
			   this->lbl_Eps->Size = System::Drawing::Size(100, 23);
			   this->lbl_Eps->Text = L"Eps";
			   // tb_Eps
			   this->tb_Eps->Location = System::Drawing::Point(310, 482);
			   this->tb_Eps->Size = System::Drawing::Size(70, 20);
			   this->tb_Eps->Text = L"0,0001";
			   // lbl_Nmax
			   this->lbl_Nmax->Location = System::Drawing::Point(401, 485);
			   this->lbl_Nmax->Size = System::Drawing::Size(100, 23);
			   this->lbl_Nmax->Text = L"Nmax";
			   // tb_Nmax
			   this->tb_Nmax->Location = System::Drawing::Point(520, 485);
			   this->tb_Nmax->Size = System::Drawing::Size(70, 20);
			   this->tb_Nmax->Text = L"100000";

			   // lbl_V0
			   this->lbl_V0->Location = System::Drawing::Point(600, 454);
			   this->lbl_V0->Size = System::Drawing::Size(30, 23);
			   this->lbl_V0->Text = L"V0";
			   // tb_V0
			   this->tb_V0->Location = System::Drawing::Point(635, 454);
			   this->tb_V0->Size = System::Drawing::Size(45, 20);
			   this->tb_V0->Text = L"1";

			   // lbl_A
			   this->lbl_A->Location = System::Drawing::Point(12, 520);
			   this->lbl_A->Size = System::Drawing::Size(30, 23);
			   this->lbl_A->Text = L"A";
			   // tb_A
			   this->tb_A->Location = System::Drawing::Point(45, 520);
			   this->tb_A->Size = System::Drawing::Size(60, 20);
			   this->tb_A->Text = L"0,1";
			   // lbl_B
			   this->lbl_B->Location = System::Drawing::Point(130, 520);
			   this->lbl_B->Size = System::Drawing::Size(30, 23);
			   this->lbl_B->Text = L"B";
			   // tb_B
			   this->tb_B->Location = System::Drawing::Point(165, 520);
			   this->tb_B->Size = System::Drawing::Size(60, 20);
			   this->tb_B->Text = L"0,5";
			   // lbl_C
			   this->lbl_C->Location = System::Drawing::Point(250, 520);
			   this->lbl_C->Size = System::Drawing::Size(30, 23);
			   this->lbl_C->Text = L"C";
			   // tb_C
			   this->tb_C->Location = System::Drawing::Point(285, 520);
			   this->tb_C->Size = System::Drawing::Size(60, 20);
			   this->tb_C->Text = L"1,0";

			   // cb_Task
			   this->cb_Task->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			   this->cb_Task->Items->AddRange(gcnew cli::array< System::Object^  >(3) {
				   L"Тестовая задача", L"Задача №1", L"Задача №2"
			   });
			   this->cb_Task->Location = System::Drawing::Point(700, 460);
			   this->cb_Task->Size = System::Drawing::Size(160, 21);
			   this->cb_Task->TabIndex = 20;
			   this->cb_Task->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::cb_Task_SelectedIndexChanged);

			   // rb_Fixed
			   this->rb_Fixed->Checked = true;
			   this->rb_Fixed->Location = System::Drawing::Point(12, 430);
			   this->rb_Fixed->Size = System::Drawing::Size(150, 24);
			   this->rb_Fixed->TabIndex = 14;
			   this->rb_Fixed->Text = L"Постоянный шаг";
			   // rb_Adaptive
			   this->rb_Adaptive->Location = System::Drawing::Point(170, 430);
			   this->rb_Adaptive->Size = System::Drawing::Size(150, 24);
			   this->rb_Adaptive->TabIndex = 15;
			   this->rb_Adaptive->Text = L"Адаптивный шаг";

			   // tb_Stats
			   this->tb_Stats->Font = (gcnew System::Drawing::Font(L"Consolas", 9));
			   this->tb_Stats->Location = System::Drawing::Point(12, 558);
			   this->tb_Stats->Multiline = true;
			   this->tb_Stats->ReadOnly = true;
			   this->tb_Stats->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			   this->tb_Stats->Size = System::Drawing::Size(1170, 150);
			   this->tb_Stats->TabIndex = 19;
			   // lbl_Stats
			   this->lbl_Stats->Location = System::Drawing::Point(12, 430);
			   this->lbl_Stats->Size = System::Drawing::Size(100, 23);
			   this->lbl_Stats->TabIndex = 18;
			   this->lbl_Stats->Text = L"Статистика:";

			   // MyForm
			   this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			   this->ClientSize = System::Drawing::Size(1200, 720);
			   this->Controls->Add(this->zedGraphControl1);
			   this->Controls->Add(this->dataGridView1);
			   this->Controls->Add(this->lbl_X0);
			   this->Controls->Add(this->tb_X0);
			   this->Controls->Add(this->lbl_Xend);
			   this->Controls->Add(this->tb_Xend);
			   this->Controls->Add(this->lbl_U0);
			   this->Controls->Add(this->tb_U0);
			   this->Controls->Add(this->lbl_H0);
			   this->Controls->Add(this->tb_H0);
			   this->Controls->Add(this->lbl_Eps);
			   this->Controls->Add(this->tb_Eps);
			   this->Controls->Add(this->lbl_Nmax);
			   this->Controls->Add(this->tb_Nmax);
			   this->Controls->Add(this->lbl_V0);
			   this->Controls->Add(this->tb_V0);
			   this->Controls->Add(this->lbl_A);
			   this->Controls->Add(this->tb_A);
			   this->Controls->Add(this->lbl_B);
			   this->Controls->Add(this->tb_B);
			   this->Controls->Add(this->lbl_C);
			   this->Controls->Add(this->tb_C);
			   this->Controls->Add(this->rb_Fixed);
			   this->Controls->Add(this->rb_Adaptive);
			   this->Controls->Add(this->cb_Task);
			   this->Controls->Add(this->button1);
			   this->Controls->Add(this->button2);
			   this->Controls->Add(this->lbl_Stats);
			   this->Controls->Add(this->tb_Stats);
			   this->Name = L"MyForm";
			   this->Text = L"Лабораторная: РК4";
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
			   this->ResumeLayout(false);
			   this->PerformLayout();
		   }
#pragma endregion

	private: System::Void cb_Task_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
		currentTask = cb_Task->SelectedIndex;
		bool isTest = (currentTask == 0);
		bool isTask2 = (currentTask == 2);

		dataGridView1->Columns[9]->Visible = isTest;
		dataGridView1->Columns[10]->Visible = isTest;

		lbl_V0->Visible = isTask2;   tb_V0->Visible = isTask2;
		lbl_A->Visible = isTask2;    tb_A->Visible = isTask2;
		lbl_B->Visible = isTask2;    tb_B->Visible = isTask2;
		lbl_C->Visible = isTask2;    tb_C->Visible = isTask2;

		dataGridView1->Rows->Clear();
		tb_Stats->Clear();
		GraphPane^ panel = zedGraphControl1->GraphPane;
		panel->CurveList->Clear();
		zedGraphControl1->AxisChange();
		zedGraphControl1->Invalidate();
	}

		   // ================== ЧИСЛЕННЫЕ МЕТОДЫ ==================

	private:
		double RHS(double x, double u) {
			if (currentTask == 0) {
				return 2.0*u;
			}
			else {
				double x2 = x * x;
				double x3 = x2 * x;
				double x5 = x3 * x2;
				double fx = (x3 + 1.0) / (x5 + 1.0);
				return fx * u * u + u - u * u * u * Math::Sin(10.0 * x);
			}
		}

		double Exact_Test(double x, double U0, double X0) {
			return U0 *Math::Exp(2.0*(x-X0));
		}

		// ---- РК4 по методичке ----
		
		double RK4_Step(double x, double u, double h) {
			double k1 = RHS(x, u);
			double k2 = RHS(x + h / 2.0, u + h / 2.0 * k1);
			double k3 = RHS(x + h / 2.0, u + h / 2.0 * k2);
			double k4 = RHS(x + h, u + h * (k3));
			return u + h / 6.0 * (k1 + 2.0 * k2 + 2.0 * k3 + k4);
		}

		// ---- РК4 для системы (по той же схеме методички) ----
		void RK4_Step_System(double x, double u, double v, double h,
			double A, double B, double C,
			double% u_new, double% v_new)
		{
			// k1
			double k1u = v;
			double k1v = -(A * v * Math::Abs(v) + B * v + C * u);

			// k2: x+h/2, u+h/2*k1u, v+h/2*k1v
			double u2 = u + h / 2.0 * k1u;
			double v2 = v + h / 2.0 * k1v;
			double k2u = v2;
			double k2v = -(A * v2 * Math::Abs(v2) + B * v2 + C * u2);

			// k3: x+h/2, u+h/2*k2u, v+h/2*k2v
			double u3 = u + h / 2.0 * k2u;
			double v3 = v + h / 2.0 * k2v;
			double k3u = v3;
			double k3v = -(A * v3 * Math::Abs(v3) + B * v3 + C * u3);

			// k4: x+h, u+h*k3u, v+h*k3v
			double u4 = u + h * k3u;
			double v4 = v + h * k3v;
			double k4u = v4;
			double k4v = -(A * v4 * Math::Abs(v4) + B * v4 + C * u4);

			u_new = u + h / 6.0 * (k1u + 2.0*k2u + 2.0 * k3u + k4u);
			v_new = v + h / 6.0 * (k1v + 2.0*k2v + 2.0 * k3v + k4v);
		}

		double ParseDouble(String^ s) {
			s = s->Trim()->Replace(',', '.');
			return Convert::ToDouble(s, System::Globalization::CultureInfo::InvariantCulture);
		}

		// ================== РЕШЕНИЕ ЗАДАЧИ №2 ==================

	private: void SolveTask2(double X0, double Xend, double U0, double V0,
		double A, double B, double C,
		double H0, double Eps, int Nmax, bool isFixed)
	{
		List<double>^ xs = gcnew List<double>();
		List<double>^ us = gcnew List<double>();
		List<double>^ vs = gcnew List<double>();

		double x = X0, u = U0, v = V0;
		int i = 0;
		int C1 = 0, C2 = 0;

		xs->Add(x); us->Add(u); vs->Add(v);

		if (isFixed) {
			while (x < Xend - 1e-12) {
				if (i >= Nmax) { MessageBox::Show("Достигнут Nmax."); break; }
				double h = H0;
				if (x + h > Xend) h = Xend - x;

				double u1, v1, u2, v2, u2b, v2b;
				RK4_Step_System(x, u, v, h, A, B, C, u1, v1);
				RK4_Step_System(x, u, v, h / 2.0, A, B, C, u2, v2);
				RK4_Step_System(x + h / 2.0, u2, v2, h / 2.0, A, B, C, u2b, v2b);

				double diffU = u1 - u2b;
				double diffV = v1 - v2b;
				// ОЛП = S * 2^p = (|diff| / (2^p - 1)) * 2^p = |diff| / 15
				double olp = Math::Sqrt(diffU * diffU + diffV * diffV) / 15.0;

				double x_new = x + h;

				dataGridView1->Rows->Add();
				int r = dataGridView1->Rows->Count - 1;
				dataGridView1->Rows[r]->Cells[0]->Value = i + 1;
				dataGridView1->Rows[r]->Cells[1]->Value = Math::Round(x_new, 6);
				dataGridView1->Rows[r]->Cells[2]->Value = Math::Round(u1, 8);
				dataGridView1->Rows[r]->Cells[3]->Value = Math::Round(u2b, 8);
				dataGridView1->Rows[r]->Cells[4]->Value = Math::Round(diffU, 10);
				dataGridView1->Rows[r]->Cells[5]->Value = Math::Round(olp, 10);
				dataGridView1->Rows[r]->Cells[6]->Value = Math::Round(h, 6);
				dataGridView1->Rows[r]->Cells[7]->Value = 0;
				dataGridView1->Rows[r]->Cells[8]->Value = 0;

				u = u1; v = v1; x = x_new;
				xs->Add(x); us->Add(u); vs->Add(v);
				i++;
			}
		}
		else {
			double h = H0;
			while (x < Xend - 1e-12) {
				if (i >= Nmax) { MessageBox::Show("Достигнут Nmax."); break; }
				if (h < 1e-12) { MessageBox::Show("Шаг стал слишком мал."); break; }
				if (x + h > Xend) h = Xend - x;

				double u1, v1, u2, v2, u2b, v2b;
				RK4_Step_System(x, u, v, h, A, B, C, u1, v1);
				RK4_Step_System(x, u, v, h / 2.0, A, B, C, u2, v2);
				RK4_Step_System(x + h / 2.0, u2, v2, h / 2.0, A, B, C, u2b, v2b);

				double diffU = u1 - u2b;
				double diffV = v1 - v2b;
				double olp = Math::Sqrt(diffU * diffU + diffV * diffV) / 15.0;

				if (Math::Abs(u1) > 1e15 || Math::Abs(v1) > 1e15) {
					MessageBox::Show("Решение уходит в бесконечность.");
					break;
				}

				int c1_step = 0, c2_step = 0;
				if (olp > Eps) { h = h / 2.0; C1++; c1_step = 1; continue; }

				double x_new = x + h;
				if (x_new <= x) { MessageBox::Show("Шаг слишком мал."); break; }

				if (olp < Eps / 32.0 && (x_new + 2.0 * h) <= Xend + 1e-12) {
					h = h * 2.0; C2++; c2_step = 1;
				}

				dataGridView1->Rows->Add();
				int r = dataGridView1->Rows->Count - 1;
				dataGridView1->Rows[r]->Cells[0]->Value = i + 1;
				dataGridView1->Rows[r]->Cells[1]->Value = Math::Round(x_new, 6);
				dataGridView1->Rows[r]->Cells[2]->Value = Math::Round(u1, 8);
				dataGridView1->Rows[r]->Cells[3]->Value = Math::Round(u2b, 8);
				dataGridView1->Rows[r]->Cells[4]->Value = Math::Round(diffU, 10);
				dataGridView1->Rows[r]->Cells[5]->Value = Math::Round(olp, 10);
				dataGridView1->Rows[r]->Cells[6]->Value = Math::Round(x_new - x, 6);
				dataGridView1->Rows[r]->Cells[7]->Value = c1_step;
				dataGridView1->Rows[r]->Cells[8]->Value = c2_step;

				u = u1; v = v1; x = x_new;
				xs->Add(x); us->Add(u); vs->Add(v);
				i++;
			}
		}

		System::Text::StringBuilder^ sb = gcnew System::Text::StringBuilder();
		sb->AppendLine(String::Format("n = {0}", i));
		sb->AppendLine(String::Format("X_end - x_n = {0:E4}", Xend - x));
		sb->AppendLine(String::Format("Общее число удвоений шага: {0}", C2));
		sb->AppendLine(String::Format("Общее число делений шага:   {0}", C1));
		tb_Stats->Text = sb->ToString();

		FormTask2^ w = gcnew FormTask2(xs->ToArray(), us->ToArray(), vs->ToArray());
		w->Show();
	}

		   // ================== РЕШЕНИЕ (тест + задача 1) ==================

	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		try {
			double X0 = ParseDouble(tb_X0->Text);
			double Xend = ParseDouble(tb_Xend->Text);
			double U0 = ParseDouble(tb_U0->Text);
			double H0 = ParseDouble(tb_H0->Text);
			double Eps = ParseDouble(tb_Eps->Text);
			int Nmax = Convert::ToInt32(tb_Nmax->Text);

			// ---- Проверки входных данных ----
			if (Xend <= X0) {
				MessageBox::Show("Ошибка: X_end должен быть больше X0.");
				return;
			}
			if (H0 <= 0) {
				MessageBox::Show("Ошибка: H0 должен быть > 0.");
				return;
			}
			if (Eps <= 0) {
				MessageBox::Show("Ошибка: Eps должен быть > 0.");
				return;
			}

			currentTask = cb_Task->SelectedIndex;
			bool isTest = (currentTask == 0);

			// ---- Задача №2 — отдельная ветка ----
			if (currentTask == 2) {
				double V0 = ParseDouble(tb_V0->Text);
				double A = ParseDouble(tb_A->Text);
				double B = ParseDouble(tb_B->Text);
				double C = ParseDouble(tb_C->Text);
				dataGridView1->Rows->Clear();
				SolveTask2(X0, Xend, U0, V0, A, B, C, H0, Eps, Nmax, rb_Fixed->Checked);
				return;
			}

			dataGridView1->Rows->Clear();
			GraphPane^ panel = zedGraphControl1->GraphPane;
			panel->CurveList->Clear();

			PointPairList^ exactList = gcnew PointPairList();
			PointPairList^ approxList = gcnew PointPairList();

			int n = 0;
			double x_last = X0;
			double maxOLP = 0.0, maxOLP_x = X0;
			int totalDiv = 0, totalDouble = 0;
			double maxH = 0.0, maxH_x = X0;
			double minH = 1e300, minH_x = X0;
			double maxErr = 0.0, maxErr_x = X0;

			// ---- Постоянный шаг ----
			if (rb_Fixed->Checked) {
				double h = H0;
				double x = X0, u = U0;
				int i = 0;

				exactList->Add(x, Exact_Test(x, U0, X0));
				approxList->Add(x, u);

				while (x < Xend - 1e-12) {
					if (i >= Nmax) { MessageBox::Show("Достигнут Nmax (постоянный шаг)."); break; }
					double h_cur = h;
					if (x + h_cur > Xend) h_cur = Xend - x;

					double v = RK4_Step(x, u, h_cur);
					double v_half = RK4_Step(x, u, h_cur / 2.0);
					double v2 = RK4_Step(x + h_cur / 2.0, v_half, h_cur / 2.0);
					double diff = v - v2;
					double olp = Math::Abs(diff) / 15.0;

					double h_next = x + h_cur;

					dataGridView1->Rows->Add();
					int r = dataGridView1->Rows->Count - 1;
					dataGridView1->Rows[r]->Cells[0]->Value = i + 1;
					dataGridView1->Rows[r]->Cells[1]->Value = Math::Round(h_next, 6);
					dataGridView1->Rows[r]->Cells[2]->Value = Math::Round(v, 8);
					dataGridView1->Rows[r]->Cells[3]->Value = Math::Round(v2, 8);
					dataGridView1->Rows[r]->Cells[4]->Value = Math::Round(diff, 10);
					dataGridView1->Rows[r]->Cells[5]->Value = Math::Round(olp, 10);
					dataGridView1->Rows[r]->Cells[6]->Value = Math::Round(h_cur, 6);
					dataGridView1->Rows[r]->Cells[7]->Value = 0;
					dataGridView1->Rows[r]->Cells[8]->Value = 0;

					if (olp > maxOLP) { maxOLP = olp; maxOLP_x = h_next; }
					if (h_cur > maxH) { maxH = h_cur; maxH_x = x; }
					if (h_cur < minH) { minH = h_cur; minH_x = x; }

					if (isTest) {
						double ue = Exact_Test(h_next, U0, X0);
						double err = Math::Abs(ue - v);
						dataGridView1->Rows[r]->Cells[9]->Value = Math::Round(ue, 8);
						dataGridView1->Rows[r]->Cells[10]->Value = Math::Round(err, 10);
						if (err > maxErr) { maxErr = err; maxErr_x = h_next; }
						approxList->Add(h_next, v);
						exactList->Add(h_next, ue);
					}
					else {
						dataGridView1->Rows[r]->Cells[9]->Value = nullptr;
						dataGridView1->Rows[r]->Cells[10]->Value = nullptr;
						approxList->Add(h_next, v);
					}

					u = v;
					x = h_next;
					x_last = x;
					n = i + 1;
					i++;
				}
			}
			// ---- Адаптивный шаг ----
			else {
				double h = H0;
				double x = X0, u = U0;
				int i = 0;

				// Локальные счетчики для ТЕКУЩЕЙ точки (живут, пока точка не принята)
				int c1_step = 0;
				int c2_step = 0;

				exactList->Add(x, Exact_Test(x, U0, X0));
				approxList->Add(x, u);

				while (x < Xend - 1e-12) {
					if (i >= Nmax) { MessageBox::Show("Достигнут Nmax (адаптивный шаг)."); break; }
					if (h < 1e-12) { MessageBox::Show("Шаг стал слишком мал."); break; }
					if (x + h > Xend) h = Xend - x;

					double v = RK4_Step(x, u, h);
					double v_half = RK4_Step(x, u, h / 2.0);
					double v2 = RK4_Step(x + h / 2.0, v_half, h / 2.0);
					double diff = v - v2;
					double olp = Math::Abs(diff) / 15.0;

					if (Math::Abs(v) > 1e15) { MessageBox::Show("Решение уходит в бесконечность."); break; }

					// Если ОЛП > Eps, ДРОБИМ шаг и пересчитываем точку
					if (olp > Eps) {
						h = h / 2.0;
						totalDiv++;
						c1_step++;   // Накапливаем деления для текущей точки
						continue;    // ВАЖНО: возвращаемся в начало цикла
					}

					// Точка принята. Считаем новый x
					double x_new = x + h;
					if (x_new <= x) { MessageBox::Show("Шаг слишком мал для double."); break; }

					// Если ОЛП < Eps/32, УДВАИВАЕМ шаг для следующей итерации
					if (olp < Eps / 32.0 && (x_new + 2.0 * h) <= Xend + 1e-12) {
						h = h * 2.0;
						totalDouble++;
						c2_step++;   // Фиксируем удвоение
					}

					// Запись в таблицу принятой точки
					dataGridView1->Rows->Add();
					int r = dataGridView1->Rows->Count - 1;
					dataGridView1->Rows[r]->Cells[0]->Value = i + 1;
					dataGridView1->Rows[r]->Cells[1]->Value = Math::Round(x_new, 6);
					dataGridView1->Rows[r]->Cells[2]->Value = Math::Round(v, 8);
					dataGridView1->Rows[r]->Cells[3]->Value = Math::Round(v2, 8);
					dataGridView1->Rows[r]->Cells[4]->Value = Math::Round(diff, 10);
					dataGridView1->Rows[r]->Cells[5]->Value = Math::Round(olp, 10);
					dataGridView1->Rows[r]->Cells[6]->Value = Math::Round(x_new - x, 6);

					// Выводим накопленные счётчики
					dataGridView1->Rows[r]->Cells[7]->Value = c1_step;
					dataGridView1->Rows[r]->Cells[8]->Value = c2_step;

					if (olp > maxOLP) { maxOLP = olp; maxOLP_x = x_new; }
					double h_used = x_new - x;
					if (h_used > maxH) { maxH = h_used; maxH_x = x; }
					if (h_used < minH) { minH = h_used; minH_x = x; }

					if (isTest) {
						double ue = Exact_Test(x_new, U0, X0);
						double err = Math::Abs(ue - v);
						dataGridView1->Rows[r]->Cells[9]->Value = Math::Round(ue, 8);
						dataGridView1->Rows[r]->Cells[10]->Value = Math::Round(err, 10);
						if (err > maxErr) { maxErr = err; maxErr_x = x_new; }
						approxList->Add(x_new, v);
						exactList->Add(x_new, ue);
					}
					else {
						dataGridView1->Rows[r]->Cells[9]->Value = nullptr;
						dataGridView1->Rows[r]->Cells[10]->Value = nullptr;
						approxList->Add(x_new, v);
					}

					u = v;
					x = x_new;
					x_last = x;
					n = i + 1;
					i++;

					// СБРАСЫВАЕМ счётчики для СЛЕДУЮЩЕЙ точки
					c1_step = 0;
					c2_step = 0;
				}

			}

			// ---- Графики ----
			if (isTest) {
				LineItem^ curveExact = panel->AddCurve("Точное u(x)", exactList, Color::Red, SymbolType::None);
				curveExact->Line->Width = 2.0f;
			}
			LineItem^ curveApprox = panel->AddCurve("Приближённое v(x)", approxList, Color::Blue, SymbolType::Circle);
			curveApprox->Symbol->Size = 4.0f;
			curveApprox->Line->Width = 1.5f;

			panel->XAxis->Title->Text = "x";
			panel->YAxis->Title->Text = "u";
			String^ taskName = isTest ? "Тест" : "Задача 1";
			String^ stepName = (rb_Fixed->Checked) ? "постоянный шаг" : "адаптивный шаг";
			panel->Title->Text = taskName + ": " + stepName;
			zedGraphControl1->AxisChange();
			zedGraphControl1->Invalidate();

			// ---- Статистика ----
			System::Text::StringBuilder^ sb = gcnew System::Text::StringBuilder();
			sb->AppendLine(String::Format("n = {0}", n));
			sb->AppendLine(String::Format("X_end - x_n = {0:E4}", Xend - x_last));
			sb->AppendLine(String::Format("max |ОЛП| = {0:E6}  при x = {1:F6}", maxOLP, maxOLP_x));
			sb->AppendLine(String::Format("Общее число удвоений шага: {0}", totalDouble));
			sb->AppendLine(String::Format("Общее число делений шага:   {0}", totalDiv));

			if (n > 0) {
				sb->AppendLine(String::Format("max h_i = {0:F6}  при x = {1:F6}", maxH, maxH_x));
				sb->AppendLine(String::Format("min h_i = {0:F6}  при x = {1:F6}", minH, minH_x));
			}
			else {
				sb->AppendLine("Шаги не выполнялись (n = 0).");
			}

			if (isTest) {
				sb->AppendLine(String::Format("max |u_i - v_i| = {0:E6}  при x = {1:F6}", maxErr, maxErr_x));
			}

			tb_Stats->Text = sb->ToString();
		}
		catch (Exception^ ex) {
			MessageBox::Show("Ошибка: " + ex->Message);
		}
	}

	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
		dataGridView1->Rows->Clear();
		tb_Stats->Clear();
		GraphPane^ panel = zedGraphControl1->GraphPane;
		panel->CurveList->Clear();
		zedGraphControl1->AxisChange();
		zedGraphControl1->Invalidate();
	}
	};
}
