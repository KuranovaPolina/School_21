#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(add_digit()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(add_digit()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(add_digit()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(add_digit()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(add_digit()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(add_digit()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(add_digit()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(add_digit()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(add_digit()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(add_digit()));

  connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(add_math_opp()));
  connect(ui->pushButton_minus, SIGNAL(clicked()), this, SLOT(add_math_opp()));
  connect(ui->pushButton_mult, SIGNAL(clicked()), this, SLOT(add_math_opp()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(add_math_opp()));
  connect(ui->pushButton_pow, SIGNAL(clicked()), this, SLOT(add_math_opp()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(add_math_opp()));

  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(add_func()));
  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(add_func()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(add_func()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(add_func()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(add_func()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(add_func()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(add_func()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(add_func()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(add_func()));

  ui->widget->xAxis->setLabel("x");
  ui->widget->yAxis->setLabel("y");

  QDoubleValidator *validator = new QDoubleValidator(-1000000, 1000000, 7);
  QDoubleValidator *validator2 = new QDoubleValidator(0.0000001, 1000000, 7);
  QDoubleValidator *validator_credit_sum = new QDoubleValidator(0, INFINITY, 2);
  QDoubleValidator *validator_time = new QDoubleValidator(1, 50, 0);
  QDoubleValidator *validator_percent = new QDoubleValidator(0.01, 999, 7);
  QLocale locale(QLocale::English);
  validator->setLocale(locale);
  validator2->setLocale(locale);
  validator_credit_sum->setLocale(locale);
  validator_percent->setLocale(locale);

  ui->lineEdit_X->setValidator(validator);
  ui->lineEdit_Xmin->setValidator(validator);
  ui->lineEdit_Xmax->setValidator(validator);
  ui->lineEdit_Ymin->setValidator(validator);
  ui->lineEdit_Ymax->setValidator(validator);
  ui->lineEdit_h->setValidator(validator2);

  ui->lineEdit_credit_sum->setValidator(validator_credit_sum);
  ui->lineEdit_time->setValidator(validator_time);
  ui->lineEdit_percent->setValidator(validator_percent);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::add_digit() {
  QPushButton *button = (QPushButton *)sender();

  ui->res_label->setText(ui->res_label->text() + button->text());
}

void MainWindow::on_pushButton_AC_clicked() { ui->res_label->setText(""); }

void MainWindow::on_pushButton_dot_clicked() {
  ui->res_label->setText(ui->res_label->text() + ".");
}

void MainWindow::add_math_opp() {
  QPushButton *button = (QPushButton *)sender();

  if (button->text() == "x") {
    ui->res_label->setText(ui->res_label->text() + "*");
  } else {
    ui->res_label->setText(ui->res_label->text() + button->text());
  }
}

void MainWindow::on_pushButton_left_br_clicked() {
  ui->res_label->setText(ui->res_label->text() + "(");
}

void MainWindow::on_pushButton_right_br_clicked() {
  ui->res_label->setText(ui->res_label->text() + ")");
}

void MainWindow::add_func() {
  QPushButton *button = (QPushButton *)sender();

  ui->res_label->setText(ui->res_label->text() + button->text());
  on_pushButton_left_br_clicked();
}

void MainWindow::on_pushButton_x_clicked() {
  ui->res_label->setText(ui->res_label->text() + "X");
}

void MainWindow::on_pushButton_del_last_clicked() {
  QString str = ui->res_label->text();
  QString letters = "modsqrtlgnica";

  int len = str.length();

  if (len > 0 && letters.contains(str[len - 1])) {
    while (len > 0 && letters.contains(str[len - 1])) {
      str.chop(1);
      len--;
    }
  } else {
    str.chop(1);
    len--;
  }

  ui->res_label->setText(str);
  str.clear();
}

void MainWindow::on_pushButton_equal_clicked() {
  std::string str = ui->res_label->text().toStdString();
  const char *p = str.c_str();
  char result[256];

  double X = ui->lineEdit_X->text().toDouble();

  if (str.length() > 255) {
    ui->res_label->setText("EXPRESSION IS TOO LONG");
  } else {
    calculate(p, result, X);
    ui->res_label->setText(result);
  }
}

void MainWindow::on_pushButton_graph_clicked() {
  std::string str = ui->res_label->text().toStdString();
  const char *p = str.c_str();
  char result[256];

  x.clear();
  y.clear();
  ui->widget->clearGraphs();

  h = ui->lineEdit_h->text().toDouble();
  xBegin = ui->lineEdit_Xmin->text().toDouble();
  xEnd = ui->lineEdit_Xmax->text().toDouble();
  yBegin = ui->lineEdit_Ymin->text().toDouble();
  yEnd = ui->lineEdit_Ymax->text().toDouble();

  ui->widget->xAxis->setRange(xBegin, xEnd);
  ui->widget->yAxis->setRange(yBegin, yEnd);

  X = xBegin;
  N = (xEnd - xBegin) / 2;

  for (X = xBegin; X <= xEnd; X += h) {
    if (calculate(p, result, X) == 0) {
      x.push_back(X);
      double res = atof(result);
      y.push_back(res);
    }
  }

  ui->widget->addGraph();
  ui->widget->graph(0)->addData(x, y);
  ui->widget->replot();
}

void MainWindow::on_pushButton_calculate_credit_clicked() {
  double credit_sum = ui->lineEdit_credit_sum->text().toDouble();
  int month = ui->lineEdit_time->text().toInt();
  double percent = ui->lineEdit_percent->text().toDouble();
  int type = -1;
  char month_pay[256], overpayment[256], full_payment[256];

  if (ui->radioButton_1->isChecked()) {
    type = 0;
  } else if (ui->radioButton_2->isChecked()) {
    type = 1;
  }

  credit(credit_sum, month, percent, type, month_pay, overpayment,
         full_payment);

  ui->res_label_month_pay->setText(month_pay);
  ui->res_label_overpayment->setText(overpayment);
  ui->res_label_full_pay->setText(full_payment);
}
