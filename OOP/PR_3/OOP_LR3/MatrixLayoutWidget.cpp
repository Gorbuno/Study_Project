#include "matrixlayoutwidget.h"

MatrixLayoutWidget::MatrixLayoutWidget(QWidget *parent)
    : QWidget(parent)
{
    cout << "succesful MatrixLayoutWidget \n";
    int controlW = 180;
    int controlH = 25;

    _1x1Btn = new QPushButton;
    _2x2Btn = new QPushButton;
    _3x3Btn = new QPushButton;
    _sizeEdit = new QLineEdit;
    _editBtn = new QPushButton;
    _outputMatrixBtn = new QPushButton;
    _transporiseBtn = new QPushButton;
    _rangBtn = new QPushButton;
    _determinantBtn = new QPushButton;
    _inputMatrixBtn = new QPushButton;


    _1x1Btn->setObjectName("btn");
    _2x2Btn->setObjectName("btn");
    _3x3Btn->setObjectName("btn");
    _editBtn->setObjectName("btn");
    _outputMatrixBtn->setObjectName("btn");
    _transporiseBtn->setObjectName("btn");
    _rangBtn->setObjectName("btn");
    _determinantBtn->setObjectName("btn");
    _inputMatrixBtn->setObjectName("btn");

    _1x1Btn->setFixedSize(controlW / 3, controlH);
    _1x1Btn->setText("1X1");
    _2x2Btn->setFixedSize(controlW/3, controlH);
    _2x2Btn->setText("2X2");
    _3x3Btn->setFixedSize(controlW / 3, controlH);
    _3x3Btn->setText("3X3");
    _sizeEdit->setFixedSize(controlW / 2, controlH);
    _editBtn->setFixedSize(controlW / 3, controlH);
    _editBtn->setText("Create");
    _outputMatrixBtn->setFixedSize(controlW / 2, controlH);
    _outputMatrixBtn->setText("Show Matrix");
    _transporiseBtn->setFixedSize(controlW / 2, controlH);
    _transporiseBtn->setText("Transpotrise");
    _rangBtn->setFixedSize(controlW / 3, controlH);
    _rangBtn->setText("Rang");
    _determinantBtn->setFixedSize(controlW / 2, controlH);
    _determinantBtn->setText("Determinant");
    _inputMatrixBtn->setFixedSize(controlW, controlH);
    _inputMatrixBtn->setText("Remember Matrix");

    QHBoxLayout *editLayout = new QHBoxLayout;
    editLayout->setMargin(0);
    editLayout->setSpacing(0);
    editLayout->addWidget(new QLabel("Size:"));
    editLayout->addWidget(_sizeEdit);
    editLayout->addWidget(_editBtn);

    QHBoxLayout *editLayout1 = new QHBoxLayout;
    editLayout1->setMargin(0);
    editLayout1->setSpacing(0);
    editLayout1->addWidget(new QLabel("MENU:"));
    editLayout1->addWidget(_inputMatrixBtn);
    editLayout1->addWidget(_outputMatrixBtn);
    editLayout1->addWidget(_transporiseBtn);
    editLayout1->addWidget(_determinantBtn);
    editLayout1->addWidget(_rangBtn);



    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->setMargin(0);
    hlayout->setSpacing(10);
    hlayout->addWidget(_1x1Btn);
    hlayout->addWidget(_2x2Btn);
    hlayout->addWidget(_3x3Btn);
    hlayout->addLayout(editLayout);


    _displayWall = new QFrame;
    _displayWall->setStyleSheet("background-color:rgb(178,232,243)");
    _displayWall->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    gridLayout = new QGridLayout;
    _displayWall->setLayout(gridLayout);

    QVBoxLayout *vhlayout = new QVBoxLayout;
    vhlayout->setMargin(0);
    vhlayout->setSpacing(5);
    vhlayout->addLayout(hlayout);
    vhlayout->addLayout(editLayout1);
    vhlayout->addWidget(_displayWall);

    connect(_1x1Btn, SIGNAL(clicked()), this, SLOT(onMatrixLayoutDivision()));
    connect(_2x2Btn, SIGNAL(clicked()), this, SLOT(onMatrixLayoutDivision()));
    connect(_3x3Btn, SIGNAL(clicked()), this, SLOT(onMatrixLayoutDivision()));
    connect(_editBtn, SIGNAL(clicked()), this, SLOT(onMatrixLayoutDivision()));
    connect(_inputMatrixBtn, SIGNAL(clicked()), this, SLOT(onInputMatrixBtnClicked()));
    connect(_outputMatrixBtn, SIGNAL(clicked()), this, SLOT(onOutputMatrixBtnClicked()));
    connect(_transporiseBtn, SIGNAL(clicked()), this, SLOT(onTransposeMatrix()));
    connect(_determinantBtn, SIGNAL(clicked()), this, SLOT(onDeterminantMatrix()));
    connect(_rangBtn, SIGNAL(clicked()), this, SLOT(onRangMatrix()));

    this->setLayout(vhlayout);
    this->setMinimumSize(600,500);
    onSetMatrixLayout(1, 1);
    matrix =  new SquareMatrix(0,0);
}


MatrixLayoutWidget::~MatrixLayoutWidget(){ // Деструктор класса MatrixLayoutWidget
    removeLabel();}

void MatrixLayoutWidget::onMatrixLayoutDivision(){
     cout << "succesful onMatrixLayoutDivision \n";
    if (sender() == _1x1Btn){
        _row = 1;
        _column = 1;}
    else if (sender() == _2x2Btn){
        _row = 2;
        _column = 2;}
    else if (sender() == _3x3Btn){
        _row = 3;
        _column = 3;}
    else if (sender() == _editBtn) {
        _row = _sizeEdit->text().toInt();
        _column = _sizeEdit->text().toInt();
        if (_row == 0 || _column == 0) {
            QMessageBox::critical(this, tr("warn"), "Row or Column Is Zero", QMessageBox::Ok);
            return;}}
            onSetMatrixLayout(_row, _column, false);}

void MatrixLayoutWidget::onSetMatrixLayout(int row, int column, bool bIsResize){
    cout << "succesful onSetMatrixLayout \n";
    QSize size = _displayWall->size();
    int num = row * column;
    if (num == 0) {
        num = 1;
        row = 1;
        column = 1;
    }

    _row = row;
    _column = column;

    int labelSpace = 3;
    int labelWidth = size.width() / column;
    int labelHeight = size.height() / row;

    if (!bIsResize){
        removeLabel();
        removeNumeratorDenominatorFields();
    }
    gridLayout->setSpacing(5);
    gridLayout->setMargin(5);

    for (int i = 0; i < num; i++){
        if (!bIsResize){
            QLineEdit *numeratorEdit = new QLineEdit(this);
            QLineEdit *denominatorEdit = new QLineEdit(this);

            numeratorEdit->setAlignment(Qt::AlignCenter);
            numeratorEdit->setStyleSheet("background-color:rgb(255,255,255)");
            numeratorEdit->resize(labelWidth - labelSpace - 5, labelHeight - labelSpace - 5);

            denominatorEdit->setAlignment(Qt::AlignCenter);
            denominatorEdit->setStyleSheet("background-color:rgb(255,255,255)");
            denominatorEdit->resize(labelWidth - labelSpace - 5, labelHeight - labelSpace - 5);

            int rowIndex = i / column;
            int columnIndex = i % column;

            QHBoxLayout *editLayout2 = new QHBoxLayout;
            editLayout2->addWidget(numeratorEdit);
            editLayout2->addWidget(new QLabel("/"));
            editLayout2->addWidget(denominatorEdit);
            gridLayout->addLayout(editLayout2, rowIndex, columnIndex);

            _numeratorEditMap[i] = numeratorEdit;
            _denominatorEditMap[i] = denominatorEdit;
        } else {

            for (int j = 0; j < column; j++){
                for (int k = 0; k < row; k++){
                    int index = (k + row*j);
                    QLineEdit *numeratorEdit = _numeratorEditMap[index];
                    QLineEdit *denominatorEdit = _denominatorEditMap[index];
                    numeratorEdit->resize(labelWidth - labelSpace - 5, labelHeight - labelSpace - 5);
                    denominatorEdit->resize(labelWidth - labelSpace - 5, labelHeight - labelSpace - 5);
                }
            }
        }
    }

    _displayWall->setLayout(gridLayout);
    _displayWall->update();
}


void MatrixLayoutWidget::removeLabel(){
    cout << "succesful removeLabel \n";
    auto numeratorIter = _numeratorEditMap.begin();
    while (numeratorIter != _numeratorEditMap.end()) {
        QLineEdit *numeratorEdit = numeratorIter.value();
        if (numeratorEdit) {
            delete numeratorEdit;
            numeratorEdit = nullptr;
        }
        ++numeratorIter;
    }
    _numeratorEditMap.clear();

    auto denominatorIter = _denominatorEditMap.begin();
    while (denominatorIter != _denominatorEditMap.end()) {
        QLineEdit *denominatorEdit = denominatorIter.value();
        if (denominatorEdit) {
            delete denominatorEdit;
            denominatorEdit = nullptr;
        }
        ++denominatorIter;
    }
    _denominatorEditMap.clear();
}

void MatrixLayoutWidget::resizeEvent(QResizeEvent *event) {
    cout << "succesful resizeEvent \n";
    if (_numeratorEditMap.count() > 0 || _denominatorEditMap.count() > 0) {
        onSetMatrixLayout(_row, _column, true);
    }
}


void MatrixLayoutWidget::onInputMatrixBtnClicked() {
    matrix = new SquareMatrix (_row, _column);
    int size = _row;
    for (int i = 0; i < _row; ++i) {
        for (int j = 0; j < _column; ++j) {
            int index = i * size + j;
            int numerator = _numeratorEditMap[index]->text().toInt();
            int denominator = _denominatorEditMap[index]->text().toInt();
            matrix->setMatrixValue(i, j, numerator,  denominator);
        }
    }
    QMessageBox::information(this, "Результат", "Матрица записана успешно.");
}

void MatrixLayoutWidget::onOutputMatrixBtnClicked() {
    MatrixDisplayWindow *matrixDisplayWindow = new MatrixDisplayWindow(this);
        std::stringstream matrixText;
        matrix->print_screen(matrixText);
        matrixDisplayWindow->displayMatrix(matrixText);
        matrixDisplayWindow->show();}

void MatrixLayoutWidget::onOutputMatrixTransp() {
    MatrixDisplayWindow *matrixDisplayWindow = new MatrixDisplayWindow(this);
        std::stringstream matrixText;
        _matrix.print_screen(matrixText);
        matrixDisplayWindow->displayMatrix(matrixText);
        matrixDisplayWindow->show();}

void MatrixLayoutWidget::onTransposeMatrix() {
    _matrix = matrix->transpose();
    QMessageBox::information(this, "Результат", "Матрица транспонирована успешно.");
    onOutputMatrixTransp();}

void MatrixLayoutWidget::onDeterminantMatrix() {
    number determinant = matrix->determinant();
    QString determinantStr = determinant.toString();
    QString message = QString("Определитель матрицы: %1").arg(determinantStr);
    QMessageBox::information(this, "Результат", message);}

void MatrixLayoutWidget::onRangMatrix(){
    int rang = matrix->rank();
    QString message = QString("Ранг матрицы: %1").arg(rang);
    QMessageBox::information(this, "Результат", message);}

void MatrixLayoutWidget::removeNumeratorDenominatorFields() {
    auto numeratorIter = _numeratorEditMap.begin();
    while (numeratorIter != _numeratorEditMap.end()) {
        QLineEdit *numeratorEdit = numeratorIter.value();
        if (numeratorEdit) {
            gridLayout->removeWidget(numeratorEdit);
            delete numeratorEdit;
            numeratorEdit = nullptr;
        }
        ++numeratorIter;
    }
    _numeratorEditMap.clear();

    auto denominatorIter = _denominatorEditMap.begin();
    while (denominatorIter != _denominatorEditMap.end()) {
        QLineEdit *denominatorEdit = denominatorIter.value();
        if (denominatorEdit) {
            gridLayout->removeWidget(denominatorEdit);
            delete denominatorEdit;
            denominatorEdit = nullptr;
        }
        ++denominatorIter;
    }
    _denominatorEditMap.clear();
    gridLayout->update();
}
