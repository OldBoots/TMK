#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "calculate_tmk.h"
#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QPushButton>
#include <QIntValidator>
#include <QDebug>
#include <QMessageBox>
#include <QFrame>
#include <QRandomGenerator>
#include <QClipboard>
#include <QStyle>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    void init_GUI();
    void clear_data();
    void get_data();
    void clear_form();
    void def_col_text();
    void gen_key_tm();
    bool check_data();
private:
    QVector <QLineEdit *> vec_input_fild;
    QPushButton input_butt;
    QLineEdit input_line;
    QFrame indicator_equal;
    QVector <QVector <int>> vec_num;
    QString str_valid;
    bool flg_training;
    bool flg_dark;
private slots:
    void next_fild_slot();
    void input_butt_slot();
    void combat_slot();
    void training_slot();
    void combat_gen_slot();
    void training_gen_slot();
    void past_key_slot();
    void copy_key_slot();
    void clear_key_slot();
    void dark_theme_slot();
    void light_theme_slot();
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
