#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRandomGenerator>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_GenerateDataset_clicked()
{
    QString numNumbersStr = ui->lineEdit->text();
    bool ok;
    int numNumbers = numNumbersStr.toInt(&ok);

    if (!ok || numNumbers <= 0) {
        qDebug() << "Invalid number of random numbers!";
        return;
    }
    QVector<int> randomNumbers;
    QString outputString;

    for (int i = 0; i < numNumbers; ++i) {
        int rand_num = QRandomGenerator::global()->bounded(0, 101);
        randomNumbers.append(rand_num);
        outputString += QString::number(rand_num) + "\n";
    }

    qDebug() << "Random numbers:";
    qDebug() << outputString;
    ui->plainTextEdit->setPlainText(outputString);
    for (int num : randomNumbers) {
        qDebug() << "Random number from array: " << num;
    }
}

// Declaration of merge and mergeSort functions
void merge(QVector<int>& numbers, int left, int mid, int right);
void mergeSort(QVector<int>& numbers, int left, int right);

void MainWindow::on_mergeSort_clicked()
{
    // Get the numbers from the plain text edit
    QString numbersText = ui->plainTextEdit->toPlainText();
    QStringList numberStrings = numbersText.split("\n", Qt::SkipEmptyParts);
    QVector<int> numbers;

    for (const QString& numberString : numberStrings) {
        bool ok;
        int number = numberString.toInt(&ok);
        if (ok) {
            numbers.append(number);
        }
    }

    // Sort the numbers using merge sort
    mergeSort(numbers, 0, numbers.size() - 1);

    // Create the output string with the sorted numbers
    QString outputString = "Sorted numbers:\n";
    for (int number : numbers) {
        outputString += QString::number(number) + "\n";
    }

    // Output the sorted numbers in the plain text edit
    ui->plainTextEdit->setPlainText(outputString);
}

void merge(QVector<int>& numbers, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    QVector<int> leftArray(n1);
    QVector<int> rightArray(n2);

    for (int i = 0; i < n1; ++i) {
        leftArray[i] = numbers[left + i];
    }

    for (int j = 0; j < n2; ++j) {
        rightArray[j] = numbers[mid + 1 + j];
    }

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (leftArray[i] <= rightArray[j]) {
            numbers[k] = leftArray[i];
            ++i;
        } else {
            numbers[k] = rightArray[j];
            ++j;
        }
        ++k;
    }

    while (i < n1) {
        numbers[k] = leftArray[i];
        ++i;
        ++k;
    }

    while (j < n2) {
        numbers[k] = rightArray[j];
        ++j;
        ++k;
    }
}

void mergeSort(QVector<int>& numbers, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(numbers, left, mid);
        mergeSort(numbers, mid + 1, right);

        merge(numbers, left, mid, right);
    }
}



#include <chrono>

void MainWindow::on_FindIt_clicked()
{
    // Get the number to search from the line edit
    QString numberToSearchStr = ui->lineEdit_2->text();
    bool ok;
    int numberToSearch = numberToSearchStr.toInt(&ok);

    if (!ok) {
        qDebug() << "Invalid number to search!";
        return;
    }

    // Get the numbers from the plain text edit
    QString numbersText = ui->plainTextEdit->toPlainText();
    QStringList numberStrings = numbersText.split("\n", Qt::SkipEmptyParts);
    QVector<int> numbers;

    for (const QString& numberString : numberStrings) {
        bool ok;
        int number = numberString.toInt(&ok);
        if (ok) {
            numbers.append(number);
        }
    }

    // Calculate the time from button click till finding the number
    auto startTime = std::chrono::high_resolution_clock::now();

    // Search for the number in the numbers vector
    bool found = false;
    int index = -1;

    for (int i = 0; i < numbers.size(); ++i) {
        if (numbers[i] == numberToSearch) {
            found = true;
            index = i;
            break;
        }
    }

    // Calculate the elapsed time in nanoseconds
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();

    // Output the search result and elapsed time
    QString outputString;
    if (found) {
        outputString = "Number " + QString::number(numberToSearch) + " found at index " + QString::number(index) + "\n";
    } else {
        outputString = "Number " + QString::number(numberToSearch) + " not found\n";
    }

    outputString += "Elapsed time: " + QString::number(duration) + " nanoseconds";

    // Append the output to the plain text edit
    ui->plainTextEdit->appendPlainText(outputString);
}
