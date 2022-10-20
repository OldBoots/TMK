#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init_GUI();
    str_valid = "0123456789";
    flg_dark = false;
    combat_slot();
    connect(&input_butt, SIGNAL(clicked()), SLOT(input_butt_slot()));
    connect(ui->combat, SIGNAL(triggered()), SLOT(combat_slot()));
    connect(ui->training, SIGNAL(triggered()), SLOT(training_slot()));
    connect(ui->combat_gen, SIGNAL(triggered()), SLOT(combat_gen_slot()));
    connect(ui->training_gen, SIGNAL(triggered()), SLOT(training_gen_slot()));
    connect(ui->past_key, SIGNAL(triggered()), SLOT(past_key_slot()));
    connect(ui->copy_key, SIGNAL(triggered()), SLOT(copy_key_slot()));
    connect(ui->clear_key, SIGNAL(triggered()), SLOT(clear_key_slot()));
    connect(ui->dark_theme, SIGNAL(triggered()), SLOT(dark_theme_slot()));
    connect(ui->light_theme, SIGNAL(triggered()), SLOT(light_theme_slot()));
    //    connect(ui->past_key, SIGNAL(triggered()), SLOT());
    //    connect(ui->past_key, SIGNAL(triggered()), SLOT());
    //    connect(ui->past_key, SIGNAL(triggered()), SLOT());
    //    connect(ui->past_key, SIGNAL(triggered()), SLOT());
}

void MainWindow::dark_theme_slot(){
    // Создаём палитру для тёмной темы оформления
    QPalette darkPalette;
    // Настраиваем палитру для цветовых ролей элементов интерфейса
    darkPalette.setColor(QPalette::Window, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::WindowText, Qt::white);
    darkPalette.setColor(QPalette::Base, QColor(25, 25, 25));
    darkPalette.setColor(QPalette::AlternateBase, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
    darkPalette.setColor(QPalette::ToolTipText, Qt::white);
    darkPalette.setColor(QPalette::Text, Qt::white);
    darkPalette.setColor(QPalette::Button, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::ButtonText, Qt::white);
    darkPalette.setColor(QPalette::BrightText, Qt::red);
    darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::HighlightedText, Qt::black);
    // Устанавливаем данную палитру
    qApp->setPalette(darkPalette);
    for(int i = 0; i < 48; i++){
        vec_input_fild[i]->setStyleSheet("background-color: black; color: white; font-size: 18px;");
    }
    input_butt.setStyleSheet("background-color: black; color: white; font-size: 20px;");
    input_line.setStyleSheet("background-color: black; color: white; font-size: 18px;");
    flg_dark = true;
}

void MainWindow::light_theme_slot(){
    // Для возврата к светлой палитре достаточно
    // будет установить стандартную палитру из темы оформления
    qApp->setPalette(style()->standardPalette());
    for(int i = 0; i < 48; i++){
        vec_input_fild[i]->setStyleSheet("background-color: white; color: black; font-size: 18px;");
    }
    input_butt.setStyleSheet("background-color: white; color: black; font-size: 20px;");
    input_line.setStyleSheet("background-color: white; color: black; font-size: 18px;");
    flg_dark = false;
}

void MainWindow::clear_key_slot(){
    clear_form();
}

void MainWindow::past_key_slot(){
    const QClipboard *clipboard = QApplication::clipboard();
    QString str_key = clipboard->text();
    for(int i = 0, cnt = 0; i < str_key.size(); i++){
        if(cnt < 48 && str_valid.contains(str_key[i])){
            vec_input_fild[cnt]->setText(QString(str_key[i]));
            cnt++;
        }
    }
}

void MainWindow::copy_key_slot(){
    QClipboard *clipboard = QApplication::clipboard();
    QString str_key;
    for(int i = 0; i < 48; i++){
        str_key += vec_input_fild[i]->text();
    }
    clipboard->setText(str_key);
}

void MainWindow::gen_key_tm(){
    for(int i = 0; i < 48; i++){
        if(i % 6 == 0){
            vec_input_fild[i]->setText(QString::number(QRandomGenerator::global()->bounded(0,2)));
        } else {
            vec_input_fild[i]->setText(QString::number(QRandomGenerator::global()->bounded(0,8)));
        }
    }
}

void MainWindow::combat_slot(){
    clear_form();
    for(int i = 0; i < 48; i++){
        vec_input_fild[i]->setReadOnly(false);
    }
    input_line.setReadOnly(true);
    input_butt.setEnabled(true);
    ui->past_key->setEnabled(true);
    flg_training = false;
}

void MainWindow::training_slot(){
    clear_form();
    for(int i = 0; i < 48; i++){
        vec_input_fild[i]->setReadOnly(false);
    }
    input_line.setReadOnly(false);
    input_butt.setEnabled(true);
    ui->past_key->setEnabled(true);
    flg_training = true;
}

void MainWindow::combat_gen_slot(){
    clear_form();
    for(int i = 0; i < 48; i++){
        vec_input_fild[i]->setReadOnly(true);
    }
    input_line.setReadOnly(true);
    input_butt.setEnabled(false);
    ui->past_key->setEnabled(false);
    flg_training = false;
    gen_key_tm();
    input_butt_slot();
}

void MainWindow::training_gen_slot(){
    clear_form();
    for(int i = 0; i < 48; i++){
        vec_input_fild[i]->setReadOnly(false);
    }
    input_line.setReadOnly(false);
    input_butt.setEnabled(true);
    ui->past_key->setEnabled(false);
    flg_training = true;
    gen_key_tm();
}

void MainWindow::def_col_text(){
    for(int i = 0; i < 48; i++){
        if(vec_input_fild[i]->text().isEmpty()){
            vec_input_fild[i]->setStyleSheet("color: black; font-size: 18px;");
        }
    }
}

void MainWindow::clear_form(){
    for(int i = 0; i < 48; i++){
        vec_input_fild[i]->clear();
    }
    input_line.clear();
    indicator_equal.setStyleSheet("background-color: rgb(200, 200, 200)");
}

void MainWindow::next_fild_slot(){
    for (int i = 0; i < 48; i++) {
        if(vec_input_fild[i]->text().isEmpty()){
            vec_input_fild[i]->setFocus();
            if(flg_dark){
                vec_input_fild[i]->setStyleSheet("color: white; font-size: 18px;");
            } else {
                vec_input_fild[i]->setStyleSheet("color: black; font-size: 18px;");
            }
            break;
        }
    }
}

void MainWindow::init_GUI(){
    // Добавляем поле ввода ключа 8х6 клеток
    ui->gridLayout->addWidget(ui->label_head, 0, 1, 1, 7, Qt::AlignLeft);
    for(int i = 1; i < 9; i++){
        for(int j = 1; j < 7; j++){
            vec_input_fild << new QLineEdit();
            vec_input_fild[vec_input_fild.size() - 1]->setFixedSize(30, 20);
            vec_input_fild[vec_input_fild.size() - 1]->setStyleSheet("font-size: 18px;");
            vec_input_fild[vec_input_fild.size() - 1]->setMaxLength(1);
            vec_input_fild[vec_input_fild.size() - 1]->setValidator(new QIntValidator);
            connect(vec_input_fild[vec_input_fild.size() - 1], SIGNAL(textChanged(QString)), SLOT(next_fild_slot()));
            ui->gridLayout->addWidget(vec_input_fild[vec_input_fild.size() - 1], i, j, Qt::AlignCenter);
        }
    }
    // Добавляем поле ввода контрольой суммы
    input_line.setPlaceholderText("Контрольная сумма");
    input_line.setMinimumSize(160, 25);
    input_line.setStyleSheet("font-size: 18px;");
    input_line.setMaxLength(3);
    input_line.setValidator(new QIntValidator);
    ui->gridLayout->addWidget(&input_line, 9, 1, 1, 4, Qt::AlignLeft);
    // Добавляем кнопку "Ввод"
    input_butt.setMinimumSize(75, 25);
    input_butt.setText("Ввод");
    input_butt.setStyleSheet("font-size: 20px;");
    ui->gridLayout->addWidget(&input_butt, 9, 5, 1, 2, Qt::AlignLeft);
    // Добавляем индикатор сравнения КС
    indicator_equal.setMinimumSize(25, 25);
    indicator_equal.setFrameStyle(QFrame::Panel | QFrame::Raised);
    indicator_equal.setLineWidth(2);
    indicator_equal.setStyleSheet("background-color: rgb(200, 200, 200)");
    ui->gridLayout->addWidget(&indicator_equal, 9, 0, 1, 1, Qt::AlignCenter);
}

void MainWindow::input_butt_slot(){
    clear_data();
    get_data();
    if(!check_data()){
        return;
    }
    Calculate_TMK ctmk;
    ctmk.set_key(vec_num);
    if(flg_training){
        if(input_line.text() == ctmk.get_CS()){
            indicator_equal.setStyleSheet("background-color: rgb(0, 200, 0)");
        }else{
            indicator_equal.setStyleSheet("background-color: rgb(200, 0, 0)");
        }
    }else{
        input_line.setText(ctmk.get_CS());
    }
}

void MainWindow::clear_data(){
    if(!vec_num.isEmpty()){
        vec_num.clear();
    }
}

void MainWindow::get_data(){
    QVector <int> row_num;
    for(int i = 0; i < 48; i++){
        row_num << vec_input_fild[i]->text().toInt();
        if(row_num.size() == 6){
            vec_num << row_num;
            row_num.clear();
        }
    }
}

bool MainWindow::check_data(){
    QMessageBox msgBox;
    int index_fild = 0;
    QString err_str = "Ошибка ввода!\n";
    int err_cnt = 0;
    bool err_flg[] = {false, false, false, false, false};
    QFont fnt;
    fnt.setPixelSize(16);
    msgBox.setFont(fnt);
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 6; j++){
            if(j == 0){
                if(vec_num[i][j] > 1){
                    err_flg[0] = true;
                    vec_input_fild[index_fild]->setStyleSheet("color: red; font-size: 18px;");
                }
            }
            if(vec_num[i][j] > 7){
                err_flg[1] = true;
                vec_input_fild[index_fild]->setStyleSheet("color: red; font-size: 18px;");
            }
            if(vec_input_fild[index_fild]->text().isEmpty()){
                err_flg[2] = true;
            }
            if(!str_valid.contains(vec_input_fild[index_fild]->text())){
                err_flg[3] = true;
                vec_input_fild[index_fild]->setStyleSheet("color: red; font-size: 18px;");
            }
            index_fild++;
        }
    }
    if(flg_training){
        if(input_line.text().size() < 3){
            err_flg[4] = true;
        }
        for(int i = 0; i < 3; i++){
            if(!str_valid.contains(input_line.text()[i])){
                err_flg[4] = true;
            }
        }
    }

    if(err_flg[0] || err_flg[1] || err_flg[2] || err_flg[3] || err_flg[4]){
        if(err_flg[0]){
            err_str += QString::number(++err_cnt) + ") В первом столбце могут "
                                                    "быть только цифры 0 и 1.\n";
        }
        if(err_flg[1]){
            err_str += QString::number(++err_cnt) + ") В столбцах со 2 по 6 могут "
                                                    "быть только цифры от 0 до 7.\n";
        }
        if(err_flg[2]){
            err_str += QString::number(++err_cnt) + ") Не все поля заполненый.\n";
        }
        if(err_flg[3]){
            err_str += QString::number(++err_cnt) + ") Недопустимые символы.\n";
        }
        if(err_flg[4]){
            err_str += QString::number(++err_cnt) + ") Недопустимая контрольная сумма.\n";
        }
        msgBox.setText(err_str);
        msgBox.exec();
        return false;
    }
    return true;
}

MainWindow::~MainWindow()
{
}
